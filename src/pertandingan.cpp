#include "../include/pertandingan.h"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

const string NAMA_FILE = "data/pertandingan.txt";
string DAFTAR_TIM[5] = {
	"PSG", "Liverpool", "Barcelona", "Real Madrid", "Man City"
};

vector<Pertandingan> daftar;

int ubahKeAngka(string teks) {
	int angka = 0;
	int jumlahHuruf = teks.length();
	for (int i = 0; i < jumlahHuruf; i++) {
		angka = angka * 10 + (teks[i] - '0');
	}
	return angka;
}

string pilihTim(string pesan) {
	int pilihan;

	cout << pesan << '\n';
	for (int i = 0; i < 5; i++) {
		cout << i + 1 << ". " << DAFTAR_TIM[i] << '\n';
	}

	do {
		cout << "Pilihan: ";
		cin >> pilihan;
		if (pilihan < 1 || pilihan > 5) {
			cout << "Pilihan tim tidak tersedia.\n";
		}
	} while (pilihan < 1 || pilihan > 5);

	return DAFTAR_TIM[pilihan - 1];
}

Pertandingan isiPertandingan(int id) {
	Pertandingan pertandingan;
	pertandingan.id = id;
	pertandingan.timKandang = pilihTim("Pilih tim kandang:");

	do {
		pertandingan.timTandang = pilihTim("Pilih tim tandang:");
		if (pertandingan.timKandang == pertandingan.timTandang) {
			cout << "Tim kandang dan tandang tidak boleh sama.\n";
		}
	} while (pertandingan.timKandang == pertandingan.timTandang);

	cout << "Skor kandang: ";
	cin >> pertandingan.skorKandang;
	cout << "Skor tandang: ";
	cin >> pertandingan.skorTandang;
	cin.ignore(1000, '\n');
	cout << "Tanggal (DD-MM-YYYY): ";
	getline(cin, pertandingan.tanggal);
	return pertandingan;
}

void bacaFile() {
	ifstream file(NAMA_FILE);
	string baris;

	while (getline(file, baris)) {
		string bagian;
		vector<string> kolom;
		stringstream stream(baris);

		while (getline(stream, bagian, ',')) {
			kolom.push_back(bagian);
		}

		if (kolom.size() != 6) {
			continue;
		}

		daftar.push_back({
			ubahKeAngka(kolom[0]), kolom[1], kolom[2],
			ubahKeAngka(kolom[3]), ubahKeAngka(kolom[4]), kolom[5]
		});
	}
}

void simpanFile() {
	ofstream file(NAMA_FILE);
	if (!file) {
		cout << "Gagal menyimpan data.\n";
		return;
	}

	for (Pertandingan pertandingan : daftar) {
		file << pertandingan.id << ',' << pertandingan.timKandang << ','
			 << pertandingan.timTandang << ',' << pertandingan.skorKandang << ','
			 << pertandingan.skorTandang << ',' << pertandingan.tanggal << '\n';
	}
}

int idBaru() {
	int id = 1;
	for (Pertandingan pertandingan : daftar) {
		if (pertandingan.id >= id) {
			id = pertandingan.id + 1;
		}
	}
	return id;
}

void tambahPertandingan() {
	daftar.push_back(isiPertandingan(idBaru()));
	simpanFile();
	cout << "Pertandingan berhasil ditambahkan.\n";
}

void editPertandingan() {
	int id;
	cout << "Masukkan ID pertandingan yang diedit: ";
	cin >> id;
	int jumlahPertandingan = daftar.size();
	for (int i = 0; i < jumlahPertandingan; i++) {
		if (daftar[i].id == id) {
			daftar[i] = isiPertandingan(id);
			simpanFile();
			cout << "Pertandingan berhasil diedit.\n";
			return;
		}
	}
	cout << "ID pertandingan tidak ditemukan.\n";
}

void hapusPertandingan() {
	int id;
	cout << "Masukkan ID pertandingan yang dihapus: ";
	cin >> id;
	int jumlahPertandingan = daftar.size();
	for (int i = 0; i < jumlahPertandingan; i++) {
		if (daftar[i].id == id) {
			daftar.erase(daftar.begin() + i);
			simpanFile();
			cout << "Pertandingan berhasil dihapus.\n";
			return;
		}
	}
	cout << "ID pertandingan tidak ditemukan.\n";
}

void cariPertandingan() {
	int id;
	cout << "Masukkan ID pertandingan: ";
	cin >> id;

	int jumlahPertandingan = daftar.size();
	for (int i = 0; i < jumlahPertandingan; i++) {
		if (daftar[i].id == id) {
			cout << "Pertandingan ditemukan.\n";
			cout << "Tim: " << daftar[i].timKandang << " vs "
				 << daftar[i].timTandang << endl;
			cout << "Skor: " << daftar[i].skorKandang << "-"
				 << daftar[i].skorTandang << endl;
			cout << "Tanggal: " << daftar[i].tanggal << endl;
			return;
		}
	}

	cout << "Pertandingan tidak ditemukan.\n";
}

vector<KlasemenTim> buatKlasemen() {
	vector<KlasemenTim> klasemen;
	for (string nama : DAFTAR_TIM) {
		klasemen.push_back({nama});
	}

	for (Pertandingan pertandingan : daftar) {
		int kandang = -1;
		int tandang = -1;
		int jumlahTim = klasemen.size();

		for (int i = 0; i < jumlahTim; i++) {
			if (klasemen[i].nama == pertandingan.timKandang) kandang = i;
			if (klasemen[i].nama == pertandingan.timTandang) tandang = i;
		}

		if (kandang == -1 || tandang == -1 || kandang == tandang) continue;

		klasemen[kandang].main++;
		klasemen[tandang].main++;
		klasemen[kandang].memasukkan += pertandingan.skorKandang;
		klasemen[kandang].kebobolan += pertandingan.skorTandang;
		klasemen[tandang].memasukkan += pertandingan.skorTandang;
		klasemen[tandang].kebobolan += pertandingan.skorKandang;

		if (pertandingan.skorKandang > pertandingan.skorTandang) {
			klasemen[kandang].menang++;
			klasemen[kandang].poin += 3;
			klasemen[tandang].kalah++;
		} else if (pertandingan.skorKandang < pertandingan.skorTandang) {
			klasemen[tandang].menang++;
			klasemen[tandang].poin += 3;
			klasemen[kandang].kalah++;
		} else {
			klasemen[kandang].seri++;
			klasemen[tandang].seri++;
			klasemen[kandang].poin++;
			klasemen[tandang].poin++;
		}
	}

	int jumlahKlasemen = klasemen.size();
	for (int i = 0; i < jumlahKlasemen - 1; i++) {
		for (int j = 0; j < jumlahKlasemen - i - 1; j++) {
			bool tukar = false;
			if (klasemen[j].poin < klasemen[j + 1].poin) tukar = true;
			else if (klasemen[j].poin == klasemen[j + 1].poin &&
				klasemen[j].selisihGol() < klasemen[j + 1].selisihGol()) tukar = true;
			else if (klasemen[j].poin == klasemen[j + 1].poin &&
				klasemen[j].selisihGol() == klasemen[j + 1].selisihGol() &&
				klasemen[j].memasukkan < klasemen[j + 1].memasukkan) tukar = true;

			if (tukar) {
				KlasemenTim sementara = klasemen[j];
				klasemen[j] = klasemen[j + 1];
				klasemen[j + 1] = sementara;
			}
		}
	}

	return klasemen;
}