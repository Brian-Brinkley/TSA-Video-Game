/*******************************************************************************************
*
*   Start v0.0.1 - Start Splash Screen
*
*   MODULE USAGE:
*       #define GUI_START_MENU_IMPLEMENTATION
*       #include "gui_Start_Menu.h"
*
*       INIT: GuiStartState state = InitGuiStart();
*       DRAW: GuiStart(&state);
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 The First Binary Initiative. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

#include "raylib.h"

// WARNING: raygui implementation is expected to be defined before including this header
#undef RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <string.h>     // Required for: strcpy()

#ifndef GUI_START_MENU_H
#define GUI_START_MENU_H

typedef struct {
    Vector2 mainAnchor;
    
    bool SplashTextEditMode;
    char SplashTextText[128];
    bool StartGamePressed;

    Rectangle layoutRecs[3];

    // Custom state variables (depend on development software)
    // NOTE: This variables should be added manually if required

} GuiStartState;

#ifdef __cplusplus
extern "C" {            // Prevents name mangling of functions
#endif

//----------------------------------------------------------------------------------
// Defines and Macros
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
// ...

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
GuiStartState InitGuiStart(void);
void GuiStart(GuiStartState *state);

#ifdef __cplusplus
}
#endif

#endif // GUI_START_MENU_H

/***********************************************************************************
*
*   GUI_START_MENU IMPLEMENTATION
*
************************************************************************************/
#if defined(GUI_START_MENU_IMPLEMENTATION)

#include "raygui.h"

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Internal Module Functions Definition
//----------------------------------------------------------------------------------
//...

//----------------------------------------------------------------------------------
// Module Functions Definition
//----------------------------------------------------------------------------------
GuiStartState InitGuiStart(void)
{
    GuiStartState state = { 0 };

    state.mainAnchor = (Vector2){ 0, 0 };
    
    state.SplashTextEditMode = false;
    strcpy(state.SplashTextText, "              Placeholder");
    state.StartGamePressed = false;

    state.layoutRecs[0] = (Rectangle){ state.mainAnchor.x + 12, state.mainAnchor.y + 12, 776, 576 };
    state.layoutRecs[1] = (Rectangle){ state.mainAnchor.x + 272, state.mainAnchor.y + 97, 256, 166 };
    state.layoutRecs[2] = (Rectangle){ state.mainAnchor.x + 272, state.mainAnchor.y + 336, 257, 48 };

    // Custom variables initialization

    return state;
}

void GuiStart(GuiStartState *state)
{
    GuiGroupBox(state->layoutRecs[0], NULL);
    if (GuiTextBox(state->layoutRecs[1], state->SplashTextText, 128, state->SplashTextEditMode)) state->SplashTextEditMode = !state->SplashTextEditMode;
    state->StartGamePressed = GuiButton(state->layoutRecs[2], "Start Game"); 
}

#endif // GUI_START_MENU_IMPLEMENTATION
