#pragma once

#include <flp/Common.h>
#include <flp/FlpEvents.h>
#include <flp/FlpStructs.h>

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

	struct Channel
	{
		enum class Type : uint8_t
		{
			// Basic sampler dragged into the rack
			Sampler,
			// Deprecated TS404 synthesizer
			Ts404,
			// FL plugin (or Fruity Wrapper for VST's)
			Plugin,
			// Layer that controls other channels
			Layer,
			// Audio clip dragged into the playlist
			AudioClip,
			// Automation clip controlling a parameter
			Automation,
		};

		uint16_t m_id = 0;
		Type m_type = Type::Sampler;

		s2::string m_name;
		s2::string m_pluginName;

		uint32_t m_color = 0;
	};

	struct Track
	{
		FlpStructs::TrackInfo m_info;
		s2::string m_name;
	};

private:
	enum class Mode
	{
		Channel,
		Track,
	};

public:
	explicit FlpFile(const s2::string& filename);
	~FlpFile();

	inline bool IsValid() const { return m_isValid; }
	inline const s2::string& Filename() const { return m_filename; }

	inline const s2::string& GetVersion() const { return m_flVersion; }
	inline int GetVersionMajor() const { return m_flVersionMajor; }
	inline int GetVersionMinor() const { return m_flVersionMinor; }
	inline const s2::string& GetLicensee() const { return m_flLicensee; }

	inline const Header& GetHeader() const { return m_header; }
	inline const Metadata& GetMetadata() const { return m_metadata; }
	inline const UserState& GetUserState() const { return m_userState; }

	inline const s2::list<s2::string>& GetChannelCategories() const { return m_channelCategories; }
	inline const s2::list<Channel*>& GetChannels() const { return m_channels; }
	inline const s2::list<Track*>& GetTracks() const { return m_tracks; }

	inline double GetBPM() const { return m_bpm; }
	inline int16_t GetMainPitch() const { return m_mainPitch; }

private:
	void ReadByte(FLP_Event ev, s2::file& file);
	void ReadWord(FLP_Event ev, s2::file& file);
	void ReadDword(FLP_Event ev, s2::file& file);
	void ReadText(FLP_Event ev, s2::file& file);

	s2::string DataAsString(void* p) const;
	bool EnsureMode(Mode mode) const;

private:
	bool m_isValid = false;
	s2::string m_filename;

	Header m_header;
	Metadata m_metadata;
	UserState m_userState;

	s2::list<s2::string> m_channelCategories;
	s2::list<Channel*> m_channels;
	s2::list<Track*> m_tracks;

	s2::string m_flVersion;
	int m_flVersionMajor = 0;
	int m_flVersionMinor = 0;
	s2::string m_flLicensee;

	double m_bpm = 140.0;

	int16_t m_mainPitch = 0;
	uint8_t m_patternLength = 0;
	uint8_t m_blockLength = 0;

private:
	Channel* m_currentChannel = nullptr;
	Track* m_currentTrack = nullptr;
};
