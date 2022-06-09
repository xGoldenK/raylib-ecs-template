#include "components_controller.h"

#include "stdlib.h"


//--------------------------------------------------------------------------------------
// local variables
//--------------------------------------------------------------------------------------
int GetComponentSizeFromType(int index) {
	switch(index) {
	case POSITION:		return sizeof(ECPosition);
	case DRAW:			return sizeof(ECDraw);
	case CONTROLLABLE:	return sizeof(ECControllable);
	case FRICTION:		return sizeof(ECFriction);
	case SPEED:			return sizeof(ECSpeed);
	case GRAVITY:		return sizeof(ECGravity);
	case BOX_COLLIDER:	return sizeof(ECBoxCollider);
	}
}

void InitializeComponentLists() {
	// fill the arrays with the respective initialized structs
	for(int i = 0; i < COMPONENT_TYPES_LENGHT; i++) {
		int component_size = GetComponentSizeFromType(i);

		component_lists[i] = (ComponentList){
			.buffer = malloc(component_size * MAX_COMPONENTS),
			.capacity = MAX_COMPONENTS,
			.single_component_size = component_size,
			.first_free_space_index = 0,
		};
	}

	// check if the arrays have been correctly initialized
	// (might not be the best solution to check that)
	if((component_lists[0].single_component_size) == 0) {
		TraceLog(LOG_ERROR, "Single component size for the 0th component array is 0!");
		TraceLog(LOG_ERROR, "This probably means that the component arrays HAVE NOT been initialized!!");
	}

}
