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

void SetEntityCanJump(entity_id e_id, bool can_jump) {
    ControllerComponent* controller = GetEntityComponent(e_id, CONTROLLER);
    controller->can_jump = can_jump;
}