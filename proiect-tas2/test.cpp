#include "pch.h"
#include <iostream>
#include <string>
#include <gtest/gtest.h>

struct Jucator {
    std::string nume;
    std::string prenume;
    int varsta;
};

struct Echipa {
    std::string nume_echipa;
    int puncte;
    int golaveraj;
    Jucator lot[30];
    int nr_jucatori;
};

void adaugaJucator(Echipa& e, const std::string& nume, const std::string& prenume, int varsta) {
    if (e.nr_jucatori > 5) {
        std::cout << "Lotul echipei " << e.nume_echipa << " este plin, nu pot adauga "
            << nume << ' ' << prenume << ".\n";
        return;
    }

    int k = e.nr_jucatori;
    e.lot[k].nume = nume;
    e.lot[k].prenume = prenume;
    e.lot[k].varsta = varsta;

    e.nr_jucatori++;
}

int numarApeluriAdaugaJucator = 0;

// STUB pentru adaugaJucator
void adaugaJucator_stub(Echipa& e, const std::string& nume,
    const std::string& prenume, int varsta) {

    numarApeluriAdaugaJucator++;

    std::cout << "[STUB] adaugaJucator a fost apelata pentru: "
        << nume << " " << prenume << " (" << varsta << " ani)\n";
}

void initEchipa(Echipa& e, const std::string& nume_echipa1, int puncte1, int golaveraj1) {
    e.nume_echipa = nume_echipa1;
    e.puncte = puncte1;
    e.golaveraj = golaveraj1;
    e.nr_jucatori = 0;
}

void arata_date(const Echipa& e) {
    std::cout << "=====================================\n";
    std::cout << "Echipa: " << e.nume_echipa << "\n";
    std::cout << "Puncte: " << e.puncte
        << " | Golaveraj: " << e.golaveraj << "\n";
    std::cout << "Numar jucatori: " << e.nr_jucatori << "\n";

    std::cout << "\nLotul echipei:\n";
    for (int i = 0; i < e.nr_jucatori; i++) {
        std::cout << "   " << i + 1 << ") "
            << e.lot[i].nume << ' '
            << e.lot[i].prenume << ", "
            << e.lot[i].varsta << " ani\n";
    }
    std::cout << "=====================================\n\n";
}

void formeazaEchipaMixtaTineri(Echipa* echipe, int n, Echipa& rezultat) {
    initEchipa(rezultat, "ALL STARS (tineri)", 0, 0);

    for (int i = 0; i < n; i++) {
        if (echipe[i].nr_jucatori == 0) {
            continue;
        }

        int idx_min = 0;
        int min_age = echipe[i].lot[0].varsta;

        for (int j = 1; j < echipe[i].nr_jucatori; j++) {
            if (echipe[i].lot[j].varsta < min_age) {
                min_age = echipe[i].lot[j].varsta;
                idx_min = j;
            }
        }

        adaugaJucator(rezultat,
            echipe[i].lot[idx_min].nume,
            echipe[i].lot[idx_min].prenume,
            echipe[i].lot[idx_min].varsta);
    }
}

/* TESTE  */

TEST(TestareEchipe, TestEchipa1) {
    Echipa team[5];

    /* Echipa 1 */
    initEchipa(team[0], "Steaua", 3, 5);
    adaugaJucator(team[0], "Popescu", "Andrei", 24);
    adaugaJucator(team[0], "Ionescu", "Mihai", 27);
    adaugaJucator(team[0], "Marin", "Daniel", 22);
    adaugaJucator(team[0], "Radu", "Claudiu", 30);

    ASSERT_EQ(team[0].nume_echipa, "Steaua");
    ASSERT_EQ(team[0].puncte, 3);
    ASSERT_EQ(team[0].golaveraj, 5);

    ASSERT_EQ(team[0].lot[0].nume, "Popescu");
    ASSERT_EQ(team[0].lot[0].prenume, "Andrei");
    ASSERT_EQ(team[0].lot[0].varsta, 24);

    ASSERT_EQ(team[0].lot[1].nume, "Ionescu");
    ASSERT_EQ(team[0].lot[1].prenume, "Mihai");
    ASSERT_EQ(team[0].lot[1].varsta, 27);

    ASSERT_EQ(team[0].lot[2].nume, "Marin");
    ASSERT_EQ(team[0].lot[2].prenume, "Daniel");
    ASSERT_EQ(team[0].lot[2].varsta, 22);

    ASSERT_EQ(team[0].lot[3].nume, "Radu");
    ASSERT_EQ(team[0].lot[3].prenume, "Claudiu");
    ASSERT_EQ(team[0].lot[3].varsta, 30);
}

