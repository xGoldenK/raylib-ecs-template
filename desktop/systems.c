#include "systems.h"
#include "raylib.h"
#include "components_controller.h"

// NOTE: we might have to implement a function to quickly check if an entity has another component
// maybe add a dependency system -> a component needs another -> if the entity doesn't have one, add it
// if we try to add the same component in another function, don't add it the second time

void UpdatePositionSystem() {

}

void UpdateDrawSystem() {
	for(int i = 0; i < GetComponentArrayLenght(DRAW); i++) {
		DrawComponent* draw_component = GetComponentAtIndex(i, DRAW);
		if(!EntityHasComponent(draw_component->id, POSITION)) { continue; }

		PositionComponent* position_component = GetEntityComponent(draw_component->id, POSITION);
		DrawTexture(draw_component->texture, position_component->x, position_component->y, RAYWHITE);
	}
}