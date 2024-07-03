#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

static int brojOdigranihIgara = 1; //5. koncept

void start() {
    printf("Dobrodosli u X/O (iks-oks miniigra)\nKako igrati:\n  -odaberite znak s kojim zelite igrati\n  -odaberite polje u koje zelite staviti znak (polja su mapirana kao na prikazu)\n  -zabavite se!\n");
    printf(" 1 | 2 | 3 \n--  --  -- \n 4 | 5 | 6 \n--  --  -- \n 7 | 8 | 9 \n");
}

char odabir() {
    char znak;
    printf("Odaberite znak igraca (X ili O): ");
    scanf(" %c", &znak);

    // 12. koncept
    while (znak != 'X' && znak != 'O') {
        printf("Neispravan unos! Molimo unesite X ili O: ");
        while (getchar() != '\n');
        scanf(" %c", &znak);
    }

    return znak;
}

int provjeriPobjednika(char mat[3][3]) {
    for (int i = 0; i < 3; i++) {
        if (mat[i][0] == mat[i][1] && mat[i][1] == mat[i][2]) return 1;
        if (mat[0][i] == mat[1][i] && mat[1][i] == mat[2][i]) return 1;
    }
    if (mat[0][0] == mat[1][1] && mat[1][1] == mat[2][2]) return 1;
    if (mat[0][2] == mat[1][1] && mat[1][1] == mat[2][0]) return 1;

    return 0;
}

int logika(char mat[3][3], Igrac* p1, Igrac* p2) {
    int w = 0;
    char winner = '\0';

    if (provjeriPobjednika(mat)) {
        winner = (p1->znak == mat[1][1]) ? p1->znak : p2->znak;
        w = 10;
    }

    if (winner != '\0') {
        if (winner == p1->znak) {
            p1->bodovi++;
        }
        else if (winner == p2->znak) {
            p2->bodovi++;
        }
    }

    return w;
}

void igra(char mat[3][3], int br, int mem[10], Igrac* p1, Igrac* p2) {
    int x = 0;
    char z;
    printf("\nIgra pocinje!\n");
    while (br < 9) { 
        if (br % 2 == 0) {
            printf("\n%s je na redu", p1->ime);
            z = p1->znak;
        }
        else {
            printf("\n%s je na redu", p2->ime);
            z = p2->znak;
        }
        printf("\nOdaberi polje: ");

        // 12. koncept
        while (scanf("%d", &x) != 1 || x < 1 || x > 9) {
            printf("\nNeispravan unos! Molimo unesite broj od 1 do 9: ");
            while (getchar() != '\n');
        }

        // 12. koncept
        for (int i = 0; i <= br; i++) {
            if (x == mem[i]) {
                printf("\nPolje je zauzeto, odaberite drugo!\n");
                x = 0;
                break;
            }
        }

        if (x == 0) {
            continue;
        }

        mem[br] = x;

        switch (x) {
        case 1: mat[0][0] = z; break;
        case 2: mat[0][1] = z; break;
        case 3: mat[0][2] = z; break;
        case 4: mat[1][0] = z; break;
        case 5: mat[1][1] = z; break;
        case 6: mat[1][2] = z; break;
        case 7: mat[2][0] = z; break;
        case 8: mat[2][1] = z; break;
        case 9: mat[2][2] = z; break;
        }

        printf(" %c | %c | %c \n", mat[0][0], mat[0][1], mat[0][2]);
        printf("--  --  -- \n");
        printf(" %c | %c | %c \n", mat[1][0], mat[1][1], mat[1][2]);
        printf("--  --  -- \n");
        printf(" %c | %c | %c \n", mat[2][0], mat[2][1], mat[2][2]);

        if (logika(mat, p1, p2) == 10) {
            printf("\n%s je pobednik!\n", (z == p1->znak) ? p1->ime : p2->ime);
            break;
        }
        br++;
    }

    if (br == 9) {
        printf("\nIgra je nerijesena!\n");
    }
}

void kraj() {
    printf("\nHvala na igranju!");
}

void unosIgraca(Igrac* p1, Igrac* p2) {
    printf("Unesite ime prvog igraca: ");
    scanf("%s", p1->ime);
    p1->znak = odabir();
    p1->bodovi = 0;

    printf("Unesite ime drugog igraca: ");
    scanf("%s", p2->ime);
    p2->znak = (p1->znak == 'X') ? 'O' : 'X';
    p2->bodovi = 0;
}

