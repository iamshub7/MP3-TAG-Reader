#ifndef MP3_H
#define MP3_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ========== VIEW ==========
void view_mp3_data(const char *filename);

// ========== EDIT ==========
void edit_mp3_data(const char *filename, const char *title, const char *artist, const char *album, const char *year, const char *context, const char *comment);

// ========== HELP ==========
void show_help();

#endif // MP3_H
