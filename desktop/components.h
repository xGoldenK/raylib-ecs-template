#pragma once

#include "raylib.h"
#include "physac.h"

#include "entity.h"

#define MAX_COMPONENTS 100
#define COMPONENT_TYPES_LENGHT 7

//--------------------------------------------------------------------------------------
// types and structure definition
//--------------------------------------------------------------------------------------
// component types
typedef enum ComponentType {
	POSITION, DRAW, CONTROLLABLE, FRICTION, SPEED,
	GRAVITY, BOX_COLLIDER
} ComponentType;

// component list
// holds important information about a component type and the array of its components
// as a void* buffer
typedef struct ComponentList {
	void* buffer;
	int capacity;
	int single_component_size;
	int first_free_space_index;
} ComponentList;

// base component
typedef struct ECBase {
	entity_id		e_id;
	ComponentType	c_type;
} ECBase;

// actual components
// registration is required using the REGISTER_COMPONENT macro
typedef struct ECPosition {
	ECBase		base;
	float		x;
	float		y;
} ECPosition;

typedef struct ECDraw {
	ECBase		base;
	Texture2D	texture;
} ECDraw;

typedef struct ECControllable {
	ECBase		base;
} ECControllable;

typedef struct ECFriction {
	ECBase		base;
	float		max_friction;
	float		current_friction;
} ECFriction;

typedef struct ECSpeed {
	ECBase		base;
	Vector2		current_speed;
	Vector2		max_speed;
} ECSpeed;

typedef struct ECGravity {
	ECBase		base;
	float		air_time;
	float		gravity_acceleration;
} ECGravity;

typedef struct ECBoxCollider {
	ECBase			base;
	PhysicsBody		body;
	int				is_grounded;
	float			width;
	float			height;
} ECBoxCollider;