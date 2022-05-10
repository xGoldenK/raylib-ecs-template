#pragma once

#include "raylib.h"
#include "entity.h"

//--------------------------------------------------------------------------------------
// types and structure definition
//--------------------------------------------------------------------------------------
typedef enum ComponentType {
	POSITION, DRAW, CONTROLLER
} ComponentType;

// FIXME: remove flight time from this component
typedef struct PositionComponent {
	entity_id	id;
	int			x;
	int			y;
	float		flight_time;
} PositionComponent;

typedef struct DrawComponent {
	entity_id	id;
	Texture2D	texture;
} DrawComponent;

typedef struct ControllerComponent {
	entity_id	id;
} ControllerComponent;