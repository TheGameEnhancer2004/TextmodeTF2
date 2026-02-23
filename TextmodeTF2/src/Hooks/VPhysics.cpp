#include "VPhysics.h"
#include "../SDK/SDK.h"

MAKE_HOOK(hkCreateFluidController, NULL, IPhysicsFluidController*, IPhysicsEnvironment* rcx, IPhysicsObject* pFluidObject, fluidparams_t* pParams)
{
	// Null out fluid simulation creation
	// This prevents water physics and other fluid interactions
	return nullptr;
}

MAKE_HOOK(hkCreateRagdollConstraint, NULL, IPhysicsConstraint*, IPhysicsEnvironment* rcx, IPhysicsObject* pReferenceObject, IPhysicsObject* pAttachedObject, IPhysicsConstraintGroup* pGroup, const constraint_ragdollparams_t& ragdoll)
{
	// Null out ragdoll constraint creation
	// This effectively disables ragdoll physics
	return nullptr;
}

MAKE_HOOK(hkDestroyConstraint, NULL, void, IPhysicsEnvironment* rcx, IPhysicsConstraint* pConstraint)
{
	// Handle null constraint destruction safely
	if (!pConstraint)
		return;

	CALL_ORIGINAL(rcx, pConstraint);
}

void Hooks::VPhysics::Initialize()
{
	if (!G::Physics)
	{
		SDK::Output("VPhysics", "Interface not found, skipping hooks");
		return;
	}

	// Create a dummy environment to get the vtable address
	// This works because all instances of CPhysicsEnvironment share the same vtable
	IPhysicsEnvironment* pEnv = G::Physics->CreateEnvironment();
	if (!pEnv)
	{
		SDK::Output("VPhysics", "Failed to create dummy environment");
		return;
	}

	void** vtable = *reinterpret_cast<void***>(pEnv);

	// Initialize hooks using the vtable from the dummy environment
	// Indices:
	// CreateFluidController: 10
	// CreateRagdollConstraint: 12
	// DestroyConstraint: 23

	// We use the 'address' parameter of MAKE_HOOK as a placeholder (NULL) 
	// and manually create the hook using the vtable address.
	// However, the MAKE_HOOK macro expects 'address' to be used in Init().
	// We need to bypass the standard Init() or manually set the address.
	
	// Let's use the CHook::Create directly for these since we have dynamic addresses
	
	// Hook CreateFluidController (Index 10)
	hkCreateFluidController::Hook.Create(vtable[10], hkCreateFluidController::Func);
	
	// Hook CreateRagdollConstraint (Index 12)
	hkCreateRagdollConstraint::Hook.Create(vtable[12], hkCreateRagdollConstraint::Func);
	
	// Hook DestroyConstraint (Index 23)
	hkDestroyConstraint::Hook.Create(vtable[23], hkDestroyConstraint::Func);

	SDK::Output("VPhysics", "Hooks initialized");

	// Clean up the dummy environment
	G::Physics->DestroyEnvironment(pEnv);
}
