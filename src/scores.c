#include "../include/scores.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 50 // no. of characters in each line
#define MAX_USERS 100 // no. of lines

void updatehighscore(const char *user, uint16_t curr_score) {
    // ensure user exists in usernames.txt file (valid user check)
    // reuse the same code used in case 1 of switch-case in main_menu.c



    FILE *file = fopen("data/highscores.csv", "r");
    if(!file){  // Assuming first user registers their score
        // make a new file



        return;
    }

    char lines[MAX_USERS][MAX_LINE_LENGTH];
    
    uint16_t tempscore, line_no = 0; // tempscore should be prev_highscore?
    bool user_found = false;

    ///////////////////////////////////////////////////////////////////
    // CHECK IF USER HAS PRE-EXISTING HIGHSCORE IN highscore.csv
    ///////////////////////////////////////////////////////////////////
    while(fgets(lines[line_no], MAX_LINE_LENGTH, file)){    // go through each user in highscore.csv
        char tempuser[MAX_LINE_LENGTH];
        if(sscanf(lines[line_no], "%48[^,],%5hu", tempuser, &tempscore) != 2)
            continue;

        if(strcmp(tempuser, user) == 0){ // if current user found in highscores.csv
            user_found = true;
            // new highscore created
            if(curr_score > tempscore){
                printf("You made a new high score: %d\n", curr_score);
                // store highscore in lines array
                snprintf(lines[line_no], MAX_LINE_LENGTH, "%s,%d\n", user, curr_score);
            }
            else    // not a highscore
                printf("Your high score is %s: %d\n", user, tempscore);
        }
        line_no++;
        if(line_no >= MAX_USERS) break; 
    }
    fclose(file);



    if (!user_found) {
        printf("You made a new high score: %d\n", curr_score);
        if (line_no < MAX_USERS) {
            snprintf(lines[line_no], MAX_LINE_LENGTH, "%s,%d\n", user, curr_score);
            line_no++;
        } else {
            printf("Error: High score list is full!\n");
            return;
        }
    }





    FILE *tempFile = fopen("data/highscores_temp.csv", "w");
    if (!tempFile) {
        perror("Error opening highscores_temp.csv");
        return;
    }

    for (int i = 0; i < line_no; i++) {
        fputs(lines[i], tempFile);
    }
    fclose(tempFile);

    if (remove("data/highscores.csv") != 0) {
        perror("Error removing old high score file");
        return;
    }

    if (rename("data/highscores_temp.csv", "data/highscores.csv") != 0) {
        perror("Error renaming temporary file");
    }
}
