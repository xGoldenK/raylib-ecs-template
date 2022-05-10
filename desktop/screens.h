#pragma once

#include <stdbool.h>

#define RAYGUI_IMPLEMENTATION

//--------------------------------------------------------------------------------------
// types and structure definition
//--------------------------------------------------------------------------------------
typedef enum Screen { LOGO, ALFA } Screen;

//--------------------------------------------------------------------------------------
// declare variables used by multiple files
//--------------------------------------------------------------------------------------
int		screen_width;
int		screen_height;
Screen	current_screen;
bool	should_quit_application;

//--------------------------------------------------------------------------------------
// drawing utilities
//--------------------------------------------------------------------------------------
bool DrawCenteredButton		(char* text, int height_margin);
void DrawCenteredText		(char* text, int height_margin);

//--------------------------------------------------------------------------------------
// screen management
//--------------------------------------------------------------------------------------
void QuitApplication		();
void TransitionToScreen		(Screen screen);
void SetScreen				(Screen screen);            // NOTE: This function changes the screen without the transition effect

//--------------------------------------------------------------------------------------
// logo screen
//--------------------------------------------------------------------------------------
void InitLogoScreen			();
void UpdateLogoScreen		();
void DrawLogoScreen			();
void DisposeLogoScreen		();

//--------------------------------------------------------------------------------------
// alfa screen
//--------------------------------------------------------------------------------------
void InitAlfaScreen			();
void UpdateAlfaScreen		();
void DrawAlfaScreen			();
void DisposeAlfaScreen		();