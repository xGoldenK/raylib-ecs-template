#include "screens.h"
#include "raygui.h"

//--------------------------------------------------------------------------------------
// global variables declaration
//--------------------------------------------------------------------------------------
int		screen_width;
int		screen_height;
int		should_quit_application;
Screen	current_screen;

//--------------------------------------------------------------------------------------
// function definition
//--------------------------------------------------------------------------------------
// quits the application
void QuitApplication() {
    should_quit_application = true;
}

// sets a new screen without a transition effect
void SetScreen(Screen screen) {
    // dispose current screen
    switch (current_screen) {
    case LOGO:  DisposeLogoScreen(); break;
    case ALFA:  DisposeAlfaScreen(); break;
    }

    // initialize new screen
    switch (screen) {
    case LOGO:  InitLogoScreen(); break;
    case ALFA:  InitAlfaScreen(); break;
    }

    current_screen = screen;
}

// draws a button at the center of the screen
// its width is calculated based on the screen's and the text's width
// its height is a random constant value
// REQUIRES:
//	char* text			: the button's label
//	int heightMargin	: an optional padding from the middle of the screen (+ is down, - is up)
// RETURNS: whether the button is pressed or not
bool DrawCenteredButton(char* text, int height_margin) {
	// we don't want the button to end just beside the text,
	// so we add a padding to make it larger
	int width_padding = 20;

	// default font size is 10;
	// we use a random value for the height of the rectangle, which currently is 24
	Rectangle rectangle = {
		(screen_width - width_padding - MeasureText(text, 10)) / 2,
		(screen_height / 2) + height_margin,
		width_padding + MeasureText(text, 10),
		24
	};

	return GuiButton(rectangle, text);
}

// draws some text at the center of the screen
// its width is calculated based on the screen's and the text's width
// its height is a random constant value
// REQUIRES:
//	char* text			: the button's label
//	int heightMargin	: an optional padding from the middle of the screen (+ is down, - is up)
// RETURNS: void
void DrawCenteredText(char* text, int height_margin) {
	GuiLabel((Rectangle) { (screen_width - MeasureText(text, 10)) / 2, (screen_height / 2) + height_margin, MeasureText(text, 10), 24 }, text);
}