TEST(TestareEchipe, TestEchipa2) {
    Echipa team[5];

    /* Echipa 2 */
    initEchipa(team[1], "Dinamo", 8, 12);
    adaugaJucator(team[1], "Stan", "Bogdan", 25);
    adaugaJucator(team[1], "Vasilescu", "Rares", 21);
    adaugaJucator(team[1], "Dumitru", "Cosmin", 26);
    adaugaJucator(team[1], "Petrescu", "Alexandru", 29);

    ASSERT_EQ(team[1].nume_echipa, "Dinamo");
    ASSERT_EQ(team[1].puncte, 8);
    ASSERT_EQ(team[1].golaveraj, 12);

    ASSERT_EQ(team[1].lot[0].nume, "Stan");
    ASSERT_EQ(team[1].lot[0].prenume, "Bogdan");
    ASSERT_EQ(team[1].lot[0].varsta, 25);

    ASSERT_EQ(team[1].lot[1].nume, "Vasilescu");
    ASSERT_EQ(team[1].lot[1].prenume, "Rares");
    ASSERT_EQ(team[1].lot[1].varsta, 21);

    ASSERT_EQ(team[1].lot[2].nume, "Dumitru");
    ASSERT_EQ(team[1].lot[2].prenume, "Cosmin");
    ASSERT_EQ(team[1].lot[2].varsta, 26);

    ASSERT_EQ(team[1].lot[3].nume, "Petrescu");
    ASSERT_EQ(team[1].lot[3].prenume, "Alexandru");
    ASSERT_EQ(team[1].lot[3].varsta, 29);
}

TEST(TestareEchipe, TestEchipa3) {
    Echipa team[5];

    /* Echipa 3 */
    initEchipa(team[2], "Universitatea", 7, 8);
    adaugaJucator(team[2], "Georgescu", "Vlad", 23);
    adaugaJucator(team[2], "Enache", "Sorin", 24);
    adaugaJucator(team[2], "Matei", "Radu", 22);
    adaugaJucator(team[2], "Ilie", "Costin", 28);

    ASSERT_EQ(team[2].nume_echipa, "Universitatea");
    ASSERT_EQ(team[2].puncte, 7);
    ASSERT_EQ(team[2].golaveraj, 8);

    ASSERT_EQ(team[2].lot[0].nume, "Georgescu");
    ASSERT_EQ(team[2].lot[0].prenume, "Vlad");
    ASSERT_EQ(team[2].lot[0].varsta, 23);

    ASSERT_EQ(team[2].lot[1].nume, "Enache");
    ASSERT_EQ(team[2].lot[1].prenume, "Sorin");
    ASSERT_EQ(team[2].lot[1].varsta, 24);

    ASSERT_EQ(team[2].lot[2].nume, "Matei");
    ASSERT_EQ(team[2].lot[2].prenume, "Radu");
    ASSERT_EQ(team[2].lot[2].varsta, 22);

    ASSERT_EQ(team[2].lot[3].nume, "Ilie");
    ASSERT_EQ(team[2].lot[3].prenume, "Costin");
    ASSERT_EQ(team[2].lot[3].varsta, 28);
}

