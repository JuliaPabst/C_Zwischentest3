#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

bookNode* createBookNode(char title[32], E_Genre genre, int publicationYear, int amount) {
    bookNode* newNode = malloc(sizeof(bookNode));
    printf("node allocated");

    strcpy(newNode->content.title, title);
    newNode->content.genre = genre;
    newNode->content.publicationYear = publicationYear;
    newNode->content.amount = amount;

    return newNode;
}



int main() {
    char genres[4][32] = {"Horror", "Abenteuer", "Romantik", "Sachbuch" };
    bookNode* inventory = NULL;

    inventory = createBookNode("Huhu", horror, 1999, 2);

    return 0;
}
