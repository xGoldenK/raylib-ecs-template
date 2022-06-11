#pragma once

#include "components.h"

#include "stdlib.h"

//--------------------------------------------------------------------------------------
// macros
//--------------------------------------------------------------------------------------
// registers a component in the component identifier list
// this is required before using any macro for that component type in this file
// component_struct: the component's struct
// component_type: the component's id (ComponentType enum)
#define REGISTER_COMPONENT(component_struct, component_type) {\
	int c_size = sizeof(component_struct);\
	component_lists[component_type] = (ComponentList){\
			.buffer = malloc(c_size * MAX_COMPONENTS),\
			.max_components = MAX_COMPONENTS,\
			.component_size = c_size,\
			.first_free_space_index = 0,\
		}; \
}\

// create component for an entity
// component_struct: the component's struct
// component_type: the component's id (ComponentType enum)
// entity: the id of the entity
// "returns": the memory address of the new component
#define CREATE_COMPONENT(entity_id, component_struct, component_type)\
	&(component_struct){ .base = { .e_id = entity_id, .c_type = component_type } }\

// store a component in the respective component list
// component_struct: the component's struct
// p_component: the pointer to the component we want to store
#define STORE_COMPONENT(p_component, component_struct){\
	/* get the component type */ \
	int type = p_component->base.c_type;\
	/* cast the correct component type to the generic component buffer */ \
	component_struct* components_of_type = GET_COMPONENTS(type);\
	/* set the first free space of the buffer to the component we want to store */ \
	/* we use pointers since they're basically the same as arrays */ \
	*(components_of_type + component_lists[type].first_free_space_index) = *(p_component);\
	/* update the new first free space index */ \
	component_lists[type].first_free_space_index += 1;\
}

// get a component list struct of the given component type
// component_type: the component's id (ComponentType enum)
// "returns": the component list struct of the given component type
#define GET_COMPONENT_LIST(component_type)\
	component_lists[component_type]\

// gets the size of a component struct's using its type
// component_type: the component's id (ComponentType enum)
// "returns": the size of the component
#define GET_COMPONENT_SIZE(component_type)\
	component_lists[component_type].component_size\

// get all the components of a specific type
// component_type: the component's id (ComponentType enum)
// "returns": the list of components as a void*
#define GET_COMPONENTS(component_type)\
	GET_COMPONENT_LIST(component_type).buffer\

// get the first_free_space_index of a specific component list
// component_type: the component's id (ComponentType enum)
// "returns": the first_free_space_index int
#define GET_COMPONENT_LIST_FREE_SPACE_INDEX(component_type)\
	GET_COMPONENT_LIST(component_type).first_free_space_index\

//--------------------------------------------------------------------------------------
// global variables
//--------------------------------------------------------------------------------------
// arrays of every component's type
ComponentList		component_lists[COMPONENT_TYPES_LENGHT];

//--------------------------------------------------------------------------------------
// global functions declaration
//--------------------------------------------------------------------------------------
