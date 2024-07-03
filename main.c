#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
int main(void) {
    start();

    //14. i 15. koncept
    Igrac* p1 = (Igrac*)calloc(1, sizeof(Igrac));
    Igrac* p2 = (Igrac*)calloc(1, sizeof(Igrac));
    if (p1 == NULL || p2 == NULL) {
        perror("Greska pri alokaciji memorije");
        return 1;
    }

    unosIgraca(p1, p2);
    izbornik(p1, p2);


    // 16. koncept
    if (p1 != NULL) {
        memset(p1, 0, sizeof(Igrac));
        free(p1); //15. koncept
        p1 = NULL;
    }

    if (p2 != NULL) {
        memset(p2, 0, sizeof(Igrac));
        free(p2); //15. koncept
        p2 = NULL;
    }

    ucitajLeaderboard(10);

    return 0;
}