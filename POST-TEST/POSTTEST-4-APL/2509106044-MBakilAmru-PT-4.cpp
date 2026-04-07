#include <iostream>
#include <string>
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
    string role; // Admin atau User
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

// Fungsi: tambah agent (Menggunakan Dereference *)
void tambahAgent(Agent tierlist[], int *jumlahAgent) {
    if (*jumlahAgent < MAX_AGENT) {
        cout << "Nama Agent: ";
        cin.ignore();
        getline(cin, tierlist[*jumlahAgent].nama);
        if (tierlist[*jumlahAgent].nama.empty()) {
            cout << "Nama agent tidak boleh kosong\n";
            return;
        }

        cout << "Tier (S/A/B/C/D): ";
        getline(cin, tierlist[*jumlahAgent].tier);

        cout << "Role: ";
        getline(cin, tierlist[*jumlahAgent].stat.role);

        cout << "Pickrate (%): ";
        cin >> tierlist[*jumlahAgent].stat.pickrate;
        if (cin.fail() || tierlist[*jumlahAgent].stat.pickrate < 0 || tierlist[*jumlahAgent].stat.pickrate > 100) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Pickrate harus berupa angka antara 0 - 100.\n";
            return;
        }

        (*jumlahAgent)++;
        cout << "Agent berhasil ditambahkan.\n";
    } else {
        cout << "Kapasitas penuh.\n";
    }
}

// Point +: Implementasi pointer pada struct (Menggunakan ->)
void prosesUpdateData(Agent *ptrAgent) {
    cout << "Nama baru: ";
    cin.ignore();
    getline(cin, ptrAgent->nama);

    cout << "Tier baru: ";
    getline(cin, ptrAgent->tier);

    cout << "Role baru: ";
    getline(cin, ptrAgent->stat.role);

    cout << "Pickrate baru: ";
    cin >> ptrAgent->stat.pickrate;
    if (ptrAgent->stat.pickrate < 0 || ptrAgent->stat.pickrate > 100) {
        cout << "Pickrate harus antara 0 - 100.\n";
        // Agar kembali ke awal jika gagal bisa diatur sesuai kebutuhan
    }
}

// Fungsi: ubah agent
void ubahAgent(Agent tierlist[], int jumlahAgent) {
    if (jumlahAgent > 0) {
        int nomorAgent;
        cout << "Nomor agent yang diubah: ";
        cin >> nomorAgent;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Input harus berupa angka\n";
            return;
        }

        if (nomorAgent > 0 && nomorAgent <= jumlahAgent) {
            // Menggunakan Address-of Operator (&)
            prosesUpdateData(&tierlist[nomorAgent - 1]);
            cout << "Update berhasil.\n";
        } else {
            cout << "Agent tidak ditemukan.\n";
        }
    } else {
        cout << "Belum ada agent.\n";
    }
}

// Fungsi: hapus agent (Menggunakan Dereference *)
void hapusAgent(Agent tierlist[], int *jumlahAgent) {
    if (*jumlahAgent > 0) {
        int nomorAgent;
        cout << "Nomor agent yang dihapus: ";
        cin >> nomorAgent;

        if (nomorAgent > 0 && nomorAgent <= *jumlahAgent) {
            for (int i = nomorAgent - 1; i < *jumlahAgent - 1; i++) {
                tierlist[i] = tierlist[i + 1];
            }
            (*jumlahAgent)--;
            cout << "Agent dihapus.\n";
        } else {
            cout << "Agent tidak ditemukan.\n";
        }
    } else {
        cout << "Belum ada agent.\n";
    }
}

// Fungsi Overloading: cari agent
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
    cout << "Agent " << nama << " tidak ditemukan.\n";
}

// Cari agent berdasarkan tier
void cariAgentTier(string tier, Agent tierlist[], int jumlahAgent) {
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
    if (!ditemukan) {
        cout << "Tidak ada agent dengan tier " << tier << ".\n";
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
        cout << "| 5. Cari Agent                             |" << endl;
        cout << "| 6. Keluar                                 |" << endl;
        cout << "+===========================================+" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1: tampilkanTierlistRekursif(tierlist, 0, *jumlahAgent); break;
        case 2: tambahAgent(tierlist, jumlahAgent); break;
        case 3: ubahAgent(tierlist, *jumlahAgent); break;
        case 4: hapusAgent(tierlist, jumlahAgent); break;
        case 5: {
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
                cout << "Pilihan tidak valid.\n";
            }
            break;
        }
        case 6: cout << "Keluar dari menu Admin.\n"; break;
        default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 6);
    return 0;
}

// ===== MENU USER =====
bool menuUser(Agent tierlist[], int jumlahAgent) {
    int pilihan;
    do {
        cout << "\n+================ MENU USER ================+" << endl;
        cout << "| 1. Lihat Tierlist                         |" << endl;
        cout << "| 2. Cari Agent                             |" << endl;
        cout << "| 3. Keluar                                 |" << endl;
        cout << "+===========================================+" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            tampilkanTierlistRekursif(tierlist, 0, jumlahAgent);
            break;
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
                cout << "Pilihan tidak valid.\n";
            }
            break;
        }
        case 3:
            cout << "Keluar dari menu User.\n";
            break;
        default:
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 3);

    return true;
}

// ===== LOGIN =====
// pada menu login jika salah 3 kali akan keluar program
int login(User users[], int jumlahUser) {
    string username, password;
    int attempt = 0;

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
                cout << "Login berhasil, Selamat datang, " << username << " (" << users[i].role << ")\n";
                return i; // kalau berhasil login
            }
        }

        attempt++;
        cout << "Username atau password salah.\n";
    }

    cout << "Login gagal 3 kali. kembali ke menu utama.\n";
    return -1; // kalau sudah 3 kali salah login
}

// ===== MAIN =====
int main() {
    Agent tierlist[MAX_AGENT];
    int jumlahAgent = 0;

    // Data user default
    User users[MAX_USER];
    int jumlahUser = 2;

    users[0] = {"Bakil", "044", "Admin"};
    users[1] = {"User", "123", "User"};

    // 3 agent sementara di list
    tierlist[jumlahAgent++] = {"Reyna", "A", {"Duelist", 60}};
    tierlist[jumlahAgent++] = {"Jett",  "S", {"Duelist", 85}};
    tierlist[jumlahAgent++] = {"Iso",   "B", {"Duelist", 40}};

    int pilihanUtama;
    do {
        cout << "\n+========================================+" << endl;
        cout << "|   Selamat datang di Valorant Tierlist  |" << endl;
        cout << "+========================================+" << endl;
        cout << "| 1. Masuk                               |" << endl;
        cout << "| 2. Keluar                              |" << endl;
        cout << "+========================================+" << endl;
        cout << "Pilihan: ";
        cin >> pilihanUtama;

        if (pilihanUtama == 1) {
            int idxUser = login(users, jumlahUser);
            if (idxUser != -1) {
                if (users[idxUser].role == "Admin") {
                    // Menggunakan Address-of Operator (&) untuk mengirim alamat variabel
                    menuAdmin(tierlist, &jumlahAgent);
                } else {
                    menuUser(tierlist, jumlahAgent);
                }
            }
        } else if (pilihanUtama == 2) {
            cout << "Terima kasih, Program selesai.\n";
        } else {
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihanUtama != 2);

    return 0;
}

