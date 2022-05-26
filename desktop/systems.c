#include <math.h>
#include "systems.h"
#include "raylib.h"
#include "entity_controller.h"
#include "components_controller.h"

#define GRAVITY_ACCELERATION 4.81
#define JUMP_ACCELERATION 10
#define MOVEMENT_ACCELERATION 10
#define	MAX_FRICTION 9
#define FRICTION_ACCELERATION 1

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
		RequireComponents(e_id, BOX_COLLIDER | POSITION);

		RigidbodyComponent* rb_component	= GetEntityComponent(e_id, RIGIDBODY);
		BoxCollider*		collider		= GetEntityComponent(e_id, BOX_COLLIDER);
		PositionComponent*	pos_component	= GetEntityComponent(e_id, POSITION);

		//--------------------------------------------------------------------------------------
		// grounding
		//--------------------------------------------------------------------------------------
		int relative_ground_y = (GetScreenHeight() - collider->height);

		// if the entity is touching the ground
		if(pos_component->y > relative_ground_y) {
			// set y pos at the level of the ground;
			pos_component->y = relative_ground_y;
			rb_component->current_speed.y = 0;

			// reset rb's flight time
			rb_component->flight_time = 0;

			// entity's grounded
			rb_component->is_grounded = true;
		} else {
			// otherwise, we're not on the ground
			rb_component->is_grounded = false;
		}

		//--------------------------------------------------------------------------------------
		// gravity
		//--------------------------------------------------------------------------------------
		// if the entity is not grounded, apply gravity
		if(!rb_component->is_grounded) {
			// keep track of flight time
			rb_component->flight_time += GetFrameTime();

			// apply gravity (s = 1/2*g*t^2)
			rb_component->current_speed.y += ((GRAVITY_ACCELERATION * rb_component->flight_time * rb_component->flight_time)/2);
		}

		//--------------------------------------------------------------------------------------
		// x-axis friction
		//--------------------------------------------------------------------------------------
		// if we're going to the left
		if(rb_component->current_speed.x < 0) {
			// apply friction
			rb_component->current_speed.x += FRICTION_ACCELERATION;

			// BUT, if the last friction tick changed the direction of the entity, we set its speed to 0.
			// this means that if while applying friction we're causing a movement in the opposite direction,
			// we stop the movement (otherwise we'd be going the opposite direction to the initial one, while instead we just want to stop)
			if(rb_component->current_speed.x > 0) { rb_component->current_speed.x = 0; }

			TraceLog(LOG_INFO, "friction is: %i", FRICTION_ACCELERATION);
		}

		// if we're going right
		if(rb_component->current_speed.x > 0) {
			// apply friction
			rb_component->current_speed.x -= FRICTION_ACCELERATION;

			// BUT, if the last friction tick changed the direction of the entity, we set its speed to 0.
			// this means that if while applying friction we're causing a movement in the opposite direction,
			// we stop the movement (otherwise we'd be going the opposite direction to the initial one, while instead we just want to stop)
			if(rb_component->current_speed.x < 0) { rb_component->current_speed.x = 0; }

			TraceLog(LOG_INFO, "friction is: %i", FRICTION_ACCELERATION);
		}

		//--------------------------------------------------------------------------------------
		// apply movement
		//--------------------------------------------------------------------------------------
		if(rb_component->can_move)	  {
			pos_component->x += rb_component->current_speed.x;
			pos_component->y += rb_component->current_speed.y;
		} else {
			rb_component->current_speed.x = 0;
			rb_component->current_speed.y = 0;
		}
	}
}

void UpdateCollisionSystem() {
	for(int i = 0; i < GetComponentArrayLenght(BOX_COLLIDER); i++) {

		entity_id e_id = GetEntityId(i, BOX_COLLIDER);
		RequireComponents(e_id, POSITION, RIGIDBODY);

		BoxCollider*		box_collider	= GetEntityComponent(e_id, BOX_COLLIDER);
		PositionComponent*	pos_component	= GetEntityComponent(e_id, POSITION);
		RigidbodyComponent* rb_component	= GetEntityComponent(e_id, RIGIDBODY);

		//--------------------------------------------------------------------------------------
		// collisions
		//--------------------------------------------------------------------------------------
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
			PositionComponent* q_pos_component = GetEntityComponent(q_id, POSITION);

			Rectangle q_rect = (Rectangle){
				q_pos_component->x,
				q_pos_component->y,
				q_box_collider->width,
				q_box_collider->height
			};

			Rectangle i_rect = (Rectangle){
				pos_component->x,
				pos_component->y,
				box_collider->width,
				box_collider->height
			};

			//float speed = rb_component->max_speed;

			//// for each step

			//// up
			//for(int step = 0; step = -speed; step++) {

			//}

			//// left
			//for(int step = 0; step = -speed; step++) {
			//	i_rect.x -= 1;


			//}

			//// down
			//for(int step = 0; step = speed; step++) {

			//}

			//// right
			//for(int step = 0; step = speed; step++) {

			//}

			//DrawEntityCollider(e_id);
		}
	}
}

void UpdateControllerSystem() {
	for(int i = 0; i < GetComponentArrayLenght(CONTROLLER); i++) {

		entity_id e_id = GetEntityId(i, CONTROLLER);
		RequireComponents(e_id, POSITION | RIGIDBODY);

		PositionComponent* pos_component = GetEntityComponent(e_id, POSITION);
		RigidbodyComponent* rb_component = GetEntityComponent(e_id, RIGIDBODY);

		//--------------------------------------------------------------------------------------
		// wasd movement + jumping
		//--------------------------------------------------------------------------------------
		float max_speed		= rb_component->max_speed;
		float current_speed = rb_component->current_speed.x;
		bool is_grounded	= rb_component->is_grounded;

		// if we're pressing the right key and the current speed is lower than the max speed
		// we use fabsf to get the absolute float value of the current speed (since the left direction is negative)
		if(left_key  && (fabsf(current_speed) < max_speed)) { rb_component->current_speed.x -= MOVEMENT_ACCELERATION; }
		if(right_key && (fabsf(current_speed) < max_speed)) { rb_component->current_speed.x += MOVEMENT_ACCELERATION; }
		if(jump_key  && is_grounded) { rb_component->current_speed.y -= JUMP_ACCELERATION; }

		TraceLog(LOG_INFO, "speed is: %f", fabsf(current_speed));
	}
}

void UpdateDrawSystem() {
	for(int i = 0; i < GetComponentArrayLenght(DRAW); i++) {

		entity_id e_id = GetEntityId(i, DRAW);
		RequireComponents(e_id, POSITION);

		DrawComponent*	   draw_component	  = GetEntityComponent(e_id, DRAW);
		PositionComponent* position_component = GetEntityComponent(e_id, POSITION);

		//--------------------------------------------------------------------------------------
		// drawing
		//--------------------------------------------------------------------------------------
		DrawTexture(draw_component->texture, (int)position_component->x, (int)position_component->y, RAYWHITE);
	}
}