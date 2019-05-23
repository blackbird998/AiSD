#include <iostream>
#include <algorithm>
#include <chrono>
using namespace std;

int rozmiar = 32768 ;//1048576;
int rozmiar2 = 12000000;
int licznik = 0;
int licznik2 = 0;
int licznik3 = 0;
int licznik_wstawionych = 0;
int licznik_cal = 0;
float proporcja = 0;
/*
int h_index(int x, int i) {
	return (x%rozmiar + i) % rozmiar;
}*/
int h1(int x) {
	return x%rozmiar;
}

int h2(int x) {
	return (((x / rozmiar) % (rozmiar / 2)) * 2) + 1;
}

int h_index(int x, int i) {
	return (h1(x)+i*h2(x)) % rozmiar;
}
int* restru(int *tab);

bool hash_al_wstaw(int x, int *&tab) {
	int i,k;
	
	
	licznik_wstawionych++;
	
	proporcja = (float)licznik_wstawionych / (float)rozmiar;
	if (proporcja > 0.60) {
		cout << "restru" << endl;
		tab = restru(tab);
	}
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

void f_mieszajaca(int *tab2) {
	int l;
	for (l = 0; l < rozmiar2; l++) {
		tab2[l] = l;
	}
	random_shuffle(tab2, tab2 + rozmiar2);
}

bool hash_al_szukaj(int x, int *tab) {
	int k;
	for (int i = 0; i < rozmiar; i++) {
		k = h_index(x, i);
		licznik2++;
		if (tab[k] == x) return true;
		if (tab[k] == -1) return false;
	}
	return false;
}



int main(){
	/*int x = 7;
	int y = 10;
	float z = (float)x / (float)y;
	cout << z << endl;
	if(z>0.5) cout << z << endl;
	*/

	int *tab = new int[rozmiar];
	int *tab2 = new int[rozmiar2];

	int j,i;
	for (j = 0; j < rozmiar; j++) {
		tab[j] = -1;
	}
	f_mieszajaca(tab2);

	for (int f = 0; f < 100; f++) {
		
		//cout << proporcja << endl;
		for (i = 0;i < 10000;i++) {
			hash_al_wstaw(tab2[i], tab);
			
		}
		for (i = 0;i < 10000;i++) {
			hash_al_szukaj(tab2[i], tab);
		}
		cout << "Pomiar " << f + 1 << ": " << licznik << " wywolan wstawiania, " << licznik2 << " wywolan wyszukiwania, " << licznik3 << " restrukturyzacji" << endl;
		licznik_cal = licznik_cal + licznik;
		licznik = 0;
		licznik2 = 0;
	}
	cout << "licznik cal: " << licznik_cal << endl;


	/*
	int procent10 = 100000;
	auto start = std::chrono::high_resolution_clock::now();
	//tutaj mierzona operacja
	for (i = 0;i < 10000;i++) {
		hash_al_wstaw(tab2[i], tab);
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::micro> duration = end - start;
	std::cerr << "Wstawianie: 0% Uplynelo: " << duration.count()/10000 << "us " << licznik << " wywolan.\n"<<endl;
	licznik = 0;
	*/
	/*
	for (int c = 1; c < 10; c++) {
		for (j = 0; j < rozmiar; j++) {
			tab[j] = -1;
		}
		
		for (i = 0;i < procent10*c;i++) {
			hash_al_wstaw(tab2[i], tab);
		}
		licznik = 0;
		licznik2 = 0;
		auto start2 = std::chrono::high_resolution_clock::now();
		int rownomierne = (procent10*c) / 10000;
		int r = 0;
		for (i = 0;i < 10000;i++) {
			hash_al_szukaj(tab2[r], tab);
			r = r + rownomierne;
		}
		auto end2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::micro> duration2 = end2 - start2;
		std::cerr << "Szukanie: " << c << "0% Uplynelo: " << duration2.count() / 10000 << "us " << licznik2 << " wywolan.\n" << endl;
		//pomiar
		auto start = std::chrono::high_resolution_clock::now();
		for (i = procent10*c;i < procent10*c + 10000;i++) {
			hash_al_wstaw(tab2[i], tab);
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::micro> duration = end - start;
		std::cerr <<"Wstawianie: "<< c << "0% Uplynelo: " << duration.count() / 10000 << "us " << licznik << " wywolan.\n" << endl;
		//wyszukanie
	}
	//*/
	//cout << end;

	delete[] tab;
	delete[] tab2;
	system("pause");
	return 0;
}


int* restru(int *tab) {
	int rozmiar_stary = rozmiar;
	rozmiar = rozmiar * 2;
	int *tab3 = new int[rozmiar];
	licznik3++;
	for (int j = 0; j < rozmiar; j++) {
		tab3[j] = -1;
	}
	for (int i = 0;i < rozmiar_stary; i++) {
		if (tab[i] != -1) {
			hash_al_wstaw(tab[i], tab3);
		}
	}
	return tab3;
}