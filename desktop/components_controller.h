#pragma once

#include "components.h"
#include "entity.h"

#define MAX_COMPONENTS 100
#define COMPONENT_TYPES_LENGHT 7

// array of every component's type
ComponentArray arrays[COMPONENT_TYPES_LENGHT];

// create component for an entity
// component_struct: the component's struct
// entity: the id of the entity
// "returns": the memory address of the new component
#define AddComponent(entity, component_struct, component_type)\
	&(component_struct){ .base = { .e_id = entity, .type = component_type } };\

// store a component in the respective component array
// component_struct: the component's struct
// component: the component we want to store
// index: the index of the component's type (use ComponentType enum)
#define StoreComponent(component, component_struct, component_type){\
	/* cast the correct component type to the generic void* buffer of the array */ \
	component_struct* components_of_type = (component_struct*) arrays[component_type].buffer;\
	/* set the first free space of the buffer to the component we want to store */ \
	*(components_of_type + arrays[component_type].first_free_space_index) = *component;\
	/* update the new first free space index */ \
	arrays[component_type].first_free_space_index += 1;\
}

#define GetComponentSizeFromType(component_type) {\
	
}\

// allocate the space needed by the component arrays
void InitializeComponentArrays();

//--------------------------------------------------------------------------------------
// global functions declaration
//--------------------------------------------------------------------------------------
//void		RequireComponents		(entity_id e_id, ComponentType component_type);
//bool		EntityHasComponent		(entity_id e_id, ComponentType type);
//void*		GetEntityComponent		(entity_id e_id, ComponentType type);

// try and implement this first, the rest come from GetComponents
//void*		GetComponents			(ComponentType type);				//NOTE: this function returns a pointer! (correct usage: DrawComponent* d = ...)
//void*		GetComponentAtIndex		(int index, ComponentType type);
//entity_id	GetEntityId				(int index, ComponentType type);
//int		GetComponentArrayLenght	(ComponentType type);