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
    cout << "[Info] Lagu '" << judul << "' berhasil ditambahkan ke Library." << endl;
}

void bersihkanReferensi(AplikasiMusik &app, ListLagu* target) {
    while (pBantu != nullptr) {
        ListIsiPlaylist* laguDiPlaylist = pBantu->headLagu;

        while (laguDiPlaylist != nullptr) {
            ListIsiPlaylist* nextNode = laguDiPlaylist->next;

            if (laguDiPlaylist->referensiLagu == target) {
                
                if (laguDiPlaylist->prev != nullptr) {
                    laguDiPlaylist->prev->next = laguDiPlaylist->next;
                }else{
                    pBantu->headLagu = laguDiPlaylist->next;
                }

                if (laguDiPlaylist->next != nullptr) {
                    laguDiPlaylist->next->prev = laguDiPlaylist->prev;
                } else {
                    pBantu->tailLagu = laguDiPlaylist->prev;
                }

                delete laguDiPlaylist;
            }
            laguDiPlaylist = nextNode;
        }
        pBantu = pBantu->next;
    }
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
    cout << "\n=== LIBRARY MUSIK ===" << endl;
    if (app.headLibrary == nullptr) {
        cout << "(Library Kosong)" << endl;
        return;
    }

    cout << left << setw(5) << "ID" 
         << setw(20) << "Judul" 
         << setw(15) << "Artis" 
         << setw(10) << "Genre" 
         << setw(6) << "Tahun" << endl;
    cout << "--------------------------------------------------------" << endl;

    ListLagu* bantu = app.headLibrary;
    while (bantu != nullptr) {
        cout << left << setw(5) << bantu->data.id 
             << setw(20) << bantu->data.judul 
             << setw(15) << bantu->data.artis 
             << setw(10) << bantu->data.genre 
             << setw(6) << bantu->data.tahun << endl;
        bantu = bantu->next;
    }
    cout << "--------------------------------------------------------" << endl;
}

void buatPlaylist(AplikasiMusik &app, string nama) {
    ListPlaylist* cek = app.headPlaylist;
    while(cek != nullptr){
        if(cek->namaPlaylist == nama){
            cout << "[Error] Playlist '" << nama << "' sudah ada!" << endl;
            return;
        }
        cek = cek->next;
    }

    ListPlaylist* baru = new ListPlaylist;
    baru->namaPlaylist = nama;
    baru->headLagu = nullptr;
    baru->tailLagu = nullptr;

    baru->next = app.headPlaylist;
    app.headPlaylist = baru;
    
    cout << "[Info] Playlist '" << nama << "' berhasil dibuat." << endl;
}

void masukLaguKePlaylist(AplikasiMusik &app, string namaPlaylist, int idLagu) {
ListPlaylist* targetPL = app.headPlaylist;
    while (targetPL != nullptr && targetPL->namaPlaylist != namaPlaylist) {
        targetPL = targetPL->next;
    }

    if (targetPL == nullptr) {
        cout << "[Error] Playlist '" << namaPlaylist << "' tidak ditemukan." << endl;
        return;
    }

    ListLagu* targetLagu = app.headLibrary;
    while (targetLagu != nullptr && targetLagu->data.id != idLagu) {
        targetLagu = targetLagu->next;
    }

    if (targetLagu == nullptr) {
        cout << "[Error] Lagu ID " << idLagu << " tidak ditemukan di Library." << endl;
        return;
    }

    ListIsiPlaylist* baru = new ListIsiPlaylist;
    baru->referensiLagu = targetLagu; // Pointing ke alamat memori lagu asli
    baru->next = nullptr;
    baru->prev = nullptr;

    if (targetPL->headLagu == nullptr) {
        targetPL->headLagu = baru;
        targetPL->tailLagu = baru;
    } else {
        targetPL->tailLagu->next = baru;
        baru->prev = targetPL->tailLagu;
        targetPL->tailLagu = baru;
    }
    
    cout << "[Info] Lagu '" << targetLagu->data.judul << "' masuk ke playlist '" << namaPlaylist << "'." << endl;
}

void tampilkanPlaylist(AplikasiMusik &app, string namaPlaylist) {
ListPlaylist* targetPL = app.headPlaylist;
    while (targetPL != nullptr && targetPL->namaPlaylist != namaPlaylist) {
        targetPL = targetPL->next;
    }

    if (targetPL == nullptr) {
        cout << "[Error] Playlist '" << namaPlaylist << "' tidak ditemukan." << endl;
        return;
    }

    cout << "\n--- Playlist: " << targetPL->namaPlaylist << " ---" << endl;
    if (targetPL->headLagu == nullptr) {
        cout << "(Playlist Kosong)" << endl;
        return;
    }

    ListIsiPlaylist* bantu = targetPL->headLagu;
    int no = 1;
    while (bantu != nullptr) {
        cout << no++ << ". " << bantu->referensiLagu->data.judul 
             << " - " << bantu->referensiLagu->data.artis << endl;
        bantu = bantu->next;
    }
}
