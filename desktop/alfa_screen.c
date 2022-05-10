#include "raylib.h"
#include "screens.h"
#include "entity_controller.h"
#include "components_controller.h"
#include "systems.h"

//--------------------------------------------------------------------------------------
// local function definition
//--------------------------------------------------------------------------------------
entity_id entity;
entity_id entity2;
entity_id entity3;

void InitAlfaScreen() {
	entity = CreateEntity();
	entity2 = CreateEntity();
	entity3 = CreateEntity();

	AddDrawComponent(entity, LoadTexture("resources/idle.png"));
	AddPositionComponent(entity, 0, 0);

	AddDrawComponent(entity2, LoadTexture("resources/idle.png"));
	AddPositionComponent(entity2, 100, 20);

	AddDrawComponent(entity3, LoadTexture("resources/idle.png"));
	AddPositionComponent(entity3, 100, 50);
}

void UpdateAlfaScreen() {
	UpdatePositionSystem();
}

void DrawAlfaScreen() {
	UpdateDrawSystem();
}

void DisposeAlfaScreen() {
	// NOTE: add dispose methods for components/entities
	// https://prdeving.wordpress.com/2018/06/27/videogames-programming-ecs-system-in-plain-c/
}