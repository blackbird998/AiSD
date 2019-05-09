#include <iostream>
#include <algorithm>
#include <chrono>
using namespace std;


const int rozmiar = 1048576;
int *tab = new int[rozmiar];
const int rozmiar2 = 12000000;
int *tab2= new int[rozmiar2];
int licznik = 0;
int licznik2 = 0;
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

bool hash_al_szukaj(int x) {
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
	std::cerr << "Wstawianie: 0% Uplynelo: " << duration.count()/10000 << "us " << licznik << " wywolan.\n"<<endl;
	licznik = 0;
	for (int c = 1; c < 10; c++) {
		for (j = 0; j < rozmiar; j++) {
			tab[j] = -1;
		}
		
		for (i = 0;i < procent10*c;i++) {
			hash_al_wstaw(tab2[i]);
		}
		licznik = 0;
		licznik2 = 0;
		auto start2 = std::chrono::high_resolution_clock::now();
		int rownomierne = (procent10*c) / 10000;
		int r = 0;
		for (i = 0;i < 10000;i++) {
			hash_al_szukaj(tab2[r]);
			r = r + rownomierne;
		}
		auto end2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::micro> duration2 = end2 - start2;
		std::cerr << "Szukanie: " << c << "0% Uplynelo: " << duration2.count() / 10000 << "us " << licznik2 << " wywolan.\n" << endl;
		//pomiar
		auto start = std::chrono::high_resolution_clock::now();
		for (i = procent10*c;i < procent10*c + 10000;i++) {
			hash_al_wstaw(tab2[i]);
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::micro> duration = end - start;
		std::cerr <<"Wstawianie: "<< c << "0% Uplynelo: " << duration.count() / 10000 << "us " << licznik << " wywolan.\n" << endl;
		//wyszukanie


	}


	delete[] tab;
	system("pause");
	return 0;
}