#include "entity_controller.h"
#include "raylib.h"
#include "malloc.h"
#include "uuid4.h"
#include "components_controller.h"

//--------------------------------------------------------------------------------------
// entity functions
//--------------------------------------------------------------------------------------
entity_id CreateEntity() {
    // uuid4 (external library) is used to generate the ids.
    // we have to automatically allocate memory otherwise the pointer is disposed of
    // as the function returns.
    entity_id e_id = malloc(UUID4_LEN * sizeof(char));
    // fill the array with the e_id
    uuid4_generate(e_id);

    return e_id;
}

void DestroyEntity(entity_id e_id) {
    // TODO: implement this
}

void DrawEntityCollider(entity_id e_id) {
	PositionComponent* pos = GetEntityComponent(e_id, POSITION);
	BoxCollider* collider = GetEntityComponent(e_id, BOX_COLLIDER);

    float padding = 1.5;

    // up
    DrawLine(pos->x - padding,
             pos->y - padding,
             pos->x + collider->width,
             pos->y - padding,
             RED);

    // left
	DrawLine(pos->x - padding,
             pos->y - padding,
             pos->x - padding,
             pos->y + collider->height + padding,
             RED);

    // down
	DrawLine(pos->x + collider->width + padding,
             pos->y + collider->height + padding,
             pos->x - padding,
             pos->y + collider->height + padding,
             RED); 
    // right
	DrawLine(pos->x + collider->width  + padding,
             pos->y + collider->height + padding,
             pos->x + collider->width  + padding,
             pos->y - padding,
             RED);
}