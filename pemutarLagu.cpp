#include <iostream>
#include <string>
#include <iomanip>
#include "pemutarLagu.h"

using namespace std;

void inisialisasi(AplikasiMusik &app) {
    app.headLibrary = nullptr;
    app.tailLibrary = nullptr;
    app.headPlaylist = nullptr;

    app.laguSedangDiputar = nullptr;
    app.nodePlaylistDiputar = nullptr;
    app.isPlaying = false;
    app.modePlaylist = false;
}

void tambahLagu(AplikasiMusik &app, int id, string judul, string artis, string genre, int tahun) {
    ListLagu* cek = app.headLibrary;
    while (cek != nullptr) {
        if (cek->data.id == id) {
            cout << "[Error] Gagal menambahkan! ID " << id << " sudah digunakan oleh lagu '"
                 << cek->data.judul << "'." << endl;
            return; // keluar kalo id udah ada
        }
        cek = cek->next;
    }
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
    // stop dulu
    if (app.laguSedangDiputar == target) {
        stopLagu(app);
        cout << "[Info] Lagu yang sedang diputar dihapus, pemutaran dihentikan." << endl;
    }

    // cek di setiap playlist
    ListPlaylist* pBantu = app.headPlaylist;

    while (pBantu != nullptr) {
        ListIsiPlaylist* laguDiPlaylist = pBantu->headLagu;

        while (laguDiPlaylist != nullptr) {
            ListIsiPlaylist* nextNode = laguDiPlaylist->next; // simpan alamat next sebelum delete

            // jika alamat playlist ini menunjuk ke lagu yang akan dihapus
            if (laguDiPlaylist->referensiLagu == target) {

                // hapus node dari DLL playlist
                if (laguDiPlaylist->prev != nullptr) {
                    laguDiPlaylist->prev->next = laguDiPlaylist->next;
                } else {
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
    bool terhapus = false;

    // loop berhenti kalo udah kehapus semuanya
    while (bantu != nullptr && !terhapus) {
        if (bantu->data.id == id) {
            // bersihkan ref
            bersihkanReferensi(app, bantu);

            // hapus
            if (bantu->prev != nullptr) bantu->prev->next = bantu->next;
            else app.headLibrary = bantu->next;

            if (bantu->next != nullptr) bantu->next->prev = bantu->prev;
            else app.tailLibrary = bantu->prev;

            cout << "[Info] Lagu '" << bantu->data.judul << "' dihapus permanen." << endl;
            delete bantu;

            terhapus = true; //biar loop stop
        } else {
            bantu = bantu->next; // kalo belom abis bisa next
        }
    }

    if (!terhapus) {
        cout << "[Error] Lagu ID " << id << " tidak ditemukan." << endl;
    }
}

void cariLaguByID(AplikasiMusik &app, int id) {
    ListLagu* bantu = app.headLibrary;
    bool found = false;

    // loop berhenti jika list habis (sudah ketemu)
    while (bantu != nullptr && !found) {
        if (bantu->data.id == id) {
            cout << "[Ditemukan] " << bantu->data.judul << " - " << bantu->data.artis << endl;
            found = true;
        } else {
            bantu = bantu->next;
        }
    }

    if (!found) cout << "[Info] Lagu dengan ID " << id << " tidak ditemukan." << endl;
}

void cariLaguByTeks(AplikasiMusik &app, string keyword) {
    cout << "\nHasil Pencarian '" << keyword << "':" << endl;
    ListLagu* bantu = app.headLibrary;
    bool found = false;
    while (bantu != nullptr) {
        // cari berdasarkan keyword dengan fungsi find
        if (bantu->data.judul.find(keyword) != string::npos ||
            bantu->data.artis.find(keyword) != string::npos ||
            bantu->data.genre.find(keyword) != string::npos) {

            cout << "- " << bantu->data.judul << " (" << bantu->data.artis << ") [" << bantu->data.genre << "]" << endl;
            found = true;
        }
        bantu = bantu->next;
    }
    if (!found) cout << "Tidak ada lagu yang cocok." << endl;
}

void tampilkanLibrary(AplikasiMusik &app) {
    cout << "\n=== LIBRARY MUSIK ===" << endl;

    if (app.headLibrary == nullptr) {
        cout << "(Library Kosong)" << endl;
    } else {
        // pake setw biar rapi
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
}

void buatPlaylist(AplikasiMusik &app, string nama) {
    ListPlaylist* cek = app.headPlaylist;
    bool sudahAda = false;

    while(cek != nullptr && !sudahAda){
        if(cek->namaPlaylist == nama){
            cout << "[Error] Playlist '" << nama << "' sudah ada!" << endl;
            sudahAda = true;
        } else {
            cek = cek->next;
        }
    }

    // jika belom ada, baru buat
    if (!sudahAda) {
        ListPlaylist* baru = new ListPlaylist;
        baru->namaPlaylist = nama;
        baru->headLagu = nullptr;
        baru->tailLagu = nullptr;

        baru->next = app.headPlaylist;
        app.headPlaylist = baru;

        cout << "[Info] Playlist '" << nama << "' berhasil dibuat." << endl;
    }
}

void masukLaguKePlaylist(AplikasiMusik &app, string namaPlaylist, int idLagu) {
    // cari playlist
    ListPlaylist* targetPL = app.headPlaylist;
    while (targetPL != nullptr && targetPL->namaPlaylist != namaPlaylist) {
        targetPL = targetPL->next;
    }

    // menggunakan if-else berjenjang pengganti return
    if (targetPL == nullptr) {
        cout << "[Error] Playlist '" << namaPlaylist << "' tidak ditemukan." << endl;
    } else {
        // cari lagu di library
        ListLagu* targetLagu = app.headLibrary;
        while (targetLagu != nullptr && targetLagu->data.id != idLagu) {
            targetLagu = targetLagu->next;
        }

        if (targetLagu == nullptr) {
            cout << "[Error] Lagu ID " << idLagu << " tidak ditemukan di Library." << endl;
        } else {
            // masukkan ke playlist
            ListIsiPlaylist* baru = new ListIsiPlaylist;
            baru->referensiLagu = targetLagu; // menunjuk ke data asli
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
    }
}

void hapusLaguDariPlaylist(AplikasiMusik &app, string namaPlaylist, int idLagu) {
    ListPlaylist* pl = app.headPlaylist;
    while (pl != nullptr && pl->namaPlaylist != namaPlaylist) pl = pl->next;

    if (pl == nullptr) {
        cout << "Playlist tidak ditemukan." << endl;
    } else {
        ListIsiPlaylist* bantu = pl->headLagu;
        bool terhapus = false;

        // loop berhenti kalau sudah terhapus
        while (bantu != nullptr && !terhapus) {
            if (bantu->referensiLagu->data.id == idLagu) {
                // stop jika lagi di play di playlist ini
                if (app.isPlaying && app.nodePlaylistDiputar == bantu) {
                    stopLagu(app);
                    cout << "[Info] Lagu sedang diputar, player dihentikan." << endl;
                }

                if (bantu->prev) bantu->prev->next = bantu->next;
                else pl->headLagu = bantu->next;

                if (bantu->next) bantu->next->prev = bantu->prev;
                else pl->tailLagu = bantu->prev;

                delete bantu;
                cout << "[Info] Lagu berhasil dihapus dari playlist '" << namaPlaylist << "'." << endl;
                terhapus = true;
            } else {
                bantu = bantu->next;
            }
        }

        if (!terhapus) {
            cout << "[Info] Lagu tidak ditemukan di playlist ini." << endl;
        }
    }
}

void tampilkanPlaylist(AplikasiMusik &app, string namaPlaylist) {
    ListPlaylist* targetPL = app.headPlaylist;
    while (targetPL != nullptr && targetPL->namaPlaylist != namaPlaylist) {
        targetPL = targetPL->next;
    }

    if (targetPL == nullptr) {
        cout << "[Error] Playlist '" << namaPlaylist << "' tidak ditemukan." << endl;
    } else {
        cout << "\n--- Playlist: " << targetPL->namaPlaylist << " ---" << endl;
        if (targetPL->headLagu == nullptr) {
            cout << "(Playlist Kosong)" << endl;
        } else {
            ListIsiPlaylist* bantu = targetPL->headLagu;
            int no = 1;
            while (bantu != nullptr) {
                cout << no++ << ". " << bantu->referensiLagu->data.judul
                     << " - " << bantu->referensiLagu->data.artis << endl;
                bantu = bantu->next;
            }
        }
    }
}

void statusPlayer(AplikasiMusik &app) {
    if (app.isPlaying && app.laguSedangDiputar != nullptr) {
        cout << "\n>>> NOW PLAYING >>>" << endl;
        cout << "Judul : " << app.laguSedangDiputar->data.judul << endl;
        cout << "Artis : " << app.laguSedangDiputar->data.artis << endl;
        cout << "Mode  : " << (app.modePlaylist ? "Playlist" : "Library") << endl;
        cout << "-------------------" << endl;
    } else {
        cout << "[Player Idle]" << endl;
    }
}

void putarLagu(AplikasiMusik &app, int idLagu) {
    ListLagu* bantu = app.headLibrary;
    bool ketemu = false;

    while (bantu != nullptr && !ketemu) {
        if (bantu->data.id == idLagu) {
            app.laguSedangDiputar = bantu;
            app.modePlaylist = false; // main di library
            app.isPlaying = true;
            statusPlayer(app);
            ketemu = true;
        } else {
            bantu = bantu->next;
        }
    }

    if (!ketemu) {
        cout << "Lagu tidak ditemukan." << endl;
    }
}

void putarPlaylist(AplikasiMusik &app, string namaPlaylist) {
    ListPlaylist* pl = app.headPlaylist;
    while (pl && pl->namaPlaylist != namaPlaylist) pl = pl->next;

    if (pl && pl->headLagu != nullptr) {
        app.nodePlaylistDiputar = pl->headLagu;
        app.laguSedangDiputar = pl->headLagu->referensiLagu;
        app.modePlaylist = true; // main dari playlist
        app.isPlaying = true;
        statusPlayer(app);
    } else {
        cout << "Playlist kosong atau tidak ditemukan." << endl;
    }
}

void stopLagu(AplikasiMusik &app) {
    app.isPlaying = false;
    cout << "[Player] Berhenti memutar." << endl;
}

void nextLagu(AplikasiMusik &app) {
    if (!app.isPlaying) {
        cout << "Tidak ada lagu yang sedang diputar." << endl;
    } else {
        if (app.modePlaylist) {
            if (app.nodePlaylistDiputar != nullptr && app.nodePlaylistDiputar->next != nullptr) {
                app.nodePlaylistDiputar = app.nodePlaylistDiputar->next;
                app.laguSedangDiputar = app.nodePlaylistDiputar->referensiLagu;
                statusPlayer(app);
            } else {
                cout << "[End of Playlist] Sudah di lagu terakhir." << endl;
            }
        } else {
            if (app.laguSedangDiputar != nullptr && app.laguSedangDiputar->next != nullptr) {
                app.laguSedangDiputar = app.laguSedangDiputar->next;
                statusPlayer(app);
            } else {
                cout << "[End of Library] Sudah di lagu terakhir." << endl;
            }
        }
    }
}

void prevLagu(AplikasiMusik &app) {
    if (app.isPlaying) {
        if (app.modePlaylist) {
            if (app.nodePlaylistDiputar != nullptr && app.nodePlaylistDiputar->prev != nullptr) {
                app.nodePlaylistDiputar = app.nodePlaylistDiputar->prev;
                app.laguSedangDiputar = app.nodePlaylistDiputar->referensiLagu;
                statusPlayer(app);
            } else {
                cout << "[Start of Playlist] Ini lagu pertama." << endl;
            }
        } else {
            if (app.laguSedangDiputar != nullptr && app.laguSedangDiputar->prev != nullptr) {
                app.laguSedangDiputar = app.laguSedangDiputar->prev;
                statusPlayer(app);
            } else {
                cout << "[Start of Library] Ini lagu pertama." << endl;
            }
        }
    }
}
