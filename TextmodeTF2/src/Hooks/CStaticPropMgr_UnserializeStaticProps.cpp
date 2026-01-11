#include "../Utils/Hooks/Hooks.h"
#include "../SDK/SDK.h"

// void CStaticPropMgr::UnserializeStaticProps()
MAKE_HOOK(CStaticPropMgr_UnserializeStaticProps, G::CStaticPropMgr_UnserializeStaticPropsAddr, void, void* rcx)
{
	return;
}
