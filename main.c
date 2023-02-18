#include <stdio.h>
#include <stdlib.h>
#include "time.h"
#include "pacman.h"
#include "map.h"
#include "ui.h"

MAP m;
POSITION hero;
int has_pill = 0;

int ghost_random_move(int current_x, int current_y, int *destination_x, int *destination_y)
{
	int options[4][2] = {
		{current_x + 1, current_y},
		{current_x - 1, current_y},
		{current_x, current_y + 1},
		{current_x, current_x - 1}};

	srand(time(0));
	for (int i = 0; i < 10; i++)
	{
		int position = rand() % 4;
		if (can_move(&m, GHOST, options[position][0], options[position][1]))
		{
			*destination_x = options[position][0];
			*destination_y = options[position][1];

			return 1;
		}
	}

	return 0;
}

void ghost()
{
	MAP copied_map;
	copy_map(&copied_map, &m);

	for (int i = 0; i < m.lines; i++)
	{
		for (int j = 0; j < m.columns; j++)
		{
			if (copied_map.matrix[i][j] == GHOST)
			{
				int destination_x;
				int destination_y;

				int found = ghost_random_move(i, j, &destination_x, &destination_y);
				if (found)
				{
					moving_in_the_map(&m, i, j, destination_x, destination_y);
				}
			}
		}
	}
	free_map(&copied_map);
}

int finish()
{
	POSITION pos;
	return !find_in_the_map(&m, &pos, HERO);
}

int is_direction(char direction)
{
	return direction == LEFT || direction == DOWN || direction == RIGHT || direction == UP;
}

void move(char direction)
{
	if (!is_direction(direction))
		return;

	int next_x = hero.x;
	int next_y = hero.y;

	switch (direction)
	{
	case LEFT:
		next_y--;
		break;
	case UP:
		next_x--;
		break;
	case RIGHT:
		next_y++;
		break;
	case DOWN:
		next_x++;
		break;
	}

	if (!can_move(&m, HERO, next_x, next_y))
		return;

	if (is_character(&m, PILL, next_x, next_y))
	{
		has_pill = 1;
	}

	moving_in_the_map(&m, hero.x, hero.y, next_x, next_y);
	hero.x = next_x;
	hero.y = next_y;
}

void explode_bomb()
{
	if (!has_pill) return;

	explode_axis(hero.x, hero.y, 0, 1, 3);
	explode_axis(hero.x, hero.y, 0, -1, 3);
	explode_axis(hero.x, hero.y, 1, 0, 3);
	explode_axis(hero.x, hero.y, -1, 0, 3);

	has_pill = 0;
}

void explode_axis(int x, int y, int sum_x, int sum_y, int quantity)
{
	if (quantity == 0) return;

	int new_x = x + sum_x;
	int new_y = y + sum_y;

	if (!validate_next_position(&m, new_x, new_y)) return;
	if (is_wall(&m, new_x, new_y)) return;

	m.matrix[new_x][new_y] = EMPTY;
	explode_axis(new_x, new_y, sum_x, sum_y, quantity - 1);
}

int main()
{
	read_map(&m);
	find_in_the_map(&m, &hero, HERO);

	do
	{
		printf("Have pill: %s\n", (has_pill ? "YES" : "NO"));
		print_map(&m);

		char command;
		scanf(" %c", &command);
		move(command);

		if (command == BOMB) explode_bomb();

		ghost();

	} while (!finish());

	free_map(&m);
}