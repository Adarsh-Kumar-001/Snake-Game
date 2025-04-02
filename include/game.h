#ifndef GAME_H
#define GAME_H

#define WIDTH  45
#define HEIGHT 25
#define MAX_LENGTH 1000

typedef struct {
    int x, y;
}coordinates;

typedef struct {
    coordinates body[MAX_LENGTH];
    int length;
    char direction;
}Snake;

extern Snake snake;
extern coordinates fruit;
extern int score;
extern int running;
extern int paused;

void initGame();
void PrintGame();
void updateGame();
void directioninput();
void run_game(const char*);

#endif
