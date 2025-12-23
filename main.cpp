#include <iostream>
#include <limits> // untuk bersihin input error
#include "pemutarLagu.h"

using namespace std;

// fungsi jeda biar bisa baca pesan
void pause() {
    cout << "\n[Tekan Enter kembali ke menu...]";
    // membersihkan sisa input enter sebelumnya jika ada
    if (cin.peek() == '\n') cin.ignore();
    cin.get();
}

// fungsi biar bisa input yang ada spasi
string inputTeks(string pesan) {
    string hasil;
    cout << pesan;
    // cek buffer
    if (cin.peek() == '\n') cin.ignore();
    getline(cin, hasil);
    return hasil;
}

int main() {
    AplikasiMusik app;
    inisialisasi(app);
    //dummy
    tambahLagu(app, 1, "Separuh Aku", "Noah", "Pop", 2012);
    tambahLagu(app, 2, "Pupus", "Dewa 19", "Rock", 2002);
    tambahLagu(app, 3, "Monokrom", "Tulus", "Jazz", 2016);
    tambahLagu(app, 4, "Sial", "Mahalini", "Pop", 2023);

    buatPlaylist(app, "Galau");
    masukLaguKePlaylist(app, "Galau", 2); // Masukkan Pupus
    masukLaguKePlaylist(app, "Galau", 4); // Masukkan Sial

    int pilihan = -1;

    // Loop Menu Utama
    while (pilihan != 0) {
        // 1. Bersihkan Layar
        cout << string(50, '\n');

        // 2. Tampilkan Status Player di Atas
        cout << "========================================" << endl;
        cout << "           TEAM-10 MUSIC PLAYER         " << endl;
        cout << "========================================" << endl;
        statusPlayer(app); // fitur untuk selalu menampilkan playernya

        // 3. Menu Pilihan
        cout << "\n[ LIBRARY ]" << endl;
        cout << "  1. Lihat Semua Lagu" << endl;
        cout << "  2. Tambah Lagu" << endl;
        cout << "  3. Cari Lagu" << endl;
        cout << "  4. Hapus Lagu" << endl;

        cout << "\n[ PLAYLIST ]" << endl;
        cout << "  5. Buat Playlist" << endl;
        cout << "  6. Lihat Playlist" << endl;
        cout << "  7. Masukkan Lagu ke Playlist" << endl;
        cout << "  8. Hapus Lagu dari Playlist" << endl;

        cout << "\n[ CONTROLLER ]" << endl;
        cout << "  9. Play Lagu (ID)" << endl;
        cout << " 10. Play Playlist" << endl;
        cout << " 11. Next >>" << endl;
        cout << " 12. << Prev" << endl;
        cout << " 13. Stop" << endl;

        cout << "\n  0. KELUAR" << endl;
        cout << "========================================" << endl;
        cout << "Pilih menu (angka): ";
        cin >> pilihan;

        // validasi jika user input huruf, bukan angka
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            pilihan = -1; // set balik lagi
        }

        cout << endl;

        if (pilihan == 1) {
            tampilkanLibrary(app);
            pause();
        }
        else if (pilihan == 2) {
            int id, tahun;
            cout << "--- Tambah Lagu Baru ---\n";
            cout << "ID Unik (angka) : "; cin >> id;
            string judul = inputTeks("Judul Lagu      : ");
            string artis = inputTeks("Nama Artis      : ");
            string genre = inputTeks("Genre           : ");
            cout << "Tahun Rilis     : "; cin >> tahun;

            tambahLagu(app, id, judul, artis, genre, tahun);
            pause();
        }
        else if (pilihan == 3) {
            string kata = inputTeks("Cari Judul/Artis: ");
            cariLaguByTeks(app, kata);
            pause();
        }
        else if (pilihan == 4) {
            int id;
            cout << "Hapus ID Lagu: "; cin >> id;
            hapusLagu(app, id);
            pause();
        }
        else if (pilihan == 5) {
            string nama = inputTeks("Nama Playlist Baru: ");
            buatPlaylist(app, nama);
            pause();
        }
        else if (pilihan == 6) {
            string nama = inputTeks("Buka Playlist Nama: ");
            tampilkanPlaylist(app, nama);
            pause();
        }
        else if (pilihan == 7) {
            string nama = inputTeks("Nama Playlist Tujuan: ");
            int id;
            cout << "ID Lagu yang dimasukkan: "; cin >> id;
            masukLaguKePlaylist(app, nama, id);
            pause();
        }
        else if (pilihan == 8) {
            string nama = inputTeks("Dari Playlist Nama: ");
            int id;
            cout << "ID Lagu yang dihapus: "; cin >> id;
            hapusLaguDariPlaylist(app, nama, id);
            pause();
        }
        else if (pilihan == 9) {
            int id;
            cout << "Play ID Lagu: "; cin >> id;
            putarLagu(app, id);
            pause();
        }
        else if (pilihan == 10) {
            string nama = inputTeks("Play Playlist Nama: ");
            putarPlaylist(app, nama);
            pause();
        }
        else if (pilihan == 11) {
            nextLagu(app);
            pause();
        }
        else if (pilihan == 12) {
            prevLagu(app);
            pause();
        }
        else if (pilihan == 13) {
            stopLagu(app);
            pause();
        }
        else if (pilihan == 0) {
            cout << "Sampai Jumpa!" << endl;
        }
        else {
            cout << "[Error] Pilihan tidak valid, coba angka 0-13." << endl;
            pause();
        }
    }

    return 0;
}
