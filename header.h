#ifndef HEADER_H
#define HEADER_H

typedef struct {
    char ime[50];
    char znak;
    int bodovi;
} Igrac; // 2.koncept, 3.koncept

extern int brojOdigranihIgara; // 7. koncept

enum Izbor {
    NOVA_IGRA = 1,
    PRIKAZ_LEADERBOARD,
    IZLAZ
}; // 9. koncept

void start(void);
char odabir(void);
inline char winer(char win) { return win; } // 8. koncept
int logika(char mat[3][3], Igrac* p1, Igrac* p2);
void igra(char mat[3][3], int br, int mem[10], Igrac* p1, Igrac* p2);
void kraj(void);
void unosIgraca(Igrac* p1, Igrac* p2);
void prikaziLeaderboard(Igrac* p1, Igrac* p2);
void izbornik(Igrac* p1, Igrac* p2);
void novaIgra(Igrac* p1, Igrac* p2);
void spremiRezultat(Igrac* p1, Igrac* p2);
void ucitajLeaderboard(void);
int kopirajDatoteku(const char* izvorna, const char* destinacija);
void sortirajIgrace(Igrac* igraci, int brojIgraca);
int usporediBodove(const void* a, const void* b);
int usporediImena(const void* a, const void* b);
Igrac* pretraziIgracaPoImenu(Igrac* igraci, int brojIgraca, const char* ime); //22. koncept
int provjeriPobjednika(char mat[3][3], int redak, int stupac, char znak, int brojac);


#endif