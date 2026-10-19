#include "../include/pertandingan.h"

#include <iostream>

using namespace std;

void tampilkanPertandingan() {
	if (daftar.empty()) {
		cout << "Belum ada pertandingan.\n";
		return;
	}

	cout << "\nDAFTAR PERTANDINGAN\n";
	cout << "ID\tKANDANG\t\tTANDANG\t\tSKOR\tTANGGAL\n";
	cout << "------------------------------------------------------------\n";

	int jumlahPertandingan = daftar.size();
	for (int i = 0; i < jumlahPertandingan; i++) {
		cout << daftar[i].id << "\t"
			 << daftar[i].timKandang << "\t\t"
			 << daftar[i].timTandang << "\t\t"
			 << daftar[i].skorKandang << "-"
			 << daftar[i].skorTandang << "\t"
			 << daftar[i].tanggal << endl;
	}
}

void tampilkanKlasemen() {
	vector<KlasemenTim> klasemen = buatKlasemen();

	cout << "\nKLASEMEN\n";
	cout << "NO\tTIM\t\tMAIN\tMENANG\tSERI\tKALAH\tGM\tGK\tSG\tPOIN\n";
	cout << "------------------------------------------------------------------\n";

	int jumlahTim = klasemen.size();
	for (int i = 0; i < jumlahTim; i++) {
		cout << i + 1 << "\t"
			 << klasemen[i].nama << "\t\t"
			 << klasemen[i].main << "\t"
			 << klasemen[i].menang << "\t"
			 << klasemen[i].seri << "\t"
			 << klasemen[i].kalah << "\t"
			 << klasemen[i].memasukkan << "\t"
			 << klasemen[i].kebobolan << "\t"
			 << klasemen[i].selisihGol() << "\t"
			 << klasemen[i].poin << endl;
	}
}

void menuUtama() {
	int pilihan;
	do {
		cout << "\n===== UCL MINI LEAGUE =====\n"
			 << "1. Tampilkan pertandingan\n"
			 << "2. Tambah pertandingan\n"
			 << "3. Edit pertandingan\n"
			 << "4. Hapus pertandingan\n"
			 << "5. Cari pertandingan\n"
			 << "6. Tampilkan klasemen\n"
			 << "0. Keluar\n";

		cout << "Pilih menu: ";
		cin >> pilihan;
		cin.ignore(1000, '\n');
		switch (pilihan) {
			case 1: tampilkanPertandingan(); break;
			case 2: tambahPertandingan(); break;
			case 3: editPertandingan(); break;
			case 4: hapusPertandingan(); break;
			case 5: cariPertandingan(); break;
			case 6: tampilkanKlasemen(); break;
			case 0: cout << "Program selesai.\n"; break;
			default: cout << "Menu tidak tersedia.\n";
		}
	} while (pilihan != 0);
}

int main() {
	bacaFile();
	menuUtama();
	return 0;
}
