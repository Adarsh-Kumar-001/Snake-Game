#include "../include/game.h"
#include "../include/scores.h"

#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>

#define WIDTH  45
#define HEIGHT 25
#define MAX_LENGTH 1000

Snake snake;
coordinates fruit;
uint16_t score; // Range: 0 to 65535
bool running;
bool paused;
char ch;

void initGame(){
    // ncurses FUNCTIONS
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(100); 

    /////////////////////////////////////////////////////////////////
    //                      GAME SETTINGS
    /////////////////////////////////////////////////////////////////

    // SNAKE DEFAULT PROPERTIES
    snake.length = 1;
    snake.direction = 'D'; // Right
    snake.body[0].x = WIDTH/2; // Initial x coordinate of snake at center
    snake.body[0].y = HEIGHT/2; // Initial y coordinate of snake at center

    // FRUIT PROPERTIES
    fruit.x = rand()%(WIDTH-2) + 1; // Random fruit spawn x-coordinate
    fruit.y = rand()%(HEIGHT-2) + 1; // Random fruit spawn y-coordinate

    // MISC.
    running = true;
    paused = false;
    score = 0;
}

void printGame(){
    clear();

    // DISPLAY THE SCORE
    mvprintw(0,(WIDTH/2),"Score: %d",score);

    // PRINTING THE BOARD
    for(int y = 0; y <= HEIGHT+2; y++){
        for(int x = 0; x < WIDTH; x++){
            if(y == 1)  mvprintw(y, x, "_");
            if(x == 0 && y >= 2 && y < HEIGHT)  mvprintw(y, x, "|");
            if(x == WIDTH-1 && y >= 2 && y < HEIGHT)    mvprintw(y, x, "|");
            if(y == HEIGHT+2)   mvprintw(y, x, "-");
            
            // Fixed coordinates
            if(x == 0 && y == HEIGHT)   mvprintw(y, x, "|");
            if(x == 0 && y == HEIGHT+1) mvprintw(y, x, "|");
            if(x == WIDTH-1 && y == HEIGHT) mvprintw(y, x, "|");
            if(x == WIDTH-1 && y == HEIGHT+1)   mvprintw(y, x, "|");
        }
    }

    // PRINTING THE SNAKE
    for (int i=0;i<snake.length;i++){
        if(i==0) mvprintw(snake.body[i].y+2,snake.body[i].x,"@");
        else mvprintw(snake.body[i].y+2,snake.body[i].x,"o");
    }

    // PRINTING THE FRUIT
    mvprintw(fruit.y+2,fruit.x,"+");

    refresh();
}

void updateGame(){
    if (paused) return;

    for (int i=snake.length-1;i>0;i--){
        snake.body[i]=snake.body[i-1];
    }

    switch (snake.direction){
        case 'W': snake.body[0].y--; break;
        case 'S': snake.body[0].y++; break;
        case 'A': snake.body[0].x--; break;
        case 'D': snake.body[0].x++; break;
    }

    if (snake.body[0].x==0 || snake.body[0].x==WIDTH - 1 ||
        snake.body[0].y==-1 || snake.body[0].y==HEIGHT){
        running=0;
    }

    for (int i=1;i<snake.length;i++){
        if (snake.body[0].x==snake.body[i].x && snake.body[0].y==snake.body[i].y){
            running=0;
        }
    }

    if (snake.body[0].x == fruit.x && snake.body[0].y == fruit.y){
        score += 10;
        if (snake.length<MAX_LENGTH)snake.length++;

        fruit.x= rand()%(WIDTH-2)+1;
        fruit.y= rand()%(HEIGHT-2)+1;
    }
}

void directioninput(){
    char dir=getch();
    switch (dir){
        case 'w': 
            if (snake.direction!='S' && snake.direction!='W') snake.direction='W'; 
            break;
        case 's': 
            if (snake.direction!='W' && snake.direction!='S') snake.direction='S';
            break;
        case 'a': 
            if (snake.direction!='D' && snake.direction!='A') snake.direction='A';
            break;
        case 'd':
            if (snake.direction!='A' && snake.direction!='D') snake.direction='D';
            break;
        case 'p': 
            paused=!paused;
            break;
        case 'q':
            running = 0;
            break;
    }
}

void run_game(const char* user){
    do{
        initGame(); // Applies default settings for the game
        while(running){
            printGame(); // Prints Board, Snake and Fruit
            directioninput();
            updateGame();
            usleep(100000);
        }
        endwin();
        printf("\nGame Over! Your Score: %d\n",score);
        updatehighscore(user,score);

        printf("Do you want to play again? (Y/N): ");
        scanf(" %c",&ch);
    }while (ch=='y' || ch == 'Y');

    printf("Exiting the game ...\n");
}