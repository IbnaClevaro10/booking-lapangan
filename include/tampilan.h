#ifndef TAMPILAN_H
#define TAMPILAN_H

#include "struktur.h"

void tampilkanJudul();
void tampilkanMenu();
void tampilkanPertandingan(const DaftarPertandingan& daftar);
void tampilkanKlasemen(const DaftarPertandingan& daftar);
void tambahPertandingan(DaftarPertandingan& daftar);
void editPertandingan(DaftarPertandingan& daftar);
void hapusPertandingan(DaftarPertandingan& daftar);
void cariPertandingan(const DaftarPertandingan& daftar);

#endif
