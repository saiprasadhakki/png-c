#include "file_explorer.h"
#include "glad/glad.h"
#include "include/raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include "tinyfiledialog/tinyfiledialogs.h"


#if defined (__linux__)
#define STB_IMAGE_IMPLEMENTATION
#endif
#include "stb/stb_image.h"

#if defined (__linux__)
#define STB_IMAGE_WRITE_IMPLEMENTATION
#endif
#include "stb/stb_image_write.h"


#define RAYLIB_NUKLEAR_IMPLEMENTATION
#include "raylib-nuklear.h"

#include "defines.h"
// #include "glad.h"


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
                NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|NK_WINDOW_TITLE|NK_WINDOW_MINIMIZABLE
                ))
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

float vertices[] = {
     1,  1, 0,   1, 1,
    -1,  1, 0,   0, 1,
    -1, -1, 0,   0, 0,
     1, -1, 0,   1, 0
};

u32 texcoord[] = {
    1, 1,
    0, 1,
    0, 0,
    1, 0
};

u32 indices[] = {
    0, 1, 2,
    0, 2, 3
};

u32 image_vbo;
u32 image_ebo;
u32 image_vao;

void init_buffers(u32 *vbo, u32 *ebo, u32 *vao) {
    glGenBuffers(1, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, *vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glGenVertexArrays(1, vao);
    glBindVertexArray(*vao);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_UNSIGNED_INT, GL_TRUE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void clean_buffers(u32 *vbo, u32 *ebo, u32 *vao) {
    glDeleteBuffers(1, vbo);
    glDeleteBuffers(1, ebo);
    glDeleteVertexArrays(1, vao);
}

u32 load_texture_glad(const char *filename) {
    u32 texid;
    glGenTextures(1, &texid);
    glBindTexture(GL_TEXTURE_2D, texid);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int w, h, nc;

    u8 *data = stbi_load(filename, &w, &h, &nc, 0);
    if (data) {
        GLenum format = (nc == 4) ? GL_RGBA : GL_RGB;
        glTexImage2D(GL_TEXTURE_2D, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else {
        printf("ERR: unable to load textures\n");
    }

    free(data);
    return texid;
}



void draw_texture_glad(u32 textureid) {
    glBindTexture(GL_TEXTURE_2D, textureid);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}


int main() {

            


    get_cwd();
    InitWindow(800, 600, "PNG-C");

    if (!gladLoadGLLoader((GLADloadproc)GetWindowHandle())) {
        printf("ERROR: glad not loaded\n");
    }

    init_buffers(&image_vbo, &image_ebo, &image_vao);

    Font font_ui = LoadFontEx("m5x7.ttf", 18, NULL, 0);
    struct nk_context *ctx = InitNuklearEx(font_ui, 18);

    int show_editor = 1;
    SetNuklearScaling(ctx, 1.33);

    unsigned char *current_image;
    open_explorer();

    u32 textureglad = load_texture_glad("./rod_blue.png");
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    while (!WindowShouldClose()) {
        if (IsKeyPressed(KEY_T)) { show_editor = !show_editor; }
        if (show_editor) { update_editor(ctx); }
        if (image_selected && !image_loaded) {
            // image_showing = LoadImage(curr_image_filepath);
            // image_texture = LoadTextureFromImage(image_showing);
            // image_showing = LoadImageFromMemory("", const unsigned char *fileData, int dataSize)
            image_texture = LoadTexture(curr_image_filepath);
            image_loaded = 1;
        }
        update_explorer();
        BeginDrawing();
        ClearBackground(BLANK);
        if (image_selected) {
            // DrawTexture(image_texture, 0, 0, WHITE);
            DrawTexturePro(image_texture, (Rectangle) { 0, 0, image_texture.width, image_texture.height }, (Rectangle) {0, 0, 800, 600}, (Vector2) { 0, 0 }, 0, WHITE);
        } else {
            DrawTextEx(font_ui, "NO IMAGE SELECTED - PRESS T TO TOGGLE TOOLBAR", (Vector2){100, 100}, 30, 1, WHITE);
            glBindVertexArray(image_vao);
            glBindTexture(GL_TEXTURE_2D, textureglad);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        }
        if (show_editor) DrawNuklear(ctx);
        render_explorer();
        EndDrawing();
    }

    // UnloadImage(image_showing);
    clean_explorer();
    UnloadTexture(image_texture);
    UnloadNuklear(ctx);
    UnloadFont(font_ui);
    glDeleteProgram(textureglad);
    clean_buffers(&image_vbo, &image_ebo, &image_vao);

}

