#include "../include/data.h"

#include <algorithm>
#include <cctype>
#include <regex>

using namespace std;

const vector<string>& daftarTim() {
	static const vector<string> tim{
		"PSG", "Liverpool", "Barcelona", "Real Madrid", "Man City"
	};
	return tim;
}

bool timValid(const string& nama) {
	const vector<string>& tim = daftarTim();
	return find(tim.begin(), tim.end(), nama) != tim.end();
}

bool tanggalValid(const string& tanggal) {
	static const regex pola("(0[1-9]|[12][0-9]|3[01])-(0[1-9]|1[0-2])-([0-9]{4})");
	return regex_match(tanggal, pola);
}

bool pertandinganValid(const Pertandingan& pertandingan,
					   const DaftarPertandingan& daftar,
					   string& pesanError,
					   int idDiabaikan) {
	if (!timValid(pertandingan.timKandang) || !timValid(pertandingan.timTandang)) {
		pesanError = "Tim harus dipilih dari 5 tim yang tersedia.";
		return false;
	}
	if (pertandingan.timKandang == pertandingan.timTandang) {
		pesanError = "Tim kandang dan tandang tidak boleh sama.";
		return false;
	}
	if (pertandingan.skorKandang < 0 || pertandingan.skorTandang < 0) {
		pesanError = "Skor tidak boleh negatif.";
		return false;
	}
	if (!tanggalValid(pertandingan.tanggal)) {
		pesanError = "Tanggal harus berformat DD-MM-YYYY.";
		return false;
	}
	for (const Pertandingan& tersimpan : daftar) {
		if (tersimpan.id == pertandingan.id && tersimpan.id != idDiabaikan) {
			pesanError = "ID pertandingan sudah digunakan.";
			return false;
		}
	}
	return true;
}

int idBerikutnya(const DaftarPertandingan& daftar) {
	int id = 1;
	for (const Pertandingan& pertandingan : daftar) {
		id = max(id, pertandingan.id + 1);
	}
	return id;
}

vector<KlasemenTim> buatKlasemen(const DaftarPertandingan& daftar) {
	vector<KlasemenTim> klasemen;
	for (const string& nama : daftarTim()) {
		klasemen.push_back({nama});
	}

	auto cariTim = [&klasemen](const string& nama) -> KlasemenTim& {
		return *find_if(klasemen.begin(), klasemen.end(),
						 [&nama](const KlasemenTim& tim) { return tim.nama == nama; });
	};

	for (const Pertandingan& pertandingan : daftar) {
		if (!timValid(pertandingan.timKandang) ||
			!timValid(pertandingan.timTandang) ||
			pertandingan.timKandang == pertandingan.timTandang ||
			pertandingan.skorKandang < 0 || pertandingan.skorTandang < 0) {
			continue;
		}
		KlasemenTim& kandang = cariTim(pertandingan.timKandang);
		KlasemenTim& tandang = cariTim(pertandingan.timTandang);
		kandang.main++;
		tandang.main++;
		kandang.memasukkan += pertandingan.skorKandang;
		kandang.kebobolan += pertandingan.skorTandang;
		tandang.memasukkan += pertandingan.skorTandang;
		tandang.kebobolan += pertandingan.skorKandang;

		if (pertandingan.skorKandang > pertandingan.skorTandang) {
			kandang.menang++;
			kandang.poin += 3;
			tandang.kalah++;
		} else if (pertandingan.skorKandang < pertandingan.skorTandang) {
			tandang.menang++;
			tandang.poin += 3;
			kandang.kalah++;
		} else {
			kandang.seri++;
			tandang.seri++;
			kandang.poin++;
			tandang.poin++;
		}
	}

	sort(klasemen.begin(), klasemen.end(), [](const KlasemenTim& kiri, const KlasemenTim& kanan) {
		if (kiri.poin != kanan.poin) return kiri.poin > kanan.poin;
		if (kiri.selisihGol() != kanan.selisihGol()) return kiri.selisihGol() > kanan.selisihGol();
		return kiri.memasukkan > kanan.memasukkan;
	});
	return klasemen;
}
