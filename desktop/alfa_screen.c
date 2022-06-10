#include "raylib.h"
#include "screens.h"
#include "entity_controller.h"
#include "components_controller.h"
#include "systems.h"

#include "stdlib.h"

//--------------------------------------------------------------------------------------
// local variable declaration
//--------------------------------------------------------------------------------------
entity_id character;
entity_id character2;

void InitAlfaScreen() {
	REGISTER_COMPONENT(ECPosition,		POSITION);
	REGISTER_COMPONENT(ECDraw,			DRAW);
	REGISTER_COMPONENT(ECControllable,	CONTROLLABLE);
	REGISTER_COMPONENT(ECFriction,		FRICTION);
	REGISTER_COMPONENT(ECSpeed,			SPEED);
	REGISTER_COMPONENT(ECGravity,		GRAVITY);
	REGISTER_COMPONENT(ECBoxCollider,	BOX_COLLIDER);

	for(int i = 0; i < 10; i++) {
		entity_id e_id = CreateEntity();
		ECSpeed* c = CREATE_COMPONENT(e_id, ECSpeed, SPEED);
		STORE_COMPONENT(c, ECSpeed);
	}

	TraceLog(LOG_INFO, "position isze is %i", sizeof(ECDraw));

	ECSpeed* speed_components = GET_COMPONENTS(SPEED);

	for(int i = 0; i < GET_COMPONENT_LIST_FREE_SPACE_INDEX(SPEED); i++) {
		TraceLog(LOG_INFO, "Logging the %i th component", i);
		TraceLog(LOG_INFO, "component's entity id is %s", (((ECSpeed*)(GET_COMPONENTS(SPEED))) + i)->base.e_id);
	}

}

void UpdateAlfaScreen() {

}

void DrawAlfaScreen() {

}

void DisposeAlfaScreen() {
	// NOTE: add dispose methods for components/entities
	// https://prdeving.wordpress.com/2018/06/27/videogames-programming-ecs-system-in-plain-c/
}