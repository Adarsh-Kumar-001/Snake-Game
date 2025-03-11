#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define WIDTH 50

void printCentered(const char *text) {
    int len = strlen(text);
    int spaces = (WIDTH - len) / 2;

    for (int i = 0; i < spaces; i++) printf(" ");
    printf("%s\n", text);
}

void displayMenu() {
    system("cls"); 

    printf("\n");
    printCentered("=== SNAKE GAME ===");
    printf("\n");

    printCentered("1. New User");
    printCentered("2. Existing User");
    printCentered("3. Leaderboard");
    printCentered("4. About Developers");
    printCentered("5. Exit");
    printf("\n");
}

void handleMenuSelection() {
    int choice;
    bool running = true;
    displayMenu();
    char name[100];
    while (running) {
        
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                printf("\nEnter your name: ");
                scanf("%s", &name);
                break;
            }
            case 2: {
                printf("\nEnter your name: ");
                scanf("%s", &name);
                break;
            }
            case 3: {
                printf("\n");
                printCentered("LEADERBOARD");
                printf("\n");
                break;
            }
            case 4: {
                printf("\n");
                printCentered("ABOUT DEVELOPERS");
                printf("\n");
                break;
            }
            case 5: {
                printf("\nExiting the game...\n");
                running = false; 
                break;
            }
            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    }
}

int main() {
    handleMenuSelection();
}