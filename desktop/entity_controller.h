#pragma once

#include "entity.h"

//--------------------------------------------------------------------------------------
// entity functions
//--------------------------------------------------------------------------------------
// this function returns entity_id because we are actually returning the e_id of the new entity.
// entities don't actually exist as a type; they're just a way to link different components to the same "object"
entity_id CreateEntity();