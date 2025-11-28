#include <stdio.h>
#include "buku.h"

void tampilkanBuku() {
    printf("\n=== DAFTAR BUKU ===\n");
    if (jumlahBuku == 0) {
        printf("Belum ada data buku.\n");
        return;
    }

    for (int i = 0; i < jumlahBuku; i++) {
        printf("\nBuku ke-%d\n", i + 1);
        printf("Judul   : %s\n", daftar[i].judul);
        printf("Penulis : %s\n", daftar[i].penulis);
        printf("Tahun   : %d\n", daftar[i].tahun);
    }
}
