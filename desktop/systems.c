//#include <math.h>
//#include "systems.h"
//#include "raylib.h"
//#include "entity_controller.h"
//#include "components_controller.h"
//
//#define GRAVITY_ACCELERATION 4.81
//
//// TODO: move these inside the rigidbody component (?)
//// this way every entity can have a different acceleration/deceleration rate
//#define JUMP_ACCELERATION 10
//#define MOVEMENT_ACCELERATION 3
//#define	MAX_FRICTION 5
//#define FRICTION_ACCELERATION 1
//
////--------------------------------------------------------------------------------------
//// local variables
////--------------------------------------------------------------------------------------
//int jump_key	= KEY_SPACE;
//int left_key	= KEY_A;
//int down_key	= KEY_S;
//int right_key	= KEY_D;
//
////--------------------------------------------------------------------------------------
//// systems
////--------------------------------------------------------------------------------------
//
//void UpdateRigidbodySystem() {
//	for(int i = 0; i < GetComponentArrayLenght(RIGIDBODY); i++) {
//
//		entity_id e_id = GetEntityId(i, RIGIDBODY);
//		RequireComponents(e_id, POSITION);
//
//		RigidbodyComponent* rb_component	= GetEntityComponent(e_id, RIGIDBODY);
//		PositionComponent*	pos_component	= GetEntityComponent(e_id, POSITION);
//
//		//--------------------------------------------------------------------------------------
//		// gravity
//		//--------------------------------------------------------------------------------------
//		// if the entity is not grounded, apply gravity
//		if(!rb_component->is_grounded) {
//			// keep track of flight time
//			rb_component->flight_time += GetFrameTime();
//
//			// apply gravity (s = 1/2*g*t^2)
//			rb_component->current_speed.y += ((GRAVITY_ACCELERATION * rb_component->flight_time * rb_component->flight_time)/2);
//		}
//
//		//--------------------------------------------------------------------------------------
//		// x-axis friction
//		//--------------------------------------------------------------------------------------
//		// if we were going to the left
//		if(IsKeyUp(left_key) && rb_component->current_speed.x < 0) {
//			// if we're still applying friction in another direction, set it to 0 since we're not moving in that direction anymore
//			if(rb_component->current_friction < 0) { rb_component->current_friction = 0; }
//
//			// keep track of our current friction
//			rb_component->current_friction += FRICTION_ACCELERATION;
//
//			// check if we're inside our bounds
//			// fabsf return the absolute value of a float
//			if(fabsf(rb_component->current_friction) > MAX_FRICTION) { rb_component->current_friction = MAX_FRICTION; }
//
//			// apply friction
//			rb_component->current_speed.x += rb_component->current_friction;
//
//			// BUT, if the last friction tick changed the direction of the entity, we set its speed to 0.
//			// this means that if while applying friction we're causing a movement in the opposite direction,
//			// we stop the movement (otherwise we'd be going the opposite direction to the initial one, while instead we just want to stop)
//			if(rb_component->current_speed.x > 0) { rb_component->current_speed.x = 0; }
//		}
//
//		// if we were going right
//		if(IsKeyUp(right_key) && rb_component->current_speed.x > 0) {
//			// if we're still applying friction in another direction, set it to 0 since we're not moving in that direction anymore
//			if(rb_component->current_friction > 0) { rb_component->current_friction = 0; }
//
//			// keep track of our current friction
//			rb_component->current_friction -= FRICTION_ACCELERATION;
//
//			// check if we're inside our bounds
//			// fabsf return the absolute value of a float
//			if(fabsf(rb_component->current_friction) > MAX_FRICTION) { rb_component->current_friction = -MAX_FRICTION; }
//
//			// apply friction
//			rb_component->current_speed.x += rb_component->current_friction;
//
//			// BUT, if the last friction tick changed the direction of the entity, we set its speed to 0.
//			// this means that if while applying friction we're causing a movement in the opposite direction,
//			// we stop the movement (otherwise we'd be going the opposite direction to the initial one, while instead we just want to stop)
//			if(rb_component->current_speed.x < 0) { rb_component->current_speed.x = 0; }
//		}
//
//		// if we're standing still, set the friction to 0
//		if(rb_component->current_speed.x == 0) {
//			rb_component->current_friction = 0;
//		}
//
//
//		//--------------------------------------------------------------------------------------
//		// apply movement
//		//--------------------------------------------------------------------------------------
//		if(rb_component->can_move)	  {
//			// movement
//			pos_component->x += rb_component->current_speed.x;
//			pos_component->y += rb_component->current_speed.y;
//		} else {
//			rb_component->current_speed.x = 0;
//			rb_component->current_speed.y = 0;
//		}
//	}
//}
//
//void UpdateCollisionSystem() {
//	for(int i = 0; i < GetComponentArrayLenght(BOX_COLLIDER); i++) {
//
//		entity_id e_id = GetEntityId(i, BOX_COLLIDER);
//		RequireComponents(e_id, POSITION, RIGIDBODY);
//
//		BoxCollider*		box_collider	= GetEntityComponent(e_id, BOX_COLLIDER);
//		PositionComponent*	pos_component	= GetEntityComponent(e_id, POSITION);
//		RigidbodyComponent* rb_component	= GetEntityComponent(e_id, RIGIDBODY);
//
//		//--------------------------------------------------------------------------------------
//		// collisions
//		//--------------------------------------------------------------------------------------
//		// NOTE: we might optimize this by only checking objects which are near the player
//		// 
//		// loop through every rigidbody object to check of they're collding with the upper "i" object
//		for(int q = 0; q < GetComponentArrayLenght(BOX_COLLIDER); q++) {
//
//			// if q == i is true it means that we're checking if the current "i" object
//			// is colliding with itself (since the ids are the same)
//			// we can just skip this and keep looping
//			if(q == i) { continue; }
//
//			entity_id other_entity = GetEntityId(q, BOX_COLLIDER);
//			RequireComponents(other_entity, POSITION);
//
//			BoxCollider* other_collider = GetEntityComponent(other_entity, BOX_COLLIDER);
//			PositionComponent* other_pos_component = GetEntityComponent(other_entity, POSITION);
//
//			Rectangle other_rect = (Rectangle){
//				other_pos_component->x,
//				other_pos_component->y,
//				other_collider->width,
//				other_collider->height
//			};
//
//			Rectangle entity_rect = (Rectangle){
//				pos_component->x,
//				pos_component->y,
//				box_collider->width,
//				box_collider->height
//			};
//
//			// this rectangle will be null if the two boxes are not already colliding
//			// if they are, it means that the rigidbody update was called before the collision system
//			// so we have to move our entity out of the other one
//			Rectangle current_collision_rect = GetCollisionRec(entity_rect, other_rect);
//
//			// TODO: Add collision info
//			// or remove them, I can't currently see any use for them and they only clutter up the component
//
//			float x = pos_component->x;
//			float y = pos_component->y;
//			float e_width = box_collider->width;
//			float e_height = box_collider->height;
//
//			float ox = other_pos_component->x;
//			float oy = other_pos_component->y;
//			float o_width = other_collider->width;
//			float o_height = other_collider->height;
//
//			TraceLog(LOG_INFO, "---------------NEW TICK---------------");
//			TraceLog(LOG_INFO, "ENTITY X: %f", x);
//			TraceLog(LOG_INFO, "ENTITY Y: %f", y);
//			TraceLog(LOG_INFO, "ENTITY WIDTH: %f", e_width);
//			TraceLog(LOG_INFO, "ENTITY HEIGHT: %f", e_height);
//
//			TraceLog(LOG_INFO, "OTHER X: %f", ox);
//			TraceLog(LOG_INFO, "OTHER Y: %f", oy);
//			TraceLog(LOG_INFO, "OTHER WIDTH: %f", o_width);
//			TraceLog(LOG_INFO, "OTHER HEIGHT: %f", o_height);
//
//			TraceLog(LOG_INFO, "COLLISIONRECT X: %f", current_collision_rect.x);
//			TraceLog(LOG_INFO, "COLLISIONRECT Y: %f", current_collision_rect.y);
//			TraceLog(LOG_INFO, "COLLISIONRECT WIDTH: %f", current_collision_rect.width);
//			TraceLog(LOG_INFO, "COLLISIONRECT HEIGHT: %f", current_collision_rect.height);
//
//
//			// is on the left
//			//if(x + e_width < ox) {
//			//	TraceLog(LOG_INFO, "we're on the left");
//			//	pos_component->x -= current_collision_rect.width;
//			//}
//
//			//// is on the right
//			//if(x > ox + o_width) {
//			//	TraceLog(LOG_INFO, "we're on the right");
//			//	pos_component->x += current_collision_rect.width;
//			//}
//
//			//// is up
//			//if(y < oy - o_height) {
//			//	TraceLog(LOG_INFO, "we're on the up");
//			//	pos_component->y -= current_collision_rect.height;
//			//}
//
//			//// is down
//			//if(y - e_height > oy) {
//			//	TraceLog(LOG_INFO, "we're on the down");
//			//	pos_component->y += current_collision_rect.height;
//			//}
//
//			// is on the left
//			if(current_collision_rect.x == ox) {
//				TraceLog(LOG_INFO, "moving to the left");
//				pos_component->x -= current_collision_rect.width;
//			}
//
//			// is on the right
//			if(current_collision_rect.x == x) {
//				TraceLog(LOG_INFO, "moving to the right");
//				pos_component->x += current_collision_rect.width;
//			}
//
//			// is up
//			if(current_collision_rect.y == y) {
//				TraceLog(LOG_INFO, "we're on the up");
//				rb_component->is_grounded = 1;
//				rb_component->current_speed.x = 0;
//				pos_component->y -= current_collision_rect.height;
//			}
//
//			//// is down
//			//if(y - e_height > oy) {
//			//	TraceLog(LOG_INFO, "we're on the down");
//			//	pos_component->y += current_collision_rect.height;
//			//}
//
//			// calculate where our entity is in relation to the other's center
//			// x axis
//
//			//if(pos_component->x + box_collider->width/2 < other_pos_component->x + other_collider->width/2) {
//			//	pos_component->x -= current_collision_rect.width;
//			//} else {
//			//	pos_component->x += current_collision_rect.width;
//			//}
//
//			//// calculate where our entity is in relation to the other's center
//			//// y axis
//			//
//			//if(pos_component->y < other_pos_component->y) {
//			//	pos_component->y -= current_collision_rect.height;
//			//} else {
//			//	pos_component->y += current_collision_rect.height;
//			//}
//
//			DrawEntityCollider(e_id);
//
//			//--------------------------------------------------------------------------------------
//			// grounding
//			//--------------------------------------------------------------------------------------
//			int relative_ground_y = (GetScreenHeight() - box_collider->height);
//
//			// if the entity is touching the ground
//			if(pos_component->y >= relative_ground_y) {
//				// set y pos at the level of the ground;
//				pos_component->y = relative_ground_y;
//				rb_component->current_speed.y = 0;
//
//				// reset rb's flight time
//				rb_component->flight_time = 0;
//
//				// entity's grounded
//				rb_component->is_grounded = true;
//			} else {
//				// otherwise, we're not on the ground
//				rb_component->is_grounded = false;
//			}
//		}
//	}
//}
//
//void UpdateControllerSystem() {
//	for(int i = 0; i < GetComponentArrayLenght(CONTROLLER); i++) {
//
//		entity_id e_id = GetEntityId(i, CONTROLLER);
//		RequireComponents(e_id, POSITION | RIGIDBODY);
//
//		PositionComponent* pos_component = GetEntityComponent(e_id, POSITION);
//		RigidbodyComponent* rb_component = GetEntityComponent(e_id, RIGIDBODY);
//
//		//--------------------------------------------------------------------------------------
//		// wasd movement + jumping
//		//--------------------------------------------------------------------------------------
//		float max_speed		 = rb_component->max_speed.x;
//		float max_jump_speed = rb_component->max_speed.y;
//		float current_speed  = rb_component->current_speed.x;
//		bool  is_grounded	 = rb_component->is_grounded;
//
//		// left and right movement
//		// if we're pressing the right key and the current speed is lower than the max speed
//		// fabsf return the absolute value of a float
//		if(IsKeyDown(left_key)  && (fabsf(current_speed) < max_speed)) { rb_component->current_speed.x -= MOVEMENT_ACCELERATION; }
//		if(IsKeyDown(right_key) && (fabsf(current_speed) < max_speed)) { rb_component->current_speed.x += MOVEMENT_ACCELERATION; }
//
//		// jumping
//		// check if we're pressing the key and we're grounded
//		if(IsKeyDown(jump_key) && is_grounded) {
//			rb_component->current_speed.y -= JUMP_ACCELERATION;
//
//			// if we're going faster than it's allowed on the y axis, set the jump to the max speed
//			// this is not a problem for movements that happen on the y axis other than the jump, since we
//			// only do this if we're grounded
//			// example: if we're using a jump pad, our speed won't be set to the max speed if it's exceeded,
//			// since we're not grounded while we're flying
//			if(fabsf(rb_component->current_speed.y) > max_jump_speed) { rb_component->current_speed.y = -max_jump_speed; }
//		}
//	}
//}
//
//void UpdateDrawSystem() {
//	for(int i = 0; i < GetComponentArrayLenght(DRAW); i++) {
//
//		entity_id e_id = GetEntityId(i, DRAW);
//		RequireComponents(e_id, POSITION);
//
//		DrawComponent*	   draw_component	  = GetEntityComponent(e_id, DRAW);
//		PositionComponent* position_component = GetEntityComponent(e_id, POSITION);
//
//		//--------------------------------------------------------------------------------------
//		// drawing
//		//--------------------------------------------------------------------------------------
//		DrawTexture(draw_component->texture, (int)position_component->x, (int)position_component->y, RAYWHITE);
//	}
//}