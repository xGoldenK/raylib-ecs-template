#include "systems.h"
#include "raylib.h"
#include "components_controller.h"

#define GRAVITY_ACCELERATION 9.81

//--------------------------------------------------------------------------------------
// local variables
//--------------------------------------------------------------------------------------
int movement_speed = 10;

//--------------------------------------------------------------------------------------
// systems
//--------------------------------------------------------------------------------------
// NOTE: we might have to implement a function to quickly check if an entity has another component
// maybe add a dependency system -> a component needs another -> if the entity doesn't have one, add it
// if we try to add the same component in another function, don't add it the second time

// NOTE: we might have to move some systems on their own
void UpdatePositionSystem() {
	for(int i = 0; i < GetComponentArrayLenght(POSITION); i++) {
		entity_id e_id = GetEntityId(i, POSITION);
		PositionComponent* pos_component = GetEntityComponent(e_id, POSITION);

		//--------------------------------------------------------------------------------------
		// controls
		//--------------------------------------------------------------------------------------
		if(EntityHasComponent(e_id, CONTROLLER)) {
			if(IsKeyDown(KEY_W)) { pos_component->y -= movement_speed; }
			if(IsKeyDown(KEY_A)) { pos_component->x -= movement_speed; }
			if(IsKeyDown(KEY_S)) { pos_component->y += movement_speed; }
			if(IsKeyDown(KEY_D)) { pos_component->x += movement_speed; }
		}

		//--------------------------------------------------------------------------------------
		// gravity
		//--------------------------------------------------------------------------------------
		if(EntityHasComponent(e_id, DRAW)) {
			DrawComponent* draw_component = GetEntityComponent(e_id, DRAW);

			// if the entity is grounded
			int relative_ground_y = (GetScreenHeight() - draw_component->texture.height);

			// if the texture is under the ground
			if(pos_component->y >= relative_ground_y) {

				// set its y at the level of the ground -> it's grounded;
				// reset its flight time
				pos_component->y = relative_ground_y;
				pos_component->flight_time = 0;
			} else {
				// keep track of flight time and apply gravity
				pos_component->flight_time += GetFrameTime();

				// gravity displacement: (g*t^2)/2
				pos_component->y += (GRAVITY_ACCELERATION * pos_component->flight_time * pos_component->flight_time) / 2;
			}
		}
	}
}

void UpdateDrawSystem() {
	for(int i = 0; i < GetComponentArrayLenght(DRAW); i++) {
		DrawComponent* draw_component = GetComponentAtIndex(i, DRAW);
		if(!EntityHasComponent(draw_component->id, POSITION)) { continue; }

		PositionComponent* position_component = GetEntityComponent(draw_component->id, POSITION);
		DrawTexture(draw_component->texture, position_component->x, position_component->y, RAYWHITE);
	}
}