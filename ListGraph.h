/*
 *  Copyright [2018] <CIUPITU DENNIS-MIRCEA 313CA>
 */

#ifndef LISTGRAPH_H_
#define LISTGRAPH_H_

#include <vector>
#include <string>
#include <stack>
#include <queue>

#include "Hashtable.h"

template <typename T> struct Node {
    std::vector<T> neighbors;
};

template <typename T> class ListGraph {
 private:
    std::vector<Node <T> > nodes;  // nodurile listei
    int size;  // numarul de elemente din lista
    std::vector<bool> vis;

 public:
    // Constructor
    explicit ListGraph(int size) {
        this->size = size;
        nodes.resize(size);
        vis.resize(size);
    }

    ListGraph<T> operator=(ListGraph<T>& other) {
        this->size = other.size;
        this->nodes.resize(other.size);
        this->nodes = other.nodes;
        this->vis.resize(other.size);
        this->vis = other.vis;
        return *this;
    }

    ListGraph(ListGraph<T>& other) {
        this->size = other.size;
        this->nodes.resize(other.size);
        this->nodes = other.nodes;
        this->vis.resize(other.size);
        this->vis = other.vis;
    }
    // Destructor
    ~ListGraph() {}

    void print() {
        for (int i = 0; i < size; i++) {
            std::cout << i << "-";
            for (auto it = nodes[i].neighbors.begin();
                    it != nodes[i].neighbors.end(); it++) {
                std::cout << " " << *it;
            }
            std::cout << std::endl;
        }
    }
    void addEdge(T src, T dst) {
        nodes[dst].neighbors.push_back(src);
    }

    void removeEdge(T src, T dst) {
        for (auto it = nodes[dst].neighbors.begin();
                it != nodes[dst].neighbors.end(); ++it) {
            if (*it == src) {
                nodes[dst].neighbors.erase(it);
                break;
            }
        }
    }

    bool hasEdge(T src, T dst) {
        for (auto it = nodes[dst].neighbors.begin();
                it != nodes[dst].neighbors.end(); ++it) {
            if (*it == src) {
                return true;
            }
        }
        return false;
    }

    std::vector<T> getNeighbors(T node) {
        return nodes[node].neighbors;
    }

    std::stack<T> minPath(int N, T source, T dest) {
        std::vector<bool> visited(N, false);
        std::queue<T> q;
        // vector de parinti
        std::vector<T> parent(N, 0);

        // initializari
        visited[source] = true;
        q.push(source);

        // BFS
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto it = nodes[v].neighbors.begin();
                    it != nodes[v].neighbors.end(); it++) {
                if (visited[*it] == false) {
                    visited[*it] = true;
                    if (parent[*it] == 0) {
                        parent[*it] = v;
                    }
                    q.push(*it);
                } else {
                    // daca exista un oras intermadiar din punct de vedere
                    // lexico gramatical mai mic
                    int p = parent[*it];
                    if (parent[p] == parent[v] && v < parent[*it]) {
                    parent[*it] = v;
                    }
                }
            }
        }

        std::stack<T> path;
        // Daca nu exista cale de a sursa la destinatie
        if (parent[dest] == 0) return path;

        // crearea traseului minim
        int dest1 = dest;
        while (dest1 != source) {
            path.push(dest1);
            dest1 = parent[dest1];
        }
        path.push(dest1);
        return path;
    }

    void TASK_3(T source, Hashtable<int,
            std::string>& towns2, ListGraph<int>& harta_t, std::ostream& out) {
        std::vector<bool> visited1(size, false), visited2(size, false);
        std::queue<T> q1;
        // BFS pentru graful normal
        visited1[source] = true;
        q1.push(source);

        while (!q1.empty()) {
            int v = q1.front();
            q1.pop();
            for (auto it = nodes[v].neighbors.begin();
                    it != nodes[v].neighbors.end(); it++) {
                    if (visited1[*it] == false) {
                        visited1[*it] = true;
                        q1.push(*it);
                    }
            }
        }

        // BFS pentru graful transpus
        visited2[source] = true;
        q1.push(source);

        while (!q1.empty()) {
            int v = q1.front();
            q1.pop();
            for (auto it = harta_t.nodes[v].neighbors.begin();
                    it != harta_t.nodes[v].neighbors.end(); it++) {
                if (visited2[*it] == false) {
                    visited2[*it] = true;
                    q1.push(*it);
                }
            }
        }
        // verificarea oraselor inaccesibile
        for (int j = 0; j < size; j++) {
            if (visited1[j] == false) {
                out << towns2.get_value(j) << " ";
            }
            if (visited1[j] == true && visited2[j] == false) {
                out << towns2.get_value(j) << " ";
            }
        }
    }

    int TASK_4(T source, Hashtable<int, std::string>& towns2,
                Hashtable<std::string, class oras>& towns) {
        std::vector<bool> visited4(size, false);
        std::queue<T> q4;
        std::vector<T> dist(size, 100000);

        int lungime;  // variabila care va retine lungimea minima a traseului
                        // pana la prima benzinarie

        // initializari
        dist[source] = 0;
        visited4[source] = true;
        q4.push(source);

        // BFS
        while (!q4.empty()) {
            int v = q4.front();
            q4.pop();
            int yes = 0;
            for (auto it = nodes[v].neighbors.begin();
                    it != nodes[v].neighbors.end(); it++) {
                    if (visited4[*it] == false) {
                        dist[*it] = dist[v] + 1;
                        // daca a gasit orasul cu benzinaria retine distanta
                        // curenta pana la nodul sursa si iese din for
                        if (towns.get_value(towns2.get_value(*it)).benzinarie) {
                            lungime = dist[*it];
                            yes = 1;
                            break;
                        }
                        visited4[*it] = true;
                        q4.push(*it);
                    }
            }
            // daca a gasit benzinarie iese si din while
            if (yes == 1) {
                break;
            }
        }
        return lungime;
    }

    bool accesibility(ListGraph<int>& harta_t) {
        // BFS pe graful normal
        std::queue<T> q;
        for (int i = 0; i < size; i++) {
             vis[i] = false;
        }
        // alegem nodul 0 ca nod sursa
        // vis[0] = true;
        q.push(0);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto it = nodes[v].neighbors.begin();
                    it != nodes[v].neighbors.end(); it++) {
                    if (vis[*it] == false) {
                        vis[*it] = true;
                        q.push(*it);
                    }
            }
        }
        // daca un nod a ramas nevizitat functia intoarce false
        for (int j = 0; j < size; j++) {
            if (vis[j] == false) {
                return false;
            }
        }

        // BFS pe graful transpus
        for (int i = 0; i < size; i++) {
             vis[i] = false;
        }
        // alegem tot nodul 0 ca nod sursa
        vis[0] = true;
        q.push(0);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto it = harta_t.nodes[v].neighbors.begin();
                    it != harta_t.nodes[v].neighbors.end(); it++) {
                    if (vis[*it] == false) {
                        vis[*it] = true;
                        q.push(*it);
                    }
            }
        }
        // daca un nod a ramas nevizitat functia intoarce false
        for (int j = 1; j < size; j++) {
            if (vis[j] == false) {
                return false;
            }
        }
        // daca s-au vizitat toate nodurile in ambele BFS-uri
        // functia intoarce true
        return true;
    }
    int getSize() {
        return size;
    }
};

#endif  // LISTGRAPH_H_
