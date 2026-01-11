#include "../Utils/Hooks/Hooks.h"
#include "../SDK/SDK.h"

// CParticleCollection::Simulate(float flTime)
MAKE_HOOK(CParticleCollection_Simulate, G::CParticleCollection_SimulateAddr, void, void* rcx, float flTime)
{
	return;
}
