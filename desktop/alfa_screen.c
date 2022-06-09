#include "raylib.h"
#include "screens.h"
#include "entity_controller.h"
#include "components_controller.h"
#include "systems.h"

//--------------------------------------------------------------------------------------
// local variable declaration
//--------------------------------------------------------------------------------------
entity_id character;
entity_id character2;

void InitAlfaScreen() {
	InitializeComponentLists();

	for(int i = 0; i < 10; i++) {
		entity_id e_id = CreateEntity();
		ECSpeed* c = CreateComponent(e_id, ECSpeed, SPEED);
		StoreComponent(c, ECSpeed);
	}

	ECSpeed* speed_components = GetComponents(SPEED);

	for(int i = 0; i < GetComponentListFreeSpaceIndex(SPEED); i++) {
		TraceLog(LOG_INFO, "Logging the %i th component", i);
		TraceLog(LOG_INFO, "component's entity id is %s", (((ECSpeed*)(GetComponents(SPEED))) + i)->base.e_id);
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

ComponentDictionary dictionary
void RegisterComponents() {

}