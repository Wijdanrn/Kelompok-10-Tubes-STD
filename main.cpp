#include <iostream>

using namespace std;

int main() {
    AplikasiMusik app;
    inisialisasi(app);

    tambahLagu(app, 1, "Fix You", "Coldplay", "Pop", 2005);
    tambahLagu(app, 2, "Yellow", "Coldplay", "Pop", 2000);
    tambahLagu(app, 3, "Happier", "Ed Sheeran", "Pop", 2017);

    buatPlaylist(app, "Favorit");

    masukLaguKePlaylist(app, "Favorit", 1);
    masukLaguKePlaylist(app, "Favorit", 3);

    cout << "\n=== Library ===\n";
    tampilkanLibrary(app);

    cout << "\n=== Playlist Favorit ===\n";
    tampilkanPlaylist(app, "Favorit");

    cout << "\nMenghapus lagu ID 1...\n";
    hapusLagu(app, 1);

    cout << "\n=== Playlist Favorit Setelah Hapus ===\n";
    tampilkanPlaylist(app, "Favorit");

    return 0;
}
