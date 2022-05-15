#include "components_controller.h"

//--------------------------------------------------------------------------------------
// local variables
//--------------------------------------------------------------------------------------
// NOTE: we have to find a way to make the current_components arrays work when a component is disposed.
// we might have to remove the component, reposition all the others next to each other and then do current_component--;
// otherwise we might wrongly mark an occupied position of the array as free (if the component we deleted was not the last one)

// store the lenght of each component array in a variable
int positions_lenght;
int drawables_lenght;
int rigidbodies_lenght;
int controllables_lenght;

// store the components in arrays
PositionComponent	positions[MAX_COMPONENTS];
DrawComponent		drawables[MAX_COMPONENTS];
ControllerComponent controllables[MAX_COMPONENTS];
RigidbodyComponent  rigidbodies[MAX_COMPONENTS];

//--------------------------------------------------------------------------------------
// add component functions
//--------------------------------------------------------------------------------------
void AddPositionComponent(entity_id e_id, int x, int y) {
	positions[positions_lenght] = (PositionComponent){e_id, x, y};
	positions_lenght++;
}

void AddDrawComponent(entity_id e_id, Texture2D texture) {
	drawables[drawables_lenght] = (DrawComponent){e_id, texture};
	drawables_lenght++;
}

void AddControllerComponent(entity_id e_id, int movement_speed) {
	controllables[controllables_lenght] = (ControllerComponent){ e_id, movement_speed };
	controllables_lenght++;
}

void AddRigidbodyComponent(entity_id e_id) {
	rigidbodies[rigidbodies_lenght] = (RigidbodyComponent){ e_id };
	rigidbodies_lenght++;
}

//--------------------------------------------------------------------------------------
// utility functions
// (lets try to keep local variables private and instead use these functions)
//--------------------------------------------------------------------------------------

// this function accepts a "required_types" parameter for the component types;
// we can pass multiple types by passing different enums using bitwise OR operator (|).
// we can then check if in the "list" of types we have a specific component
// by using the bitwise AND operator (&).
// NOTE: this function is called only after the first system update
// this means that we can add the components to an entity in any order without problems
void RequireComponents(entity_id e_id, ComponentType required_types) {
	bool requirement_was_unmet = false;

	// FIXME: move that LoadTexture for the default DrawComponent somewhere else.
	// we don't want to load a file from the resources each time the function is called
	if(IsComponentRequired(required_types, POSITION) && !EntityHasComponent(e_id, POSITION)) {
		AddPositionComponent(e_id, 0, 0);
		requirement_was_unmet = true;
	}

	if(IsComponentRequired(required_types, DRAW) && !EntityHasComponent(e_id, DRAW)) {
		AddDrawComponent(e_id, LoadTexture("resources/default.png"));
		requirement_was_unmet = true;
	}

	if(IsComponentRequired(required_types, CONTROLLER) && !EntityHasComponent(e_id, CONTROLLER)) {
		AddControllerComponent(e_id, 10);
		requirement_was_unmet = true;
	}

	if(IsComponentRequired(required_types, RIGIDBODY) && !EntityHasComponent(e_id, RIGIDBODY)) {
		AddRigidbodyComponent(e_id);
		requirement_was_unmet = true;
	}

	if(requirement_was_unmet) {
		TraceLog(LOG_WARNING, "An entity was missing a required component. It has now been added with default values.");
		TraceLog(LOG_DEBUG, "Entity id is = %s", e_id);
	}
}

void* GetEntityComponent(entity_id e_id, ComponentType type) {
	switch(type) {

	case POSITION:
		for(int i = 0; i < positions_lenght; i++) {
			if(e_id == positions[i].e_id) { return &positions[i]; }
		}
		break;

	case DRAW:
		for(int i = 0; i < drawables_lenght; i++) {
			if(e_id == drawables[i].e_id) { return &drawables[i]; }
		}
		break;

	case CONTROLLER:
		for(int i = 0; i < controllables_lenght; i++) {
			if(e_id == controllables[i].e_id) { return &controllables[i]; }
		}
		break;

	case RIGIDBODY:
		for(int i = 0; i < rigidbodies_lenght; i++) {
			if(e_id == rigidbodies[i].e_id) { return &rigidbodies[i]; }
		}
		break;

	}

	return NULL;
}

void* GetComponents(ComponentType type) {
	switch(type) {

	case POSITION:		return &positions;
	case DRAW:			return &drawables;
	case CONTROLLER:	return &controllables;
	case RIGIDBODY:		return &rigidbodies;

	}

	return NULL;
}

entity_id GetEntityId(int index, ComponentType type) {
	switch(type) {

	case POSITION:		return positions[index].e_id;
	case DRAW:			return drawables[index].e_id;
	case CONTROLLER:	return controllables[index].e_id;
	case RIGIDBODY:		return rigidbodies[index].e_id;

	}

	return NULL;
}

void* GetComponentAtIndex(int index, ComponentType type) {
	switch(type) {

	case POSITION:		return &positions[index];
	case DRAW:			return &drawables[index];
	case CONTROLLER:	return &controllables[index];
	case RIGIDBODY:		return &rigidbodies[index];

	}

	return NULL;
}

// if this function returns -1, then we asked for an unimplemented component
int GetComponentArrayLenght(ComponentType type) {
	switch(type) {

	case POSITION:		return positions_lenght;
	case DRAW:			return drawables_lenght;
	case CONTROLLER:	return controllables_lenght;
	case RIGIDBODY:		return rigidbodies_lenght;

	}

	return -1;
}

bool EntityHasComponent(entity_id e_id, ComponentType type) {
	return (GetEntityComponent(e_id, type) != NULL);
}

// bitwise check
bool IsComponentRequired(ComponentType type_list, ComponentType type_to_check) {
	return (type_list & type_to_check);
}