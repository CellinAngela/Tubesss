#include <stdio.h>
#include "buku.h"

void tampilkanBuku() {
    FILE *file;  // Pointer file

    file = fopen("Perpustakaan.txt", "w"); // mode write (w) → data lama akan ditimpa

    if (file == NULL) {
        printf("❌ Gagal membuat file.\n");
        return;
    }

    fprintf(file, "=== DATA BUKU PERPUSTAKAAN ===\n");

    if (jumlahBuku == 0) {
        fprintf(file, "Belum ada data buku.\n");
        fclose(file);
        return;
    }

    for (int i = 0; i < jumlahBuku; i++) {
        fprintf(file, "\nBuku ke-%d\n", i + 1);
        fprintf(file, "Judul   : %s\n", daftar[i].judul);
        fprintf(file, "Penulis : %s\n", daftar[i].penulis);
        fprintf(file, "Tahun   : %d\n", daftar[i].tahun);
    }

    fclose(file); // tutup file setelah selesai
    printf("✔ Data berhasil disimpan di 'Perpustakaan.txt'\n");
}
