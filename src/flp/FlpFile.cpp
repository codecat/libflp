#include <flp/Common.h>
#include <flp/FlpFile.h>

#if defined(_MSC_VER)
#include <Windows.h>
#endif

static s2::string StringFromWide(const wchar_t* wsz)
{
	size_t length = wcslen(wsz);

#if defined(_MSC_VER)
	int needed_bytes = WideCharToMultiByte(CP_UTF8, 0, wsz, (int)length, nullptr, 0, nullptr, nullptr);
	char* buffer = (char*)alloca(needed_bytes + 1);
	WideCharToMultiByte(CP_UTF8, 0, wsz, (int)length, buffer, needed_bytes, nullptr, nullptr);
	buffer[needed_bytes] = '\0';
	return s2::string(buffer);
#else
#error This needs Linux support!
#endif
}

static s2::string StringFromWide(const void* wsz)
{
	return StringFromWide((const wchar_t*)wsz);
}

FlpFile::FlpFile(const s2::string& filename)
{
	m_filename = filename;

	s2::file file(filename);
	file.open(s2::filemode::read);

	char identifier[5] = {0};
	file.read(identifier, 4);

	// First chunk is always FLhd
	if (!!strcmp(identifier, "FLhd")) {
		return;
	}

	// Read header size (which we expect to be 6)
	uint32_t headerSize = file.read<uint32_t>();
	if (headerSize != 6) {
		return;
	}

	// Read header
	file.read(m_header.m_format);
	file.read(m_header.m_numChannels);
	file.read(m_header.m_ppq);

	// We now expect "FLdt"
	file.read(identifier, 4);
	if (!!strcmp(identifier, "FLdt")) {
		return;
	}

	m_isValid = true;

	// Data length
	file.read<uint32_t>();

	// Begin reading events
	while (!file.eof()) {
		FLP_Event ev = file.read<FLP_Event>();

		if (ev >= FLP_Text) {
			ReadText(ev, file);
		} else if (ev >= FLP_Int) {
			ReadDword(ev, file);
		} else if (ev >= FLP_Word) {
			ReadWord(ev, file);
		} else {
			ReadByte(ev, file);
		}
	}
}

FlpFile::~FlpFile()
{
}

void FlpFile::ReadByte(FLP_Event ev, s2::file& file)
{
	size_t startPos = file.pos();

	uint8_t value = file.read<uint8_t>();

	if (ev == FLP_LoopActive) {
		m_userState.m_playbackSong = (value == 1);
	} else if (ev == FLP_Shuffle) {
		m_userState.m_shuffle = (value == 1);

	} else if (ev == FLP_ShowInfo) {
		m_metadata.m_showInfoOnStart = (value == 1);

	} else if (ev == FLP_PatLength) {
		m_patternLength = value;
	} else if (ev == FLP_BlockLength) {
		m_blockLength = value;

	} else {
		printf("0x%08" PRIXPTR ": Unhandled byte event %s (%d, %02X)\n", startPos, FLP_GetEventName(ev), (int)ev, value);
	}
}

void FlpFile::ReadWord(FLP_Event ev, s2::file& file)
{
	size_t startPos = file.pos();

	uint16_t value = file.read<uint16_t>();

	if (ev == FLP_MainPitch) {
		m_mainPitch = (int16_t)value;

	} else if (ev == FLP_CurrentPatNum) {
		m_userState.m_pattern = value;

	} else {
		printf("0x%08" PRIXPTR ": Unhandled word event %s (%d, %04X)\n", startPos, FLP_GetEventName(ev), (int)ev, value);
	}
}

void FlpFile::ReadDword(FLP_Event ev, s2::file& file)
{
	size_t startPos = file.pos();

	uint32_t value = file.read<uint32_t>();

	if (ev == FLP_BPM) {
		m_bpm = value / 1000.0;

	} else {
		printf("0x%08" PRIXPTR ": Unhandled dword event %s (%d, %08X)\n", startPos, FLP_GetEventName(ev), (int)ev, value);
	}
}

void FlpFile::ReadText(FLP_Event ev, s2::file& file)
{
	size_t startPos = file.pos();

	/* Start with a DWORD Size = 0. You're going to reconstruct the size by getting packs of 7 bits:
	 *   1. Get a byte.
	 *   2. Add the first 7 bits of this byte to Size.
	 *   3. Check bit 7 (the last bit) of this byte. If it's on, go back to step 1 to process the next byte.
	 */
	uint32_t len = 0;
	uint32_t lenShift = 0;
	while (true) {
		uint8_t b = file.read<uint8_t>();

		len |= (b & 0x7F) << lenShift;
		lenShift += 7;

		if ((b & 0x80) == 0) {
			break;
		}

		assert(lenShift <= 32);
	}

	if (len == 0) {
		return;
	}

	void* buffer = malloc(len);
	file.read(buffer, len);

	if (ev == FLP_Version) {
		m_flVersion = (const char*)buffer;
		auto versionParse = m_flVersion.split(".");
		if (versionParse.len() > 0) {
			m_flVersionMajor = atoi(versionParse[0]);
		}
		if (versionParse.len() > 1) {
			m_flVersionMinor = atoi(versionParse[1]);
		}

	} else if (ev == FLP_Text_Licensee) {
		m_flLicensee = DataAsString(buffer);
		for (size_t i = 0; i < m_flLicensee.len(); i++) {
			char& c = m_flLicensee[(int)i];
			uint8_t c1 = (uint8_t)(c - (26 - i));
			uint8_t c2 = (uint8_t)(c + (49 + i));
			if (isalnum(c1)) {
				c = c1;
			} else if (isalnum(c2)) {
				c = c2;
			} else {
				assert(false);
			}
		}

	} else if (ev == FLP_Text_Title) {
		m_metadata.m_title = DataAsString(buffer);
	} else if (ev == FLP_Text_Comment) {
		m_metadata.m_comments = DataAsString(buffer);
	} else if (ev == FLP_Text_URL) {
		m_metadata.m_webUrl = DataAsString(buffer);
	} else if (ev == FLP_Text_Genre) {
		m_metadata.m_genre = DataAsString(buffer);
	} else if (ev == FLP_Text_Author) {
		m_metadata.m_author = DataAsString(buffer);

	} else {
		printf("0x%08" PRIXPTR ": Unhandled text event %s (%d, size 0x%x)", startPos, FLP_GetEventName(ev), (int)ev, len);

		wchar_t* str = (wchar_t*)buffer;

		bool printable = true;
		for (uint32_t i = 0; i < len / sizeof(wchar_t) - 1; i++) {
			wchar_t c = str[i];
			if (c < 0x20 || c > 0x7E) {
				printable = false;
				break;
			}
		}

		if (printable) {
			printf(" \"%S\"\n", str);
		} else {
			printf("\n");
		}
	}

	free(buffer);
}

s2::string FlpFile::DataAsString(void* p) const
{
	if (m_flVersionMajor >= 12) {
		return StringFromWide(p);
	}
	return (const char*)p;
}
