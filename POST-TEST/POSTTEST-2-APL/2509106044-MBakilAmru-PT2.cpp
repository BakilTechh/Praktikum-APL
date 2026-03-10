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

Agent tierlist[MAX_AGENT];
int jumlahAgent = 0;
User users[MAX_USER];
int jumlahUser = 0;

// Fungsi menampilkan tierlist
int tampilkanTierlist() {
    if (jumlahAgent == 0) {
        cout << "Belum ada agent yang ditambahkan." << endl;
        return 0;
    }

    cout << "\n=== TIERLIST VALORANT ===" << endl;
    cout << "+----+-----------------+------+-------------+----------+" << endl;
    cout << "| No | Nama Agent      | Tier | Role        | Pickrate |" << endl;
    cout << "+----+-----------------+------+-------------+----------+" << endl;

    for (int i = 0; i < jumlahAgent; i++) {
        cout << "| " << i + 1
             << "  | " << tierlist[i].nama
             << string(15 - tierlist[i].nama.size(), ' ')
             << "| " << tierlist[i].tier
             << "    | " << tierlist[i].stat.role
             << string(11 - tierlist[i].stat.role.size(), ' ')
             << "| " << tierlist[i].stat.pickrate << "%"
             << string(8 - to_string(tierlist[i].stat.pickrate).size(), ' ')
             << "|" << endl;
    }

    cout << "+----+-----------------+------+-------------+----------+" << endl;
    return 1;
}

// Menu Admin
int menuAdmin() {
    cout << "\n========================================================" << endl;
    cout << "   SELAMAT DATANG ADMIN DI TIERLIST AGENT VALORANT      " << endl;
    cout << "========================================================" << endl;

    int pilihan;
    do {
        cout << "\n=== Hai, Admin Bakil, apa yang ingin anda lakukan? ===" << endl;
        cout << "1. Lihat Tierlist" << endl;
        cout << "2. Tambah Agent" << endl;
        cout << "3. Ubah Agent" << endl;
        cout << "4. Hapus Agent" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            tampilkanTierlist();
            break;

        case 2:
            if (jumlahAgent < MAX_AGENT) {
                cout << "Nama Agent: ";
                cin.ignore();
                getline(cin, tierlist[jumlahAgent].nama);

                cout << "Tier (S/A/B/C/D): ";
                getline(cin, tierlist[jumlahAgent].tier);

                cout << "Role: ";
                getline(cin, tierlist[jumlahAgent].stat.role);

                cout << "Pickrate (%): ";
                cin >> tierlist[jumlahAgent].stat.pickrate;

                jumlahAgent++;
                cout << "Agent berhasil ditambahkan.\n";
            } else {
                cout << "Kapasitas penuh.\n";
            }
            break;

        case 3:
            if (jumlahAgent > 0) {
                int nomorAgent;
                cout << "Nomor agent yang diubah: ";
                cin >> nomorAgent;

                if (nomorAgent > 0 && nomorAgent <= jumlahAgent) {
                    cout << "Nama baru: ";
                    cin.ignore();
                    getline(cin, tierlist[nomorAgent - 1].nama);

                    cout << "Tier baru: ";
                    getline(cin, tierlist[nomorAgent - 1].tier);

                    cout << "Role baru: ";
                    getline(cin, tierlist[nomorAgent - 1].stat.role);

                    cout << "Pickrate baru: ";
                    cin >> tierlist[nomorAgent - 1].stat.pickrate;

                    cout << "Update berhasil.\n";
                } else {
                    cout << "Agent tidak ditemukan.\n";
                }
            } else {
                cout << "Belum ada agent.\n";
            }
            break;

        case 4:
            if (jumlahAgent > 0) {
                int nomorAgent;
                cout << "Nomor agent yang dihapus: ";
                cin >> nomorAgent;

                if (nomorAgent > 0 && nomorAgent <= jumlahAgent) {
                    for (int i = nomorAgent - 1; i < jumlahAgent - 1; i++) {
                        tierlist[i] = tierlist[i + 1];
                    }
                    jumlahAgent--;
                    cout << "Agent dihapus.\n";
                } else {
                    cout << "Agent tidak ditemukan.\n";
                }
            } else {
                cout << "Belum ada agent.\n";
            }
            break;

        case 5:
            cout << "Keluar dari menu Admin.\n";
            break;

        default:
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 5);

    return 0;
}

// Menu User
bool menuUser() {
    cout << "\n---------------------------------------------------------------" << endl;
    cout << "   SELAMAT DATANG USER TIERLIST DI TIERLIST AGENT VALORANT      " << endl;
    cout << "---------------------------------------------------------------" << endl;

    int pilihan;
    do {
        cout << "\n=== MENU USER ===" << endl;
        cout << "1. Lihat Tierlist" << endl;
        cout << "2. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;

        switch (pilihan) {
        case 1:
            tampilkanTierlist();
            break;

        case 2:
            cout << "Keluar dari menu User.\n";
            break;

        default:
            cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 2);

    return true;
}

// Fungsi login
string login() {
    string uname, pw;
    int attempt = 0;
    while (attempt < 3) {
        cout << "\n|==================================|" << endl;
        cout << "|========== LOGIN DAHULU ==========|" << endl;
        cout << "|==================================|" << endl;
        cout << "Masukkan Username: "; cin >> uname;
        cout << "Masukkan Password: "; cin >> pw;

        for (int i = 0; i < jumlahUser; i++) {
            if (users[i].username == uname && users[i].password == pw) {
                cout << "\nLogin berhasil sebagai " << users[i].role << "\n";
                return users[i].role;
            }
        }
        attempt++;
        cout << "Login gagal (" << attempt << "/3)\n";
    }
    return "gagal,coba lagi nanti";
}

int main() {
    // Ini untuk Memasukkan Nama dan password, untuk login admin maupun user
    users[jumlahUser++] = {"Bakil", "044", "Admin"};
    users[jumlahUser++] = {"User", "123", "User"};

    // Tambahkan agent contoh
    tierlist[jumlahAgent++] = {"Jett", "S", {"Duelist", 85}};
    tierlist[jumlahAgent++] = {"Iso", "B", {"Duelist", 40}};
    tierlist[jumlahAgent++] = {"Reyna", "A", {"Duelist", 60}};

    string role = login();
    if (role == "Admin") {
        menuAdmin();
    } else if (role == "User") {
        menuUser();
    } else {
        cout << "Program berhenti.\n";
    }
    return 0;
}