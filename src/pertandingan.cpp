#include "../include/pertandingan.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

const string NAMA_FILE = "data/pertandingan.txt";
const vector<string> DAFTAR_TIM = {
	"PSG", "Liverpool", "Barcelona", "Real Madrid", "Man City"
};

vector<Pertandingan> daftar;

string pilihTim(string pesan) {
	string tim[5] = {
		"PSG", "Liverpool", "Barcelona", "Real Madrid", "Man City"
	};
	int pilihan;

	cout << pesan << '\n';
	for (int i = 0; i < 5; i++) {
		cout << i + 1 << ". " << tim[i] << '\n';
	}

	do {
		cout << "Pilihan: ";
		cin >> pilihan;
		if (pilihan < 1 || pilihan > 5) {
			cout << "Pilihan tim tidak tersedia.\n";
		}
	} while (pilihan < 1 || pilihan > 5);

	return tim[pilihan - 1];
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

		try {
			daftar.push_back({
				stoi(kolom[0]), kolom[1], kolom[2],
				stoi(kolom[3]), stoi(kolom[4]), kolom[5]
			});
		} catch (const exception&) {
			continue;
		}
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
		id = max(id, pertandingan.id + 1);
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
	for (int i = 0; i < daftar.size(); i++) {
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
	for (int i = 0; i < daftar.size(); i++) {
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
	string kataKunci;
	cout << "Masukkan nama tim atau tanggal: ";
	getline(cin, kataKunci);

	for (Pertandingan pertandingan : daftar) {
		if (pertandingan.timKandang.find(kataKunci) != string::npos ||
			pertandingan.timTandang.find(kataKunci) != string::npos ||
			pertandingan.tanggal.find(kataKunci) != string::npos) {
			cout << pertandingan.id << ". " << pertandingan.timKandang
				 << " vs " << pertandingan.timTandang << " "
				 << pertandingan.skorKandang << "-" << pertandingan.skorTandang
				 << " " << pertandingan.tanggal << '\n';
		}
	}
}

vector<KlasemenTim> buatKlasemen() {
	vector<KlasemenTim> klasemen;
	for (string nama : DAFTAR_TIM) {
		klasemen.push_back({nama});
	}

	for (Pertandingan pertandingan : daftar) {
		int kandang = -1;
		int tandang = -1;

		for (int i = 0; i < klasemen.size(); i++) {
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

	sort(klasemen.begin(), klasemen.end(), [](KlasemenTim kiri, KlasemenTim kanan) {
		if (kiri.poin != kanan.poin) return kiri.poin > kanan.poin;
		if (kiri.selisihGol() != kanan.selisihGol()) {
			return kiri.selisihGol() > kanan.selisihGol();
		}
		return kiri.memasukkan > kanan.memasukkan;
	});

	return klasemen;
}
