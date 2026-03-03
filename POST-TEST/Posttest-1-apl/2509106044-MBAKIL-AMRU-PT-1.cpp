#include <iostream>
using namespace std;

int main() {

    string namaBenar = "Bakil";
    string pwBenar   = "044";

    string nama, pw;
    int percobaan = 0;

    cout << "==============================\n";
    cout << "[  PROGRAM KONVERSI PANJANG  ]\n";
    cout << "==============================\n\n";

    // ===== LOGIN =====
    while (percobaan < 3) {

        cout << "=== Sebelum lanjut silahkan login dulu ===\n";
        cout << "Masukkan Nama: ";
        cin >> nama;

        cout << "Masukkan Password (3 digit terakhir NIM): ";
        cin >> pw;

        if (nama == namaBenar && pw == pwBenar) {
            cout << "\n>>> Login berhasil, Selamat datang yang mulia "
                 << nama << " <<<\n\n";
            break;
        } 
        else {
            percobaan++;
            cout << "Periksa Nama atau Password dengan benar. Percobaan ke-"
                 << percobaan << "\n\n";
        }
    }

    if (percobaan == 3) {
        cout << "Anda salah memasukkan nama atau password 3 kali.\n";
        cout << "Program kami hentikan, mohon maaf.\n";
        return 0;
    }

    // ===== MENU =====
    char pilihan;
    double nilai;

    do {

        cout << "-------------------------------------\n";
        cout << "          MENU KONVERSI PANJANG      \n";
        cout << "-------------------------------------\n";
        cout << "1. Meter -> Kilometer dan Centimeter\n";
        cout << "2. Kilometer -> Meter dan Centimeter\n";
        cout << "3. Centimeter -> Meter dan Kilometer\n";
        cout << "4. Keluar\n";
        cout << "-------------------------------------\n";
        cout << "Pilih menu (1-4): ";

        cin >> pilihan;

        switch (pilihan) {

            case '1':
                cout << "\nMasukkan panjang (m): ";
                cin >> nilai;
                cout << "Hasil: " << nilai << " m = "
                     << nilai / 1000 << " km dan "
                     << nilai * 100 << " cm\n\n";
                break;

            case '2':
                cout << "\nMasukkan panjang (km): ";
                cin >> nilai;
                cout << "Hasil: " << nilai << " km = "
                     << nilai * 1000 << " m dan "
                     << nilai * 100000 << " cm\n\n";
                break;

            case '3':
                cout << "\nMasukkan panjang (cm): ";
                cin >> nilai;
                cout << "Hasil: " << nilai << " cm = "
                     << nilai / 100 << " m dan "
                     << nilai / 100000 << " km\n\n";
                break;

            case '4':
                cout << "\n>>> Terima kasih, program selesai. <<<\n";
                break;

            default:
                cout << "\nPilihan tidak valid. Silakan coba lagi.\n\n";
        }

    } while (pilihan != '4');

    return 0;
}

