#include "components_controller.h"

#include "stdlib.h"


//--------------------------------------------------------------------------------------
// local variables
//--------------------------------------------------------------------------------------
void InitializeComponentLists() {
	// fill the arrays with the respective initialized structs
	for(int i = 0; i < COMPONENT_TYPES_LENGHT; i++) {
		int component_size = GET_COMPONENT_SIZE(i);

		// if the component size is 0, it means that we did not register it using the REGISTER_COMPONENT macro
		if(component_size == 0) {
			TraceLog(LOG_ERROR, "A component has not been registered correctly!");
			TraceLog(LOG_ERROR, "The component's type is %i", i);
			continue;
		}

		// fill our current list
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
