#include "../include/main_menu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void about_developers_window() {
    print_centered("ABOUT DEVELOPERS");
    
    printf("Roshan (Team Leader)\n1. ...\n2. ...\n\n");
    printf("Adarsh Kumar\n1. ...\n2. ...\n\n");
    printf("Arnav Amrit\n1. ...\n2. ...\n\n");
}

void print_centered(const char *text) {
    int len = strlen(text);
    int spaces = (WIDTH - len) / 2;

    for (int i = 0; i < spaces; i++) printf(" ");
    printf("%s\n", text);
}

void display_main_menu() {
    printf("\n");
    print_centered("=== SNAKE GAME ===");
    printf("\n");

    print_centered("New User");
    print_centered("Existing User");
    print_centered("Leaderboard");
    print_centered("About Developers");
    print_centered("Exit");
    printf("\n");
}

void run_main_menu() {
    int choice;
    bool running = true;
    char name[50]; // make this global

    while (running) { 
        system("clear || cls");
        display_main_menu();
        printf("Enter your choice (1-5): ");
        scanf("%d", &choice);
        while(getchar() != '\n');

        switch(choice){
            case 1:{
                printf("Enter your username: ");
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0';
                // Check if username already exists
                // if exists, then break
                FILE* fptr = fopen("data/usernames.txt", "a+");
                if(fptr == NULL){
                    printf("Error opening usernames.txt!");
                    break;
                }
                rewind(fptr); // To bring the pointer to the start of the file
                
                // Scanning the usernames for existing user
                bool username_exists = false;
                char existing_name[100];
                while(fgets(existing_name, sizeof(existing_name), fptr) != NULL){
                    existing_name[strcspn(existing_name, "\n")] = '\0'; // Remove newline from file line
                    if (strcmp(name, existing_name) == 0){
                        printf("Username already exists");
                        getchar();
                        username_exists = true;
                        break;
                    }
                }
                if(!username_exists){
                    fprintf(fptr, "%s\n", name);
                }
                fclose(fptr);
                break;
            }
            case 2: {
                printf("Enter your username: ");
                getchar(); // Consume newline
                fgets(name, sizeof(name), stdin);
                name[strcspn(name, "\n")] = '\0'; 
                break;
            }
            case 3:
                printf("\n");
                print_centered("LEADERBOARD");
                printf("\n");
                break;
            case 4:
                system("clear || cls");
                about_developers_window();
                printf("Press <Enter> to go back to Main Menu...");
                while (getchar() != '\n');
                getchar();
                break;
            case 5:
                printf("Exiting the game...\n");
                running = false;
                break;
            default:
                printf("Invalid choice. Please try again.");
                getchar();
        }
    }
}

