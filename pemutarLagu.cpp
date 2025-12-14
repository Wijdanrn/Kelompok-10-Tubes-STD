#include "struktur.h"

void inisialisasi(AplikasiMusik &app) {
    app.headLibrary = nullptr;
    app.tailLibrary = nullptr;
    app.headPlaylist = nullptr;
}

void tambahLagu(AplikasiMusik &app, int id, string judul, string artis, string genre, int tahun) {
    ListLagu* baru = new ListLagu;
    baru->data.id = id;
    baru->data.judul = judul;
    baru->data.artis = artis;
    baru->data.genre = genre;
    baru->data.tahun = tahun;
    baru->next = nullptr;
    baru->prev = nullptr;

    if (app.headLibrary == nullptr) {
        app.headLibrary = baru;
        app.tailLibrary = baru;
    } else {
        app.tailLibrary->next = baru;
        baru->prev = app.tailLibrary;
        app.tailLibrary = baru;
    }
}

void bersihkanReferensi(AplikasiMusik &app, ListLagu* target) {

}

void hapusLagu(AplikasiMusik &app, int id) {
    ListLagu* bantu = app.headLibrary;
    while (bantu != nullptr) {
        if (bantu->data.id == id) {
            bersihkanReferensi(app, bantu);

            if (bantu->prev!=nullptr) bantu->prev->next = bantu->next;
            else app.headLibrary = bantu->next;

            if (bantu->next!=nullptr) bantu->next->prev = bantu->prev;
            else app.tailLibrary = bantu->prev;

            cout << "[Info] Lagu '" << bantu->data.judul << "' dihapus." << endl;
            delete bantu;
            return;
        }
        bantu = bantu->next;
    }
    cout << "[Error] Lagu ID " << id << " tidak ditemukan." << endl;
}

void tampilkanLibrary(AplikasiMusik &app) {
    ListLagu* p = app.headLibrary;

    if (p == nullptr) {
        cout << "Library kosong\n";
        return;
    }

    while (p != nullptr) {
        cout << p->data.id << " | "
             << p->data.judul << " | "
             << p->data.artis << " | "
             << p->data.genre << " | "
             << p->data.tahun << endl;
        p = p->next;
    }
}

void buatPlaylist(AplikasiMusik &app, string nama) {
    ListPlaylist* baru = new ListPlaylist;
    baru->namaPlaylist = nama;
    baru->headLagu = nullptr;
    baru->tailLagu = nullptr;

    baru->next = app.headPlaylist;
    app.headPlaylist = baru;
}

void masukLaguKePlaylist(AplikasiMusik &app, string namaPlaylist, int idLagu) {
    ListPlaylist* p = app.headPlaylist;
    ListLagu* lagu = app.headLibrary;

    while (p != nullptr && p->namaPlaylist != namaPlaylist)
        p = p->next;

    while (lagu != nullptr && lagu->data.id != idLagu)
        lagu = lagu->next;

    if (p == nullptr || lagu == nullptr) {
        cout << "Playlist atau lagu tidak ditemukan\n";
        return;
    }

    ListIsiPlaylist* baru = new ListIsiPlaylist;
    baru->referensiLagu = lagu;
    baru->prev = nullptr;
    baru->next = nullptr;

    if (p->headLagu == nullptr) {
        p->headLagu = baru;
        p->tailLagu = baru;
    } else {
        p->tailLagu->next = baru;
        baru->prev = p->tailLagu;
        p->tailLagu = baru;
    }
}

void tampilkanPlaylist(AplikasiMusik &app, string namaPlaylist) {

}
