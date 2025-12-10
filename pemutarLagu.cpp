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

}

void tampilkanPlaylist(AplikasiMusik &app, string namaPlaylist) {

}
