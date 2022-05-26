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

	// init character
	AddDrawComponent(character, LoadTexture("resources/idle.png"));
	AddRigidbodyComponent(character, 5, 5);
	AddControllerComponent(character);
	AddPositionComponent(character, 0, 40);

	DrawComponent* character_draw_c = GetEntityComponent(character, DRAW);
	AddBoxCollider(character, character_draw_c->texture.width, character_draw_c->texture.height);

	// init boxes
	AddDrawComponent(box, LoadTexture("resources/box.png"));
	AddPositionComponent(box, 150, 20);
	AddRigidbodyComponent(box, 0, 0);

	DrawComponent* box_draw_c = GetEntityComponent(box, DRAW);
	AddBoxCollider(box, box_draw_c->texture.width, box_draw_c->texture.height);

	AddDrawComponent(box2, LoadTexture("resources/box.png"));
	AddPositionComponent(box2, 100, 50);
	AddRigidbodyComponent(box2, 0, 0);

	DrawComponent* box2_draw_c = GetEntityComponent(box2, DRAW);
	AddBoxCollider(box2, box2_draw_c->texture.width, box2_draw_c->texture.height);
}

void UpdateAlfaScreen() {
	UpdateKeyListener();
	UpdateRigidbodySystem();
	UpdateCollisionSystem();
	UpdateControllerSystem();
}

void DrawAlfaScreen() {
	UpdateDrawSystem();
}

void DisposeAlfaScreen() {
	// NOTE: add dispose methods for components/entities
	// https://prdeving.wordpress.com/2018/06/27/videogames-programming-ecs-system-in-plain-c/
}