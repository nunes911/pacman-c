#ifndef _MAP_H_
#define _MAP_H_

#define HERO 'H'
#define GHOST 'G'
#define EMPTY '.'
#define VERTICAL_WALL '|'
#define HORIZONTAL_WALL '-'
#define PILL 'P'

struct map
{
    char **matrix;
    int lines;
    int columns;
};

typedef struct map MAP;

struct position
{
    int x;
    int y;
};

typedef struct position POSITION;

void free_map(MAP *m);
void read_map(MAP *m);
void allocate_map(MAP *m);
void print_map(MAP *m);
int find_in_the_map(MAP *m, POSITION *p, char c);
int validate_next_position(MAP *m, int x, int y);
int is_empty(MAP *m, int x, int y);
void moving_in_the_map(MAP *m, int x_origin, int y_origin, int x_destiny, int y_destiny);
void copy_map(MAP *destiny_map, MAP *origin_map);
int can_move(MAP *m, char character, int x, int y);
int is_wall(MAP *m, int x, int y);
int is_character(MAP *m, char character, int x, int y);

#endif