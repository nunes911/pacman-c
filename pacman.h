#ifndef _PACMAN_H_
#define _PACMAN_H_

#define UP 'w'
#define DOWN 's'
#define RIGHT 'd'
#define LEFT 'a'
#define BOMB 'b'


int finish();
void move(char direction);
int is_direction(char direction);
void ghost();
int ghost_random_move(int current_x, int current_y, int *destination_x, int *destination_y);
void explode_axis(int x, int y, int sum_x, int sum_y, int quantity);
void explode_bomb();

#endif