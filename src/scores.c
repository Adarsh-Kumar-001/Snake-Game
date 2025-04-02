#include "../include/scores.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define MAX_LINE_LENGTH 50
#define MAX_USERS 100

void updatehighscore(const char *user, uint16_t curr_score) {
    FILE *file = fopen("data/highscores.csv", "r");
    if (!file) {
        perror("Error opening highscores.csv");
        return;
    }

    char lines[MAX_USERS][MAX_LINE_LENGTH];
    char tempuser[MAX_LINE_LENGTH];
    int tempscore, found = 0, count = 0;

    while (fgets(lines[count], MAX_LINE_LENGTH, file)) {
        if (sscanf(lines[count], "%49[^,],%d", tempuser, &tempscore) != 2) {
            continue;
        }

        if (strcmp(tempuser, user) == 0) {
            found = 1;
            if (curr_score > tempscore) {
                printf("You made a new high score: %d\n", curr_score);
                snprintf(lines[count], MAX_LINE_LENGTH, "%s,%d\n", user, curr_score);
            } else {
                printf("Your high score is %s: %d\n", user, tempscore);
            }
        }
        count++;
        if (count >= MAX_USERS) break; 
    }
    fclose(file);

    if (!found) {
        printf("You made a new high score: %d\n", curr_score);
        if (count < MAX_USERS) {
            snprintf(lines[count], MAX_LINE_LENGTH, "%s,%d\n", user, curr_score);
            count++;
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

    for (int i = 0; i < count; i++) {
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
