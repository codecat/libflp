#include <flp/FlpEvents.h>

const char* FLP_GetEventName(FLP_Event ev)
{
	switch (ev) {
	case FLP_Enabled: return "FLP_Enabled";
	case FLP_NoteOn: return "FLP_NoteOn";
	case FLP_Vol: return "FLP_Vol";
	case FLP_Pan: return "FLP_Pan";
	case FLP_MIDIChan: return "FLP_MIDIChan";
	case FLP_MIDINote: return "FLP_MIDINote";
	case FLP_MIDIPatch: return "FLP_MIDIPatch";
	case FLP_MIDIBank: return "FLP_MIDIBank";
	case FLP_LoopActive: return "FLP_LoopActive";
	case FLP_ShowInfo: return "FLP_ShowInfo";
	case FLP_Shuffle: return "FLP_Shuffle";
	case FLP_MainVol: return "FLP_MainVol";
	case FLP_Stretch: return "FLP_Stretch";
	case FLP_Pitchable: return "FLP_Pitchable";
	case FLP_Zipped: return "FLP_Zipped";
	case FLP_Delay_Flags: return "FLP_Delay_Flags";
	case FLP_PatLength: return "FLP_PatLength";
	case FLP_BlockLength: return "FLP_BlockLength";
	case FLP_UseLoopPoints: return "FLP_UseLoopPoints";
	case FLP_LoopType: return "FLP_LoopType";
	case FLP_ChanType: return "FLP_ChanType";
	case FLP_MixSliceNum: return "FLP_MixSliceNum";
	case FLP_Unknown_28: return "FLP_Unknown_28";
	case FLP_Unknown_37: return "FLP_Unknown_37";

	case FLP_NewChan: return "FLP_NewChan";
	case FLP_NewPat: return "FLP_NewPat";
	case FLP_Tempo: return "FLP_Tempo";
	case FLP_CurrentPatNum: return "FLP_CurrentPatNum";
	case FLP_PatData: return "FLP_PatData";
	case FLP_FX: return "FLP_FX";
	case FLP_Fade_Stereo: return "FLP_Fade_Stereo";
	case FLP_CutOff: return "FLP_CutOff";
	case FLP_DotVol: return "FLP_DotVol";
	case FLP_DotPan: return "FLP_DotPan";
	case FLP_PreAmp: return "FLP_PreAmp";
	case FLP_Decay: return "FLP_Decay";
	case FLP_Attack: return "FLP_Attack";
	case FLP_DotNote: return "FLP_DotNote";
	case FLP_DotPitch: return "FLP_DotPitch";
	case FLP_DotMix: return "FLP_DotMix";
	case FLP_MainPitch: return "FLP_MainPitch";
	case FLP_RandChan: return "FLP_RandChan";
	case FLP_MixChan: return "FLP_MixChan";
	case FLP_Resonance: return "FLP_Resonance";
	case FLP_LoopBar: return "FLP_LoopBar";
	case FLP_StDel: return "FLP_StDel";
	case FLP_FX3: return "FLP_FX3";
	case FLP_DotReso: return "FLP_DotReso";
	case FLP_DotCutOff: return "FLP_DotCutOff";
	case FLP_ShiftDelay: return "FLP_ShiftDelay";
	case FLP_LoopEndBar: return "FLP_LoopEndBar";
	case FLP_Dot: return "FLP_Dot";
	case FLP_DotShift: return "FLP_DotShift";

	case FLP_Color: return "FLP_Color";
	case FLP_PlayListItem: return "FLP_PlayListItem";
	case FLP_Echo: return "FLP_Echo";
	case FLP_FXSine: return "FLP_FXSine";
	case FLP_CutCutBy: return "FLP_CutCutBy";
	case FLP_WindowH: return "FLP_WindowH";
	case FLP_MiddleNote: return "FLP_MiddleNote";
	case FLP_Reserved: return "FLP_Reserved";
	case FLP_MainResoCutOff: return "FLP_MainResoCutOff";
	case FLP_DelayReso: return "FLP_DelayReso";
	case FLP_Reverb: return "FLP_Reverb";
	case FLP_IntStretch: return "FLP_IntStretch";
	case FLP_SSNote: return "FLP_SSNote";
	case FLP_FineTune: return "FLP_FineTune";
	case FLP_BPM: return "FLP_BPM";
	case FLP_Unknown_159: return "FLP_Unknown_159";

	case FLP_Text_ChanName: return "FLP_Text_ChanName";
	case FLP_Text_PatName: return "FLP_Text_PatName";
	case FLP_Text_Title: return "FLP_Text_Title";
	case FLP_Text_Comment: return "FLP_Text_Comment";
	case FLP_Text_SampleFileName: return "FLP_Text_SampleFileName";
	case FLP_Text_URL: return "FLP_Text_URL";
	case FLP_Text_CommentRTF: return "FLP_Text_CommentRTF";
	case FLP_Version: return "FLP_Version";
	case FLP_Text_Licensee: return "FLP_Text_Licensee";
	case FLP_Text_PluginName: return "FLP_Text_PluginName";
	case FLP_Text_ChannelName: return "FLP_Text_ChannelName";
	case FLP_Text_Genre: return "FLP_Text_Genre";
	case FLP_Text_Author: return "FLP_Text_Author";
	case FLP_MIDICtrls: return "FLP_MIDICtrls";
	case FLP_Delay: return "FLP_Delay";
	case FLP_TS404Params: return "FLP_TS404Params";
	case FLP_DelayLine: return "FLP_DelayLine";
	case FLP_NewPlugin: return "FLP_NewPlugin";
	case FLP_PluginParams: return "FLP_PluginParams";
	case FLP_ChanParams: return "FLP_ChanParams";
	case FLP_Text_ChannelCategoryName: return "FLP_Text_ChannelCategoryName";
	case FLP_Text_ArrangementName: return "FLP_Text_ArrangementName";
	}

	return "FLP_Unknown";
}
