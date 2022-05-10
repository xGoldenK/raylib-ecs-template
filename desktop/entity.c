#include "entity.h"

//--------------------------------------------------------------------------------------
// entity functions
//--------------------------------------------------------------------------------------
//char* CreateEntity() {
//    // uuid4 (external library) is used to generate the ids.
//    // we have to automatically allocate memory otherwise the pointer is disposed of
//    // as the function returns.
//    char* id = malloc(UUID4_LEN*sizeof(char));
//    // fill the array with the id
//    uuid4_generate(id);
//
//    return id;
//}
//
//void DestroyEntity(char* id) {
//    if(EntityHasComponent(id, POSITION)) {
//
//    }
//}