#ifndef AGENT_EXCEPTION_H
#define AGENT_EXCEPTION_H

#include <stdexcept>
#include <string>
using namespace std;

// Exception untuk pickrate tidak valid
class PickrateException : public runtime_error {
public:
    PickrateException(int nilai)
        : runtime_error("Pickrate " + to_string(nilai) +
                        " tidak valid! Masukkan angka antara 0 sampai 100.") {}
};

// Exception untuk tier tidak valid
class TierException : public runtime_error {
public:
    TierException(string tier)
        : runtime_error("Tier \"" + tier +
                        "\" tidak dikenali! Tier yang tersedia hanya S, A, B, C, atau D.") {}
};

// Exception untuk field yang dikosongkan
class InputKosongException : public runtime_error {
public:
    InputKosongException(string field)
        : runtime_error("Kolom " + field + " tidak boleh dibiarkan kosong!") {}
};

// Exception ketika data agent sudah mencapai batas maksimal
class KapasitasPenuhException : public runtime_error {
public:
    KapasitasPenuhException()
        : runtime_error("Daftar agent sudah penuh! Maksimal hanya 100 agent.") {}
};

// Exception ketika agent yang dicari tidak ada
class AgentTidakDitemukanException : public runtime_error {
public:
    AgentTidakDitemukanException(string keterangan)
        : runtime_error("Tidak ada agent dengan " + keterangan + " yang cocok.") {}
};

// Exception untuk nomor urut yang di luar jangkauan
class NomorTidakValidException : public runtime_error {
public:
    NomorTidakValidException(int nomor, int maks)
        : runtime_error("Nomor " + to_string(nomor) +
                        " tidak ada dalam daftar! Pilih antara 1 sampai " +
                        to_string(maks) + ".") {}
};

// Exception ketika login gagal sebanyak 3 kali
class LoginGagalException : public runtime_error {
public:
    LoginGagalException()
        : runtime_error("Anda sudah salah memasukkan password sebanyak 3 kali. Akses ditolak!") {}
};

// ===== FUNGSI VALIDASI =====
void validasiPickrate(int nilai) {
    if (nilai < 0 || nilai > 100)
        throw PickrateException(nilai);
}

void validasiTier(string tier) {
    if (tier != "S" && tier != "A" && tier != "B" && tier != "C" && tier != "D")
        throw TierException(tier);
}

void validasiTidakKosong(string input, string namaKolom) {
    if (input.empty())
        throw InputKosongException(namaKolom);
}

void validasiNomor(int nomor, int maks) {
    if (nomor < 1 || nomor > maks)
        throw NomorTidakValidException(nomor, maks);
}

#endif
