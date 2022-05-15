#pragma once

#include "raylib.h"
#include "entity.h"

//--------------------------------------------------------------------------------------
// types and structure definition
//--------------------------------------------------------------------------------------
// assign a power of two to the component types in order to use bitwise or to pass multiple enums
// see RequireComponents in components_controller.c
typedef enum ComponentType {
	POSITION	= 1,
	DRAW		= 2,
	RIGIDBODY	= 4,
	CONTROLLER	= 8
} ComponentType;

typedef struct PositionComponent {
	entity_id	e_id;
	int			x;
	int			y;
} PositionComponent;

typedef struct DrawComponent {
	entity_id	e_id;
	Texture2D	texture;
} DrawComponent;

typedef struct RigidbodyComponent {
	entity_id	e_id;
	float		flight_time;
} RigidbodyComponent;

typedef struct ControllerComponent {
	entity_id	e_id;
	int			movement_speed;
} ControllerComponent;