#include "parser.h"
#include "structs/vectors.h"
#include "structs/colors.h"
#include "structs/figures.h"
#include "structs/graphicObjects.h"
#include "scenery.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int load_vec3D(Vec3D * result, const char * buffer) {
    float x,y,z;
#ifdef __LOGGING__
printf("load_vec3D buffer: %s\n", buffer);
#endif
    if (EOF == sscanf(buffer, "%f %f %f", &x, &y, &z)) {
        return 1;
    };
    *result = (Vec3D){x,y,z};
    return 0;
}

int load_colorsRGBA(ColorRGBA * result, const char * buffer) {
    float r,g,b,a;
#ifdef __LOGGING__
printf("load_colorsRGBA buffer: %s\n", buffer);
#endif
    if (EOF == sscanf(buffer, "%f %f %f %f", &r, &g, &b, &a)) {
        return 1;
    }
    *result = (ColorRGBA){r,g,b,a};
    return 0;
}

int load_figureType(FigureType* result, const char * buffer) {
    char key[128];
#ifdef __LOGGING__
printf("load_figureType buffer: %s\n", buffer);
#endif
    sscanf(buffer, "%s", key);
    if (strstr("RECTANGLE", buffer) != NULL) {
        *result = RECTANGLE;
        return 0;
    }
    if (strstr("CIRCLE", buffer) != NULL) {
        *result = CIRCLE;
        return 0;
    }
    if (strstr("SPHERE", buffer) != NULL) {
        *result = SPHERE;
        return 0;
    }
    if (strstr("LABEL", buffer) != NULL) {
        *result = LABEL;
        return 0;
    } 
    return 1;
}

int load_rectangle(Figure * result, const char * buffer, ColorRGBA color) {
    char point1[1024];
    char point2[1024];
#ifdef __LOGGING__
printf("load_rectangle buffer: %s\n", buffer);
#endif
    if (EOF == sscanf(buffer, "{%[^}]}, {%[^}]}}", point1, point2)) {
        return 1;
    }
    Point3D p1, p2;
    if (load_vec3D(&p1, point1)) return 1;
    if (load_vec3D(&p2, point2)) return 1;
    *result = make_rectangle(p1, p2, color);

    return 0;
}

int load_circle(Figure * result, const char * buffer, ColorRGBA color) {
    float radius;
#ifdef __LOGGING__
printf("load_circle buffer: %s\n", buffer);
#endif
    if (EOF == sscanf(buffer, "{%f}", &radius)) {
        return 1;
    }
    *result = make_circle(radius, color);
    return 0;
}

int load_sphere(Figure * result, const char * buffer, ColorRGBA color) {
    float radius;
#ifdef __LOGGING__
printf("load_sphere buffer: %s\n", buffer);
#endif
    if (EOF == sscanf(buffer, "{%f}", &radius)) {
        return 1;
    }
    *result = make_sphere(radius, color);
    return 0;
}

int load_label(Figure * result, const char * buffer, ColorRGBA color) {
    char text[4096];
    int font_size;
#ifdef __LOGGING__
printf("load_label buffer: %s\n", buffer);
#endif
    if (EOF == sscanf(buffer, "{\"%[^\"], %d}", text, &font_size)) {
        return 1;
    }
    *result = make_label(text, font_size, color);
    return 0;
}

int load_graphic_object(Graphic_Object * result, const char * buffer) {
    char position3D_bfr[256], orientation3D_bfr[256], colorRGBA_bfr[256], figureType_bfr[256], figureData_bfr[5000];
#ifdef __LOGGING__
printf("load_graphic_object buffer: %s\n", buffer);
#endif
    if (EOF == sscanf(buffer, "{%[^}]}, {%[^}]}, {%[^}]}, %[^,], {%[^;];", position3D_bfr, orientation3D_bfr, colorRGBA_bfr, figureType_bfr, figureData_bfr)) {
        memset(position3D_bfr, 0, sizeof(position3D_bfr));
        memset(orientation3D_bfr, 0, sizeof(orientation3D_bfr));
        memset(colorRGBA_bfr, 0, sizeof(colorRGBA_bfr));
        memset(figureType_bfr, 0, sizeof(figureType_bfr));
        return 1;
    }
#ifdef __LOGGING__
printf("\n");
printf("Parse :%s --- %s --- %s --- %s --- %s\n", position3D_bfr, orientation3D_bfr, colorRGBA_bfr, figureType_bfr, figureData_bfr);
#endif 

    Vec3D position3D, orientation3D;
    ColorRGBA colorRGBA;
    FigureType figureType;
    Figure figure;
    int errorParse = 0;

    if (load_vec3D(&position3D, position3D_bfr) 
        | load_vec3D(&orientation3D, orientation3D_bfr) 
        | load_colorsRGBA(&colorRGBA, colorRGBA_bfr) 
        | load_figureType(&figureType, figureType_bfr)) 
    {
        errorParse =1;
    }
    memset(position3D_bfr, 0, sizeof(position3D_bfr));
    memset(orientation3D_bfr, 0, sizeof(orientation3D_bfr));
    memset(colorRGBA_bfr, 0, sizeof(colorRGBA_bfr));
    memset(figureType_bfr, 0, sizeof(figureType_bfr));
    if (errorParse) {
        printf("Out 1\n");
        return 1;
    }
    switch (figureType) {
        case RECTANGLE: {
            if (load_rectangle(&figure, figureData_bfr, colorRGBA)) errorParse = 1;
            break;
        }
        case CIRCLE: {
            if (load_circle(&figure, figureData_bfr, colorRGBA)) errorParse = 1;
            break;
        }
        case SPHERE: {
            if (load_sphere(&figure, figureData_bfr, colorRGBA)) errorParse = 1;
            break;
        }
        case LABEL : {
            if (load_label(&figure, figureData_bfr, colorRGBA)) errorParse = 1;
            break;
        }
        default: {
            return -1;
        }
    }
    memset(figureData_bfr, 0, sizeof(figureData_bfr));
    if (errorParse) {
        printf("Out 2\n");
        return 1;
    }

    *result = (Graphic_Object){position3D, orientation3D, figure};

    return 0;
}

