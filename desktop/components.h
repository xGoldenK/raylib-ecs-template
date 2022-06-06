#pragma once

#include "raylib.h"
#include "entity.h"

#define COMPONENTS_LENGHT sizeof(ComponentType) 

//--------------------------------------------------------------------------------------
// types and structure definition
//--------------------------------------------------------------------------------------
// assign a power of two to the component types in order to use bitwise or to pass multiple enums
// see RequireComponents in components_controller.c
typedef enum ComponentType {
	POSITION		= 1,
	DRAW			= 2,
	RIGIDBODY		= 4,
	CONTROLLER		= 8,
	BOX_COLLIDER	= 16,
} ComponentType;

typedef struct PositionComponent {
	entity_id	e_id;
	float		x;
	float		y;
} PositionComponent;

typedef struct DrawComponent {
	entity_id	e_id;
	Texture2D	texture;
} DrawComponent;

// TODO: separate components based on the system they're used in
// for example, we might create a movement component to assign speed and jump force
typedef struct RigidbodyComponent {
	entity_id	e_id;
	Vector2		max_speed;
	Vector2		current_speed;
	float		current_friction;
	float		flight_time;
	int			is_grounded;
	int			can_move;
} RigidbodyComponent;

typedef struct ControllerComponent {
	entity_id	e_id;
} ControllerComponent;

typedef struct CollisionInfo {
	int			is_colliding_up;
	int			is_colliding_left;
	int			is_colliding_down;
	int			is_colliding_right;
} CollisionInfo;

typedef struct BoxCollider {
	entity_id		e_id;
	float			width;
	float			height;
	CollisionInfo	collision_info;
} BoxCollider;