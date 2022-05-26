#pragma once

#include "components.h"
#include "entity.h"

#define MAX_COMPONENTS 100

//--------------------------------------------------------------------------------------
// global functions
//--------------------------------------------------------------------------------------
void  AddPositionComponent		(entity_id e_id, float x, float y);
void  AddDrawComponent			(entity_id e_id, Texture2D texture);
void  AddControllerComponent	(entity_id e_id);
void  AddRigidbodyComponent		(entity_id e_id, float max_speed, float max_jump_speed);
void  AddBoxCollider			(entity_id e_id, float width, float height);

void		RequireComponents		(entity_id e_id, ComponentType component_type);
bool		EntityHasComponent		(entity_id e_id, ComponentType type);
void*		GetEntityComponent		(entity_id e_id, ComponentType type);
void*		GetComponents			(ComponentType type);				//NOTE: this function returns a pointer! (correct usage: DrawComponent* d = ...)
void*		GetComponentAtIndex		(int index, ComponentType type);
entity_id	GetEntityId				(int index, ComponentType type);
int			GetComponentArrayLenght	(ComponentType type);