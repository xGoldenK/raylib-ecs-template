#pragma once

#include "components.h"
#include "entity.h"

#define MAX_COMPONENTS 100

//--------------------------------------------------------------------------------------
// global functions
//--------------------------------------------------------------------------------------
void  AddPositionComponent		(entity_id id, int x, int y);
void  AddDrawComponent			(entity_id id, Texture2D texture);
void  AddControllerComponent	(entity_id id);

bool		EntityHasComponent		(entity_id id, ComponentType type);
void*		GetEntityComponent		(entity_id id, ComponentType type);
void*		GetComponents			(ComponentType type);				//NOTE: this function returns a pointer! (correct usage: DrawComponent* d = ...)
void*		GetComponentAtIndex		(int index, ComponentType type);
entity_id	GetEntityId				(int index, ComponentType type);
int			GetComponentArrayLenght	(ComponentType type);