#include <flp/flp.h>
#include <flp/Folder.h>

#include <cctype>

static void ReportInfo(const FlpFile& flp, bool compact)
{
	if (compact) {
		s2::string strLine = flp.Filename();

		strLine += s2::strprintf(" / %g BPM", flp.GetBPM());

		auto& meta = flp.GetMetadata();
		if (meta.m_genre != "") {
			strLine += s2::strprintf(" / %s", meta.m_genre.c_str());
		}
		if (meta.m_title != "") {
			strLine += s2::strprintf(" / %s", meta.m_title.c_str());
		}
		if (meta.m_author != "") {
			strLine += s2::strprintf(" / %s", meta.m_author.c_str());
		}

		printf("%s\n", strLine.c_str());
		return;
	}

	printf("%s:\n", flp.Filename().c_str());

	if (!flp.IsValid()) {
		printf("  Invalid!\n");
		return;
	}

	printf("  saved with version: %s\n", flp.GetVersion().c_str());
	printf("  saved with license: %s\n", flp.GetLicensee().c_str());

	auto& header = flp.GetHeader();
	printf("  format: %d\n", header.m_format);
	printf("  num channels: %hu\n", header.m_numChannels);
	printf("  ppq: %hu\n", header.m_ppq);

	auto& md = flp.GetMetadata();
	printf("  title: %s\n", md.m_title.c_str());
	printf("  author: %s\n", md.m_author.c_str());
	printf("  genre: %s\n", md.m_genre.c_str());

	printf("  bpm: %g\n", flp.GetBPM());

	for (FlpFile::Channel* chan : flp.GetChannels()) {
		printf("  channel %hu:\n", chan->m_id);
		printf("    name: %s\n", chan->m_name.c_str());
		printf("    type: %d\n", (int)chan->m_type);
		printf("    plugin name: %s\n", chan->m_pluginName.c_str());
	}

	for (FlpFile::Track* track : flp.GetTracks()) {
		printf("  track %u:\n", track->m_info.m_id);
		printf("    name: %s\n", track->m_name.c_str());
	}
}

static s2::string EncodeLicensee(s2::string name)
{
	for (size_t j = 0; j < name.len(); j++) {
		uint8_t& c = (uint8_t&)name[(int)j];
		if (isupper(c) || isdigit(c)) {
			c += (uint8_t)(26 - j);
		} else if (islower(c)) {
			c -= (uint8_t)(49 + j);
			if (c < 0x30) {
				c += 0x7B - 0x30;
			}
		}
	}
	return name;
}

static void PrintUsage()
{
	printf("Usage: parseflp [options] <path>\n");
	printf("Usage: parseflp --encode-licensee <name>\n");
	printf("\nOptions:\n");
	printf("  --folder, --recursive, --compact, --sort <path|title|bpm>\n");
}

enum class ESorting
{
	None,
	Path,
	Title,
	BPM,
};

static ESorting ParseSorting(const char* szName)
{
	if (!strcmp(szName, "path")) {
		return ESorting::Path;
	} else if (!strcmp(szName, "title")) {
		return ESorting::Title;
	} else if (!strcmp(szName, "bpm")) {
		return ESorting::BPM;
	}
	return ESorting::None;
}

int main(int argc, char* argv[])
{
	if (argc == 1) {
		PrintUsage();
		return 1;
	}

	bool debug = false;
	bool reportCompact = false;
	bool readFolder = false;
	bool readFolderRecursive = false;
	static ESorting readFolderSorting = ESorting::None;
	s2::string strInput;

	for (int i = 1; i < argc; i++) {
		s2::string strArg = argv[i];

		if (strArg.len() > 0 && strArg[0] == '-') {
			if (strArg == "--encode-licensee" && i + 1 < argc) {
				s2::string name = EncodeLicensee(argv[++i]);
				printf("%s\n", name.c_str());
				return 0;
			}

			if (strArg == "--debug") {
				debug = true;

			} else if (strArg == "--compact") {
				reportCompact = true;

			} else if (strArg == "--folder") {
				readFolder = true;

			} else if (strArg == "--recursive") {
				readFolderRecursive = true;

			} else if (strArg == "--sort") {
				readFolderSorting = ParseSorting(argv[++i]);
			}
		} else {
			strInput = strArg;
		}
	}

	if (readFolder) {
		s2::list<FlpFile*> sortedResults;

		FolderIndex folder(strInput, readFolderRecursive);
		for (int i = 0; i < folder.GetFileCount(); i++) {
			s2::string strPath = folder.GetFilePath(i);
			if (strPath.endswith(".flp")) {
				if (readFolderSorting == ESorting::None) {
					ReportInfo(FlpFile(strPath, debug), reportCompact);
					continue;
				}

				sortedResults.add(new FlpFile(strPath, debug));
			}
		}

		sortedResults.sort([](const void* pa, const void* pb) -> int {
			auto& a = **(const FlpFile**)pa;
			auto& b = **(const FlpFile**)pb;

			switch (readFolderSorting) {
			case ESorting::Path: return strcmp(a.Filename(), b.Filename());
			case ESorting::Title: return strcmp(a.GetMetadata().m_title, b.GetMetadata().m_title);
			case ESorting::BPM:
				if (a.GetBPM() > b.GetBPM()) {
					return 1;
				} else if (a.GetBPM() < b.GetBPM()) {
					return -1;
				}
				return 0;
			default:
				assert(false);
				return 0;
			}
		});

		for (auto flp : sortedResults) {
			ReportInfo(*flp, reportCompact);
			delete flp;
		}
	} else {
		ReportInfo(FlpFile(strInput, debug), reportCompact);
	}

	return 0;
}
