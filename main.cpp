#include <iostream>
#include <limits> 
#include "pemutarLagu.h"

using namespace std;

void cleanInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main()
{
    AplikasiMusik app;
    inisialisasi(app);

    tambahLagu(app, 101, "Hati-Hati di Jalan", "Tulus", "Pop", 2022);
    tambahLagu(app, 102, "Sang Dewi", "Lyodra", "Pop", 2022);
    tambahLagu(app, 103, "Heavy Rotation", "JKT48", "Pop", 2013);
    buatPlaylist(app, "Favorit");
    masukLaguKePlaylist(app, "Favorit", 101);

    int pilihan;
    do {
        cout << "\n===============================" << endl;
        cout << "   APLIKASI PEMUTAR MUSIK" << endl;
        cout << "===============================" << endl;
        cout << "1. Tambah Lagu ke Library" << endl;
        cout << "2. Tampilkan Library" << endl;
        cout << "3. Hapus Lagu (ID)" << endl;
        cout << "4. Buat Playlist Baru" << endl;
        cout << "5. Masukkan Lagu ke Playlist" << endl;
        cout << "6. Tampilkan Playlist" << endl;
        cout << "0. Keluar" << endl;
        cout << "Pilihan: ";
        
        if (!(cin >> pilihan)) {
            cout << "Input harus angka!" << endl;
            cleanInput();
            continue;
        }

        switch(pilihan) {
            case 1: {
                int id, tahun;
                string judul, artis, genre;
                cout << "Masukkan ID (angka): "; cin >> id;
                cleanInput(); 
                
                cout << "Judul: "; getline(cin, judul);
                cout << "Artis: "; getline(cin, artis);
                cout << "Genre: "; getline(cin, genre);
                cout << "Tahun: "; cin >> tahun;
                
                tambahLagu(app, id, judul, artis, genre, tahun);
                break;
            }
            case 2:
                tampilkanLibrary(app);
                break;
            case 3: {
                int id;
                cout << "Masukkan ID lagu yang akan dihapus: "; cin >> id;
                hapusLagu(app, id);
                break;
            }
            case 4: {
                cleanInput();
                string namaPL;
                cout << "Nama Playlist Baru: "; getline(cin, namaPL);
                buatPlaylist(app, namaPL);
                break;
            }
            case 5: {
                cleanInput();
                string namaPL;
                int id;
                cout << "Nama Playlist Tujuan: "; getline(cin, namaPL);
                cout << "ID Lagu dari Library: "; cin >> id;
                masukLaguKePlaylist(app, namaPL, id);
                break;
            }
            case 6: {
                cleanInput();
                string namaPL;
                cout << "Masukkan Nama Playlist: "; getline(cin, namaPL);
                tampilkanPlaylist(app, namaPL);
                break;
            }
            case 0:
                cout << "Terima kasih!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid." << endl;
        }

    } while (pilihan != 0);

    return 0;
}
