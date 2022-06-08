#pragma once

#include "components.h"
#include "entity.h"

#define MAX_COMPONENTS 100
#define COMPONENT_TYPES_LENGHT 7

//--------------------------------------------------------------------------------------
// macros
//--------------------------------------------------------------------------------------
// create component for an entity
// component_struct: the component's struct
// component_type: the component's id (ComponentType enum)
// entity: the id of the entity
// "returns": the memory address of the new component
#define CreateComponent(entity_id, component_struct, component_type)\
	&(component_struct){ .base = { .e_id = entity_id, .c_type = component_type } }\

// get all the components of a specific type
// component_type: the component's id (ComponentType enum)
// "returns": the list of components as a pointer
#define GetComponents(component_type)\
	GetComponentArray(component_type).buffer\

// get the first_free_space_index of a specific component array
// component_type: the component's id (ComponentType enum)
// "returns": the first_free_space_index int
#define GetComponentArrayFreeSpaceIndex(component_type)\
	GetComponentArray(component_type).first_free_space_index\

// get a component array struct of the given component type
// component_type: the component's id (ComponentType enum)
// "returns": the component array struct of the given component type
#define GetComponentArray(component_type)\
	component_arrays[component_type]\

// store a component in the respective component array
// component_struct: the component's struct
// p_component: the pointer to the component we want to store
#define StoreComponent(p_component, component_struct){\
	/* get the component type */ \
	int type = p_component->base.c_type;\
	/* cast the correct component type to the generic void* buffer of the array */ \
	component_struct* components_of_type = GetComponents(type);\
	/* set the first free space of the buffer to the component we want to store */ \
	/* we use pointers since they're basically the same as arrays */ \
	*(components_of_type + component_arrays[type].first_free_space_index) = *(p_component);\
	/* update the new first free space index */ \
	component_arrays[type].first_free_space_index += 1;\
}

//--------------------------------------------------------------------------------------
// global variables
//--------------------------------------------------------------------------------------
// arrays of every component's type
ComponentArray component_arrays[COMPONENT_TYPES_LENGHT];

//--------------------------------------------------------------------------------------
// global functions declaration
//--------------------------------------------------------------------------------------
// allocate the space needed by the component arrays
void InitializeComponentArrays();
