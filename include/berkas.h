#ifndef BERKAS_H
#define BERKAS_H

#include "struktur.h"
#include <string>

using namespace std;

const string FILE_PERTANDINGAN = "data/pertandingan.txt";

DaftarPertandingan bacaPertandingan(const string& namaFile = FILE_PERTANDINGAN);
bool simpanPertandingan(const DaftarPertandingan& daftar,
						const string& namaFile = FILE_PERTANDINGAN);

#endif
