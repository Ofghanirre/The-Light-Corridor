#ifndef __PARSER_H__
#define __PARSER_H__

#include "structs/graphicObjects.h"

int load_graphic_object(Graphic_Object * result, const char * buffer);

int load_level(const char * file_path);

#endif