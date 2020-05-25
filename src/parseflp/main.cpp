#include <flp/flp.h>

#include <cctype>

static void ReportInfo(FlpFile& flp)
{
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
	printf("Usage: parseflp <path>\n");
	printf("Usage: parseflp --encode-licensee <name>\n");
}

int main(int argc, char* argv[])
{
	if (argc == 1) {
		PrintUsage();
		return 1;
	}

	if (!strcmp(argv[1], "--encode-licensee")) {
		if (argc < 3) {
			PrintUsage();
			return 1;
		}

		s2::string name = EncodeLicensee(argv[2]);
		printf("%s\n", name.c_str());
		return 0;
	}

	FlpFile flp(argv[1]);
	ReportInfo(flp);
	return 0;
}
