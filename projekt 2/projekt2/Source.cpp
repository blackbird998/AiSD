#include <iostream>
#include <algorithm>
#include <chrono>

using namespace std;
//zmienne globalne
int rozmiar = 32768 ;//rozmiar tablicy haszującej
int rozmiar2 = 12000000;//rozmiar tablicy z losowymi elementami
int licznik = 0;//licznik wywołań funkcji haszującej dla wstawiania
int licznik2 = 0;//licznik wywołań funkcji haszującej dla szukania
int licznik3 = 0;//licznik wywołań funkcji haszującej dla wstawiania
int licznik_wstawionych = 0;//licznik wstawionych elementów
int licznik_cal = 0;//licznik łącznych wywołań funkcji haszującej dla wstawiania
int licznik_cal2 = 0;//licznik łącznych wywołań funkcji haszującej dla szukania
double proporcja = 0;//zapełnienie przez rozmiar

//funkcje
int h1(int x);//pierwsza podfunkcja mieszająca | x - wstawiana liczba
int h2(int x);//druga podfunkcja mieszająca | x - wstawiana liczba
int h_index(int x, int i, bool lin);//główna funkcja mieszająca | x - wstawiana liczba, i - licznik, lin - 1=liniowe, 0=podwójne haszowanie
int* restru(int *tab, bool lin);//funkcja restrukturyzacyjna | tab - tablica do restrukturyzacji, i - licznik, lin - 1=liniowe, 0=podwójne haszowanie

bool hash_al_wstaw(int x, int *&tab, bool eks2, bool lin, double wspolczynnik);//funkcja wstawiająca elementy do tablicy | x - wstawiana liczba, eks2 - 1=eksperyment2, 0=eksperyment1, lin - 1=liniowe, 0=podwójne haszowanie, wspolczynnik - stopień zapełnienia tablicy
bool hash_al_szukaj(int x, int *tab, bool eks2, bool lin);//funkcja wyszukująca elementy w tablicy | x - wstawiana liczba, eks2 - 1=eksperyment2, 0=eksperyment1, lin - 1=liniowe, 0=podwójne haszowanie, wspolczynnik - stopień zapełnienia tablicy

void f_mieszajaca(int *tab2);//funkcja mieszająca elementy w tablicy tab2
void eksperyment2(int *tab2, bool lin, double wspolczynnik);//100 pomiarów dla próbki 10 000 z restrukturyzacją | lin - 1=liniowe, 0=podwójne haszowanie, wspolczynnik - stopień zapełnienia tablicy
void eksperyment1(int *tab2, bool lin);//10 pomiarów dla różnych stopni zapełnienia tablicy | lin - 1=liniowe, 0=podwójne haszowanie, wspolczynnik - stopień zapełnienia tablicy


int main(){
	int *tab2 = new int[rozmiar2];
	//zapełnienie tablicy tab2 losowymi wartościami
	f_mieszajaca(tab2);

	cout << "=================================Adresowanie podwojne=================================" << endl;
	cout << "\t\t###### Eksperyment 1 ######" << endl;
	//eksperyment1(tab2, false); //adresowanie podwójne
	cout << "\t\t###### Eksperyment 2 ######" << endl;
	cout << "Wspolczynnik zapelnienia: 0.5" << endl;
	//eksperyment2(tab2, false, 0.5);//adresowanie podwójne
	cout << "Wspolczynnik zapelnienia: 0.6" << endl;
	//eksperyment2(tab2, false, 0.6);//adresowanie podwójne
	cout << "Wspolczynnik zapelnienia: 0.8" << endl;
	eksperyment2(tab2, false, 0.8);//adresowanie podwójne

	cout << "\n=================================Adresowanie liniowe=================================" << endl;
	cout << "\t\t###### Eksperyment 1 ######" << endl;
	//eksperyment1(tab2, true); //adresowanie liniowe
	cout << "\t\t###### Eksperyment 2 ######" << endl;
	cout << "Wspolczynnik zapelnienia: 0.5" << endl;
	//eksperyment2(tab2, true, 0.5);//adresowanie liniowe
	cout << "Wspolczynnik zapelnienia: 0.6" << endl;
	eksperyment2(tab2, true, 0.6);//adresowanie liniowe
	cout << "Wspolczynnik zapelnienia: 0.8" << endl;
	eksperyment2(tab2, true, 0.8);//adresowanie liniowe
	
	delete[] tab2;

	system("pause");
	return 0;
}

int h1(int x) {
	return x % rozmiar;
}
int h2(int x) {
	return (((x / rozmiar) % (rozmiar / 2)) * 2) + 1;
}
int h_index(int x, int i, bool lin) {
	if (lin) return (x%rozmiar + i) % rozmiar;//adresowanie liniowe
	else return (h1(x) + i * h2(x)) % rozmiar;//adresowanie podwójne
}
int* restru(int *tab, bool lin) {
	licznik3++;
	//cout << "\t\t\t\t****Restrukturyzacja nr " << licznik3 <<"****"<< endl;
	licznik_wstawionych = 0;
	int rozmiar_stary = rozmiar;
	rozmiar = rozmiar * 2;
	int *tab3 = new int[rozmiar];
	for (int j = 0; j < rozmiar; j++) {
		tab3[j] = -1;
	}
	for (int i = 0; i < rozmiar_stary; i++) {
		if (tab[i] != -1) {
			hash_al_wstaw(tab[i], tab3, false, lin, 0.0);
		}
	}
	proporcja = 0;
	delete[] tab;
	return tab3;
}

