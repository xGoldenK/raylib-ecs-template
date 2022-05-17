#include "systems.h"
#include "raylib.h"
#include "entity_controller.h"
#include "components_controller.h"

#define GRAVITY_ACCELERATION 9.81

//--------------------------------------------------------------------------------------
// local variables
//--------------------------------------------------------------------------------------
bool left_key, down_key, right_key, jump_key;

//--------------------------------------------------------------------------------------
// systems
//--------------------------------------------------------------------------------------
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

		// if the entity is under the ground
		if(pos_component->y >= relative_ground_y) {

			// set y pos at the level of the ground;
			pos_component->y = relative_ground_y;

			// reset rb's flight time
			rb_component->flight_time = 0;
			
			// since we're grounded, we can jump
			if(EntityHasComponent(e_id, CONTROLLER)) { SetEntityCanJump(e_id, true); }

		} else {
			// keep track of flight time
			rb_component->flight_time += GetFrameTime();

			// apply gravity:
			// gravity displacement: (g*t^2)/2
			pos_component->y += (int)(GRAVITY_ACCELERATION * rb_component->flight_time * rb_component->flight_time) / 2;

			// since we're not grounded, we cannot jump
			if(EntityHasComponent(e_id, CONTROLLER)) { SetEntityCanJump(e_id, false); }
		}
	}
}

void UpdateCollisionSystem() {
	for(int i = 0; i < GetComponentArrayLenght(BOX_COLLIDER); i++) {

		entity_id e_id = GetEntityId(i, BOX_COLLIDER);
		RequireComponents(e_id, POSITION);

		BoxCollider*		box_collider	= GetEntityComponent(e_id, BOX_COLLIDER);
		PositionComponent*	pos_component	= GetEntityComponent(e_id, POSITION);

		//--------------------------------------------------------------------------------------
		// collisions
		// REQUIRES: BoxCollider & PositionComponent
		//--------------------------------------------------------------------------------------
		// NOTE: move movement_speed to another component; there will be entities which will move without a controller component
		int speed = 0;
		if(EntityHasComponent(e_id, CONTROLLER)) {
			ControllerComponent* controller = GetEntityComponent(e_id, CONTROLLER);
			speed = controller->movement_speed;
		}

		// modified rectangle, we want to try and predict where the player will move next frame
		// so that we can stop before he does
		Rectangle i_rect = (Rectangle){
			pos_component->x - speed,
			pos_component->y + speed,
			box_collider->width + speed*2,
			box_collider->height + speed*2
		};

		// NOTE: we might optimize this by only checking objects which are near the player
		// 
		// loop through every rigidbody object to check of they're collding with the upper "i" object
		for(int q = 0; q < GetComponentArrayLenght(BOX_COLLIDER); q++) {

			// if q == i is true it means that we're checking if the current "i" object
			// is colliding with itself (since the ids are the same)
			// we can just skip this and keep looping
			if(q == i) { continue; }

			entity_id q_id = GetEntityId(q, BOX_COLLIDER);
			RequireComponents(q_id, POSITION);

			BoxCollider* q_box_collider = GetEntityComponent(q_id, BOX_COLLIDER);
			PositionComponent* q_pos_comp = GetEntityComponent(q_id, POSITION);

			Rectangle q_rect = (Rectangle){
				q_pos_comp->x,
				q_pos_comp->y,
				q_box_collider->width,
				q_box_collider->height
			};

			if(CheckCollisionRecs(i_rect, q_rect)) {
				TraceLog(LOG_INFO, "COLLISION");
			}
		}
	}
}

void UpdateControllerSystem() {
	for(int i = 0; i < GetComponentArrayLenght(CONTROLLER); i++) {

		entity_id e_id = GetEntityId(i, CONTROLLER);
		RequireComponents(e_id, POSITION);

		PositionComponent* pos_component = GetEntityComponent(e_id, POSITION);
		ControllerComponent* controller = GetEntityComponent(e_id, CONTROLLER);

		//--------------------------------------------------------------------------------------
		// wasd movement + jumping
		// REQUIRES: ControllerComponent & PositionComponent
		//--------------------------------------------------------------------------------------
		int speed = controller->movement_speed;
		TraceLog(LOG_INFO, "%i", controller->movement_speed);

		// DEBUG:
		controller->can_move = true;
		controller->can_jump = true;

		if(left_key	 && controller->can_move)  { pos_component->x -= speed; }
		if(down_key	 && controller->can_move)  { pos_component->y += speed; }
		if(right_key && controller->can_move)  { pos_component->x += speed; }
		if(jump_key	 && controller->can_jump)  { pos_component->y -= speed; }
	}
}

void UpdateDrawSystem() {
	for(int i = 0; i < GetComponentArrayLenght(DRAW); i++) {

		entity_id e_id = GetEntityId(i, DRAW);
		RequireComponents(e_id, POSITION);

		DrawComponent* draw_component = GetEntityComponent(e_id, DRAW);
		PositionComponent* position_component = GetEntityComponent(e_id, POSITION);

		//--------------------------------------------------------------------------------------
		// drawing
		// REQUIRES: DrawComponent & PositionComponent
		//--------------------------------------------------------------------------------------
		DrawTexture(draw_component->texture, position_component->x, position_component->y, RAYWHITE);
	}
}