#include "raygui.h"
#include "screens.h"

#include "components.h"
#include "components_controller.h"

//--------------------------------------------------------------------------------------
// declare local variables
//--------------------------------------------------------------------------------------
const char* PLAY_TEXT = "Play";
const char* QUIT_TEXT = "Quit";

bool is_play_button_pressed;
bool is_exit_button_pressed;

//--------------------------------------------------------------------------------------
// local function definition
//--------------------------------------------------------------------------------------
void InitLogoScreen() {

}

void UpdateLogoScreen() {

	if (is_play_button_pressed) { SetScreen(ALFA); }
	if (is_exit_button_pressed) { QuitApplication(); }

}

void DrawLogoScreen() {

	DrawCenteredText("Main Menu", -32);

	is_play_button_pressed = DrawCenteredButton(PLAY_TEXT, 0);
	is_exit_button_pressed = DrawCenteredButton(QUIT_TEXT, 32);

}

void DisposeLogoScreen() {

}