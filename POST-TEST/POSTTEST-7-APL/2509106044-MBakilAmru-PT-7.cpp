#include <iostream>
#include <string>
#include <stdexcept>
#include "errorhandling.h"
using namespace std;

#define MAX_AGENT 100
#define MAX_USER  10

struct Statistik {
    string role;
    int pickrate;
};

struct Agent {
    string nama;
    string tier;
    Statistik stat;
};

struct User {
    string username;
    string password;
    string role;
};

// ===== SUB PROGRAM =====
void tampilkanTierlistRekursif(Agent tierlist[], int i, int jumlahAgent) {
    if (jumlahAgent == 0) {
        cout << "Belum ada agent yang ditambahkan." << endl;
        return;
    }
    if (i == 0) {
        cout << "\n=== TIERLIST VALORANT ===" << endl;
        cout << "+----+-----------------+------+-------------+----------+" << endl;
        cout << "| No | Nama Agent       | Tier | Role         | Pickrate |" << endl;
        cout << "+----+-----------------+------+-------------+----------+" << endl;
    }

    cout << "| " << i+1
         << "  | " << tierlist[i].nama
         << string(15 - tierlist[i].nama.size(), ' ')
         << "| " << tierlist[i].tier
         << "    | " << tierlist[i].stat.role
         << string(11 - tierlist[i].stat.role.size(), ' ')
         << "| " << tierlist[i].stat.pickrate << "%"
         << string(8 - to_string(tierlist[i].stat.pickrate).size(), ' ')
         << "|" << endl;

    if (i == jumlahAgent - 1) {
        cout << "+----+-----------------+------+-------------+----------+" << endl;
        return;
    }
    tampilkanTierlistRekursif(tierlist, i+1, jumlahAgent);
}

// ===== TAMBAH AGENT =====
void tambahAgent(Agent tierlist[], int *jumlahAgent) {
    try {
        if (*jumlahAgent >= MAX_AGENT)
            throw KapasitasPenuhException();

        string nama, tier, role;
        int pickrate;

        cout << "Nama Agent: ";
        cin.ignore();
        getline(cin, nama);
        validasiTidakKosong(nama, "Nama");

        cout << "Tier (S/A/B/C/D): ";
        getline(cin, tier);
        validasiTidakKosong(tier, "Tier");
        validasiTier(tier);

        cout << "Role: ";
        getline(cin, role);
        validasiTidakKosong(role, "Role");

        cout << "Pickrate (%): ";
        if (!(cin >> pickrate)) {
            cin.clear();
            cin.ignore(1000, '\n');
            throw runtime_error("Input pickrate harus berupa angka.");
        }
        validasiPickrate(pickrate);

        tierlist[*jumlahAgent] = {nama, tier, {role, pickrate}};
        (*jumlahAgent)++;
        cout << ">> Agent \"" << nama << "\" berhasil ditambahkan ke daftar.\n";

    } catch (KapasitasPenuhException &e) {
        cout << ">> Kesalahan: " << e.what() << "\n";
    } catch (InputKosongException &e) {
        cout << ">> Kesalahan: " << e.what() << "\n";
    } catch (TierException &e) {
        cout << ">> Kesalahan: " << e.what() << "\n";
    } catch (PickrateException &e) {
        cout << ">> Kesalahan: " << e.what() << "\n";
    } catch (runtime_error &e) {
        cout << ">> Kesalahan: " << e.what() << "\n";
    }
}

