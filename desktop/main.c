#include "main.h"
#include "raylib.h"
#include "screens.h"

#include "components.h"
#include "components_controller.h"

#include "uuid4.h"

//--------------------------------------------------------------------------------------
// forward declare functions
//--------------------------------------------------------------------------------------
void GameLoop(void);

//--------------------------------------------------------------------------------------
// declare variables used by multiple files
//--------------------------------------------------------------------------------------
int		screen_width = 800;
int		screen_height = 450;
int	    should_quit_application;
Screen	current_screen;

//--------------------------------------------------------------------------------------
// main function
//--------------------------------------------------------------------------------------
int main() {
    //--------------------------------------------------------------------------------------
    // initialize
    //--------------------------------------------------------------------------------------

    // register the default components
    REGISTER_COMPONENT(ECPosition, POSITION);
    REGISTER_COMPONENT(ECDraw, DRAW);
    REGISTER_COMPONENT(ECControllable, CONTROLLABLE);
    REGISTER_COMPONENT(ECFriction, FRICTION);
    REGISTER_COMPONENT(ECGravity, GRAVITY);
    REGISTER_COMPONENT(ECBoxCollider, BOX_COLLIDER);
    REGISTER_COMPONENT(ECSpeed, SPEED);

    // initialize the uuid library
    uuid4_init();

    // initialize raylib
    InitWindow(screen_width, screen_height, "platformer");
    SetTargetFPS(60);

    //--------------------------------------------------------------------------------------
    // main loop
    //--------------------------------------------------------------------------------------
    // set the first screen of the game
    // and call its init method
    SetScreen(LOGO);

    // WindowShouldClose() checks whether the escape key or the close button are pressed;
    // shouldExitApplication is used to determine when we want to close the application;
    // (for example, when the exit button in the logo screen is pressed)
    while (!WindowShouldClose() && !should_quit_application) {
        GameLoop();
    }

    //--------------------------------------------------------------------------------------
    // de-initialize
    //--------------------------------------------------------------------------------------
    CloseWindow();                                  // Close window and OpenGL context

    return 0;
}

//--------------------------------------------------------------------------------------
// local function definition
//--------------------------------------------------------------------------------------
void GameLoop() {
    // update current screen
    switch (current_screen) {
    case LOGO: UpdateLogoScreen(); break;
    case ALFA: UpdateAlfaScreen(); break;
    }

    // draw current screen
    BeginDrawing();

        ClearBackground(RAYWHITE);

        switch (current_screen) {
        case LOGO: DrawLogoScreen(); break;
        case ALFA: DrawAlfaScreen(); break;
        }

    EndDrawing();
}