char* parser_getLine(FILE* file) {
    char* line = (char*) malloc(sizeof(char) * 16);
    if (NULL == line) return NULL;
    int capacity = 16;
    int size = 0;
    char c;
    int gotComment = 0;

    while ((c = fgetc(file)) != EOF && c != '\n') {
        if (c == '#') {
            // on ignore le reste de la ligne
            gotComment = 1;
            while ((c = fgetc(file)) != EOF && c != '\n');
            break;
        }
        if (size == capacity) {
            capacity *= 2;
            line = realloc(line, capacity);
            if (!line) {
                return NULL;
            }
        }
        line[size++] = c;
    }

    if (size > 0 || gotComment) {
        line = realloc(line, size + 1);
        if (!line) {
            return NULL;
        }
        line[size] = '\0';
        return line;
    } else {
        free(line);
        return NULL;
    }
}

int load_level_name(char ** result, FILE * istream) {
    char* line = NULL;
    while ((line = parser_getLine(istream)) != NULL) {
        if (strlen(line) != 0) {

            if (*result == NULL)
                *result = (char*) malloc(sizeof(line));
            if (*result == NULL) {
                __FLAG_MEMORY_ERROR__ = 1;
                free(line);
                return MEMORY_ERROR;
            }
            strncpy(*result, line, sizeof(*result)-1);
            free(line);
            #ifdef __LOGGING__
            printf("Level Name : %s\n", *result);
            #endif
            return 0;
        }
        free(line);
    }

    return 1;
}

int load_level_length(int * result, FILE * istream) {
    char* line = NULL;
    while ((line = parser_getLine(istream)) != NULL) {
        if (strlen(line) != 0) {
            if (EOF != sscanf(line, "%d\n", result)) {
                free(line);
                #ifdef __LOGGING__
                printf("Level Length : %d\n", *result);
                #endif
                return 0;
            }
        }
        free(line);
    }

    return 1;
}

int load_level_objects(FILE * istream) {
    char * line;
    while ((line = parser_getLine(istream)) != NULL) {
        if (strlen(line) != 0) {
            #ifdef __LOGGING__
                printf("Line (%d): %s\n", (int) strlen(line), line );
            #endif
            int object_type = 0;
            sscanf(line, "%d:", &object_type);
            char * line2 = strchr(line, '{');

            if (object_type != 1 && object_type != 2) {
                #ifdef __LOGGING__
                    printf("Could not recognized the line as an Obstacle or Bonus (INVALID CODE: %d)\n", object_type);
                #endif
            } else {
                Graphic_Object object;
                if (load_graphic_object(&object, line2)) {
                    #ifdef __LOGGING__
                    printf("Could not load the line as an Obstacle or Bonus : %s\n", line2);
                #endif
                    free(line);
                    continue;
                }
                
                if (object_type == 1) {
                    #ifdef __LOGGING__
                    printf("New Obstacle Loaded:");
                    print_graphic_object(object);
                    #endif
                    scenery_append_obstacle(object);
                } else {
                    #ifdef __LOGGING__
                    printf("New Bonus Loaded:");
                    print_graphic_object(object);
                    #endif
                    scenery_append_bonus(object);
                }
            }
        }
        free(line);
    }

    return 0;
}


int load_level(const char * file_path) {
    FILE * file = fopen(file_path, "r");
    if (NULL == file) {
        return 1;
    }

    char * level_name;
    int level_length;

    load_level_name(&level_name, file);
    load_level_length(&level_length, file);
    load_level_objects(file);
    #ifdef __LOGGING__
    printf("\n");
    print_scenery();
    printf("\n");
    #endif
    fclose(file);
    return 0;
}

