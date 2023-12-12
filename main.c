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

int checkIfAllAreBorrowed(bookNode* inventoryHead, int selectedBookToBorrow);

void findTitleToBorrow(bookNode* inventoryHead, int selectedBookToBorrow, char *titleToBorrow);

int checkIfTheyAlreadyBorrowed(borrowNode* booksBorrowedHead, int lengthBorrowedNodes, char title[32], char name[32], bookNode* inventoryHead, int selectedBookToBorrow);

borrowNode* addBorrowNodeFront(borrowNode* booksBorrowedHead, borrowNode* newNode, int* lengthBorrowedNodes);

borrowNode* returnBookAt(borrowNode* booksBorrowedHead, int* lengthBorrowedNodes, int selectedBookToReturn, bookNode* inventoryHead);

void swap(S_Book* a, S_Book* b){
    S_Book temp = *a;
    *a = *b;
    *b = temp;
}

void sortArrayByPublishingYearBubbleSort (S_Book* booksSorted, int n){
    {
        for(int i = 0; i<n-1; ++i)
            for(int j = 0; j<n-1; ++j)
                if(booksSorted[j].publicationYear > booksSorted[j+1].publicationYear)
                    swap(&booksSorted[j], &booksSorted[j+1]);
    }
}

void printInventory (bookNode* inventoryHead, int lengthInventory, char genres[4][32]);

void printBorrowed (borrowNode* booksBorrowedHead, int lengthBorrowedNodes);

void printSorted(bookNode* inventoryHead, int lengthInventory, char genres[4][32]);

void freeInventory (bookNode* inventoryHead, int lengthInventory);

void freeBorrowedNodes (borrowNode* booksBorrowedHead, int lengthBorrowedNodes);

void addReturnedBookToAmount(char title[32], bookNode* inventoryHead, int selectedBookToReturn){
    bookNode* amountNode = inventoryHead;

   /* printf("\ntitle: %s, amount title: %s", title, amountNode->content.title);
    printf("\n next amount title: %s", (amountNode->next)->content.title); */
    while(strcmp(title, amountNode->content.title) != 0){
        amountNode = amountNode->next;
       // printf("\nnext");
    }

   // printf("\ntitle: %s, amount title: %s", title, amountNode->content.title);

    (amountNode->content.amount)++;
  //  printf("\n%s amount: %d", amountNode->content.title, amountNode->content.amount);
}

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
    int selectedBookToReturn = 0;
    char name[32];
    char titleToBorrow[32];

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
                    printf("\n\nEs sind keine Buecher im Inventar vorhanden.");
                    break;
                }
                printInventory(inventoryHead, lengthInventory, genres);
                do{
                    printf("\nWelchen Titel moechten Sie leihen? (1-%d): ", lengthInventory);
                    scanf("%d", &selectedBookToBorrow);


                    if (selectedBookToBorrow < 1 || selectedBookToBorrow > lengthInventory) {
                        printf("\nUngueltige Eingabe!");
                    } else {
                        printf("\nGeben Sie Ihren Namen ein: ");
                        scanf(" %s", name);
                         if(!checkIfAllAreBorrowed(inventoryHead, selectedBookToBorrow)) {
                            printf("\nBereits alle Exemplare ausgeliehen!");
                        } else {
                           findTitleToBorrow(inventoryHead, selectedBookToBorrow, titleToBorrow);
                             if(checkIfTheyAlreadyBorrowed(booksBorrowedHead, lengthBorrowedNodes, titleToBorrow, name, inventoryHead, selectedBookToBorrow)){
                                printf("\nSie haben diesen Titel bereits ausgeliehen!");
                            } else {
                                booksBorrowedHead = addBorrowNodeFront(booksBorrowedHead, createBorrowNode(titleToBorrow, name), &lengthBorrowedNodes);
                            }
                        }
                    }
                } while(selectedBookToBorrow < 1 || selectedBookToBorrow > lengthInventory);
                break;
            case 'r': // return book
                printBorrowed (booksBorrowedHead, lengthBorrowedNodes);
                if(lengthBorrowedNodes == 0){
                   printf("\n\nEs sind keine Titel ausgeliehen!");
                }  else {
                   while(selectedBookToReturn < 1){
                       printf("\nWelchen Titel moechten Sie retournieren? (1-%d): ", lengthBorrowedNodes);
                       scanf(" %d", &selectedBookToReturn);
                       if (selectedBookToReturn < 1 || selectedBookToReturn > lengthBorrowedNodes) {
                           printf("\nUngueltige Eingabe!");
                       }
                   }
                    booksBorrowedHead = returnBookAt(booksBorrowedHead, &lengthBorrowedNodes, selectedBookToReturn, inventoryHead);
                    selectedBookToReturn = 0;
                }
               break;
            case 'l': // list books
                printInventory(inventoryHead, lengthInventory, genres);
                break;
            case 's': // sort books
                printSorted(inventoryHead, lengthInventory, genres);
                break;
            case 'x': // exit program
                freeInventory (inventoryHead, lengthInventory);
                freeBorrowedNodes (booksBorrowedHead, lengthBorrowedNodes);
                break;
            default:
                printf("\nUngueltige Eingabe!");
                break;
        }
    }
    return 0;
}

bookNode* createBookNode(char title[32], E_Genre genre, int publicationYear, int amount) {
    bookNode* newNode = malloc(sizeof(bookNode));
    #ifdef SHOWALLOCATIONS
        printf("\nbook node allocated");
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
        printf("\n borrow node allocated");
    #endif

        strcpy(newNode->title, titleToBorrow);
        strcpy(newNode->name, name);
        newNode->next = NULL;
        return newNode;

}

