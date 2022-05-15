#include "raylib.h"
#include "screens.h"
#include "entity_controller.h"
#include "components_controller.h"
#include "systems.h"

//--------------------------------------------------------------------------------------
// local function definition
//--------------------------------------------------------------------------------------
entity_id character;
entity_id box;
entity_id box2;

void InitAlfaScreen() {
	character = CreateEntity();
	box = CreateEntity();
	box2 = CreateEntity();

	AddDrawComponent(character, LoadTexture("resources/idle.png"));
	AddRigidbodyComponent(character);
	AddControllerComponent(character, 10);

	AddDrawComponent(box, LoadTexture("resources/box.png"));
	AddPositionComponent(box, 120, 20);
	AddRigidbodyComponent(box);

	AddDrawComponent(box2, LoadTexture("resources/box.png"));
	AddPositionComponent(box2, 100, 50);
	AddRigidbodyComponent(box2);
}

void UpdateAlfaScreen() {
	UpdateKeyListener();
	UpdateRigidbodySystem();
	UpdateControllerSystem();
}

void DrawAlfaScreen() {
	UpdateDrawSystem();
}

void DisposeAlfaScreen() {
	// NOTE: add dispose methods for components/entities
	// https://prdeving.wordpress.com/2018/06/27/videogames-programming-ecs-system-in-plain-c/
}