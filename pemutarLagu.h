#ifndef STRUKTUR_H
#define STRUKTUR_H

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

struct DataLagu {
    int id;
    string judul;
    string artis;
    string genre;
    int tahun;
};

struct ListLagu {
    DataLagu data;
    ListLagu* prev;
    ListLagu* next;
};

struct ListIsiPlaylist {
    ListLagu* referensiLagu;
    ListIsiPlaylist* prev;
    ListIsiPlaylist* next;
};

struct ListPlaylist {
    string namaPlaylist;
    ListIsiPlaylist* headLagu;
    ListIsiPlaylist* tailLagu;
    ListPlaylist* next;
};

struct AplikasiMusik {
    ListLagu* headLibrary;
    ListLagu* tailLibrary;
    ListPlaylist* headPlaylist;
};

void inisialisasi(AplikasiMusik &app);

void tambahLagu(AplikasiMusik &app, int id, string judul, string artis, string genre, int tahun);
void hapusLagu(AplikasiMusik &app, int id);
void tampilkanLibrary(AplikasiMusik &app);

void buatPlaylist(AplikasiMusik &app, string nama);
void masukLaguKePlaylist(AplikasiMusik &app, string namaPlaylist, int idLagu);
void tampilkanPlaylist(AplikasiMusik &app, string namaPlaylist);

void bersihkanReferensi(AplikasiMusik &app, ListLagu* target);

#endif
