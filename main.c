#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define GENRES {"Horror", "Abenteuer", "Romantik", "Sachbuch" }

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


int main() {
    char genres[4][32] = GENRES;
    int lengthInventory = 0;

    bookNode* inventoryHead = NULL;

    inventoryHead = addBookNodeFront(inventoryHead, createBookNode("Huhu", horror, 1999, 2), &lengthInventory);

    printInventory(inventoryHead, lengthInventory, genres);

    return 0;
}

bookNode* createBookNode(char title[32], E_Genre genre, int publicationYear, int amount) {
    bookNode* newNode = malloc(sizeof(bookNode));
    printf("node allocated");

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
        printf("\n%s", currentNode->content.title);
        printf("\n%s", genres[currentNode->content.genre]);
        printf("\n%d", currentNode->content.publicationYear);
        printf("\n%d", currentNode->content.amount);
        currentNode = currentNode->next;
    }
}