TEST(TestareEchipe, TestEchipa4) {
    Echipa team[5];

    /* Echipa 4 */
    initEchipa(team[3], "Rapid", 12, 14);
    adaugaJucator(team[3], "Nistor", "Adrian", 31);
    adaugaJucator(team[3], "Cristea", "Marius", 30);
    adaugaJucator(team[3], "Dragan", "Mihnea", 20);
    adaugaJucator(team[3], "Anton", "Laurentiu", 24);

    ASSERT_EQ(team[3].nume_echipa, "Rapid");
    ASSERT_EQ(team[3].puncte, 12);
    ASSERT_EQ(team[3].golaveraj, 14);

    ASSERT_EQ(team[3].lot[0].nume, "Nistor");
    ASSERT_EQ(team[3].lot[0].prenume, "Adrian");
    ASSERT_EQ(team[3].lot[0].varsta, 31);

    ASSERT_EQ(team[3].lot[1].nume, "Cristea");
    ASSERT_EQ(team[3].lot[1].prenume, "Marius");
    ASSERT_EQ(team[3].lot[1].varsta, 30);

    ASSERT_EQ(team[3].lot[2].nume, "Dragan");
    ASSERT_EQ(team[3].lot[2].prenume, "Mihnea");
    ASSERT_EQ(team[3].lot[2].varsta, 20);

    ASSERT_EQ(team[3].lot[3].nume, "Anton");
    ASSERT_EQ(team[3].lot[3].prenume, "Laurentiu");
    ASSERT_EQ(team[3].lot[3].varsta, 24);
}

TEST(TestareEchipe, TestEchipa5) {
    Echipa team[5];

    /* Echipa 5 */
    initEchipa(team[4], "Craiova", 21, 30);
    adaugaJucator(team[4], "Barbu", "Stefan", 19);
    adaugaJucator(team[4], "Olteanu", "George", 20);
    adaugaJucator(team[4], "Popa", "Iulian", 22);
    adaugaJucator(team[4], "Stoican", "Rares", 23);

    ASSERT_EQ(team[4].nume_echipa, "Craiova");
    ASSERT_EQ(team[4].puncte, 21);
    ASSERT_EQ(team[4].golaveraj, 30);

    ASSERT_EQ(team[4].lot[0].nume, "Barbu");
    ASSERT_EQ(team[4].lot[0].prenume, "Stefan");
    ASSERT_EQ(team[4].lot[0].varsta, 19);

    ASSERT_EQ(team[4].lot[1].nume, "Olteanu");
    ASSERT_EQ(team[4].lot[1].prenume, "George");
    ASSERT_EQ(team[4].lot[1].varsta, 20);

    ASSERT_EQ(team[4].lot[2].nume, "Popa");
    ASSERT_EQ(team[4].lot[2].prenume, "Iulian");
    ASSERT_EQ(team[4].lot[2].varsta, 22);

    ASSERT_EQ(team[4].lot[3].nume, "Stoican");
    ASSERT_EQ(team[4].lot[3].prenume, "Rares");
    ASSERT_EQ(team[4].lot[3].varsta, 23);
}

