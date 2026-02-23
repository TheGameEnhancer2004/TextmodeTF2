#include "../Utils/Hooks/Hooks.h"
#include "../SDK/SDK.h"

// void IBaseClientDLL::FrameStageNotify(ClientFrameStage_t curStage)
MAKE_HOOK(IBaseClientDLL_FrameStageNotify, G::IBaseClientDLL_FrameStageNotifyAddr, void, void* rcx, ClientFrameStage_t curStage)
{
	if (curStage == FRAME_RENDER_START || curStage == FRAME_RENDER_END)
		return;

	CALL_ORIGINAL(rcx, curStage);
}
