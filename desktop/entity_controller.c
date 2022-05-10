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
    entity_id id = malloc(UUID4_LEN * sizeof(char));
    // fill the array with the id
    uuid4_generate(id);

    return id;
}

void DestroyEntity(entity_id id) {
    // TODO: implement this
}