TEST(TestareEchipe, TestToateEchipele) {
    Echipa team[5];

    /* Echipa 1 */
    initEchipa(team[0], "Steaua", 3, 5);
    adaugaJucator(team[0], "Popescu", "Andrei", 24);
    adaugaJucator(team[0], "Ionescu", "Mihai", 27);
    adaugaJucator(team[0], "Marin", "Daniel", 22);
    adaugaJucator(team[0], "Radu", "Claudiu", 30);

    /* Echipa 2 */
    initEchipa(team[1], "Dinamo", 8, 12);
    adaugaJucator(team[1], "Stan", "Bogdan", 25);
    adaugaJucator(team[1], "Vasilescu", "Rares", 21);
    adaugaJucator(team[1], "Dumitru", "Cosmin", 26);
    adaugaJucator(team[1], "Petrescu", "Alexandru", 29);

    /* Echipa 3 */
    initEchipa(team[2], "Universitatea", 7, 8);
    adaugaJucator(team[2], "Georgescu", "Vlad", 23);
    adaugaJucator(team[2], "Enache", "Sorin", 24);
    adaugaJucator(team[2], "Matei", "Radu", 22);
    adaugaJucator(team[2], "Ilie", "Costin", 28);

    /* Echipa 4 */
    initEchipa(team[3], "Rapid", 12, 14);
    adaugaJucator(team[3], "Nistor", "Adrian", 31);
    adaugaJucator(team[3], "Cristea", "Marius", 30);
    adaugaJucator(team[3], "Dragan", "Mihnea", 20);
    adaugaJucator(team[3], "Anton", "Laurentiu", 24);

    /* Echipa 5 */
    initEchipa(team[4], "Craiova", 21, 30);
    adaugaJucator(team[4], "Barbu", "Stefan", 19);
    adaugaJucator(team[4], "Olteanu", "George", 20);
    adaugaJucator(team[4], "Popa", "Iulian", 22);
    adaugaJucator(team[4], "Stoican", "Rares", 23);

    //Asserturi echipa1
    ASSERT_EQ(team[0].nume_echipa, "Steaua");
    ASSERT_EQ(team[0].puncte, 3);
    ASSERT_EQ(team[0].golaveraj, 5);

    ASSERT_EQ(team[0].lot[0].nume, "Popescu");
    ASSERT_EQ(team[0].lot[0].prenume, "Andrei");
    ASSERT_EQ(team[0].lot[0].varsta, 24);

    ASSERT_EQ(team[0].lot[1].nume, "Ionescu");
    ASSERT_EQ(team[0].lot[1].prenume, "Mihai");
    ASSERT_EQ(team[0].lot[1].varsta, 27);

    ASSERT_EQ(team[0].lot[2].nume, "Marin");
    ASSERT_EQ(team[0].lot[2].prenume, "Daniel");
    ASSERT_EQ(team[0].lot[2].varsta, 22);

    ASSERT_EQ(team[0].lot[3].nume, "Radu");
    ASSERT_EQ(team[0].lot[3].prenume, "Claudiu");
    ASSERT_EQ(team[0].lot[3].varsta, 30);

    //Asserturi echipa2
    ASSERT_EQ(team[1].nume_echipa, "Dinamo");
    ASSERT_EQ(team[1].puncte, 8);
    ASSERT_EQ(team[1].golaveraj, 12);

    ASSERT_EQ(team[1].lot[0].nume, "Stan");
    ASSERT_EQ(team[1].lot[0].prenume, "Bogdan");
    ASSERT_EQ(team[1].lot[0].varsta, 25);

    ASSERT_EQ(team[1].lot[1].nume, "Vasilescu");
    ASSERT_EQ(team[1].lot[1].prenume, "Rares");
    ASSERT_EQ(team[1].lot[1].varsta, 21);

    ASSERT_EQ(team[1].lot[2].nume, "Dumitru");
    ASSERT_EQ(team[1].lot[2].prenume, "Cosmin");
    ASSERT_EQ(team[1].lot[2].varsta, 26);

    ASSERT_EQ(team[1].lot[3].nume, "Petrescu");
    ASSERT_EQ(team[1].lot[3].prenume, "Alexandru");
    ASSERT_EQ(team[1].lot[3].varsta, 29);

    //Asserturi echipa3
    ASSERT_EQ(team[2].nume_echipa, "Universitatea");
    ASSERT_EQ(team[2].puncte, 7);
    ASSERT_EQ(team[2].golaveraj, 8);

    ASSERT_EQ(team[2].lot[0].nume, "Georgescu");
    ASSERT_EQ(team[2].lot[0].prenume, "Vlad");
    ASSERT_EQ(team[2].lot[0].varsta, 23);

    ASSERT_EQ(team[2].lot[1].nume, "Enache");
    ASSERT_EQ(team[2].lot[1].prenume, "Sorin");
    ASSERT_EQ(team[2].lot[1].varsta, 24);

    ASSERT_EQ(team[2].lot[2].nume, "Matei");
    ASSERT_EQ(team[2].lot[2].prenume, "Radu");
    ASSERT_EQ(team[2].lot[2].varsta, 22);

    ASSERT_EQ(team[2].lot[3].nume, "Ilie");
    ASSERT_EQ(team[2].lot[3].prenume, "Costin");
    ASSERT_EQ(team[2].lot[3].varsta, 28);

    //Asserturi echipa4
    ASSERT_EQ(team[3].nume_echipa, "Rapid");
    ASSERT_EQ(team[3].puncte, 12);
    ASSERT_EQ(team[3].golaveraj, 14);

    ASSERT_EQ(team[3].lot[0].nume, "Nistor");
    ASSERT_EQ(team[3].lot[0].prenume, "Adrian");
    ASSERT_EQ(team[3].lot[0].varsta, 31);

    ASSERT_EQ(team[3].lot[1].nume, "Cristea");
    ASSERT_EQ(team[3].lot[1].prenume, "Marius");
    ASSERT_EQ(team[3].lot[1].varsta, 30);

    ASSERT_EQ(team[3].lot[2].nume, "Dragan");
    ASSERT_EQ(team[3].lot[2].prenume, "Mihnea");
    ASSERT_EQ(team[3].lot[2].varsta, 20);

    ASSERT_EQ(team[3].lot[3].nume, "Anton");
    ASSERT_EQ(team[3].lot[3].prenume, "Laurentiu");
    ASSERT_EQ(team[3].lot[3].varsta, 24);

    //Asserturi echipa5
    ASSERT_EQ(team[4].nume_echipa, "Craiova");
    ASSERT_EQ(team[4].puncte, 21);
    ASSERT_EQ(team[4].golaveraj, 30);

    ASSERT_EQ(team[4].lot[0].nume, "Barbu");
    ASSERT_EQ(team[4].lot[0].prenume, "Stefan");
    ASSERT_EQ(team[4].lot[0].varsta, 19);

    ASSERT_EQ(team[4].lot[1].nume, "Olteanu");
    ASSERT_EQ(team[4].lot[1].prenume, "George");
    ASSERT_EQ(team[4].lot[1].varsta, 20);

    ASSERT_EQ(team[4].lot[2].nume, "Popa");
    ASSERT_EQ(team[4].lot[2].prenume, "Iulian");
    ASSERT_EQ(team[4].lot[2].varsta, 22);

    ASSERT_EQ(team[4].lot[3].nume, "Stoican");
    ASSERT_EQ(team[4].lot[3].prenume, "Rares");
    ASSERT_EQ(team[4].lot[3].varsta, 23);
}

