#ifndef __CPARSER_H__
#define __CPARSER_H__

#include "structs/graphicObjects.h"

#define LEVEL_FOLDER "./resources/levels/"

int load_level(const char * file_path, Level * level);

int load_level_loader(const char * file_path, LevelLoader * loader);

#endif