#include "map.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void copy_map(MAP *destiny_map, MAP *origin_map)
{
    destiny_map->lines = origin_map->lines;
    destiny_map->columns = origin_map->columns;

    allocate_map(destiny_map);

    for (int i = 0; i < origin_map->lines; i++)
    {
        strcpy(destiny_map->matrix[i], origin_map->matrix[i]);
    }
}


int validate_next_position(MAP *m, int x, int y)
{
    if (x >= m->lines)
        return 0;
    if (y >= m->columns)
        return 0;

    return 1;
}


int is_empty(MAP *m, int x, int y)
{
    return m->matrix[x][y] == EMPTY;
}


void moving_in_the_map(MAP *m, int x_origin, int y_origin, int x_destiny, int y_destiny)
{
    char character = m->matrix[x_origin][y_origin];
    m->matrix[x_destiny][y_destiny] = character;
    m->matrix[x_origin][y_origin] = EMPTY;
}


int find_in_the_map(MAP *m, POSITION *p, char c)
{
    for (int i = 0; i < m->lines; i++)
    {
        for (int j = 0; j < m->columns; j++)
        {
            if (m->matrix[i][j] == c)
            {
                p->x = i;
                p->y = j;
                return 1;
            }
        }
    }
    return 0;
}


void allocate_map(MAP *m)
{
    // alocando memória dinamicamente de uma matriz
    m->matrix = malloc(sizeof(char *) * m->lines);

    for (int i = 0; i < m->lines; i++)
    {
        m->matrix[i] = malloc(sizeof(char) * (m->columns + 1));
    }
}


void free_map(MAP *m)
{
    // liberando memoria que foi alocada para a matriz
    for (int i = 0; i < m->lines; i++)
    {
        free(m->matrix[i]);
    }
    free(m->matrix);
}


void read_map(MAP *m)
{
    FILE *f;
    f = fopen("map.txt", "r");
    if (f == 0)
    {
        printf("Erro na leitura do mapa.\n");
        exit(1);
    }

    fscanf(f, "%d %d", &m->lines, &m->columns);

    allocate_map(m);

    for (int i = 0; i < m->lines; i++)
    {
        fscanf(f, "%s", m->matrix[i]);
    }

    fclose(f);
}


int is_wall(MAP *m, int x, int y)
{
    return m->matrix[x][y] == VERTICAL_WALL ||
           m->matrix[x][y] == HORIZONTAL_WALL;
}


int is_character(MAP *m, char character, int x, int y)
{
    return m->matrix[x][y] == character;
}


int can_move(MAP *m, char character, int x, int y)
{
    return validate_next_position(m, x, y) &&
           !is_wall(m, x, y) &&
           !is_character(m, character, x, y);
}