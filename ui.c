#include <stdio.h>
#include "map.h"
// #include "ui.h"

char ghost_draw[4][7] = {
    {" .-.  " },
    {"| OO| " },
    {"|   | " },
    {"'^^^' " }
};

char wall_draw[4][7] = {
    {"......" },
    {"......" },
    {"......" },
    {"......" }
};

char hero_draw[4][7] = {
    {" .--. "  },
    {"/ _.-'"  },
    {"\\  '-." },
    {" '--' "  }
};

char pill_draw[4][7] = {
    {"      "},
    {" .-.  "},
    {" '-'  "},
    {"      "}
};

char empty_draw[4][7] = {
    {"      "},
    {"      "},
    {"      "},
    {"      "}
};

void print_part(char draw[4][7], int part)
{
    printf("%s", draw[part]);
}


void print_map(MAP *m)
{
    for (int i = 0; i < m->lines; i++)
    {
        for (int part = 0; part < 4; part++)
        {
            for (int j = 0; j < m->columns; j++)
            {
                switch (m->matrix[i][j])
                {
                    case GHOST:
                        print_part(ghost_draw, part);
                        break;

                    case HERO:
                        print_part(hero_draw, part);
                        break;

                    case PILL:
                        print_part(pill_draw, part);
                        break;

                    case VERTICAL_WALL:
                    case HORIZONTAL_WALL:
                        print_part(wall_draw, part);
                        break;

                    case EMPTY:
                        print_part(empty_draw, part);
                        break;
                }
            }
            printf("\n");
        }
    }
}