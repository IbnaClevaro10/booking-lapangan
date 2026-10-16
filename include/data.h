#ifndef DATA_H
#define DATA_H

#include "struktur.h"
#include <string>
#include <vector>

using namespace std;

const vector<string>& daftarTim();
bool timValid(const string& nama);
bool tanggalValid(const string& tanggal);
bool pertandinganValid(const Pertandingan& pertandingan,
					   const DaftarPertandingan& daftar,
					   string& pesanError,
					   int idDiabaikan = -1);
int idBerikutnya(const DaftarPertandingan& daftar);
vector<KlasemenTim> buatKlasemen(const DaftarPertandingan& daftar);

#endif