// ===== PROSES UPDATE DATA =====
void prosesUpdateData(Agent *ptrAgent) {
    try {
        string nama, tier, role;
        int pickrate;

        cout << "Nama baru: ";
        cin.ignore();
        getline(cin, nama);
        validasiTidakKosong(nama, "Nama");

        cout << "Tier baru (S/A/B/C/D): ";
        getline(cin, tier);
        validasiTidakKosong(tier, "Tier");
        validasiTier(tier);

        cout << "Role baru: ";
        getline(cin, role);
        validasiTidakKosong(role, "Role");

        cout << "Pickrate baru (%): ";
        if (!(cin >> pickrate)) {
            cin.clear();
            cin.ignore(1000, '\n');
            throw runtime_error("Input pickrate harus berupa angka.");
        }
        validasiPickrate(pickrate);

        ptrAgent->nama = nama;
        ptrAgent->tier = tier;
        ptrAgent->stat.role = role;
        ptrAgent->stat.pickrate = pickrate;
        cout << ">> Data agent berhasil diperbarui.\n";

    } catch (InputKosongException &e) {
        cout << ">> Kesalahan: " << e.what() << "\n";
    } catch (TierException &e) {
        cout << ">> Kesalahan: " << e.what() << "\n";
    } catch (PickrateException &e) {
        cout << ">> Kesalahan: " << e.what() << "\n";
    } catch (runtime_error &e) {
        cout << ">> Kesalahan: " << e.what() << "\n";
    }
}

// ===== UBAH AGENT =====
void ubahAgent(Agent tierlist[], int jumlahAgent) {
    try {
        if (jumlahAgent == 0)
            throw runtime_error("Belum ada agent yang bisa diubah.");

        int nomorAgent;
        cout << "Nomor agent yang diubah: ";
        if (!(cin >> nomorAgent)) {
            cin.clear();
            cin.ignore(1000, '\n');
            throw runtime_error("Input nomor harus berupa angka.");
        }
        validasiNomor(nomorAgent, jumlahAgent);
        prosesUpdateData(&tierlist[nomorAgent - 1]);

    } catch (NomorTidakValidException &e) {
        cout << ">> Kesalahan: " << e.what() << "\n";
    } catch (runtime_error &e) {
        cout << ">> Kesalahan: " << e.what() << "\n";
    }
}

// ===== HAPUS AGENT =====
void hapusAgent(Agent tierlist[], int *jumlahAgent) {
    try {
        if (*jumlahAgent == 0)
            throw runtime_error("Belum ada agent yang bisa dihapus.");

        int nomorAgent;
        cout << "Nomor agent yang dihapus: ";
        if (!(cin >> nomorAgent)) {
            cin.clear();
            cin.ignore(1000, '\n');
            throw runtime_error("Input nomor harus berupa angka.");
        }
        validasiNomor(nomorAgent, *jumlahAgent);

        string namaHapus = tierlist[nomorAgent - 1].nama;
        for (int i = nomorAgent - 1; i < *jumlahAgent - 1; i++) {
            tierlist[i] = tierlist[i + 1];
        }
        (*jumlahAgent)--;
        cout << ">> Agent \"" << namaHapus << "\" berhasil dihapus dari daftar.\n";

    } catch (NomorTidakValidException &e) {
        cout << ">> Kesalahan: " << e.what() << "\n";
    } catch (runtime_error &e) {
        cout << ">> Kesalahan: " << e.what() << "\n";
    }
}

// ===== CARI AGENT =====
void cariAgent(string nama, Agent tierlist[], int jumlahAgent) {
    for (int i = 0; i < jumlahAgent; i++) {
        if (tierlist[i].nama == nama) {
            cout << "\n=== DATA AGENT DITEMUKAN ===" << endl;
            cout << "Nama     : " << tierlist[i].nama << endl;
            cout << "Tier     : " << tierlist[i].tier << endl;
            cout << "Role     : " << tierlist[i].stat.role << endl;
            cout << "Pickrate : " << tierlist[i].stat.pickrate << "%" << endl;
            return;
        }
    }
    cout << ">> Agent \"" << nama << "\" tidak ditemukan di daftar.\n";
}

void cariAgentTier(string tier, Agent tierlist[], int jumlahAgent) {
    try {
        validasiTier(tier);
        bool ditemukan = false;
        for (int i = 0; i < jumlahAgent; i++) {
            if (tierlist[i].tier == tier) {
                cout << "\n=== DATA AGENT DITEMUKAN ===" << endl;
                cout << "Nama     : " << tierlist[i].nama << endl;
                cout << "Tier     : " << tierlist[i].tier << endl;
                cout << "Role     : " << tierlist[i].stat.role << endl;
                cout << "Pickrate : " << tierlist[i].stat.pickrate << "%" << endl;
                ditemukan = true;
            }
        }
        if (!ditemukan)
            throw AgentTidakDitemukanException("tier " + tier);

    } catch (TierException &e) {
        cout << ">> Kesalahan: " << e.what() << "\n";
    } catch (AgentTidakDitemukanException &e) {
        cout << ">> Kesalahan: " << e.what() << "\n";
    }
}