TEST(TestareEchipe, FormeazaEchipaMixta) {
    Echipa team[5];
    Echipa echipaMixtaTineri;

    /* Echipa 1 */
    initEchipa(team[0], "Steaua", 3, 5);
    adaugaJucator(team[0], "Popescu", "Andrei", 24);
    adaugaJucator(team[0], "Ionescu", "Mihai", 27);
    adaugaJucator(team[0], "Marin", "Daniel", 22);
    adaugaJucator(team[0], "Radu", "Claudiu", 30);

    /* Echipa 2 */
    initEchipa(team[1], "Dinamo", 8, 12);
    adaugaJucator(team[1], "Stan", "Bogdan", 25);
    adaugaJucator(team[1], "Vasilescu", "Rares", 21);
    adaugaJucator(team[1], "Dumitru", "Cosmin", 26);
    adaugaJucator(team[1], "Petrescu", "Alexandru", 29);

    /* Echipa 3 */
    initEchipa(team[2], "Universitatea", 7, 8);
    adaugaJucator(team[2], "Georgescu", "Vlad", 23);
    adaugaJucator(team[2], "Enache", "Sorin", 24);
    adaugaJucator(team[2], "Matei", "Radu", 22);
    adaugaJucator(team[2], "Ilie", "Costin", 28);

    /* Echipa 4 */
    initEchipa(team[3], "Rapid", 12, 14);
    adaugaJucator(team[3], "Nistor", "Adrian", 31);
    adaugaJucator(team[3], "Cristea", "Marius", 30);
    adaugaJucator(team[3], "Dragan", "Mihnea", 20);
    adaugaJucator(team[3], "Anton", "Laurentiu", 24);

    /* Echipa 5 */
    initEchipa(team[4], "Craiova", 21, 30);
    adaugaJucator(team[4], "Barbu", "Stefan", 19);
    adaugaJucator(team[4], "Olteanu", "George", 20);
    adaugaJucator(team[4], "Popa", "Iulian", 22);
    adaugaJucator(team[4], "Stoican", "Rares", 23);

    formeazaEchipaMixtaTineri(team, 5, echipaMixtaTineri);

    //Asserturi echipa mixta
    ASSERT_EQ(echipaMixtaTineri.nume_echipa, "ALL STARS (tineri)");
    ASSERT_EQ(echipaMixtaTineri.puncte, 0);
    ASSERT_EQ(echipaMixtaTineri.golaveraj, 0);

    ASSERT_EQ(echipaMixtaTineri.lot[0].nume, "Marin");
    ASSERT_EQ(echipaMixtaTineri.lot[0].prenume, "Daniel");
    ASSERT_EQ(echipaMixtaTineri.lot[0].varsta, 22);

    ASSERT_EQ(echipaMixtaTineri.lot[1].nume, "Vasilescu");
    ASSERT_EQ(echipaMixtaTineri.lot[1].prenume, "Rares");
    ASSERT_EQ(echipaMixtaTineri.lot[1].varsta, 21);

    ASSERT_EQ(echipaMixtaTineri.lot[2].nume, "Matei");
    ASSERT_EQ(echipaMixtaTineri.lot[2].prenume, "Radu");
    ASSERT_EQ(echipaMixtaTineri.lot[2].varsta, 22);

    ASSERT_EQ(echipaMixtaTineri.lot[3].nume, "Dragan");
    ASSERT_EQ(echipaMixtaTineri.lot[3].prenume, "Mihnea");
    ASSERT_EQ(echipaMixtaTineri.lot[3].varsta, 20);

    ASSERT_EQ(echipaMixtaTineri.lot[4].nume, "Barbu");
    ASSERT_EQ(echipaMixtaTineri.lot[4].prenume, "Stefan");
    ASSERT_EQ(echipaMixtaTineri.lot[4].varsta, 19);

    arata_date(echipaMixtaTineri);
}

