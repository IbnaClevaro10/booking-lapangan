#include "../include/berkas.h"
#include "../include/tampilan.h"

#include <iostream>

using namespace std;

int main() {
	DaftarPertandingan daftar = bacaPertandingan();
	int pilihan;
	tampilkanJudul();

	do {
		tampilkanMenu();
		cout << "\nPilih menu: ";
		if (!(cin >> pilihan)) {
			cin.clear();
			cin.ignore(10000, '\n');
			cout << "Pilihan harus berupa angka.\n";
			continue;
		}
		cin.ignore(10000, '\n');

		switch (pilihan) {
			case 1: tampilkanPertandingan(daftar); break;
			case 2: tambahPertandingan(daftar); break;
			case 3: editPertandingan(daftar); break;
			case 4: hapusPertandingan(daftar); break;
			case 5: cariPertandingan(daftar); break;
			case 6: tampilkanKlasemen(daftar); break;
			case 0: cout << "Program selesai.\n"; break;
			default: cout << "Menu tidak tersedia.\n";
		}
	} while (pilihan != 0);

	return 0;
}
