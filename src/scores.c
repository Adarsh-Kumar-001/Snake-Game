#include "../include/scores.h"
#include "../include/common.h"

#define INITIAL_CAPACITY 5

void updatehighscore(const char *user, uint16_t curr_score){
    typedef struct{
        char name[50];
        uint16_t score;
    }Player;

    int capacity = INITIAL_CAPACITY;
    int linecount = 0;
    bool user_found = false;

    // Dynamically allocate memory for players
    Player *players = malloc(capacity * sizeof(Player));
    if(!players){
        perror("Memory allocation failed");
        return;
    }

    FILE *file = fopen("data/highscores.csv", "r");
    if(!file){  // Assuming first user registers their score
        file = fopen("data/highscores.csv", "w+"); // make a new file for new user
        if(!file){
            perror("Error opening data/highscores.csv for writing");
            free(players);
            return;
        }
    }

    ////////////////////////////////////////////////////////////////////////////
    //      CHECK IF USER HAS PRE-EXISTING HIGHSCORE IN highscore.csv
    ////////////////////////////////////////////////////////////////////////////

    // Read each record from highscore.csv, growing our players array if needed
    while(fscanf(file, " %49[^,],%hu", players[linecount].name, &players[linecount].score) == 2){
        linecount++;
        if(linecount >= capacity){
            capacity *= 2;
            Player *temp = realloc(players, capacity * sizeof(Player));
            if(!temp){
                perror("Memory reallocation failed");
                free(players);
                fclose(file);
                return;
            }
            players = temp;
        }
    }
    fclose(file);

    // Update score if the user already exists, else add new entry
    for(int i = 0; i < linecount; i++){
        if(strcmp(players[i].name, user) == 0){   // found existing record
            user_found = true;
            // new highscore created
            if(curr_score > players[i].score){
                printf("You made a new high score: %hu\n", curr_score);
                players[i].score = curr_score;
            }else{
                // not a highscore
                printf("Your high score is: %hu\n", players[i].score);
            }
        }
    }

    // if no highscore exists for the current user, add new record
    if(!user_found){
        // Ensure there is room
        if(linecount >= capacity){
            capacity *= 2;
            Player *temp = realloc(players, capacity * sizeof(Player));
            if(!temp){
                perror("Memory reallocation failed");
                free(players);
                return;
            }
            players = temp;
        }
        strcpy(players[linecount].name, user);
        players[linecount].score = curr_score;  // Adds current score as new high score
        printf("You made a new high score: %hu\n", curr_score);
        linecount++;
    }

    ///////////////////////////////////////////////////////
    //      UPDATE THE highscore.csv file
    ///////////////////////////////////////////////////////
    
    FILE *tempFile = fopen("data/highscores_temp.csv", "w");
    if (!tempFile) {
        perror("Error opening highscores_temp.csv");
        free(players);
        return;
    }

    for (int i = 0; i < linecount; i++)
        fprintf(tempFile, "%s,%hu\n", players[i].name, players[i].score);
    fclose(tempFile);

    remove("data/highscores.csv");
    rename("data/highscores_temp.csv", "data/highscores.csv");

    free(players);
}
