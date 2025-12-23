#ifndef PEMUTARLAGU_H_INCLUDED
#define PEMUTARLAGU_H_INCLUDED

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

// struktur data lagu

struct DataLagu {
    int id;
    string judul;
    string artis;
    string genre;
    int tahun;
};

// ini untuk elemen list di library (data asli)
struct ListLagu {
    DataLagu data;
    ListLagu* prev;
    ListLagu* next;
};

// pakai DLL untuk isi Playlist
// pointer ke data asli
struct ListIsiPlaylist {
    ListLagu* referensiLagu;
    ListIsiPlaylist* prev;
    ListIsiPlaylist* next;
};

// daftar playlist pakai SLL
struct ListPlaylist {
    string namaPlaylist;
    ListIsiPlaylist* headLagu;
    ListIsiPlaylist* tailLagu;
    ListPlaylist* next;
};

// struct aplikasi utama
struct AplikasiMusik {
    // pointer paling dasar
    ListLagu* headLibrary;
    ListLagu* tailLibrary;

    // untuk playlist
    ListPlaylist* headPlaylist;

    // pointer & status (untuk fitur player)
    ListLagu* laguSedangDiputar;
    ListIsiPlaylist* nodePlaylistDiputar;
    bool isPlaying;
    bool modePlaylist;
};

// inisialisasi
void inisialisasi(AplikasiMusik &app);

// manajemen library
void tambahLagu(AplikasiMusik &app, int id, string judul, string artis, string genre, int tahun);
void hapusLagu(AplikasiMusik &app, int id);
void tampilkanLibrary(AplikasiMusik &app);
void cariLaguByID(AplikasiMusik &app, int id);           // tambahan
void cariLaguByTeks(AplikasiMusik &app, string keyword); // tambahan

// manajemen playlist
void buatPlaylist(AplikasiMusik &app, string nama);
void masukLaguKePlaylist(AplikasiMusik &app, string namaPlaylist, int idLagu);
void hapusLaguDariPlaylist(AplikasiMusik &app, string namaPlaylist, int idLagu); // tambahan
void tampilkanPlaylist(AplikasiMusik &app, string namaPlaylist);

// fitur player control (tambahan)
void putarLagu(AplikasiMusik &app, int idLagu);
void putarPlaylist(AplikasiMusik &app, string namaPlaylist);
void stopLagu(AplikasiMusik &app);
void nextLagu(AplikasiMusik &app);
void prevLagu(AplikasiMusik &app);
void statusPlayer(AplikasiMusik &app);

// bersihkan referensi
void bersihkanReferensi(AplikasiMusik &app, ListLagu* target);

#endif // PEMUTARLAGU_H_INCLUDED