bool hash_al_wstaw(int x, int *&tab, bool eks2, bool lin, double wspolczynnik) {
	int i, k;
	if (eks2) {
		if (proporcja > wspolczynnik) {
			tab = restru(tab, lin);
			licznik = 0;
		}
	}
	licznik_wstawionych++;
	for (i = 0; i < rozmiar; i++) {
		k = h_index(x, i, lin);
		licznik++;
		if (tab[k] == -1) {
			tab[k] = x;
			return 1;
		}
	}
	
	return 0;
}
bool hash_al_szukaj(int x, int *tab, bool eks2, bool lin) {
	int k;
	for (int i = 0; i < rozmiar; i++) {
		k = h_index(x, i, lin);
		licznik2++;
		if (tab[k] == x) return true;
		if (tab[k] == -1) return false;
	}
	return false;
}

void f_mieszajaca(int *tab2) {
	int l;
	for (l = 0; l < rozmiar2; l++) {
		tab2[l] = l;
	}
	random_shuffle(tab2, tab2 + rozmiar2);
}
void eksperyment1(int *tab2, bool lin) {
	rozmiar = 1048576;
	int *tab = new int[rozmiar];
	//czyszczenie tablicy tab
	for (int j = 0; j < rozmiar; j++) {
		tab[j] = -1;
	}

	int procent10 = 100000;
	int i, j;
	//Pierwszy pomiar wstawiania
	auto start = std::chrono::high_resolution_clock::now();
	for (i = 0; i < 10000; i++) {
		hash_al_wstaw(tab2[i], tab, false, lin, 0.0);
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::micro> duration = end - start;
	std::cerr << "Wstawianie: \t0% Uplynelo: " << duration.count() / 10000 << "us \t\t" << licznik << " wywolan funkcji haszujacej.\n" << endl;
	licznik = 0;
	int rownomierne, r;
	//Pomiary wyszukiwania i wstawiania dla różnych zapełnień tablicy
	for (int c = 1; c < 10; c++) {
		//Czyszczenie tablicy
		for (j = 0; j < rozmiar; j++) {
			tab[j] = -1;
		}

		//Zapełnienie tablicy w X procentach
		for (i = 0; i < procent10*c; i++) {
			hash_al_wstaw(tab2[i], tab, false, lin, 0.0);
		}
		licznik = 0;
		licznik2 = 0;

		//Pomiar szukania
		rownomierne = (procent10*c) / 10000;
		r = 0;
		auto start2 = std::chrono::high_resolution_clock::now();
		for (i = 0; i < 10000; i++) {
			hash_al_szukaj(tab2[r], tab, false, lin);
			r = r + rownomierne;
		}
		auto end2 = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::micro> duration2 = end2 - start2;
		std::cerr << "Szukanie: \t" << c << "0% Uplynelo: " << duration2.count() / 10000 << "us \t\t" << licznik2 << " wywolan funkcji haszujacej." << endl;

		//Pomiar wstawiania
		auto start = std::chrono::high_resolution_clock::now();
		for (i = procent10 * c; i < procent10*c + 10000; i++) {
			hash_al_wstaw(tab2[i], tab, false, lin, 0.0);
		}
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::micro> duration = end - start;
		std::cerr << "Wstawianie: \t" << c << "0% Uplynelo: " << duration.count() / 10000 << "us \t\t" << licznik << " wywolan funkcji haszujacej.\n" << endl;
	}
	licznik = 0;
	licznik2 = 0;
	licznik3 = 0;
	licznik_wstawionych = 0;
	delete[] tab;
}
void eksperyment2(int *tab2, bool lin, double wspolczynnik) {
	rozmiar = 32768;
	int *tab = new int[rozmiar];
	licznik_wstawionych = 0;
	//czyszczenie tablicy tab
	for (int j = 0; j < rozmiar; j++) {
		tab[j] = -1;
	}

	int rownomierne = 0;
	int r = 0;
	int i;
	//100 pomiarów dla próbki 10 000
	for (int f = 0; f < 100; f++) {

		licznik = 0;
		licznik2 = 0;
		proporcja = (double)licznik_wstawionych / (double)rozmiar;
		//pomiar wstawiania
		for (i = f * 10000; i < f * 10000 + 10000; i++) {
			hash_al_wstaw(tab2[i], tab, true, lin, wspolczynnik);
		}
		
		rownomierne = (licznik_wstawionych) / 10000;
		r = 0;
		//pomiar szukania
		for (i = 0; i < 10000; i++) {
			hash_al_szukaj(tab2[r], tab, true, lin);
			r = r + rownomierne;
		}

		proporcja = (double)licznik_wstawionych / (double)rozmiar;
		//cout << "Pomiar " << f + 1 << ": " << licznik << " wywolan funkci haszujacej dla wstawiania, "<< licznik2 << " wywolan funkci haszujacej dla wyszukiwania." << endl;
		//cout << "Rozmiar tablicy haszujacej: " << rozmiar << "\t\tWstawiono: " << licznik_wstawionych << " elementow. Wspolczynnik zapelnienia: " <<proporcja<<".\n"<< endl;
		cout << rozmiar << endl;
		licznik_cal = licznik_cal + licznik;
		licznik_cal2 = licznik_cal2 + licznik2;
		
	}
	cout << "Laczna liczba wywolan funkcji haszujacej dla wstawiania: " << licznik_cal << endl;
	cout << "Laczna liczba wywolan funkcji haszujacej dla szukania: " << licznik_cal2 << endl;
	cout << "Lacznie restrukturyzacji: " << licznik3 << endl;
	licznik = 0;
	licznik2 = 0;
	licznik3 = 0;
	licznik_wstawionych = 0;
	licznik_cal = 0;
	licznik_cal2 = 0;
	delete[] tab;
}