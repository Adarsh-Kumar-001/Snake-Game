#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 50
#define MAX_USERS 100

void updatehighscore(const char* user, int curr_score){
    FILE *file = fopen("data/highscores.csv", "r");
    if (!file) return; 
    char lines[MAX_USERS][MAX_LINE_LENGTH];
    char tempuser[MAX_LINE_LENGTH];
    int tempscore, found = 0, count = 0;
    while (fgets(lines[count],MAX_LINE_LENGTH,file)){
        fscanf(file, "%[^,],%d\n",tempuser,&tempscore);
        if (strcmp(tempuser,user)==0){
            found = 1;
            if (curr_score>tempscore){
                fprintf(stdout,"You Made New High score: %d\n",curr_score);
                snprintf(lines[count],MAX_LINE_LENGTH, "%s,%d\n",user,curr_score);
            } 
            else{
                fprintf(stdout, "Your High score is %s: %d\n",user,tempscore);
            }
        }
        count++;
    }
    fclose(file);
    
    if (!found){
        fprintf(stdout,"You Made New High score: %d\n",curr_score);
        snprintf(lines[count],MAX_LINE_LENGTH,"%s,%d\n",user,curr_score);
    }    
    FILE *tempFile = fopen("data/highscores_temp.csv", "w");
    if (!tempFile) return;
    for (int i=0;i<=count;i++){
        fprintf(tempFile, "%s", lines[i]);
    }
    fclose(tempFile); 
    if (remove("data/highscores.csv")!=0){
        printf("Error removing old high score file!\n");
        return;
    }
    if (rename("data/highscores_temp.csv","highscores.csv")!=0){
        printf("Error renaming temporary file!\n");
        return;
    }
}
