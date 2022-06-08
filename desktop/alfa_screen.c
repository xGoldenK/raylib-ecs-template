#include "raylib.h"
#include "screens.h"
#include "entity_controller.h"
#include "components_controller.h"
#include "systems.h"

//--------------------------------------------------------------------------------------
// local variable declaration
//--------------------------------------------------------------------------------------
entity_id character;

void InitAlfaScreen() {
	InitializeComponentArrays();

	character = CreateEntity();

	TraceLog(LOG_INFO, "character is %s", character);
	ECSpeed* c = AddComponent(character, ECSpeed);

	StoreComponent(c, SPEED, ECSpeed);
	StoreComponent(c, SPEED, ECSpeed);

	ECSpeed* speed_components = (ECSpeed*) arrays[SPEED].buffer;
	TraceLog(LOG_INFO, "array id is %s", (speed_components + 1)->e_id);
	TraceLog(LOG_INFO, "array id is %s", (speed_components)->e_id);
}

void UpdateAlfaScreen() {

}

void DrawAlfaScreen() {

}

void DisposeAlfaScreen() {
	// NOTE: add dispose methods for components/entities
	// https://prdeving.wordpress.com/2018/06/27/videogames-programming-ecs-system-in-plain-c/
}