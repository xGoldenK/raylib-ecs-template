#include "entity.h"

//--------------------------------------------------------------------------------------
// entity functions
//--------------------------------------------------------------------------------------
//char* CreateEntity() {
//    // uuid4 (external library) is used to generate the ids.
//    // we have to automatically allocate memory otherwise the pointer is disposed of
//    // as the function returns.
//    char* e_id = malloc(UUID4_LEN*sizeof(char));
//    // fill the array with the e_id
//    uuid4_generate(e_id);
//
//    return e_id;
//}
//
//void DestroyEntity(char* e_id) {
//    if(EntityHasComponent(e_id, POSITION)) {
//
//    }
//}