void prikaziLeaderboard(Igrac* p1, Igrac* p2) {
    printf("\n--- Leaderboard ---\n");
    printf("%s: %d bodova\n", p1->ime, p1->bodovi);
    printf("%s: %d bodova\n", p2->ime, p2->bodovi);
}

void izbornik(Igrac* p1, Igrac* p2) {
    int izbor;
    do {
        printf("\nIzbornik:\n1. Nova igra\n2. Prikazi leaderboard\n3. Izlaz\nIzbor: ");

        while (scanf("%d", &izbor) != 1) {
            printf("Neispravan unos! Molimo unesite broj (1, 2 ili 3): ");
            while (getchar() != '\n');
        }

        switch (izbor) {
        case 1:
            novaIgra(p1, p2);
            break;
        case 2:
            prikaziLeaderboard(p1, p2);
            break;
        case 3:
            kraj();
            break;
        default:
            printf("Neispravan izbor! Pokusajte ponovo.\n");
        }

    } while (izbor != 3);
}

void novaIgra(Igrac* p1, Igrac* p2) {
    char mat[3][3] = { {'1','2','3'}, {'4','5','6'}, {'7','8','9'} };
    int mem[10] = { 0 };
    igra(mat, 0, mem, p1, p2);
    spremiRezultat(p1, p2, brojOdigranihIgara);
    brojOdigranihIgara++;
}

void spremiRezultat(Igrac* p1, Igrac* p2, int brojPartije) {
    FILE* file = fopen("leaderboard.txt", "a");
    if (file == NULL) {
        perror("Greska pri otvaranju datoteke za pisanje");
        return;
    }

    fprintf(file, "Partija %d:\n", brojPartije);

    fprintf(file, "%s: %d bodova\n", p1->ime, p1->bodovi);
    fprintf(file, "%s: %d bodova\n", p2->ime, p2->bodovi);

    fprintf(file, "-----------------\n");

    if (fclose(file) != 0) {
        perror("Greska pri zatvaranju datoteke");
    }
}

void ucitajLeaderboard(void) {
    FILE* file = fopen("leaderboard.txt", "r");
    if (file == NULL) {
        perror("Greska pri otvaranju datoteke za citanje");
        return;
    }

    rewind(file); // 18. koncept

    char linija[100];

    printf("\n--- Leaderboard ---\n");

    while (fgets(linija, sizeof(linija), file) != NULL) {
        if (strstr(linija, "Partija") != NULL) {
            continue;
        }
        printf("%s", linija);
    }

    if (fclose(file) != 0) {
        perror("Greska pri zatvaranju datoteke"); //20. koncept
    }
}

// 19. koncept kopriranje datoteke
int kopirajDatoteku(const char* izvorna, const char* destinacija) {
    FILE* file_izvorna = fopen(izvorna, "rb");
    if (file_izvorna == NULL) {
        perror("Greška pri otvaranju izvorne datoteke");
        return 0;
    }

    FILE* file_destinacija = fopen(destinacija, "wb");
    if (file_destinacija == NULL) {
        perror("Greška pri otvaranju destinacijske datoteke");
        fclose(file_izvorna);
        return 0;
    }

    char buffer[1024];
    size_t bytes;

    while ((bytes = fread(buffer, 1, sizeof(buffer), file_izvorna)) > 0) {
        fwrite(buffer, 1, bytes, file_destinacija);
    }

    fclose(file_izvorna);
    fclose(file_destinacija);

    return 1;
}

void sortirajIgrace(Igrac* igraci, int brojIgraca) {
    qsort(igraci, brojIgraca, sizeof(Igrac), usporediBodove); //21. koncept
}

int usporediBodove(const void* a, const void* b) {
    const Igrac* igracA = (const Igrac*)a;
    const Igrac* igracB = (const Igrac*)b;

    return (igracB->bodovi - igracA->bodovi);
}

int usporediImena(const void* a, const void* b) {
    const Igrac* igracA = (const Igrac*)a;
    const Igrac* igracB = (const Igrac*)b;
    return strcmp(igracA->ime, igracB->ime);
}

//22. koncept
Igrac* pretraziIgracaPoImenu(Igrac* igraci, int brojIgraca, const char* ime) {
    Igrac trazeniIgrac;
    strcpy(trazeniIgrac.ime, ime);

    qsort(igraci, brojIgraca, sizeof(Igrac), usporediImena);

    Igrac* rezultat = bsearch(&trazeniIgrac, igraci, brojIgraca, sizeof(Igrac), usporediImena);

    return rezultat;
}
