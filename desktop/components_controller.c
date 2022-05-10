#include "components_controller.h"

//--------------------------------------------------------------------------------------
// local variables
//--------------------------------------------------------------------------------------
// NOTE: we have to find a way to make the current_components arrays work when a component is disposed.
// we might have to remove the component, reposition all the others next to each other and then do current_component--;
// otherwise we might wrongly mark an occupied position of the array as free (if the component we deleted was not the last one)
unsigned int positions_lenght;
unsigned int drawables_lenght;
unsigned int controllables_lenght;
unsigned int rigidbodies_lenght;

// store the components in arrays
PositionComponent	positions[MAX_COMPONENTS];
DrawComponent		drawables[MAX_COMPONENTS];
ControllerComponent controllables[MAX_COMPONENTS];
RigidbodyComponent	rigidbodies[MAX_COMPONENTS];

//--------------------------------------------------------------------------------------
// add component functions
//--------------------------------------------------------------------------------------
void AddPositionComponent(entity_id id, int x, int y) {
	positions[positions_lenght] = (PositionComponent){id, x, y};
	positions_lenght++;
}

void AddDrawComponent(entity_id id, Texture2D texture) {
	drawables[drawables_lenght] = (DrawComponent){id, texture};
	drawables_lenght++;
}

void AddControllerComponent(entity_id id) {
	controllables[controllables_lenght] = (ControllerComponent){id};
	controllables_lenght++;
}

void AddRigidbodyComponent(entity_id id, int mass) {
	rigidbodies[rigidbodies_lenght] = (RigidbodyComponent){id, mass};
	rigidbodies_lenght++;
}

//--------------------------------------------------------------------------------------
// utility functions
// (lets try to keep local variables private and instead use these functions)
//--------------------------------------------------------------------------------------
bool EntityHasComponent(entity_id id, ComponentType type) {
	switch(type) {

	case POSITION:
		for(int i = 0; i < positions_lenght; i++) {
			if(id != positions[i].id) { continue; }

			return true;
		}
		break;

	case DRAW:
		for(int i = 0; i < drawables_lenght; i++) {
			if(id != drawables[i].id) { continue; }

			return true;
		}
		break;

	case CONTROLLER:
		for(int i = 0; i < controllables_lenght; i++) {
			if(id != controllables[i].id) { continue; }

			return true;
		}
		break;

	case RIGIDBODY:
		for(int i = 0; i < rigidbodies_lenght; i++) {
			if(id != rigidbodies[i].id) { continue; }

			return true;
		}
		break;

	}

	return false;
}

void* GetEntityComponent(entity_id id, ComponentType type) {
	switch(type) {

	case POSITION:
		for(int i = 0; i < positions_lenght; i++) {
			if(id == positions[i].id) { return &positions[i]; }
		}
		break;

	case DRAW:
		for(int i = 0; i < drawables_lenght; i++) {
			if(id == drawables[i].id) { return &drawables[i]; }
		}
		break;

	case CONTROLLER:
		for(int i = 0; i < controllables_lenght; i++) {
			if(id == controllables[i].id) { return &controllables[i]; }
		}
		break;

	case RIGIDBODY:
		for(int i = 0; i < rigidbodies_lenght; i++) {
			if(id == rigidbodies[i].id) { return &rigidbodies[i]; }
		}
		break;

	}

	return false;
}

void* GetComponents(ComponentType type) {
	switch(type) {

	case POSITION:		return &positions;
	case DRAW:			return &drawables;
	case CONTROLLER:	return &controllables;
	case RIGIDBODY:		return &rigidbodies;

	}
}

void* GetComponentAtIndex(int index, ComponentType type) {
	switch(type) {

	case POSITION:		return &positions[index];
	case DRAW:			return &drawables[index];
	case CONTROLLER:	return &controllables[index];
	case RIGIDBODY:		return &rigidbodies[index];

	}
}

int GetComponentArrayLenght(ComponentType type) {
	switch(type) {

	case POSITION:		return positions_lenght;
	case DRAW:			return drawables_lenght;
	case CONTROLLER:	return controllables_lenght;
	case RIGIDBODY:		return rigidbodies_lenght;

	}
}