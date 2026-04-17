#include <stdio.h>
#include <string.h>

#define MAX_JUCATORI 30
#define MAX_NUME     32
#define NR_ECHIPE    5

/* ===================== STRUCTURI ===================== */

/* informații despre un jucător */
struct Jucator {
    char nume[MAX_NUME];
    char prenume[MAX_NUME];
    int varsta;
};

/* informații despre o echipă */
struct Echipa {
    char nume_echipa[64];
    int puncte;
    int golaveraj;   // goluri marcate - goluri primite
    /*1. Comentariul cu double slash de pe linia de mai sus nu ar trebui sa fie scris la final de cod (MISRA rule 13)*/
    struct Jucator lot[MAX_JUCATORI];
    int nr_jucatori;
};

/* Adaugă un jucător în lotul unei echipe */
void adaugaJucator(struct Echipa *e, const char *nume,const char *prenume,int varsta){
    if (e->nr_jucatori > MAX_JUCATORI) {
        printf("Lotul echipei %s este plin, nu pot adauga %s %s.\n",
               e->nume_echipa, nume, prenume);
        return;
        /*2. Return se afla in interiorul lui if, ar fi trebuit sa se afle la finalul functiei(MISRA 24) */
    }

    int k = e->nr_jucatori;
    strcpy(e->lot[k].nume, nume);
    strcpy(e->lot[k].prenume, prenume);
    e->lot[k].varsta = varsta;

    e->nr_jucatori++;
}

/* Inițializează o echipă cu nume, puncte și golaveraj */
void initEchipa(struct Echipa *e,const char *nume_echipa1,int puncte1,int golaveraj1){
    strcpy(e->nume_echipa, nume_echipa1);
    e->puncte = puncte1;
    e->golaveraj = golaveraj1;
    e->nr_jucatori = 0;
}

/* Afișează toate datele despre o echipă și lotul ei */
void arata_date(struct Echipa *e) {
    printf("=====================================\n");
    printf("Echipa: %s\n", e->nume_echipa);
    printf("Puncte: %d | Golaveraj: %d\n", e->puncte, e->golaveraj);
    printf("Numar jucatori: %d\n", e->nr_jucatori);

    printf("\nLotul echipei:\n");
    for (int i = 0; i < e->nr_jucatori; i++) {
        printf("   %d) %s %s, %d ani\n",
               i + 1,
               e->lot[i].nume,
               e->lot[i].prenume,
               e->lot[i].varsta);
    }
    printf("=====================================\n\n");
}

/* Creează echipa mixtă ("All Stars (tineri)"): pentru fiecare echipă din listă alege cel mai tânăr jucător îl adaugă în echipa mixtă*/
void formeazaEchipaMixtaTineri(struct Echipa *echipe, int n, struct Echipa *rezultat) {
    initEchipa(rezultat, "ALL STARS (tineri)", 0, 0);

    for (int i = 0; i < n; i++) {
        if (echipe[i].nr_jucatori == 0) {
        /* 3.Constanta 0 ar trebui sa fie prima in conditia de verificare: (0==echipe[i].nr_jucatori) (MISRA 21)*/
            continue;
            /* 4. Regula 20: Continue nu ar trebui folosit*/
        }
        int idx_min = 0;
        int min_age = echipe[i].lot[0].varsta;

        for (int j = 1; j < echipe[i].nr_jucatori; j++) {
            if (echipe[i].lot[j].varsta < min_age) {
                min_age = echipe[i].lot[j].varsta;
                idx_min = j;
            }
        }
        adaugaJucator(rezultat, echipe[i].lot[idx_min].nume, echipe[i].lot[idx_min].prenume, echipe[i].lot[idx_min].varsta);
    }
}

/* ===================== MAIN ===================== */