// ===== SORTING =====
int nilaiTier(string tier) {
    if (tier == "S") return 5;
    if (tier == "A") return 4;
    if (tier == "B") return 3;
    if (tier == "C") return 2;
    if (tier == "D") return 1;
    return 0;
}

void sortTierDescending(Agent tierlist[], int jumlahAgent) {
    for (int i = 0; i < jumlahAgent - 1; i++) {
        int indeksMax = i;
        for (int j = i + 1; j < jumlahAgent; j++) {
            if (nilaiTier(tierlist[j].tier) > nilaiTier(tierlist[indeksMax].tier))
                indeksMax = j;
        }
        if (indeksMax != i) {
            Agent temp = tierlist[i];
            tierlist[i] = tierlist[indeksMax];
            tierlist[indeksMax] = temp;
        }
    }
    cout << ">> Daftar berhasil diurutkan berdasarkan Tier (S -> D).\n";
}

void sortPickrateAscending(Agent tierlist[], int jumlahAgent) {
    bool swapped;
    for (int i = 0; i < jumlahAgent - 1; i++) {
        swapped = false;
        for (int j = 0; j < jumlahAgent - i - 1; j++) {
            if (tierlist[j].stat.pickrate > tierlist[j + 1].stat.pickrate) {
                Agent temp = tierlist[j];
                tierlist[j] = tierlist[j + 1];
                tierlist[j + 1] = temp;
                swapped = true;
            }
        }
        if (swapped == false) break;
    }
    cout << ">> Daftar berhasil diurutkan berdasarkan Pickrate (rendah -> tinggi).\n";
}

void sortNamaAscending(Agent tierlist[], int jumlahAgent) {
    for (int i = 1; i < jumlahAgent; i++) {
        Agent key = tierlist[i];
        int j = i - 1;
        while (j >= 0 && tierlist[j].nama > key.nama) {
            tierlist[j + 1] = tierlist[j];
            j = j - 1;
        }
        tierlist[j + 1] = key;
    }
    cout << ">> Daftar berhasil diurutkan berdasarkan Nama (A -> Z).\n";
}

// ===== SEARCHING =====
void binarySearchPickrate(Agent *tierlist, int jumlahAgent, int targetPickrate) {
    try {
        validasiPickrate(targetPickrate);

        bool swapped;
        for (int i = 0; i < jumlahAgent - 1; i++) {
            swapped = false;
            for (int j = 0; j < jumlahAgent - i - 1; j++) {
                if ((tierlist + j)->stat.pickrate > (tierlist + j + 1)->stat.pickrate) {
                    Agent temp = *(tierlist + j);
                    *(tierlist + j) = *(tierlist + j + 1);
                    *(tierlist + j + 1) = temp;
                    swapped = true;
                }
            }
            if (swapped == false) break;
        }

        int kiri = 0, kanan = jumlahAgent - 1;
        bool ditemukan = false;

        while (kiri <= kanan) {
            int tengah = (kiri + kanan) / 2;
            if ((tierlist + tengah)->stat.pickrate == targetPickrate) {
                int awal = tengah;
                while (awal > 0 && (tierlist + awal - 1)->stat.pickrate == targetPickrate)
                    awal--;
                cout << "\n=== HASIL BINARY SEARCH (Pickrate: " << targetPickrate << "%) ===" << endl;
                for (int i = awal; i < jumlahAgent && (tierlist + i)->stat.pickrate == targetPickrate; i++) {
                    cout << "Nama     : " << (tierlist + i)->nama << endl;
                    cout << "Tier     : " << (tierlist + i)->tier << endl;
                    cout << "Role     : " << (tierlist + i)->stat.role << endl;
                    cout << "Pickrate : " << (tierlist + i)->stat.pickrate << "%" << endl;
                    cout << "---" << endl;
                }
                ditemukan = true;
                break;
            } else if ((tierlist + tengah)->stat.pickrate < targetPickrate) {
                kiri = tengah + 1;
            } else {
                kanan = tengah - 1;
            }
        }

        if (!ditemukan)
            throw AgentTidakDitemukanException("pickrate " + to_string(targetPickrate) + "%");

    } catch (PickrateException &e) {
        cout << ">> Kesalahan: " << e.what() << "\n";
    } catch (AgentTidakDitemukanException &e) {
        cout << ">> Kesalahan: " << e.what() << "\n";
    }
}

