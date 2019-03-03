# Hit-the-road


MENTIUNE - functiile de hash, o parte din implementarea hashtable-ului si
a listei de grafuri sunt luate din laborator;

Am ales la inceput sa lucrez cu doua hastable-uri
generice si cu 2 liste de adiacenta:
	-> towns - hashtable string to class oras(clasa ce retine numarul de ordine
al fiecarui oras atribuit prin citirea consecutiva de la tastatura, cat si o
valoare booleana care retine daca in orasul respectiv este o benzinarie sau nu)
	-> towns2 - hashtable int to string, adica cheia va fi numarul de ordine al
orasului, iar valoarea retinuta va fi chiar numarul orasului;
	-> harta - lista de adiacenta a grafului normal care va fi int to int(va
lucra cu numerele de ordine ale fiecarui oras);
	-> harta_t - lista de adiacenta a grafului transpus care fi implementata
la fel ca lista harta;

Rezolvarea TASK-urilor:
---TASK_1---
>> Am parcurs intreaga lista de adiacenta a grafului transpus si am
verificat pentru fiecare nod in parte numarul de vecini(adica numarul de
autostrazi care intra in fiecare oras) si astfel am retinut numarul de ordine
al orasului unde intra cele mai multe autostrazi cat si numarul de autostrazi,
si am afisat orasul de la numarul de ordine respectiv cat si valoarea gradului
de aglomerare;

---TASK_2---
>> Am verificat daca harta este valida sau nu cu ajutorului functiei
accesibility care intoarce true daca harta este valida si false daca harta este
invalida. Aceasta functie face 2 BFS-uri, atat pe graful normal cat si pe
graful transpus plecand dintr-un nod aleator(am ales nodul 0), iar daca la
finalul unui BFS un nod nu a fost vizitat functia se opreste si intoarce false,
iar daca nu intoarce true;

---TASK_3---
>> Pentru rezolvarea acestui task, am construit functia TASK_3 pe care o
apelez dupa ce citesc cate un oras de la tastatura caruia trebuie sa-i aflu
orasele inaccesibile. Aceasta functie face mai intai un BFS pe graful normal,
avand ca nod sursa numarul de ordine al orasului caruia vrem sa-i aflam orasele
inaccesibile, iar apoi face un BFS si pe graful transpus. Daca la final un oras
a fost vizitat intr-o parcurgere BFS, iar in cealalta nu, inseamna ca si acesta
din urma este inaccesibili, alaturi de celelalte orase care n-au fost vizitate
de la inceput;

---TASK_4---
>> Pentru rezolvarea acestui task, am construit functia TASK_4, pe care o
apelez dupa ce am fixat orasele cu benzinarii si am citit pe rand de la tasta-
tura orasul din care se pleaca, combustibilul, si consumu per unitate. Aceasta
functie face un BFS pentru numarul de ordine al orasului dat ca parametru, si
cauta cea mai apropiata benzinarie, iar cand o gaseste, retine distanta de la
nodul curent catre sursa, distanta care va fii minima pentru ajungerea la cea
mai apropiata benzinarie. Dupa ce se iese din functie se verifica lungimea
drumului ori consumul per unitate este mai mare decat combustibilul, iar apoi
se afiseaza un mesaj corespunzator;

---TASK_5---
>> Pentru rezolvarea acestui task am creat un hashtable string(orasul
sursa) to struct way(structura care retine destinatia traseului dat, cat si
numarul de calatori ai treseului), pentru a memora eficient toate rutele
citite de la tastatura. Am creat functia put_5 care adauga in hashtable-ul
nou creat o structura de tip way la un oras sursa(adica pentru fiecare oras
sursa pot exista mai multe destinatii, cu numar diferit de calatori; acest
hashtable are ca rol retinerea tuturor rutelor pentru fiecare oras cat si
numarul de calatori care parcurg acel traseu, cu conditia ca, in cazul
repetarii unei rute, adica adaugarea unei rute deja existente, aceasta va avea
drept rezultat cresterea numarului de calatori care parcurg acea ruta). In
final apelez functia TASK_5 care selecteaza ruta cea mai frecventata de cala-
tori din punct de vedere lexico-gramatical, iar apoi pentru acea ruta, se afla
orasele intermediare prin care va trece autobuzul prin apelarea functiei
minPath din cadrul headerului ListGraph.h. Apoi se vor afisa pe rand orasele
intermediare; 