int main() {

    struct Echipa team[NR_ECHIPE];
    int puncte_echipa1,puncte_echipa2, puncte_echipa3, puncte_echipa4, puncte_echipa5;
    int golaveraj_echipa1,golaveraj_echipa2, golaveraj_echipa3, golaveraj_echipa4, golaveraj_echipa5;
/*
5. puncte_echipa1,puncte_echipa2, puncte_echipa3, puncte_echipa4, puncte_echipa5 are undefined (MISRA rule 2)
6. golaveraj_echipa1,golaveraj_echipa2, golaveraj_echipa3, golaveraj_echipa4, golaveraj_echipa5 are undefined (MISRA rule 2)
*/

    printf("Introdu punctele pentru echipa 1: ");
    scanf("%d", &puncte_echipa1); //citeste puncte pt echipa1
/*7. Comentariul cu double slash de pe linia de mai sus nu ar trebui sa fie scris la final de cod (MISRA rule 13)*/

    printf("Introdu punctele pentru echipa 2: ");
    scanf("%d", &puncte_echipa2);

    printf("Introdu punctele pentru echipa 3: ");
    scanf("%d", &puncte_echipa3);

    printf("Introdu punctele pentru echipa 4: ");
    scanf("%d", &puncte_echipa4);

    printf("Introdu punctele pentru echipa 5: ");
    scanf("%d", &puncte_echipa5);

    printf("\n Punctele introduse sunt:\n");
    printf("Echipa 1: %d\n", puncte_echipa1);
    printf("Echipa 2: %d\n", puncte_echipa2);
    printf("Echipa 3: %d\n", puncte_echipa3);
    printf("Echipa 4: %d\n", puncte_echipa4);
    printf("Echipa 5: %d\n", puncte_echipa5);
    printf("--------------------------------");

    printf("\nIntrodu golaverajul pentru echipa 1: ");
    scanf("%d", &golaveraj_echipa1);

    printf("Introdu golaverajul pentru echipa 2: ");
    scanf("%d", &golaveraj_echipa2);

    printf("Introdu golaverajul pentru echipa 3: ");
    scanf("%d", &golaveraj_echipa3);

    printf("Introdu golaverajul pentru echipa 4: ");
    scanf("%d", &golaveraj_echipa4);

    printf("Introdu golaverajul pentru echipa 5: ");
    scanf("%d", &golaveraj_echipa5);

    printf("\n Golaverajul introdus este:\n");
    printf("Echipa 1: %d\n", golaveraj_echipa1);
    printf("Echipa 2: %d\n", golaveraj_echipa2);
    printf("Echipa 3: %d\n", golaveraj_echipa3);
    printf("Echipa 4: %d\n", golaveraj_echipa4);
    printf("Echipa 5: %d\n", golaveraj_echipa5);
    printf("--------------------------------");

    /* Echipa 1 */
    initEchipa(&team[0], "Steaua", puncte_echipa1, golaveraj_echipa1);
    adaugaJucator(&team[0], "Popescu", "Andrei", 24);
    adaugaJucator(&team[0], "Ionescu", "Mihai", 27);
    adaugaJucator(&team[0], "Marin", "Daniel", 22);
    adaugaJucator(&team[0], "Radu", "Claudiu", 30);

    /* Echipa 2 */
    initEchipa(&team[1], "Dinamo", puncte_echipa2, golaveraj_echipa2);
    adaugaJucator(&team[1], "Stan", "Bogdan", 25);
    adaugaJucator(&team[1], "Vasilescu", "Rares", 21);
    adaugaJucator(&team[1], "Dumitru", "Cosmin", 26);
    adaugaJucator(&team[1], "Petrescu", "Alexandru", 29);

    /* Echipa 3 */
    initEchipa(&team[2], "Universitatea", puncte_echipa3, golaveraj_echipa3);
    adaugaJucator(&team[2], "Georgescu", "Vlad", 23);
    adaugaJucator(&team[2], "Enache", "Sorin", 24);
    adaugaJucator(&team[2], "Matei", "Radu", 22);
    adaugaJucator(&team[2], "Ilie", "Costin", 28);

    /* Echipa 4 */
    initEchipa(&team[3], "Rapid", puncte_echipa4, golaveraj_echipa4);
    adaugaJucator(&team[3], "Nistor", "Adrian", 31);
    adaugaJucator(&team[3], "Cristea", "Marius", 30);
    adaugaJucator(&team[3], "Dragan", "Mihnea", 20);
    adaugaJucator(&team[3], "Anton", "Laurentiu", 24);

    /* Echipa 5 */
    initEchipa(&team[4], "Craiova", puncte_echipa5, golaveraj_echipa5);
    adaugaJucator(&team[4], "Barbu", "Stefan", 19);
    adaugaJucator(&team[4], "Olteanu", "George", 20);
    adaugaJucator(&team[4], "Popa", "Iulian", 22);
    adaugaJucator(&team[4], "Stoican", "Rares", 23);

    /* 1. Afișăm toate echipele cu loturile lor */
    printf("\n DETALII ECHIPE (LOTURI COMPLETE):\n\n");
    for (int i = 0; i < NR_ECHIPE; i++) {
        arata_date(&team[i]);
    }

    /* 3. Formăm echipa mixtă din cei mai tineri jucători ai fiecărei echipe */
    struct Echipa allStars;
    formeazaEchipaMixtaTineri(team, NR_ECHIPE, &allStars);

    /* 4. Afișăm echipa mixtă */
    printf("SELECTIONATA MIXTA (cei mai tineri jucatori din fiecare echipa):\n\n");
    arata_date(&allStars);
    return 0;
}
