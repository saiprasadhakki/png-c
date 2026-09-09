// WORK IN PROGRESS


#ifndef FILE_EXPLORER_H
#define FILE_EXPLORER_H

#include <stdio.h>
#include "raylib.h"

#if defined (__linux__)
#include <unistd.h>
/* later use getenv() to open in home dir */
#define CWD_STR         getcwd(cwd_buf, 64)
#endif

typedef _Bool b8 ;
typedef unsigned int u32 ;

extern char cwd_buf[64];
extern struct nk_context *file_ctx;
extern Font explorer_font;

typedef struct file_t {
    u32 num_file;
    FILE **file; /* array of file pointers/file ids*/
    struct file_t **C;
    b8 leaf;
} file_t;


void get_cwd(void);

void open_explorer(void);
void render_explorer(void);
void update_explorer(void);
void clean_explorer(void);

#endif
