#pragma once

#include "raylib.h"
#include "entity.h"

//--------------------------------------------------------------------------------------
// types and structure definition
//--------------------------------------------------------------------------------------
typedef enum ComponentType {
	POSITION, DRAW, CONTROLLER, RIGIDBODY
} ComponentType;

typedef struct PositionComponent {
	entity_id	id;
	int			x;
	int			y;
} PositionComponent;

typedef struct DrawComponent {
	entity_id	id;
	Texture2D	texture;
} DrawComponent;

typedef struct ControllerComponent {
	entity_id	id;
} ControllerComponent;

typedef struct RigidbodyComponent {
	entity_id	id;
	int			mass;
} RigidbodyComponent;