#include "include/raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "tinyfiledialog/tinyfiledialogs.h"


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
char * curr_image_filepath;
char const * lFilterPatterns[2] = { "*.png", "*.json" };
int image_selected = 0;
int image_loaded = 0;
Image image_showing;
Texture2D image_texture;

void update_editor(struct nk_context *ctx) {
    UpdateNuklear(ctx);
    if (nk_begin(ctx, "Toolbar - Press \"T\" to toggle", nk_rect(50, 50, 230, 250),
                NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
                NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
    {

        nk_layout_space_begin(ctx, NK_STATIC, 500, 64);
        
        nk_layout_space_push(ctx, nk_rect(0,0,150,500));
        if (nk_group_begin(ctx, "Recent", NK_WINDOW_BORDER)) {
            static nk_bool selected;
            nk_layout_row_static(ctx, 18, 100, 1);
            nk_selectable_label(ctx, selected ? "selected" : "unselected", NK_TEXT_CENTERED, &selected);
            if (selected && image_selected) {
                // UnloadImage(image_showing);
                UnloadTexture(image_texture);
                image_selected = 0;
                image_loaded = 0;
            }
            if (selected) {
                curr_image_filepath = tinyfd_openFileDialog("Select a PNG file", "./", 2, lFilterPatterns, "image files", 1);
                selected = 0;
            }
            if (curr_image_filepath) {
                image_selected = 1;
            }
            // if (!selected) {
            //     image_selected = 0;
            // }
            if (!curr_image_filepath) {
                selected = 0;
            }
            nk_group_end(ctx);
        }
        nk_layout_space_end(ctx);
    }
    nk_end(ctx);
}

int main() {


    InitWindow(800, 600, "ImageGrayscaler");

    Font font_ui = LoadFontEx("m5x7.ttf", 18, NULL, 0);
    struct nk_context *ctx = InitNuklearEx(font_ui, 18);

    int show_editor = 1;
    SetNuklearScaling(ctx, 1.33);

    unsigned char *current_image;

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_T)) { show_editor = !show_editor; }
        if (show_editor) { update_editor(ctx); }
        if (image_selected && !image_loaded) {
            // image_showing = LoadImage(curr_image_filepath);
            // image_texture = LoadTextureFromImage(image_showing);
            image_texture = LoadTexture(curr_image_filepath);
            image_loaded = 1;
        }
        BeginDrawing();
        ClearBackground(BLANK);
        if (image_selected) {
            // DrawTexture(image_texture, 0, 0, WHITE);
            DrawTexturePro(image_texture, (Rectangle) { 0, 0, image_texture.width, image_texture.height }, (Rectangle) {0, 0, 800, 600}, (Vector2) { 0, 0 }, 0, WHITE);
        } else {
            DrawTextEx(font_ui, "NO IMAGE SELECTED - PRESS T TO TOGGLE TOOLBAR", (Vector2){100, 100}, 30, 1, WHITE);
        }
        if (show_editor) DrawNuklear(ctx);
        EndDrawing();
    }

    // UnloadImage(image_showing);
    UnloadTexture(image_texture);
    UnloadNuklear(ctx);
    UnloadFont(font_ui);

}

