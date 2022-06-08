#include "components_controller.h"

#include "stdlib.h"

//
////--------------------------------------------------------------------------------------
//// local variables
////--------------------------------------------------------------------------------------
//// NOTE: we have to find a way to make the current_components arrays work when a component is disposed.
//// we might have to remove the component, reposition all the others next to each other and then do current_component--;
//// otherwise we might wrongly mark an occupied position of the array as free (if the component we deleted was not the last one)

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

void InitializeComponentArrays() {
	for(int i = 0; i < COMPONENT_TYPES_LENGHT; i++) {
		int component_size = GetComponentSizeFromType(i);

		arrays[i] = (ComponentArray){
			.buffer = malloc(component_size * MAX_COMPONENTS),
			.capacity = MAX_COMPONENTS,
			.single_component_size = component_size,
			.first_free_space_index = 0,
		};
	}
}

//// store the lenght of each component array in a variable
//int positions_lenght;
//int drawables_lenght;
//int rigidbodies_lenght;
//int controllables_lenght;
//int box_colliders_lenght;
//
//// store the components in arrays
//PositionComponent	positions[MAX_COMPONENTS];
//DrawComponent		drawables[MAX_COMPONENTS];
//ControllerComponent controllables[MAX_COMPONENTS];
//RigidbodyComponent  rigidbodies[MAX_COMPONENTS];
//BoxCollider			box_colliders[MAX_COMPONENTS];
//CollisionInfo		collision_infos[MAX_COMPONENTS];
//
////--------------------------------------------------------------------------------------
//// forward declare local functions
////--------------------------------------------------------------------------------------
//bool IsComponentRequired(ComponentType type_list, ComponentType type_to_check);
//void WarnMissingComponent(entity_id e_id, const char* component_name);
//
////--------------------------------------------------------------------------------------
//// add component functions
////--------------------------------------------------------------------------------------
//void AddPositionComponent(entity_id e_id, float x, float y) {
//	positions[positions_lenght] = (PositionComponent){
//		.e_id = e_id,
//		.x = x,
//		.y = y
//	};
//	positions_lenght++;
//}
//
//void AddDrawComponent(entity_id e_id, Texture2D texture) {
//	drawables[drawables_lenght] = (DrawComponent){
//		.e_id = e_id,
//		.texture = texture
//	};
//	drawables_lenght++;
//}
//
//void AddControllerComponent(entity_id e_id) {
//	controllables[controllables_lenght] = (ControllerComponent){
//		.e_id = e_id
//	};
//	controllables_lenght++;
//}
//
//void AddRigidbodyComponent(entity_id e_id, float max_speed, float max_jump_speed) {
//	rigidbodies[rigidbodies_lenght] = (RigidbodyComponent){
//		.e_id				= e_id,
//		.max_speed			= (Vector2){max_speed, max_jump_speed},
//		.current_speed		= (Vector2){0, 0},
//		.current_friction	= 0,
//		.flight_time		= 0,
//		.is_grounded		= 0,
//		.can_move			= 1
//	};
//	rigidbodies_lenght++;
//}
//
//void AddBoxCollider(entity_id e_id, float width, float height) {
//	box_colliders[box_colliders_lenght] = (BoxCollider){
//		.e_id	= e_id,
//		.width	= width,
//		.height	= height,
//
//		.collision_info = (CollisionInfo) {
//			.is_colliding_down	= 0,
//			.is_colliding_left	= 0,
//			.is_colliding_right = 0,
//			.is_colliding_up	= 0
//		}
//	};
//
//	box_colliders_lenght++;
//}
//
////--------------------------------------------------------------------------------------
//// utility functions
//// (lets try to keep local variables private and instead use these functions)
////--------------------------------------------------------------------------------------
//
//// this function accepts a "required_types" parameter for the component types;
//// we can pass multiple types by passing different enums using bitwise OR operator (|).
//// we can then check if in the "list" of types we have a specific component
//// by using the bitwise AND operator (&).
//// NOTE: this function is called only after the first system update
//// this means that we can add the components to an entity in any order without problems
//
//void* GetEntityComponent(entity_id e_id, ComponentType type) {
//	switch(type) {
//
//	case POSITION:
//		for(int i = 0; i < positions_lenght; i++) {
//			if(e_id == positions[i].e_id) { return &positions[i]; }
//		}
//		break;
//
//	case DRAW:
//		for(int i = 0; i < drawables_lenght; i++) {
//			if(e_id == drawables[i].e_id) { return &drawables[i]; }
//		}
//		break;
//
//	case CONTROLLER:
//		for(int i = 0; i < controllables_lenght; i++) {
//			if(e_id == controllables[i].e_id) { return &controllables[i]; }
//		}
//		break;
//
//	case RIGIDBODY:
//		for(int i = 0; i < rigidbodies_lenght; i++) {
//			if(e_id == rigidbodies[i].e_id) { return &rigidbodies[i]; }
//		}
//		break;
//
//	case BOX_COLLIDER:
//		for(int i = 0; i < box_colliders_lenght; i++) {
//			if(e_id == box_colliders[i].e_id) { return &box_colliders[i]; }
//		}
//		break;
//
//	}
//
//	return NULL;
//}
//
//void* GetComponents(ComponentType type) {
//	switch(type) {
//
//	case POSITION:		return &positions;
//	case DRAW:			return &drawables;
//	case CONTROLLER:	return &controllables;
//	case RIGIDBODY:		return &rigidbodies;
//	case BOX_COLLIDER:	return &box_colliders;
//
//	}
//
//	return NULL;
//}
//
//entity_id GetEntityId(int index, ComponentType type) {
//	switch(type) {
//
//	case POSITION:		return positions[index].e_id;
//	case DRAW:			return drawables[index].e_id;
//	case CONTROLLER:	return controllables[index].e_id;
//	case RIGIDBODY:		return rigidbodies[index].e_id;
//	case BOX_COLLIDER:	return box_colliders[index].e_id;
//
//	}
//
//	return NULL;
//}
//
//void* GetComponentAtIndex(int index, ComponentType type) {
//	switch(type) {
//
//	case POSITION:		return &positions[index];
//	case DRAW:			return &drawables[index];
//	case CONTROLLER:	return &controllables[index];
//	case RIGIDBODY:		return &rigidbodies[index];
//	case BOX_COLLIDER:	return &box_colliders[index];
//
//	}
//
//	return NULL;
//}
//
//// if this function returns -1, then we asked for an unimplemented component
//int GetComponentArrayLenght(ComponentType type) {
//	switch(type) {
//
//	case POSITION:		return positions_lenght;
//	case DRAW:			return drawables_lenght;
//	case CONTROLLER:	return controllables_lenght;
//	case RIGIDBODY:		return rigidbodies_lenght;
//	case BOX_COLLIDER:	return box_colliders_lenght;
//
//	}
//
//	return -1;
//}
//
//bool EntityHasComponent(entity_id e_id, ComponentType type) {
//	return (GetEntityComponent(e_id, type) != NULL);
//}