/*
 *  Copyright [2018] <CIUPITU DENNIS-MIRCEA 313CA>
 */

#ifndef HASHTABLE_H_
#define HASHTABLE_H_
#include <iterator>
#include <list>

#define TRESHOLD 0.75

class oras {
 public:
    bool benzinarie;  // daca exista benzinarie
    int number;  // numarul de ordine

    // Rule of three
    oras() {
        this->benzinarie = false;
        this->number = -1;
    }

    oras(const oras& other) {
        this->benzinarie = other.benzinarie;
        this->number = other.number;
    }

    oras operator=(const oras& other) {
        this->benzinarie = other.benzinarie;
        this->number = other.number;
        return *this;
    }
};

template <typename Tkey, typename Tvalue> struct elem_info {
	Tkey key;
	Tvalue value;
};

template <typename Tkey, typename Tvalue> class Hashtable {
 public:
	std::list<struct elem_info<Tkey, Tvalue> > * H;  // pointer la buckets
	int HMAX;  // numarul de liste(buckets)
	unsigned int (*hash)(Tkey);  // pointer la functia de hash
	unsigned int size;  // numarul elementelor din hashtable

	Hashtable(int hmax, unsigned int (*h)(Tkey)) {
		HMAX = hmax;
		hash = h;
		H = new std::list<struct elem_info<Tkey, Tvalue> > [HMAX];
		size = 0;
	}

	~Hashtable() {
		int i;
		for (i = 0; i < HMAX; i++)
			while (!H[i].empty()) {
				H[i].pop_front();
			}
		delete[] H;
	}

	Hashtable<Tkey, Tvalue>& operator=(const Hashtable<Tkey, Tvalue>& other) {
		this->HMAX = other.HMAX;
		this->hash = other.hash;
		this->H = new std::list<struct elem_info<Tkey, Tvalue> > [other.HMAX];
		for (int i = 0; i < other.HMAX; i++) {
			this->H[i].resize(other.H[i].size());
			this->H[i] = other.H[i];
		}
		this->size = other.size;
		return *this;
	}

	Hashtable(const Hashtable<Tkey, Tvalue>& other) {
		this->HMAX = other.HMAX;
		this->hash = other.hash;
		this->H = new std::list<struct elem_info<Tkey, Tvalue> > [other.HMAX];
		for (int i = 0; i < other.HMAX; i++) {
			this->H[i].resize(other.H[i].size());
			this->H[i] = other.H[i];
		}
		this->size = other.size;
	}

	// functie pentru afisarea hashtable-ului
	void print() {
		for (int i = 0; i < HMAX; i++) {
			if (!H[i].empty()) {
				for (auto it = H[i].begin(); it != H[i].end(); ++it) {
					std::cout << it->key << " " << it->value << " ";
				}
				std::cout << std::endl;
			}
		}
	}

	void put(Tkey key, Tvalue value) {
		struct elem_info<Tkey, Tvalue> p;
		int hkey = hash(key) % HMAX;
		int q = 0;
		for (auto it = H[hkey].begin(); it != H[hkey].end(); ++it) {
			if (it->key == key) {
				it->value = value;
				q = 1;
		 	}
		 }
		 if (q == 0){
			p.key = key;
			p.value = value;
			H[hkey].push_back(p);
			size++;
		 }
		if ((float)size / (float)HMAX > 0.75) resize();
	}

	void remove(Tkey key) {
		int hkey = hash(key) % HMAX;
		int q = 0;
		typename std::list<struct elem_info<Tkey, Tvalue>> :: iterator it;
		for (it = H[hkey].begin(); it != H[hkey].end(); ++it) {
			if (it->key == key) {
				q = 1;
				break;
			}
		}
		if (q == 0 && it != H[hkey].end()) {
			std::cerr << "ERORR" <<std::endl;
		}
		if (it != H[hkey].end()) {
			H[hkey].erase(it);
			size--;
		}
	}

	Tvalue get_value(Tkey key) {
		Tvalue aux;
		int hkey = hash(key) % HMAX;
		for (auto it = H[hkey].begin(); it != H[hkey].end(); ++it) {
			if (it->key == key) {
				return it->value;
				break;
			}
		}
		return aux;
	}

	Tkey get_key(Tvalue value) {
		for (int i = 0; i < HMAX; i++) {
			if(!H[i].empty()) {
				for (auto it = H[i].begin(); it != H[i].end(); it++) {
					if (it->value == value) {
						return it->key;
					}
				}
			}
		}
		return 0;
	}

	bool has_key(Tkey key) {
		int hkey = hash(key) % HMAX;
		for (auto it = H[hkey].begin(); it != H[hkey].end(); ++it) {
			if (it->key == key) {
				return true;
			}
		}
		return false;
	}

	bool has_value(Tvalue value) {
		for (int i = 0; i < HMAX; i++) {
			if(!H[i].empty()) {
				for (auto it = H[i].begin(); it != H[i].end(); it++) {
					if (it->value == value) {
						return true;
					}
				}
			}
		}
		return false;
	}

	void resize() {
		std::list<struct elem_info<Tkey, Tvalue> > *newH;
		newH = new std::list<struct elem_info<Tkey, Tvalue> > [2*HMAX];
		typename std::list<struct elem_info<Tkey, Tvalue> >::iterator it;
		for(int i = 0; i < HMAX ; i++){
			for(it = H[i].begin(); it != H[i].end(); ++it) {
				int index1 = hash(it -> key) % (2 * HMAX);
				newH[index1].push_back(*it);
			}
		}
		delete[] H;
		H = newH;
		HMAX = 2 * HMAX;
	}

	int get_size() {
		return size;
	}

	int get_capacity() {
		return HMAX;
	}

	float current_factor(){
		return (float)(size) / (float)(HMAX);
	}
};

#endif  // HASHTABLE_H_