/* Test negativ: numele echipei NU trebuie sa fie altceva */
TEST(TestareEchipe, TestEchipa1_cu_numeEchipa_gresit) {
    Echipa team[5];

    initEchipa(team[0], "Steaua", 3, 5);
    ASSERT_NE(team[0].nume_echipa, "F.C Steaua");
}

/* Test negativ: punctaj negativ -> arata ca sistemul accepta valori < 0 */
TEST(TestareEchipe, TestEchipa1_cu_punctaj_negativ) {
    Echipa team[5];

    initEchipa(team[0], "Steaua", -3, 5);
    ASSERT_LT(team[0].puncte, 0);
}

/* BOUNDARY: al 5-lea jucator este inca acceptat */
TEST(TestareEchipe, Test_adaugaJucator_nr5) {
    Echipa team[5];

    initEchipa(team[2], "Universitatea", 7, 8);
    adaugaJucator(team[2], "Georgescu", "Vlad", 23);
    adaugaJucator(team[2], "Enache", "Sorin", 24);
    adaugaJucator(team[2], "Matei", "Radu", 22);
    adaugaJucator(team[2], "Ilie", "Costin", 28);
    adaugaJucator(team[2], "Costescu", "Dan", 30);

    ASSERT_EQ(team[2].nr_jucatori, 5);
    EXPECT_EQ(team[2].lot[4].nume, "Costescu");
    EXPECT_EQ(team[2].lot[4].prenume, "Dan");
    EXPECT_EQ(team[2].lot[4].varsta, 30);
}

