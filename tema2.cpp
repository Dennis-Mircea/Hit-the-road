/*
 *  Copyright [2018] <CIUPITU DENNIS-MIRCEA 313CA>
 */

#ifndef __TEMA2_
#define __TEMA2_

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <list>
#include <stack>
#include <queue>

#include "Hash_functions.h"
#include "Hashtable.h"
#include "ListGraph.h"

// structura necesara pentru rezolvarea task-ului 4
struct way {
    std::string dest;
    int number;
};

// functie care adauga un element in hashtable intr-un caz particular
void put_5(Hashtable<std::string, struct way>& traseu, struct way ruta,
                 std::string source) {
    struct elem_info<std::string, struct way> p;
    int hkey = hash_fct(source) % traseu.HMAX;
    int q = 0;
    for (auto it = traseu.H[hkey].begin(); it != traseu.H[hkey].end(); ++it) {
        if (it->key == source) {
            if (it->value.dest == ruta.dest) {
                // marirea numarului de calatori in cazul in care
                // s-a gasit in hashtable aceeasi ruta
                it->value.number += ruta.number;
                q = 1;
            }
        }
    }
    if (q == 0){
    p.key = source;
    p.value = ruta;
    traseu.H[hkey].push_back(p);
    traseu.size++;
    }
    if ((float)traseu.size / (float)traseu.HMAX > 0.75) traseu.resize();
}

// functie care rezolva TASK-ul 5
void TASK_5(Hashtable<std::string, struct way>& traseu, int max_value, int N,
                std::string town_1, std::string town_2, std::ostream& task5,
                ListGraph<int>& harta, Hashtable<int, std::string>& towns2,
                Hashtable<std::string, class oras>& towns) {
    // verific care este cea mai circulata ruta de calatori din punct de
    // vedere lexico-gramatical
    for (int i = 0; i < traseu.HMAX; i++) {
        if (!traseu.H[i].empty()) {
            for (auto it = traseu.H[i].begin();
             it != traseu.H[i].end(); ++it) {
                if (it->value.number > max_value) {
                    max_value = it->value.number;
                    town_1 = it->key;
                    town_2 = it->value.dest;
                } else if (it->value.number == max_value) {
                    if (town_1.compare(it->key) > 0) {
                        town_1 = it->key;
                        town_2 = it->value.dest;
                    } else if (town_1.compare(it->key) == 0) {
                        if (town_2.compare(it->value.dest) > 0) {
                            town_2 = it->value.dest;
                        }
                    }
                }
            }
        }
    }
    // memorarea oraselor traseului cel mai circulat de lungime minima
    // prin care trece autobuzul
    std::stack<int> traseu_minim = harta.minPath(N,
            towns.get_value(town_1).number, towns.get_value(town_2).number);
    // afisarea pe rand a numarului maxim de calatori care frecventeaza ruta
    // cat si orasele prin care trece autobuzul
    task5 << max_value;
    while (!traseu_minim.empty()) {
        task5 << " " << towns2.get_value(traseu_minim.top());
        traseu_minim.pop();
    }
    task5 << std::endl;
}

int main() {
    std::ofstream task1, task2, task3, task4, task5;
    task1.open("task1.out");
    task2.open("task2.out");
    task3.open("task3.out");
    task4.open("task4.out");
    task5.open("task5.out");

    int N, M;
    std::cin >> N >> M;
    // declararea celor 2 hashtable-uri necesare rezolvarii problemei
    Hashtable<std::string, class oras> towns(N, &hash_fct);
    Hashtable<int, std::string> towns2(N, &hashingFunction);
    // citirea oraselor
    std::string town;
    class oras city;
    for (int i = 0; i < N; i++) {
        std::cin >> town;
        city.number = i;
        towns.put(town, city);
        towns2.put(i, town);
    }

    // declararea listelor vecinilor(a grafului normal si a grafului transpus)
    ListGraph<int> harta(N);
    ListGraph<int> harta_t(N);
    std::string town1, town2;
    class oras city2;
    for (int i = 0; i < M; i++) {
        // citirea de la tastatura a perechilor de orase
        std::cin >> town1 >> town2;
        // formarea celor 2 liste
        harta.addEdge(towns.get_value(town2).number,
                        towns.get_value(town1).number);
        harta_t.addEdge(towns.get_value(town1).number,
                        towns.get_value(town2).number);
    }

    // TASK_1
    int pos;
    unsigned int max = 0;
    // stabilirea gradului maxim de aglomerare
    for (int i = 0; i < N; i++) {
        if (harta_t.getNeighbors(i).size() > max) {
            max = harta_t.getNeighbors(i).size();
            pos = i;
        }
    }
    task1 << towns2.get_value(pos) << " " << max << std::endl;

    // TASK_2
    // verificarea accesibilitatii hartii
    // valid - variabila care retina daca harta e valida sau nu
    int valid = 0;
    if (harta.accesibility(harta_t) == false) {
        valid = 1;
        task2 << "HARTA INVALIDA" << std::endl;
    } else {
        task2 << "HARTA VALIDA" << std::endl;
    }

    // informatiile necesare pentru TASK-ul 4
    int B;
    std::cin >> B;
    class oras town_3;
    // citesc B orase in care se afla benzinarii si modific hashtable-ul
    for (int i = 0; i < B; i++) {
        std::cin >> town;
        town_3 = towns.get_value(town);
        town_3.benzinarie = true;
        towns.put(town, town_3);
    }

    // TASK_3
    int K;
    std::cin >> K;
    std::string oras_3;
    // citirea celor K orase si aflarea oraselor inaccesibile pentru acestea
    for (int i = 0; i < K; i++) {
        std::cin >> oras_3;
        if (valid == 1) {
            task3 << "Orase inaccesibile pentru " << oras_3 << ": ";
            // apelarea functiei TASK_3 pentru aflarea oraselor inaccesibile
            harta.TASK_3(towns.get_value(oras_3).number,
                             towns2, harta_t, task3);
            task3 << std::endl;
        } else {
            if (i == 0) {
                task3 << "Exista drum intre oricare doua orase" << std::endl;
            }
        }
    }

    // TASK_4
    int L;
    std::cin >> L;
    int combustile, consum, min;
    // citirea informatiilor necesare pentru rezolvarea task-ului 4
    for (int i = 0; i < L; i++) {
        std::cin >> town >> combustile >> consum;
        // apelarea functiei TASK_4 pentru aflarea distantei minime pana
        // la prima benzilarie
        min = harta.TASK_4(towns.get_value(town).number, towns2, towns);
        if (min*consum > combustile) {
            task4 << "NU" << std::endl;
        } else {
            int ramas = combustile - min*consum;
            task4 << "DA " << ramas << std::endl;
        }
    }

    // TASK_5
    int P;
    std::cin >> P;
    // formarea hastable-ului necesar rezolvarii task-ului 5
    Hashtable<std::string, struct way> traseu(P, &hash_fct);
    struct way ruta;
    std::string source;

    for (int i = 0; i < P; i++){
        std::cin >> source >> ruta.dest >> ruta.number;
        // adaugarea informatiilor necesare in hashtable-ul construit anterior
        put_5(traseu, ruta, source);
    }

    // aflarea rutei cea mai populate din punct de vedere lexico-gramatical
    int max_value = 0;
    std::string town_1 = "", town_2 = "";
    TASK_5(traseu, max_value, N, town_1, town_2, task5, harta, towns2, towns);
    task1.close();
    task2.close();
    task3.close();
    task4.close();
    task5.close();
    return 0;
}

#endif  // __TEMA2_
