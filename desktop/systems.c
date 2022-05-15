#include "systems.h"
#include "raylib.h"
#include "components_controller.h"

#define GRAVITY_ACCELERATION 9.81

//--------------------------------------------------------------------------------------
// local variables
//--------------------------------------------------------------------------------------
bool left_key, down_key, right_key, jump_key;

//--------------------------------------------------------------------------------------
// systems
//--------------------------------------------------------------------------------------
// NOTE: we might have to implement a function to quickly check if an entity has another component
// maybe add a dependency system -> a component needs another -> if the entity doesn't have one, add it
// if we try to add the same component in another function, don't add it the second time

void UpdateKeyListener() {
	left_key	= IsKeyDown(KEY_A);
	down_key	= IsKeyDown(KEY_S);
	right_key	= IsKeyDown(KEY_D);
	jump_key	= IsKeyDown(KEY_SPACE);
}

void UpdateRigidbodySystem() {
	for(int i = 0; i < GetComponentArrayLenght(RIGIDBODY); i++) {

		entity_id e_id = GetEntityId(i, RIGIDBODY);
		RequireComponents(e_id, DRAW | POSITION);

		RigidbodyComponent* rb_component	= GetEntityComponent(e_id, RIGIDBODY);
		DrawComponent*		draw_component	= GetEntityComponent(e_id, DRAW);
		PositionComponent*	pos_component	= GetEntityComponent(e_id, POSITION);

		//--------------------------------------------------------------------------------------
		// gravity + bottom border grounding
		// REQUIRES: DrawComponent & RigidbodyComponent & PositionComponent
		//--------------------------------------------------------------------------------------
		// get the relative ground y limit (based on the texture's height)
		int relative_ground_y = (GetScreenHeight() - draw_component->texture.height);

		// if the texture is under the ground
		if(pos_component->y >= relative_ground_y) {

			// set its y at the level of the ground;
			// reset its flight time
			pos_component->y = relative_ground_y;
			rb_component->flight_time = 0;
		} else {
			// keep track of flight time and apply gravity
			rb_component->flight_time += GetFrameTime();

			// gravity displacement: (g*t^2)/2
			pos_component->y += (int)(GRAVITY_ACCELERATION * rb_component->flight_time * rb_component->flight_time) / 2;
		}
	}
}

void UpdateControllerSystem() {
	for(int i = 0; i < GetComponentArrayLenght(CONTROLLER); i++) {

		entity_id e_id = GetEntityId(i, CONTROLLER);
		RequireComponents(e_id, POSITION);

		PositionComponent* pos_component = GetEntityComponent(e_id, POSITION);
		ControllerComponent* con_component = GetEntityComponent(e_id, CONTROLLER);

		//--------------------------------------------------------------------------------------
		// wasd movement + jumping
		// REQUIRES: ControllerComponent & PositionComponent
		//--------------------------------------------------------------------------------------
		int speed = con_component->movement_speed;

		if(left_key)  { pos_component->x -= speed; }
		if(down_key)  { pos_component->y += speed; }
		if(right_key) { pos_component->x += speed; }
		if(jump_key)  { pos_component->y -= speed; }
	}
}

void UpdateDrawSystem() {
	for(int i = 0; i < GetComponentArrayLenght(DRAW); i++) {

		entity_id e_id = GetEntityId(i, DRAW);
		RequireComponents(e_id, POSITION);

		DrawComponent* draw_component = GetComponentAtIndex(i, DRAW);
		PositionComponent* position_component = GetEntityComponent(draw_component->e_id, POSITION);

		//--------------------------------------------------------------------------------------
		// drawing
		// REQUIRES: DrawComponent & PositionComponent
		//--------------------------------------------------------------------------------------
		DrawTexture(draw_component->texture, position_component->x, position_component->y, RAYWHITE);
	}
}