/* BOUNDARY: al 6-lea jucator NU mai este acceptat (ramura if > 5) */
TEST(TestareEchipe, Test_adaugaJucator_nr6) {
    Echipa team[5];

    initEchipa(team[2], "Universitatea", 7, 8);
    adaugaJucator(team[2], "Georgescu", "Vlad", 23);
    adaugaJucator(team[2], "Enache", "Sorin", 24);
    adaugaJucator(team[2], "Matei", "Radu", 22);
    adaugaJucator(team[2], "Ilie", "Costin", 28);
    adaugaJucator(team[2], "Stanciu", "Nicolae", 31);
    adaugaJucator(team[2], "Hagi", "Ianis", 33);

    ASSERT_EQ(team[2].nr_jucatori, 5);
    EXPECT_EQ(team[2].lot[4].nume, "Stanciu");
    EXPECT_EQ(team[2].lot[4].prenume, "Nicolae");
    EXPECT_EQ(team[2].lot[4].varsta, 31);
}

/* Test negativ: varsta prea mare */
TEST(TestareEchipe, Test_adaugaJucator_varsta_prea_Mare) {
    Echipa team[5];

    initEchipa(team[2], "Universitatea", 7, 8);
    adaugaJucator(team[2], "Georgescu", "Vlad", 23);
    adaugaJucator(team[2], "Enache", "Sorin", 24);
    adaugaJucator(team[2], "Matei", "Radu", 22);
    adaugaJucator(team[2], "Ilie", "Costin", 55);

    ASSERT_EQ(team[2].lot[3].nume, "Ilie");
    ASSERT_EQ(team[2].lot[3].prenume, "Costin");
    EXPECT_GT(team[2].lot[3].varsta, 40);
}

/* Test pentru stub */
TEST(TestareEchipe, TestStub) {
    Echipa team[5];

    initEchipa(team[4], "Craiova", 21, 30);
    adaugaJucator_stub(team[4], "Barbu", "Stefan", 19);
    adaugaJucator_stub(team[4], "Olteanu", "George", 20);
    adaugaJucator_stub(team[4], "Popa", "Iulian", 22);
    adaugaJucator_stub(team[4], "Stoican", "Rares", 23);

    ASSERT_EQ(numarApeluriAdaugaJucator, 4);
}

/* Test pentru formeazaEchipaMixtaTineri cu o echipa goala */
TEST(TestareEchipe, FormeazaEchipaMixta_CuEchipaGoala) {
    Echipa team[2];
    Echipa echipaMixta;

    // Echipa 0 – goala
    initEchipa(team[0], "FaraJucatori", 0, 0);

    initEchipa(team[1], "CuJucatori", 10, 5);
    adaugaJucator(team[1], "Mihai", "Andrei", 20);

    formeazaEchipaMixtaTineri(team, 2, echipaMixta);

    ASSERT_EQ(echipaMixta.nr_jucatori, 1);
    EXPECT_EQ(echipaMixta.lot[0].nume, "Mihai");
    EXPECT_EQ(echipaMixta.lot[0].prenume, "Andrei");
    EXPECT_EQ(echipaMixta.lot[0].varsta, 20);
}

/* Test clase de echivalenta / boundary pentru varsta: 18 si 40*/
TEST(TestareEchipe, Test_adaugaJucator_varsta_limita) {
    Echipa e;
    initEchipa(e, "Steaua", 0, 0);
    adaugaJucator(e, "Popescu", "Andrei", 18);
    adaugaJucator(e, "Ionescu", "Mihai", 40);

    ASSERT_EQ(e.nr_jucatori, 2);
    EXPECT_EQ(e.lot[0].varsta, 18);
    EXPECT_EQ(e.lot[1].varsta, 40);
}