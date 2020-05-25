#pragma once

#include <flp/Common.h>
#include <flp/FlpEvents.h>

class FlpFile
{
public:
	struct Header
	{
		uint16_t m_format = 0; // "0 for full songs"
		uint16_t m_numChannels = 0; // "not really used" (back in 1999, it seems to contain the actual number of channels though)
		uint16_t m_ppq = 0; // 96 by default
	};

	struct Metadata
	{
		s2::string m_title;
		s2::string m_author;
		s2::string m_genre;
		s2::string m_comments;
		s2::string m_webUrl;
		bool m_showInfoOnStart = true;
	};

	struct UserState
	{
		bool m_playbackSong = false;
		bool m_shuffle = false;
		uint16_t m_pattern = 0;
	};

public:
	explicit FlpFile(const s2::string& filename);
	~FlpFile();

	inline bool IsValid() const { return m_isValid; }
	inline const s2::string& Filename() const { return m_filename; }

	inline const s2::string& GetVersion() const { return m_flVersion; }
	inline int GetVersionMajor() { return m_flVersionMajor; }
	inline int GetVersionMinor() { return m_flVersionMinor; }
	inline const s2::string& GetLicensee() const { return m_flLicensee; }

	inline const Header& GetHeader() const { return m_header; }
	inline const Metadata& GetMetadata() const { return m_metadata; }
	inline const UserState& GetUserState() const { return m_userState; }

	inline double GetBPM() const { return m_bpm; }
	inline int16_t GetMainPitch() const { return m_mainPitch; }

private:
	void ReadByte(FLP_Event ev, s2::file& file);
	void ReadWord(FLP_Event ev, s2::file& file);
	void ReadDword(FLP_Event ev, s2::file& file);
	void ReadText(FLP_Event ev, s2::file& file);

	s2::string DataAsString(void* p) const;

private:
	bool m_isValid = false;
	s2::string m_filename;

	Header m_header;
	Metadata m_metadata;
	UserState m_userState;

	s2::string m_flVersion;
	int m_flVersionMajor = 0;
	int m_flVersionMinor = 0;
	s2::string m_flLicensee;

	double m_bpm = 140.0;

	int16_t m_mainPitch = 0;
	uint8_t m_patternLength = 0;
	uint8_t m_blockLength = 0;
};