void linearSearchRole(Agent *tierlist, int jumlahAgent, string targetRole) {
    try {
        validasiTidakKosong(targetRole, "Role");
        bool ditemukan = false;
        cout << "\n=== HASIL LINEAR SEARCH (Role: " << targetRole << ") ===" << endl;
        for (int i = 0; i < jumlahAgent; i++) {
            if ((tierlist + i)->stat.role == targetRole) {
                cout << "Nama     : " << (tierlist + i)->nama << endl;
                cout << "Tier     : " << (tierlist + i)->tier << endl;
                cout << "Role     : " << (tierlist + i)->stat.role << endl;
                cout << "Pickrate : " << (tierlist + i)->stat.pickrate << "%" << endl;
                cout << "---" << endl;
                ditemukan = true;
            }
        }
        if (!ditemukan)
            throw AgentTidakDitemukanException("role \"" + targetRole + "\"");

    } catch (InputKosongException &e) {
        cout << ">> Kesalahan: " << e.what() << "\n";
    } catch (AgentTidakDitemukanException &e) {
        cout << ">> Kesalahan: " << e.what() << "\n";
    }
}

// ===== MENU SEARCHING =====
void menuSearching(Agent tierlist[], int jumlahAgent) {
    try {
        if (jumlahAgent == 0)
            throw runtime_error("Belum ada agent untuk dicari.");

        int pilihan;
        cout << "\n+------------------------------------+" << endl;
        cout << "|          SEARCHING AGENT           |" << endl;
        cout << "+------------------------------------+" << endl;
        cout << "| 1. Binary Search (cari Pickrate)   |" << endl;
        cout << "| 2. Linear Search (cari Role)       |" << endl;
        cout << "+------------------------------------+" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        if (pilihan == 1) {
            int targetPickrate;
            cout << "Masukkan pickrate yang dicari (%): ";
            if (!(cin >> targetPickrate)) {
                cin.clear();
                cin.ignore(1000, '\n');
                throw runtime_error("Input pickrate harus berupa angka.");
            }
            binarySearchPickrate(tierlist, jumlahAgent, targetPickrate);
        } else if (pilihan == 2) {
            string targetRole;
            cout << "Masukkan role yang dicari: ";
            cin.ignore();
            getline(cin, targetRole);
            linearSearchRole(tierlist, jumlahAgent, targetRole);
        } else {
            throw runtime_error("Pilihan tidak valid.");
        }

    } catch (runtime_error &e) {
        cout << ">> Kesalahan: " << e.what() << "\n";
    }
}

// ===== MENU SORTING =====
void menuSorting(Agent tierlist[], int jumlahAgent) {
    try {
        if (jumlahAgent == 0)
            throw runtime_error("Belum ada agent untuk diurutkan.");

        int pilihan;
        cout << "\n+------------------------------+" << endl;
        cout << "|         SORTING AGENT        |" << endl;
        cout << "+------------------------------+" << endl;
        cout << "| 1. Sort Tier (S -> D)        |" << endl;
        cout << "| 2. Sort Pickrate (kecil->bsr)|" << endl;
        cout << "| 3. Sort Nama (A -> Z)        |" << endl;
        cout << "+------------------------------+" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: sortTierDescending(tierlist, jumlahAgent);    break;
            case 2: sortPickrateAscending(tierlist, jumlahAgent); break;
            case 3: sortNamaAscending(tierlist, jumlahAgent);     break;
            default: throw runtime_error("Pilihan tidak valid.");
        }

    } catch (runtime_error &e) {
        cout << ">> Kesalahan: " << e.what() << "\n";
    }
}

