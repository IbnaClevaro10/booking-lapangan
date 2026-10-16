#include "../include/tampilan.h"
#include "../include/berkas.h"
#include "../include/data.h"

#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

namespace {
	void bersihkanInput() {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	}

	int bacaBilangan(const string& label) {
		int nilai;
		while (true) {
			cout << label;
			if (cin >> nilai) {
				bersihkanInput();
				return nilai;
			}
			cout << "Input harus berupa angka.\n";
			bersihkanInput();
		}
	}

	string pilihTim(const string& label) {
		cout << label << '\n';
		for (size_t i = 0; i < daftarTim().size(); ++i) {
			cout << i + 1 << ". " << daftarTim()[i] << '\n';
		}
		int pilihan;
		do {
			pilihan = bacaBilangan("Pilihan: ");
			if (pilihan < 1 || pilihan > static_cast<int>(daftarTim().size())) {
				cout << "Pilihan tim tidak tersedia.\n";
			}
		} while (pilihan < 1 || pilihan > static_cast<int>(daftarTim().size()));
		return daftarTim()[pilihan - 1];
	}

	Pertandingan inputPertandingan(int id) {
		Pertandingan pertandingan;
		pertandingan.id = id;
		pertandingan.timKandang = pilihTim("Pilih tim kandang:");
		do {
			pertandingan.timTandang = pilihTim("Pilih tim tandang:");
			if (pertandingan.timTandang == pertandingan.timKandang) {
				cout << "Tim tandang harus berbeda dari tim kandang.\n";
			}
		} while (pertandingan.timTandang == pertandingan.timKandang);
		pertandingan.skorKandang = bacaBilangan("Skor kandang: ");
		pertandingan.skorTandang = bacaBilangan("Skor tandang: ");
		cout << "Tanggal (DD-MM-YYYY): ";
		getline(cin, pertandingan.tanggal);
		return pertandingan;
	}

	void simpanAtauTampilkanGagal(const DaftarPertandingan& daftar) {
		if (!simpanPertandingan(daftar)) {
			cout << "Gagal menyimpan data pertandingan.\n";
		}
	}
}

void tampilkanJudul() {
	cout << "\n========================================\n"
			  << "       UCL MINI LEAGUE - 5 TIM\n"
			  << "========================================\n";
}

void tampilkanMenu() {
	cout << "\n1. Tampilkan pertandingan\n"
			  << "2. Tambah pertandingan\n"
			  << "3. Edit pertandingan\n"
			  << "4. Hapus pertandingan\n"
			  << "5. Cari pertandingan\n"
			  << "6. Tampilkan klasemen\n"
			  << "0. Keluar\n";
}

void tampilkanPertandingan(const DaftarPertandingan& daftar) {
	if (daftar.empty()) {
		cout << "Belum ada pertandingan.\n";
		return;
	}
	cout << "\n" << left << setw(5) << "ID" << setw(18) << "KANDANG"
		  << setw(18) << "TANDANG" << setw(8) << "SKOR" << "TANGGAL\n";
	cout << string(70, '-') << '\n';
	for (const Pertandingan& pertandingan : daftar) {
		cout << left << setw(5) << pertandingan.id
			  << setw(18) << pertandingan.timKandang
			  << setw(18) << pertandingan.timTandang
			  << setw(8) << (to_string(pertandingan.skorKandang) + "-" +
							  to_string(pertandingan.skorTandang))
				  << pertandingan.tanggal << '\n';
	}
}

void tambahPertandingan(DaftarPertandingan& daftar) {
	Pertandingan pertandingan = inputPertandingan(idBerikutnya(daftar));
	string pesanError;
	if (!pertandinganValid(pertandingan, daftar, pesanError)) {
		cout << "Gagal menambah: " << pesanError << '\n';
		return;
	}
	daftar.push_back(pertandingan);
	simpanAtauTampilkanGagal(daftar);
	cout << "Pertandingan berhasil ditambahkan dengan ID " << pertandingan.id << ".\n";
}

void editPertandingan(DaftarPertandingan& daftar) {
	int id = bacaBilangan("Masukkan ID pertandingan yang diedit: ");
	for (Pertandingan& pertandingan : daftar) {
		if (pertandingan.id == id) {
			Pertandingan baru = inputPertandingan(id);
			string pesanError;
			if (!pertandinganValid(baru, daftar, pesanError, id)) {
				cout << "Gagal mengedit: " << pesanError << '\n';
				return;
			}
			pertandingan = baru;
			simpanAtauTampilkanGagal(daftar);
			cout << "Pertandingan berhasil diedit.\n";
			return;
		}
	}
	cout << "ID pertandingan tidak ditemukan.\n";
}

void hapusPertandingan(DaftarPertandingan& daftar) {
	int id = bacaBilangan("Masukkan ID pertandingan yang dihapus: ");
	for (auto it = daftar.begin(); it != daftar.end(); ++it) {
		if (it->id == id) {
			daftar.erase(it);
			simpanAtauTampilkanGagal(daftar);
			cout << "Pertandingan berhasil dihapus.\n";
			return;
		}
	}
	cout << "ID pertandingan tidak ditemukan.\n";
}

void cariPertandingan(const DaftarPertandingan& daftar) {
	string kataKunci;
	cout << "Masukkan nama tim atau tanggal: ";
	getline(cin, kataKunci);
	DaftarPertandingan hasil;
	for (const Pertandingan& pertandingan : daftar) {
		if (pertandingan.timKandang.find(kataKunci) != string::npos ||
			pertandingan.timTandang.find(kataKunci) != string::npos ||
			pertandingan.tanggal.find(kataKunci) != string::npos) {
			hasil.push_back(pertandingan);
		}
	}
	tampilkanPertandingan(hasil);
}

void tampilkanKlasemen(const DaftarPertandingan& daftar) {
	const vector<KlasemenTim> klasemen = buatKlasemen(daftar);
	cout << "\n" << left << setw(5) << "#" << setw(18) << "TIM"
		  << setw(5) << "M" << setw(5) << "W" << setw(5) << "D"
		  << setw(5) << "L" << setw(6) << "GM" << setw(6) << "GK"
		  << setw(6) << "SG" << "PTS\n";
	cout << string(70, '-') << '\n';
	for (size_t i = 0; i < klasemen.size(); ++i) {
		const KlasemenTim& tim = klasemen[i];
		cout << left << setw(5) << i + 1 << setw(18) << tim.nama
			  << setw(5) << tim.main << setw(5) << tim.menang
			  << setw(5) << tim.seri << setw(5) << tim.kalah
			  << setw(6) << tim.memasukkan << setw(6) << tim.kebobolan
			  << setw(6) << tim.selisihGol() << tim.poin << '\n';
	}
}
