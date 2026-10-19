#include "../include/pertandingan.h"

#include <iostream>

using namespace std;

void tampilkanPertandingan() {
	if (daftar.empty()) {
		cout << "Belum ada pertandingan.\n";
		return;
	}

	cout << "\nDAFTAR PERTANDINGAN\n";

	for (int i = 0; i < daftar.size(); i++) {
		cout << "\nID: " << daftar[i].id << endl;
		cout << "Tim kandang: " << daftar[i].timKandang << endl;
		cout << "Tim tandang: " << daftar[i].timTandang << endl;
		cout << "Skor: " << daftar[i].skorKandang << "-"
			 << daftar[i].skorTandang << endl;
		cout << "Tanggal: " << daftar[i].tanggal << endl;
		cout << "-------------------------\n";
	}
}

void tampilkanKlasemen() {
	vector<KlasemenTim> klasemen = buatKlasemen();

	cout << "\nKLASEMEN\n";

	for (int i = 0; i < klasemen.size(); i++) {
		cout << "\nPeringkat: " << i + 1 << endl;
		cout << "Tim: " << klasemen[i].nama << endl;
		cout << "Main: " << klasemen[i].main << endl;
		cout << "Menang: " << klasemen[i].menang << endl;
		cout << "Seri: " << klasemen[i].seri << endl;
		cout << "Kalah: " << klasemen[i].kalah << endl;
		cout << "Gol memasukkan: " << klasemen[i].memasukkan << endl;
		cout << "Gol kebobolan: " << klasemen[i].kebobolan << endl;
		cout << "Selisih gol: " << klasemen[i].selisihGol() << endl;
		cout << "Poin: " << klasemen[i].poin << endl;
		cout << "-------------------------\n";
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
