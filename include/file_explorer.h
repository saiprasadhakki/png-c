// WORK IN PROGRESS


#ifndef FILE_EXPLORER_H
#define FILE_EXPLORER_H

#include <stdio.h>

typedef struct file_t {
    FILE *file;
    struct file_t *left;
    struct file_t *right;
    int fd;
} file_t;


#endif
