// WORK IN PROGRESS

#include "file_explorer.h"
#include <stdio.h>
#include "nuklear.h"
#include "raylib-nuklear.h"
#include "raylib.h"

struct nk_context *file_ctx;
Font explorer_font;

char cwd_buf[64];
void get_cwd(void) {
    printf("%s\n", CWD_STR);
}

void update_explorer(void) {
    UpdateNuklear(file_ctx);
    // do stuff
    if (nk_begin(file_ctx, "Explorer", nk_rect(50, 50, 230, 250),
                NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|NK_WINDOW_TITLE|NK_WINDOW_MINIMIZABLE
                )) {

    }
    nk_end(file_ctx);
}

void render_explorer(void) {
    DrawNuklear(file_ctx);
}

void open_explorer(void) {
    explorer_font = LoadFontEx("./m5x7.ttf", 18, NULL, 0);
    file_ctx = InitNuklearEx(explorer_font, 18);
}

void clean_explorer(void) {
    UnloadNuklear(file_ctx);
    UnloadFont(explorer_font);
}
