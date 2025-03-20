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

    print_centered("1. New User");
    print_centered("2. Existing User");
    print_centered("3. Leaderboard");
    print_centered("4. About Developers");
    print_centered("5. Exit");
    printf("\n");
}

void run_main_menu() {
    int choice;
    bool running = true;
    char name[100];

    while (running) { 
        system("clear || cls");
        display_main_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
            case 2: {
                printf("\nEnter your name: ");
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
                printf("\nExiting the game...\n");
                running = false;
                break;
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }
}

