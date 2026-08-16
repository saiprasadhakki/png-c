#include "include/raylib.h"
#include <stdlib.h>
#include <sys/types.h>


#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"


#define RAYLIB_NUKLEAR_IMPLEMENTATION
#include "raylib-nuklear.h"

typedef struct matx {
    float m00, m01, m02;
    float m10, m11, m12;
    float m20, m21, m22;
} matx;

struct nk_colorf bg;

void update_editor(struct nk_context *ctx) {
    UpdateNuklear(ctx);
    if (nk_begin(ctx, "Toolbar - Press \"T\" to toggle", nk_rect(50, 50, 230, 250),
                NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
                NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
    {

    }
    nk_end(ctx);
}

int main() {


    InitWindow(800, 600, "ImageGrayscaler");

    Font font_ui = LoadFontEx("m5x7.ttf", 18, NULL, 0);
    struct nk_context *ctx = InitNuklearEx(font_ui, 18);

    int show_editor = 1;
    SetNuklearScaling(ctx, 1.33);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_T)) { show_editor = !show_editor; }
        if (show_editor) { update_editor(ctx); }
        BeginDrawing();
        ClearBackground(BLANK);
        if (show_editor) DrawNuklear(ctx);
        EndDrawing();
    }

    UnloadNuklear(ctx);
    UnloadFont(font_ui);

}

