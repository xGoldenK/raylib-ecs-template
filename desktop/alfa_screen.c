#include "raylib.h"
#include "screens.h"
#include "entity_controller.h"
#include "components_controller.h"
#include "systems.h"

//--------------------------------------------------------------------------------------
// local variable declaration
//--------------------------------------------------------------------------------------
entity_id character;
entity_id box;
entity_id box2;

//--------------------------------------------------------------------------------------
// local forward function declaration
//--------------------------------------------------------------------------------------
entity_id CreateBox(int x, int y);

void InitAlfaScreen() {
	character = CreateEntity();

	// init character
	AddDrawComponent(character, LoadTexture("resources/idle.png"));
	AddControllerComponent(character);
	AddPositionComponent(character, 0, 40);

	PositionComponent* character_pos_c = GetEntityComponent(character, POSITION);
	AddRigidbodyComponent(character, 5, 5);

	DrawComponent* character_draw_c = GetEntityComponent(character, DRAW);
	AddBoxCollider(character, character_draw_c->texture.width, character_draw_c->texture.height);

	// init boxes
	// first box
	box = CreateBox(300, 20);

	// second box
	// box2 = CreateBox(100, 50);
}

void UpdateAlfaScreen() {
	UpdateControllerSystem();
	UpdateRigidbodySystem();
	UpdateCollisionSystem();
}

void DrawAlfaScreen() {
	UpdateDrawSystem();
}

void DisposeAlfaScreen() {
	// NOTE: add dispose methods for components/entities
	// https://prdeving.wordpress.com/2018/06/27/videogames-programming-ecs-system-in-plain-c/
}

entity_id CreateBox(int x, int y) {
	entity_id e_id = CreateEntity();

	// FIXME: do not use load texture each time
	AddDrawComponent(e_id, LoadTexture("resources/box.png"));
	AddPositionComponent(e_id, x, y);

	PositionComponent* pos_component = GetEntityComponent(e_id, POSITION);
	AddRigidbodyComponent(e_id, 0, 0);

	DrawComponent* draw_component = GetEntityComponent(e_id, DRAW);
	AddBoxCollider(
		e_id, 
		draw_component->texture.width,
		draw_component->texture.height
	);

	return e_id;
}