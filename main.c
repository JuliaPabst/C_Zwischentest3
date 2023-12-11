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

typedef struct borrowNode {
    char title[32];
    char name[32];
    struct borrowNode* next;
} borrowNode;

bookNode* createBookNode(char title[32], E_Genre genre, int publicationYear, int amount);

borrowNode* createBorrowNode(char selectedTitle[32], char name[32]);

bookNode* addBookNodeFront(bookNode* inventoryHead, bookNode* newNode, int* lengthInventory);

char* checkIfAllAreBorrowed(bookNode* inventoryHead, int selectedBookToBorrow);

borrowNode* addBorrowNodeFront(borrowNode* booksBorrowedHead, borrowNode* newNode, int* lengthBorrowedNodes);

void printInventory (bookNode* inventoryHead, int lengthInventory, char genres[4][32]);

void freeInventory (bookNode* inventoryHead, int lengthInventory);

void freeBorrowedNodes (borrowNode* booksBorrowedHead, int lengthBorrowedNodes);

int main() {
    char genres[4][32] = GENRES;
    int lengthInventory = 0;
    int lengthBorrowedNodes = 0;
    char selected = 'a';

    char title[32];
    int genre = 0;
    int publicationYear = 0;
    int amount = 0;
    int selectedBookToBorrow = 0;
    char selectedTitle[32];
    char name[32];

    bookNode* inventoryHead = NULL;
    borrowNode* booksBorrowedHead = NULL;

    while(selected != 'x'){
        printf("\nNeues Buch eingeben (n), Buch ausleihen (b), Buch zurueckgeben (r), Buecher auflisten (l), Buecher sortieren (s), Programm beenden (x)\n"
               "Auswahl: ");

        scanf(" %c", &selected);

        switch(selected){
            case 'n': // insert book
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
                inventoryHead = addBookNodeFront(inventoryHead, createBookNode(title, --genre, publicationYear, amount), &lengthInventory);
                genre = 0;
                publicationYear = 0;
                amount = 0;
                break;
            case 'b': // borrow book
                if (lengthInventory < 1){
                    printf("\nEs sind keine Buecher im Inventar vorhanden.");
                    break;
                }
                printInventory(inventoryHead, lengthInventory, genres);
                do{
                    printf("\nWelchen Titel moechten Sie leihen? (1-%d): ", lengthInventory);
                    scanf(" %d", &selectedBookToBorrow);
                    char* borrowedTitle = checkIfAllAreBorrowed(inventoryHead, selectedBookToBorrow);
                    if (selectedBookToBorrow < 1 || selectedBookToBorrow > lengthInventory) {
                        printf("\nUngueltige Eingabe!");
                    }
                    if(borrowedTitle == NULL) {
                        printf("\nBereits alle Exemplare ausgeliehen!");
                    } else {
                        printf("\nGeben Sie Ihren Namen ein: ");
                        scanf(" %s", name);
                        booksBorrowedHead = addBorrowNodeFront(booksBorrowedHead, createBorrowNode(selectedTitle, name), &lengthBorrowedNodes);
                    }
                } while(selectedBookToBorrow < 1 || selectedBookToBorrow > lengthInventory);
                break;
            case 'r': // return book
                break;
            case 'l': // list books
                printInventory(inventoryHead, lengthInventory, genres);
                break;
            case 's': // sort books
                break;
            case 'x':
                freeInventory (inventoryHead, lengthInventory);
                freeBorrowedNodes (booksBorrowedHead, lengthBorrowedNodes);
                break;
        }
    }
    return 0;
}

bookNode* createBookNode(char title[32], E_Genre genre, int publicationYear, int amount) {
    bookNode* newNode = malloc(sizeof(bookNode));
    #ifdef SHOWALLOCATIONS
        printf("book node allocated");
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

borrowNode* createBorrowNode(char titleToBorrow[32], char name[32]){
    borrowNode* newNode = malloc(sizeof(borrowNode));

    #ifdef SHOWALLOCATIONS
        printf("borrow node allocated");
    #endif

        strcpy(newNode->title, titleToBorrow);
        strcpy(newNode->name, name);
        newNode->next = NULL;
        return newNode;

}

char* checkIfAllAreBorrowed(bookNode* inventoryHead, int selectedBookToBorrow){
    bookNode* currentBook = inventoryHead;
    for (int i = 1; i < selectedBookToBorrow && currentBook != NULL; i++) {
        currentBook = currentBook->next;
    }

    if (currentBook == NULL || currentBook->content.amount <= 0) {
        return NULL;
    } else {
        return currentBook->content.title;
    }
}

borrowNode* addBorrowNodeFront(borrowNode* booksBorrowedHead, borrowNode* newNode, int* lengthBorrowedNodes){
    newNode->next = booksBorrowedHead;
    (*lengthBorrowedNodes)++;
    return newNode;
}


void printInventory (bookNode* inventoryHead, int lengthInventory, char genres[4][32] ){
    bookNode* currentNode = inventoryHead;
    for(int i = 0; i < lengthInventory; i++){
        printf("\n%d: %s, %s (%d)", i+1, currentNode->content.title, genres[currentNode->content.genre], currentNode->content.publicationYear);
        currentNode = currentNode->next;
    }
    printf("\n");
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

void freeBorrowedNodes (borrowNode* booksBorrowedHead, int lengthBorrowedNodes){
    borrowNode * currentNode = booksBorrowedHead;
    for(int i = 0; i < lengthBorrowedNodes; i++){
        borrowNode * nextNode = currentNode->next;
        free(currentNode);
    #ifdef SHOWFREEINGS
            printf("\nNode freed");
    #endif
        currentNode = nextNode;
    }
}
