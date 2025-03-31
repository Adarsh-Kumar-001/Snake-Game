#include "../include/game.h"
#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>

#define WIDTH  45
#define HEIGHT 25
#define MAX_LENGTH 1000

Snake snake;
coordinates fruit;
int score=0;
int running=1; 
int paused=0;

void initGame(){
    initscr();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    timeout(100); 

    snake.length=1;
    snake.direction='D';
    snake.body[0].x=1;
    snake.body[0].y=1;
    fruit.x=rand()%(WIDTH-2)+1;
    fruit.y=rand()%(HEIGHT-2)+1;
}

void PrintGame(){
    clear();
    
    mvprintw(0,(WIDTH/2),"Score: %d",score);
    
    for (int i=0;i<WIDTH;i++)  mvprintw(1,i,"-");
    for (int i=2;i<HEIGHT+2;i++){
        mvprintw(i,0,"|");
        mvprintw(i,WIDTH-1,"|");
    }
    for (int i=0;i<WIDTH;i++)  mvprintw(HEIGHT+2,i,"-");
    
    for (int i=0;i<snake.length;i++){
        if(i==0) mvprintw(snake.body[i].y+2,snake.body[i].x,"@");
        else mvprintw(snake.body[i].y+2,snake.body[i].x,"o");
    }
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
        snake.body[0].y==0 || snake.body[0].y==HEIGHT){
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
            if (snake.direction!='S') snake.direction='W'; 
            break;
        case 's': 
            if (snake.direction!='W') snake.direction='S';
            break;
        case 'a': 
            if (snake.direction!='D') snake.direction='A';
            break;
        case 'd':
            if (snake.direction!='A') snake.direction='D';
            break;
        case 'p': 
            paused=!paused;
            break;
        case 'q':
            running = 0;
            break;
    }
}

int run_game(){
    initGame();
    while (running) {
        PrintGame();
        directioninput();
        updateGame();
        usleep(100000);
    }
    endwin();
    printf("\nGame Over! Your Score: %d\n",score);
    
    return score;
}
