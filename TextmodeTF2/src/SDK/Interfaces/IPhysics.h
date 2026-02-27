#pragma once
#include "../Globals.h"

// Forward declarations
struct Vector;
struct QAngle;

// Indices for IPhysicsEnvironment (VPhysics030)
// CreateFluidController: 10
// CreateRagdollConstraint: 12
// DestroyConstraint: 23

class IPhysicsObject;
class IPhysicsFluidController;
class IPhysicsConstraint;
class IPhysicsConstraintGroup;
struct fluidparams_t;
struct constraint_ragdollparams_t;
struct constraint_groupparams_t;

class IPhysicsEnvironment
{
public:
	virtual void			Unused0() = 0; // Destructor
	virtual void			SetDebugOverlay( void* debugOverlayFactory ) = 0;
	virtual void*			GetDebugOverlay( void ) = 0;
	virtual void			SetGravity( const Vector &gravityVector ) = 0;
	virtual void			GetGravity( Vector &gravityVector ) = 0;
	virtual void			SetAirDensity( float density ) = 0;
	virtual float			GetAirDensity( void ) = 0;
	virtual IPhysicsObject	*CreatePolyObject( const void *pCollisionModel, int materialIndex, const Vector &position, const QAngle &angles, void *pParams ) = 0;
	virtual IPhysicsObject	*CreatePolyObjectStatic( const void *pCollisionModel, int materialIndex, const Vector &position, const QAngle &angles, void *pParams ) = 0;
	virtual IPhysicsObject *CreateSphereObject( float radius, int materialIndex, const Vector &position, const QAngle &angles, void *pParams, bool isStatic ) = 0;
	
	// Index 10
	virtual IPhysicsFluidController	*CreateFluidController( IPhysicsObject *pFluidObject, fluidparams_t *pParams ) = 0;

	virtual void*			CreateSpring( IPhysicsObject *pObjectStart, IPhysicsObject *pObjectEnd, void *pParams ) = 0;

	// Index 12
	virtual IPhysicsConstraint	*CreateRagdollConstraint( IPhysicsObject *pReferenceObject, IPhysicsObject *pAttachedObject, IPhysicsConstraintGroup *pGroup, const constraint_ragdollparams_t &ragdoll ) = 0;
	
	virtual IPhysicsConstraint	*CreateHingeConstraint( IPhysicsObject *pReferenceObject, IPhysicsObject *pAttachedObject, IPhysicsConstraintGroup *pGroup, const void *hinge ) = 0;
	virtual IPhysicsConstraint	*CreateFixedConstraint( IPhysicsObject *pReferenceObject, IPhysicsObject *pAttachedObject, IPhysicsConstraintGroup *pGroup, const void *fixed ) = 0;
	virtual IPhysicsConstraint	*CreateSlidingConstraint( IPhysicsObject *pReferenceObject, IPhysicsObject *pAttachedObject, IPhysicsConstraintGroup *pGroup, const void *sliding ) = 0;
	virtual IPhysicsConstraint	*CreateBallsocketConstraint( IPhysicsObject *pReferenceObject, IPhysicsObject *pAttachedObject, IPhysicsConstraintGroup *pGroup, const void *ballsocket ) = 0;
	virtual IPhysicsConstraint *CreatePulleyConstraint( IPhysicsObject *pReferenceObject, IPhysicsObject *pAttachedObject, IPhysicsConstraintGroup *pGroup, const void *pulley ) = 0;
	virtual IPhysicsConstraint *CreateLengthConstraint( IPhysicsObject *pReferenceObject, IPhysicsObject *pAttachedObject, IPhysicsConstraintGroup *pGroup, const void *length ) = 0;

	virtual IPhysicsConstraintGroup *CreateConstraintGroup( const constraint_groupparams_t &groupParams ) = 0;

	virtual void DestroyObject( IPhysicsObject * ) = 0;
	virtual void DestroySpring( void * ) = 0;
	virtual void DestroyFluidController( IPhysicsFluidController * ) = 0;
	
	// Index 23
	virtual void DestroyConstraint( IPhysicsConstraint * ) = 0;
};

class IPhysics
{
public:
	// IAppSystem
	virtual void Unused0() = 0;
	virtual void Unused1() = 0;
	virtual void Unused2() = 0;
	virtual void Unused3() = 0;
	virtual void Unused4() = 0;

	// IPhysics
	virtual	IPhysicsEnvironment		*CreateEnvironment( void ) = 0;
	virtual void DestroyEnvironment( IPhysicsEnvironment * ) = 0;
	virtual IPhysicsEnvironment		*GetActiveEnvironmentByIndex( int index ) = 0;
};

namespace G
{
	inline IPhysics* Physics = nullptr;
	inline IPhysicsEnvironment* PhysicsEnvironment = nullptr;
}
