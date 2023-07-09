#pragma once

// Originally from here: https://github.com/raysan5/raylib/blob/master/examples/text/text_rectangle_bounds.c
// Modified a little for c++
// And for this project

/*******************************************************************************************
*
*   raylib [text] example - Rectangle bounds
*
*   Example originally created with raylib 2.5, last time updated with raylib 4.0
*
*   Example contributed by Vlad Adrian (@demizdor) and reviewed by Ramon Santamaria (@raysan5)
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2018-2023 Vlad Adrian (@demizdor) and Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "rl.h"

// Draw text using font inside rectangle limits
void DrawTextBoxed(
    const char *text,
    Rectangle rec,
    float fontSize,
    float lineSpacing,
    float spacing,
    Color tint
);

