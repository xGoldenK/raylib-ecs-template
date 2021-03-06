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
	for(int i = 0; i < 10; i++) {
		entity_id e_id = CreateEntity();
		ECSpeed* c = CREATE_COMPONENT(e_id, ECSpeed, SPEED);
		STORE_COMPONENT(c, ECSpeed);
	}
	
	ECSpeed* speed_components = GET_COMPONENTS(SPEED);
	for(int i = 0; i < GET_COMPONENT_LIST_FREE_SPACE_INDEX(SPEED); i++) {
		TraceLog(LOG_INFO, "component's %i th entity id is %s", i, (speed_components + i)->base.e_id);
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