int checkIfAllAreBorrowed(bookNode* inventoryHead, int selectedBookToBorrow){
    bookNode* currentBook = inventoryHead;

    for (int i = 0; i < selectedBookToBorrow - 1; i++) {
        currentBook = currentBook->next;
    }

    if (currentBook == NULL || currentBook->content.amount <= 0) {
        return 0;
    } else {
        return 1;
    }
}

void findTitleToBorrow(bookNode* inventoryHead, int selectedBookToBorrow, char *titleToBorrow){
    bookNode* currentNode = inventoryHead;

    for(int i = 0; i < selectedBookToBorrow - 1; i++){
        currentNode = currentNode->next;
    }
    strcpy(titleToBorrow, currentNode->content.title);

}


int checkIfTheyAlreadyBorrowed(borrowNode* booksBorrowedHead, int lengthBorrowedNodes, char title[32], char name[32], bookNode* inventoryHead, int selectedBookToBorrow){
    borrowNode* currentNode = booksBorrowedHead;
    for(int i = 0; i < lengthBorrowedNodes; i++){
        if(strcmp(currentNode->title, title) == 0 && strcmp(currentNode->name, name) == 0){
            return 1;
        }
        currentNode = currentNode->next;
    }

    bookNode* amountNode = inventoryHead;

    for(int i = 0; i < selectedBookToBorrow - 1; i++){
        amountNode = amountNode->next;
    }
    (amountNode->content.amount)--;
    // printf("\n%s amount: %d", amountNode->content.title, amountNode->content.amount);

    return 0;
}


borrowNode* addBorrowNodeFront(borrowNode* booksBorrowedHead, borrowNode* newNode, int* lengthBorrowedNodes){
    newNode->next = booksBorrowedHead;
    (*lengthBorrowedNodes)++;
    return newNode;
}

borrowNode* returnBookAt(borrowNode* booksBorrowedHead, int* lengthBorrowedNodes, int selectedBookToReturn, bookNode* inventoryHead){
    borrowNode* nodeToDelete = NULL;
    borrowNode* head = booksBorrowedHead;


    if (selectedBookToReturn == 1) {
        nodeToDelete = booksBorrowedHead;
        booksBorrowedHead = nodeToDelete->next;
        addReturnedBookToAmount(nodeToDelete->title, inventoryHead, selectedBookToReturn);
        free(nodeToDelete);
        (*lengthBorrowedNodes)--;

        return booksBorrowedHead;
    } else
    {
        borrowNode* previousNode = head;
        if(*lengthBorrowedNodes == 2){
           nodeToDelete = previousNode->next;
            addReturnedBookToAmount(nodeToDelete->title, inventoryHead, selectedBookToReturn);
            free(nodeToDelete);
            previousNode->next = NULL;
            (*lengthBorrowedNodes)--;
        } else {
           for (int i = 0; i < selectedBookToReturn - 2; i++) {
            previousNode = previousNode->next;
            }
            nodeToDelete = previousNode->next;
            previousNode->next = nodeToDelete->next;
            addReturnedBookToAmount(nodeToDelete->title, inventoryHead, selectedBookToReturn);
            free(nodeToDelete);
            (*lengthBorrowedNodes)--;
        }
    }

   // printf("\n book returned");




    #ifdef SHOWFREEINGS
            printf("\nNode freed");
    #endif

    return head;
}


void printInventory (bookNode* inventoryHead, int lengthInventory, char genres[4][32] ){
    bookNode* currentNode = inventoryHead;
    for(int i = 0; i < lengthInventory; i++){
        printf("\n%d: %s, %s (%d)", i+1, currentNode->content.title, genres[currentNode->content.genre], currentNode->content.publicationYear);
        currentNode = currentNode->next;
    }
    printf("\n");
}

void printBorrowed (borrowNode* booksBorrowedHead, int lengthBorrowedNodes){
    borrowNode * currentNode = booksBorrowedHead;
    if(currentNode != NULL){
        for(int i = 0; i < lengthBorrowedNodes; i++){
            printf("\n%d: %s geliehen von %s", i+1, currentNode->title, currentNode->name);
            currentNode = currentNode->next;
        }
        printf("\n");
    }

}

void printSorted(bookNode* inventoryHead, int lengthInventory, char genres[4][32]){
    S_Book booksSorted[lengthInventory];
    bookNode* currentNode = inventoryHead;

    for(int i = 0; i < lengthInventory; i++){
        booksSorted[i] = currentNode->content;
        if(currentNode != NULL){
            currentNode = currentNode->next;
        }
    }

    sortArrayByPublishingYearBubbleSort(booksSorted, lengthInventory);

    for(int i = 0; i < lengthInventory; i++){
        printf("\n%d: %s, %s (%d)", i+1, booksSorted[i].title, genres[booksSorted[i].genre], booksSorted[i].publicationYear);
    }
    printf("\n");
}

void freeInventory (bookNode* inventoryHead, int lengthInventory){
    bookNode* currentNode = inventoryHead;
    for(int i = 0; i < lengthInventory; i++){
        bookNode* nextNode = currentNode->next;
        free(currentNode);
        #ifdef SHOWFREEINGS
                printf("\ninventory Node freed");
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
            printf("\n borrowed Node freed");
    #endif
        currentNode = nextNode;
    }
}
