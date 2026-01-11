#include "../Utils/Hooks/Hooks.h"
#include "../SDK/SDK.h"

// CSfxTable *S_PrecacheSound( const char *name )
MAKE_HOOK(S_PrecacheSound, G::S_PrecacheSoundAddr, void*, const char* name)
{
	return nullptr;
}
