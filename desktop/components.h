#pragma once

#include "raylib.h"
#include "entity.h"
#include "physac.h"

//--------------------------------------------------------------------------------------
// types and structure definition
//--------------------------------------------------------------------------------------
// TODO: remove this enum
typedef enum ComponentType {
	POSITION, DRAW, CONTROLLABLE, FRICTION, SPEED,
	GRAVITY, BOX_COLLIDER
} ComponentType;

typedef struct ComponentArray {
	void* buffer;
	int capacity;
	int single_component_size;
	int first_free_space_index;
} ComponentArray;

typedef struct ECBase {
	entity_id		e_id;
	ComponentType	type;
} ECBase;

typedef struct ECPosition {
	ECBase*		base;
	float		x;
	float		y;
} ECPosition;

typedef struct ECDraw {
	ECBase*		base;
	Texture2D	texture;
} ECDraw;

typedef struct ECControllable {
	ECBase*		base;
} ECControllable;

typedef struct ECFriction {
	ECBase*		base;
	float		max_friction;
	float		current_friction;
} ECFriction;

typedef struct ECSpeed {
	ECBase*		base;
	Vector2		current_speed;
	Vector2		max_speed;
} ECSpeed;

typedef struct ECGravity {
	ECBase*		base;
	float		air_time;
	float		gravity_acceleration;
} ECGravity;

typedef struct ECBoxCollider {
	ECBase*			base;
	PhysicsBody*	body;
	int				is_grounded;
	float			width;
	float			height;
} ECBoxCollider;