#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GENRES {"Horror", "Abenteuer", "Romantik", "Sachbuch" }

// #define SHOWALLOCATIONS
// #define SHOWFREEINGS

typedef enum {
    horror, abenteuer, romantik, sachbuch
} E_Genre;

typedef struct {
    char title[32];
    E_Genre genre;
    int publicationYear;
    int amount;
} S_Book;

typedef struct bookNode {
    S_Book content;
    struct bookNode* next;
} bookNode;

bookNode* createBookNode(char title[32], E_Genre genre, int publicationYear, int amount);

bookNode* addBookNodeFront(bookNode* inventoryHead, bookNode* newNode, int* lengthInventory);

void printInventory (bookNode* inventoryHead, int lengthInventory, char genres[4][32]);

void freeInventory (bookNode* inventoryHead, int lengthInventory);

int main() {
    char genres[4][32] = GENRES;
    int lengthInventory = 0;
    char selected = 'a';
    char title[32];
    int genre;
    int publicationYear = 0;
    int amount = 0;

    bookNode* inventoryHead = NULL;

    while(selected != 'x'){
        printf("\nNeues Buch eingeben (n), Buch ausleihen (b), Buch zurueckgeben (r), Buecher auflisten (l), Buecher sortieren (s), Programm beenden (x)\n"
               "Auswahl: ");

        scanf(" %c", &selected);

        switch(selected){
            case 'n':
                printf("\nGeben Sie den Titel ein: ");
                scanf(" %s", title);
                while(genre < 1 || genre > 4){
                    printf("\nGeben Sie das Genre ein. Horror (1), Abenteuer (2), Romantik (3), Sachbuch (4): ");
                    scanf(" %d", &genre);
                    if (genre < 1 || genre > 4){
                        printf("\nUngueltige Eingabe!");
                    }
                }
                while(publicationYear < 1){
                    printf("\nGeben Sie das Erscheinungsjahr ein: ");
                    scanf(" %d", &publicationYear);
                    if (publicationYear < 1){
                        printf("\nUngueltige Eingabe!");
                    }
                }
                while(amount < 1) {
                    printf("\nGeben Sie ein wieviele Exemplare vorhanden sind: ");
                    scanf(" %d", &amount);
                    if (amount < 1){
                        printf("\nUngueltige Eingabe!");
                    }
                }
                genre = 0;
                publicationYear = 0;
                amount = 0;
                inventoryHead = addBookNodeFront(inventoryHead, createBookNode(title, genre, publicationYear, amount), &lengthInventory);
                break;
            case 'b':
                break;
            case 'r':
                break;
            case 'l':
                printInventory(inventoryHead, lengthInventory, genres);
                break;
            case 's':
                break;
            case 'x':
                freeInventory (inventoryHead, lengthInventory);
                break;
        }
    }
    return 0;
}

bookNode* createBookNode(char title[32], E_Genre genre, int publicationYear, int amount) {
    bookNode* newNode = malloc(sizeof(bookNode));
    #ifdef SHOWALLOCATIONS
        printf("node allocated");
    #endif
    strcpy(newNode->content.title, title);
    newNode->content.genre = genre;
    newNode->content.publicationYear = publicationYear;
    newNode->content.amount = amount;
    newNode->next = NULL;
    return newNode;
}

bookNode* addBookNodeFront(bookNode* inventoryHead, bookNode* newNode, int* lengthInventory){
    newNode->next = inventoryHead;
    (*lengthInventory)++;
    return newNode;
}

void printInventory (bookNode* inventoryHead, int lengthInventory, char genres[4][32] ){
    bookNode* currentNode = inventoryHead;
    for(int i = 0; i < lengthInventory; i++){
        printf("\n%d: %s, %s, (%d)", i+1, currentNode->content.title, genres[currentNode->content.genre], currentNode->content.publicationYear);
        currentNode = currentNode->next;
    }
}

void freeInventory (bookNode* inventoryHead, int lengthInventory){
    bookNode* currentNode = inventoryHead;
    for(int i = 0; i < lengthInventory; i++){
        bookNode* nextNode = currentNode->next;
        free(currentNode);
        #ifdef SHOWFREEINGS
                printf("\nNode freed");
        #endif
        currentNode = nextNode;
    }
}
