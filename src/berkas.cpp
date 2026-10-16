#include "../include/berkas.h"

#include <fstream>
#include <sstream>

using namespace std;

DaftarPertandingan bacaPertandingan(const string& namaFile) {
	DaftarPertandingan daftar;
	ifstream file(namaFile);
	if (!file) {
		return daftar;
	}

	string baris;
	while (getline(file, baris)) {
		if (baris.empty()) {
			continue;
		}

		stringstream stream(baris);
		string bagian;
		vector<string> kolom;
		while (getline(stream, bagian, ',')) {
			kolom.push_back(bagian);
		}
		if (kolom.size() != 6) {
			continue;
		}

		try {
			Pertandingan pertandingan{
				stoi(kolom[0]), kolom[1], kolom[2],
				stoi(kolom[3]), stoi(kolom[4]), kolom[5]
			};
			daftar.push_back(pertandingan);
		} catch (const exception&) {
			// Abaikan baris yang tidak memiliki format angka yang benar.
		}
	}
	return daftar;
}

bool simpanPertandingan(const DaftarPertandingan& daftar, const string& namaFile) {
	ofstream file(namaFile);
	if (!file) {
		return false;
	}

	for (const Pertandingan& pertandingan : daftar) {
		file << pertandingan.id << ',' << pertandingan.timKandang << ','
			 << pertandingan.timTandang << ',' << pertandingan.skorKandang << ','
			 << pertandingan.skorTandang << ',' << pertandingan.tanggal << '\n';
	}
	return true;
}
