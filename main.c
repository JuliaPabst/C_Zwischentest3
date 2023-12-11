#include <stdio.h>

typedef enum {
    horror, abenteuer, romantik, sachbuch
} E_Genre;

typedef struct {
    char title[32];
    E_Genre genre;
    int erscheinungsjahr;
    int anzahlExemplare;
} S_Book;

int main() {

    return 0;
}
