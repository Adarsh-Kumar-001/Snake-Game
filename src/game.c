#include "../include/game.h"
#include "../include/scores.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdint.h>

#define WIDTH  45
#define HEIGHT 25
#define MAX_LENGTH 1000 // max length of snake body

Snake snake;
coordinates fruit;
uint16_t score; // Range: 0 to 65535
bool running;
bool paused;

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
    snake.direction = 'l'; // Right
    snake.body[0].x = WIDTH/2; // Initial x coordinate of snake at center
    snake.body[0].y = HEIGHT/2; // Initial y coordinate of snake at center

    // FRUIT PROPERTIES
    srand(time(NULL));
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
    if(paused) return;

    /////////////////////////////////////////////////////////////
    //                      UPDATE SNAKE
    /////////////////////////////////////////////////////////////

    // MAKE THE BODY ELEMENT FOLLOW ITS LEADING ELEMENT
    for(int i = snake.length-1; i > 0; i--)
        snake.body[i] = snake.body[i-1];

    // SET THE NEW SNAKE HEAD DIRECTION
    switch(snake.direction){
        case 'k': snake.body[0].y--; break;
        case 'j': snake.body[0].y++; break;
        case 'h': snake.body[0].x--; break;
        case 'l': snake.body[0].x++; break;
    }

    /////////////////////////////////////////////////////////////
    //                      CHECK COLLISIONS
    /////////////////////////////////////////////////////////////

    // COLLISION WITH WALLS CHECK
    if(snake.body[0].x == 0 || snake.body[0].x == WIDTH - 1 ||
        snake.body[0].y == -1 || snake.body[0].y == HEIGHT)
        running=false;
    
    // COLLISION WITH ITSELF CHECK
    for(int i = 1; i < snake.length; i++){
        if (snake.body[0].x == snake.body[i].x && snake.body[0].y == snake.body[i].y){
            running=0;
        }
    }

    /////////////////////////////////////////////////////////////
    //                      UPDATE SCORE
    /////////////////////////////////////////////////////////////
    if(snake.body[0].x == fruit.x && snake.body[0].y == fruit.y){
        score += 10;
        if(snake.length<MAX_LENGTH) snake.length++; // to prevent overflow
        fruit.x = rand()%(WIDTH-2) + 1;
        fruit.y = rand()%(HEIGHT-2) + 1;
    }
}

void keyboardInput(){
    char dir = getch();
    switch(dir){
        case 'k': // up
            if (snake.direction != 'k' && snake.direction != 'j') snake.direction = 'k'; 
            break;
        case 'j': // down
            if (snake.direction != 'j' && snake.direction != 'k') snake.direction = 'j';
            break;
        case 'h': // left
            if (snake.direction != 'h' && snake.direction != 'l') snake.direction = 'h';
            break;
        case 'l': // right
            if (snake.direction != 'l' && snake.direction != 'h') snake.direction = 'l';
            break;
        case 'p': // Toggle Pause and Play
            paused = !paused;
            break;
        case 'q': // quit game
            running = false;
            break;
    }
}

void run_game(const char* user){
    char choice;
    do{
        initGame(); // Applies default settings for the game
        while(running){
            printGame(); // Prints Board, Snake and Fruit
            keyboardInput(); // Takes the user input
            updateGame();
            usleep(100000);
        }
        endwin(); // to return to console (ncurses function)

        printf("\nGame Over! Your Score: %d\n", score);
        updatehighscore(user, score); // Also, print if new highscore

        printf("Do you want to play again? (Y/N): ");
        scanf(" %c", &choice);
    }while(choice == 'y' || choice == 'Y');

    printf("Exiting the game...\n");
}