// ===== MENU ADMIN =====
int menuAdmin(Agent tierlist[], int *jumlahAgent) {
    int pilihan;
    do {
        cout << "\n+================ MENU ADMIN ================+" << endl;
        cout << "| 1. Lihat Tierlist                         |" << endl;
        cout << "| 2. Tambah Agent                           |" << endl;
        cout << "| 3. Ubah Agent                             |" << endl;
        cout << "| 4. Hapus Agent                            |" << endl;
        cout << "| 5. Sorting Agent                          |" << endl;
        cout << "| 6. Searching Agent                        |" << endl;
        cout << "| 7. Cari Agent                             |" << endl;
        cout << "| 8. Keluar                                 |" << endl;
        cout << "+===========================================+" << endl;
        cout << "Pilihan: ";

        try {
            if (!(cin >> pilihan)) {
                cin.clear();
                cin.ignore(1000, '\n');
                throw runtime_error("Input harus berupa angka.");
            }
        } catch (runtime_error &e) {
            cout << ">> Kesalahan: " << e.what() << "\n";
            pilihan = 0;
            continue;
        }

        switch (pilihan) {
        case 1: tampilkanTierlistRekursif(tierlist, 0, *jumlahAgent); break;
        case 2: tambahAgent(tierlist, jumlahAgent); break;
        case 3: ubahAgent(tierlist, *jumlahAgent); break;
        case 4: hapusAgent(tierlist, jumlahAgent); break;
        case 5: menuSorting(tierlist, *jumlahAgent); break;
        case 6: menuSearching(tierlist, *jumlahAgent); break;
        case 7: {
            int subPilihan;
            cout << "\n+---------------------------+" << endl;
            cout << "|        CARI AGENT         |" << endl;
            cout << "+---------------------------+" << endl;
            cout << "| 1. Cari berdasarkan Nama  |" << endl;
            cout << "| 2. Cari berdasarkan Tier  |" << endl;
            cout << "+---------------------------+" << endl;
            cout << "Pilihan: ";
            cin >> subPilihan;
            if (subPilihan == 1) {
                string nama;
                cout << "Masukkan nama agent: ";
                cin.ignore();
                getline(cin, nama);
                cariAgent(nama, tierlist, *jumlahAgent);
            } else if (subPilihan == 2) {
                string tier;
                cout << "Masukkan tier (S/A/B/C/D): ";
                cin.ignore();
                getline(cin, tier);
                cariAgentTier(tier, tierlist, *jumlahAgent);
            } else {
                cout << ">> Kesalahan: Pilihan tidak valid.\n";
            }
            break;
        }
        case 8: cout << "Keluar dari menu Admin.\n"; break;
        default: cout << ">> Kesalahan: Pilihan tidak valid.\n";
        }
    } while (pilihan != 8);
    return 0;
}

// ===== MENU USER =====
bool menuUser(Agent tierlist[], int jumlahAgent) {
    int pilihan;
    do {
        cout << "\n+================ MENU USER ================+" << endl;
        cout << "| 1. Lihat Tierlist                         |" << endl;
        cout << "| 2. Cari Agent                             |" << endl;
        cout << "| 3. Sorting Agent                          |" << endl;
        cout << "| 4. Searching Agent                        |" << endl;
        cout << "| 5. Keluar                                 |" << endl;
        cout << "+===========================================+" << endl;
        cout << "Pilihan: ";

        try {
            if (!(cin >> pilihan)) {
                cin.clear();
                cin.ignore(1000, '\n');
                throw runtime_error("Input harus berupa angka.");
            }
        } catch (runtime_error &e) {
            cout << ">> Kesalahan: " << e.what() << "\n";
            pilihan = 0;
            continue;
        }

        switch (pilihan) {
        case 1: tampilkanTierlistRekursif(tierlist, 0, jumlahAgent); break;
        case 2: {
            int subPilihan;
            cout << "\n+---------------------------+" << endl;
            cout << "|        CARI AGENT         |" << endl;
            cout << "+---------------------------+" << endl;
            cout << "| 1. Cari berdasarkan Nama  |" << endl;
            cout << "| 2. Cari berdasarkan Tier  |" << endl;
            cout << "+---------------------------+" << endl;
            cout << "Pilihan: ";
            cin >> subPilihan;
            if (subPilihan == 1) {
                string nama;
                cout << "Masukkan nama agent: ";
                cin.ignore();
                getline(cin, nama);
                cariAgent(nama, tierlist, jumlahAgent);
            } else if (subPilihan == 2) {
                string tier;
                cout << "Masukkan tier (S/A/B/C/D): ";
                cin.ignore();
                getline(cin, tier);
                cariAgentTier(tier, tierlist, jumlahAgent);
            } else {
                cout << ">> Kesalahan: Pilihan tidak valid.\n";
            }
            break;
        }
        case 3: menuSorting(tierlist, jumlahAgent); break;
        case 4: menuSearching(tierlist, jumlahAgent); break;
        case 5: cout << "Keluar dari menu User.\n"; break;
        default: cout << ">> Kesalahan: Pilihan tidak valid.\n";
        }
    } while (pilihan != 5);
    return true;
}

