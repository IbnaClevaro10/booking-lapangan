#ifndef STRUKTUR_H
#define STRUKTUR_H

#include <string>
#include <vector>

using namespace std;

struct Pertandingan {
	int id{};
	string timKandang;
	string timTandang;
	int skorKandang{};
	int skorTandang{};
	string tanggal;
};

struct KlasemenTim {
	string nama;
	int main{};
	int menang{};
	int seri{};
	int kalah{};
	int memasukkan{};
	int kebobolan{};
	int poin{};

	int selisihGol() const { return memasukkan - kebobolan; }
};

using DaftarPertandingan = vector<Pertandingan>;

#endif
