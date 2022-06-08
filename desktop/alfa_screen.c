#include "raylib.h"
#include "screens.h"
#include "entity_controller.h"
#include "components_controller.h"
#include "systems.h"

//--------------------------------------------------------------------------------------
// local variable declaration
//--------------------------------------------------------------------------------------
entity_id character;
entity_id character2;

void InitAlfaScreen() {
	InitializeComponentArrays();

	character = CreateEntity();
	character2 = CreateEntity();

	TraceLog(LOG_INFO, "character is %s", character);
	ECSpeed* c = CreateComponent(character, ECSpeed, SPEED);
	ECSpeed* c2 = CreateComponent(character2, ECSpeed, SPEED);

	StoreComponent(c, ECSpeed);
	StoreComponent(c2, ECSpeed);

	ComponentArray comp_array = GetComponentArray(SPEED);
	TraceLog(LOG_INFO, "capacity is %i", comp_array.capacity);
	TraceLog(LOG_INFO, "first free space index is %i", GetComponentArrayFreeSpaceIndex(SPEED));

	/*ECSpeed* speed_components = (ECSpeed*) component_arrays[SPEED].buffer;*/
	//TraceLog(LOG_INFO, "array id is %s", (speed_components + 1)->base.e_id);
	//TraceLog(LOG_INFO, "array id is %s", (speed_components)->base.e_id);*/

	ECSpeed* speed_components = GetComponents(SPEED);
	TraceLog(LOG_INFO, "array id is %s", (speed_components)->base.e_id);
	TraceLog(LOG_INFO, "array id is %s", (speed_components + 1)->base.e_id);

	TraceLog(LOG_INFO, "character2 is %s", character2);

}

void UpdateAlfaScreen() {

}

void DrawAlfaScreen() {

}

void DisposeAlfaScreen() {
	// NOTE: add dispose methods for components/entities
	// https://prdeving.wordpress.com/2018/06/27/videogames-programming-ecs-system-in-plain-c/
}