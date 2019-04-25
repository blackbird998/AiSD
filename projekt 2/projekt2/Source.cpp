#include <iostream>
#include <algorithm>
#include <chrono>
using namespace std;


const int rozmiar = 1048576;
int *tab = new int[rozmiar];
const int rozmiar2 = 12000000;
int *tab2= new int[rozmiar2];
int licznik = 0;

int h_index(int x, int i) {
	
	return (x%rozmiar + i) % rozmiar;
}

bool hash_al_wstaw(int x) {
	int i,k;
	for (i = 0; i < rozmiar; i++) {
		
		k = h_index(x, i);
		licznik++;
		if (tab[k] == -1) {
			tab[k] = x;
			return 1;
		}
	}
	return 0;
}

void f_mieszajaca() {
	int l;
	for (l = 0; l < rozmiar2; l++) {
		tab2[l] = l;
	}
	random_shuffle(tab2, tab2 + rozmiar2);
}


int main(){
	int j,i;
	for (j = 0; j < rozmiar; j++) {
		tab[j] = -1;
	}
	f_mieszajaca();
	
	int procent10 = 100000;
	auto start = std::chrono::high_resolution_clock::now();
	//tutaj mierzona operacja
	for (i = 0;i < 10000;i++) {
		hash_al_wstaw(tab2[i]);
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::micro> duration = end - start;
	std::cerr << "0% Uplynelo: " << duration.count()/10000 << "us\n " << licznik << " wywolan."<<endl;
	licznik = 0;
	for (int c = 1; c < 10; c++) {
		for (j = 0; j < rozmiar; j++) {
			tab[j] = -1;
		}
		//tutaj mierzona operacja
		for (i = 0;i < procent10*c;i++) {
			hash_al_wstaw(tab2[i]);
		}
		licznik = 0;
		auto start = std::chrono::high_resolution_clock::now();
		for (i = procent10*c;i < procent10*c + 10000;i++) {
			hash_al_wstaw(tab2[i]);
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::micro> duration = end - start;
		std::cerr << c << "0% Uplynelo: " << duration.count() / 10000 << "us\n " << licznik << " wywolan." << endl;
		
	}


	delete[] tab;
	system("pause");
	return 0;
}