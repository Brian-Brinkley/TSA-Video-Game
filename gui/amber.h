//////////////////////////////////////////////////////////////////////////////////
//                                                                              //
// StyleAsCode exporter v2.0 - Style data exported as a values array            //
//                                                                              //
// USAGE: On init call: GuiLoadStyleAmber();                                   //
//                                                                              //
// more info and bugs-report:  github.com/raysan5/raygui                        //
// feedback and support:       ray[at]raylibtech.com                            //
//                                                                              //
// Copyright (c) 2020-2025 raylib technologies (@raylibtech)                    //
//                                                                              //
//////////////////////////////////////////////////////////////////////////////////

#define AMBER_STYLE_PROPS_COUNT  18

// Custom style name: Amber
static const GuiStyleProp amberStyleProps[AMBER_STYLE_PROPS_COUNT] = {
    { 0, 0, (int)0x898988ff },    // DEFAULT_BORDER_COLOR_NORMAL 
    { 0, 1, (int)0x292929ff },    // DEFAULT_BASE_COLOR_NORMAL 
    { 0, 2, (int)0xd4d4d4ff },    // DEFAULT_TEXT_COLOR_NORMAL 
    { 0, 3, (int)0xeb891dff },    // DEFAULT_BORDER_COLOR_FOCUSED 
    { 0, 4, (int)0x292929ff },    // DEFAULT_BASE_COLOR_FOCUSED 
    { 0, 5, (int)0xffffffff },    // DEFAULT_TEXT_COLOR_FOCUSED 
    { 0, 6, (int)0xf1cf9dff },    // DEFAULT_BORDER_COLOR_PRESSED 
    { 0, 7, (int)0xf39333ff },    // DEFAULT_BASE_COLOR_PRESSED 
    { 0, 8, (int)0x191410ff },    // DEFAULT_TEXT_COLOR_PRESSED 
    { 0, 9, (int)0x6a6a6aff },    // DEFAULT_BORDER_COLOR_DISABLED 
    { 0, 10, (int)0x818181ff },    // DEFAULT_BASE_COLOR_DISABLED 
    { 0, 11, (int)0x606060ff },    // DEFAULT_TEXT_COLOR_DISABLED 
    { 0, 16, (int)0x00000010 },    // DEFAULT_TEXT_SIZE 
    { 0, 18, (int)0xef922aff },    // DEFAULT_LINE_COLOR 
    { 0, 19, (int)0x333333ff },    // DEFAULT_BACKGROUND_COLOR 
    { 0, 20, (int)0x00000018 },    // DEFAULT_TEXT_LINE_SPACING 
    { 1, 8, (int)0xe7e0d4ff },    // LABEL_TEXT_COLOR_PRESSED 
    { 4, 8, (int)0xf1cf9dff },    // SLIDER_TEXT_COLOR_PRESSED 
};

// Style loading function: Amber
static void GuiLoadStyleAmber(void)
{
    // Load style properties provided
    // NOTE: Default properties are propagated
    for (int i = 0; i < AMBER_STYLE_PROPS_COUNT; i++)
    {
        GuiSetStyle(amberStyleProps[i].controlId, amberStyleProps[i].propertyId, amberStyleProps[i].propertyValue);
    }
}
