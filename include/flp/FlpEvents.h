#pragma once

// Source: https://raw.githubusercontent.com/andrewrk/PyDaw/master/FLP_Format
// Added a bunch of undocumented fields as well

#include <flp/Common.h>

enum FLP_Event : uint8_t
{
	// BYTE EVENTS
	FLP_Byte = 0,
	FLP_Enabled = 0,
	FLP_NoteOn = 1,  	//+pos (byte)
	FLP_Vol = 2,
	FLP_Pan = 3,
	FLP_MIDIChan = 4,
	FLP_MIDINote = 5,
	FLP_MIDIPatch = 6,
	FLP_MIDIBank = 7,
	FLP_LoopActive = 9,
	FLP_ShowInfo = 10,
	FLP_Shuffle = 11,
	FLP_MainVol = 12,
	FLP_Stretch = 13, 	// old byte version
	FLP_Pitchable = 14,
	FLP_Zipped = 15,
	FLP_Delay_Flags = 16,
	FLP_PatLength = 17,
	FLP_BlockLength = 18,
	FLP_UseLoopPoints = 19,
	FLP_LoopType = 20,
	FLP_ChanType = 21,
	FLP_MixSliceNum = 22,

	FLP_Unknown_28 = 28, // 1 or 3
	FLP_Unknown_37 = 37, // bool (resets to true on saving)

	// WORD EVENTS
	FLP_Word = 64,
	FLP_NewChan = FLP_Word,
	FLP_NewPat = FLP_Word + 1,  	//+PatNum (word)
	FLP_Tempo = FLP_Word + 2,
	FLP_CurrentPatNum = FLP_Word + 3,
	FLP_PatData = FLP_Word + 4,
	FLP_FX = FLP_Word + 5,
	FLP_Fade_Stereo = FLP_Word + 6,
	FLP_CutOff = FLP_Word + 7,
	FLP_DotVol = FLP_Word + 8,
	FLP_DotPan = FLP_Word + 9,
	FLP_PreAmp = FLP_Word + 10,
	FLP_Decay = FLP_Word + 11,
	FLP_Attack = FLP_Word + 12,
	FLP_DotNote = FLP_Word + 13,
	FLP_DotPitch = FLP_Word + 14,
	FLP_DotMix = FLP_Word + 15,
	FLP_MainPitch = FLP_Word + 16,
	FLP_RandChan = FLP_Word + 17,
	FLP_MixChan = FLP_Word + 18,
	FLP_Resonance = FLP_Word + 19,
	FLP_LoopBar = FLP_Word + 20,
	FLP_StDel = FLP_Word + 21,
	FLP_FX3 = FLP_Word + 22,
	FLP_DotReso = FLP_Word + 23,
	FLP_DotCutOff = FLP_Word + 24,
	FLP_ShiftDelay = FLP_Word + 25,
	FLP_LoopEndBar = FLP_Word + 26,
	FLP_Dot = FLP_Word + 27,
	FLP_DotShift = FLP_Word + 28,

	// DWORD EVENTS
	FLP_Int = 128,
	FLP_Color = FLP_Int,
	FLP_PlayListItem = FLP_Int + 1,      	//+Pos (word) +PatNum (word)
	FLP_Echo = FLP_Int + 2,
	FLP_FXSine = FLP_Int + 3,
	FLP_CutCutBy = FLP_Int + 4,
	FLP_WindowH = FLP_Int + 5,
	FLP_MiddleNote = FLP_Int + 7,
	FLP_Reserved = FLP_Int + 8,        	// may contain an invalid version info
	FLP_MainResoCutOff = FLP_Int + 9,
	FLP_DelayReso = FLP_Int + 10,
	FLP_Reverb = FLP_Int + 11,
	FLP_IntStretch = FLP_Int + 12,
	FLP_SSNote = FLP_Int + 13,
	FLP_FineTune = FLP_Int + 14,

	FLP_BPM = FLP_Int + 28,

	FLP_Unknown_159 = FLP_Int + 31, // 0x6B2 on 20.7, 0x5E9 on 20.6

	// TEXT EVENTS
	FLP_Undef = 192,            	//+Size (var length)
	FLP_Text = FLP_Undef,         	//+Size (var length)+Text (Null Term. String)
	FLP_Text_ChanName_Deprecated = FLP_Text,	// name for the current channel
	FLP_Text_PatName = FLP_Text + 1,	// name for the current pattern
	FLP_Text_Title = FLP_Text + 2,	// title of the loop
	FLP_Text_Comment = FLP_Text + 3,	// old comments in text format. Not used anymore
	FLP_Text_SampleFileName = FLP_Text + 4,	// filename for the sample in the current channel, stored as relative path
	FLP_Text_URL = FLP_Text + 5,
	FLP_Text_CommentRTF = FLP_Text + 6,  	// new comments in Rich Text format
	FLP_Version = FLP_Text + 7,
	FLP_Text_Licensee = FLP_Text + 8,
	FLP_Text_PluginName = FLP_Text + 9,	// plugin file name (without path)

	FLP_Text_ChannelName = FLP_Text + 11, // seems to be the new version of FLP_Text_ChanName_Deprecated

	FLP_Text_Genre = FLP_Text + 14,
	FLP_Text_Author = FLP_Text + 15,

	FLP_MIDICtrls = FLP_Text + 16,
	FLP_Delay = FLP_Text + 17,
	FLP_TS404Params = FLP_Text + 18,
	FLP_DelayLine = FLP_Text + 19,
	FLP_NewPlugin = FLP_Text + 20,
	FLP_PluginParams = FLP_Text + 21, // Size = WORD
	FLP_ChanParams = FLP_Text + 23, 	// block of various channel params (can grow)

	FLP_Text_ChannelCategoryName = FLP_Text + 39, // "Unsorted"

	FLP_NewTrack = FLP_Text + 46,
	FLP_Text_TrackName = FLP_Text + 47,

	FLP_Text_ArrangementName = FLP_Text + 49,
};

const char* FLP_GetEventName(FLP_Event ev);