// ===== LOGIN =====
int login(User users[], int jumlahUser) {
    string username, password;
    int attempt = 0;

    try {
        while (attempt < 3) {
            cout << "\n+================= LOGIN ====================+" << endl;
            cout << "| Masukkan username dan password untuk login |" << endl;
            cout << "+============================================+" << endl;
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;

            for (int i = 0; i < jumlahUser; i++) {
                if (users[i].username == username && users[i].password == password) {
                    cout << ">> Selamat datang, " << username
                         << "! (" << users[i].role << ")\n";
                    return i;
                }
            }

            attempt++;
            cout << ">> Username atau password salah. Sisa percobaan: "
                 << (3 - attempt) << "x\n";
        }
        throw LoginGagalException();

    } catch (LoginGagalException &e) {
        cout << ">> Kesalahan: " << e.what() << "\n";
    }
    return -1;
}

// ===== MAIN =====
int main() {
    Agent tierlist[MAX_AGENT];
    int jumlahAgent = 0;

    User users[MAX_USER];
    int jumlahUser = 2;

    users[0] = {"Bakil", "044", "Admin"};
    users[1] = {"User",  "123", "User"};

    tierlist[jumlahAgent++] = {"Reyna", "A", {"Duelist",   60}};
    tierlist[jumlahAgent++] = {"Jett",  "S", {"Duelist",   85}};
    tierlist[jumlahAgent++] = {"Iso",   "B", {"Duelist",   40}};
    tierlist[jumlahAgent++] = {"Sage",  "B", {"Sentinel",  67}};
    tierlist[jumlahAgent++] = {"Kay-O", "A", {"Initiator", 45}};

    int pilihanUtama;
    do {
        cout << "\n+========================================+" << endl;
        cout << "|   Selamat datang di Valorant Tierlist  |" << endl;
        cout << "+========================================+" << endl;
        cout << "| 1. Masuk                               |" << endl;
        cout << "| 2. Keluar                              |" << endl;
        cout << "+========================================+" << endl;
        cout << "Pilihan: ";

        try {
            if (!(cin >> pilihanUtama)) {
                cin.clear();
                cin.ignore(1000, '\n');
                throw runtime_error("Input harus berupa angka.");
            }
            if (pilihanUtama == 1) {
                int idxUser = login(users, jumlahUser);
                if (idxUser != -1) {
                    if (users[idxUser].role == "Admin")
                        menuAdmin(tierlist, &jumlahAgent);
                    else
                        menuUser(tierlist, jumlahAgent);
                }
            } else if (pilihanUtama == 2) {
                cout << ">> Terima kasih sudah menggunakan Valorant Tierlist. Sampai jumpa!\n";
            } else {
                throw runtime_error("Pilihan tidak valid. Masukkan 1 atau 2.");
            }
        } catch (runtime_error &e) {
            cout << ">> Kesalahan: " << e.what() << "\n";
            pilihanUtama = 0;
        }
    } while (pilihanUtama != 2);

    return 0;
}

