#include <stdio.h>
#include <windows.h>
#include "buku.h"

void tampilkanBuku() {
    system("cls");
    if (jumlahBuku == 0) {
        printf("\n Belum ada data buku yang dimasukkan \n");
        return ;
    }

    FILE *file = fopen("Perpustakaan.txt", "a");

    if (file == NULL) {
        printf("Gagal membuat file\n");
        return;
    }

    fprintf(file, "============ DATA BUKU PERPUSTAKAAN ============\n");
    for (int i = 0; i < jumlahBuku; i++) {
        fprintf(file, "\nBuku ke-%d\n", i + 1);
        fprintf(file, "Judul Buku    : %s\n", daftar[i].judul);
        fprintf(file, "Penulis       : %s\n", daftar[i].penulis);
        fprintf(file, "Tahun Terbit  : %d\n", daftar[i].tahun);
    }

    fclose(file);
    printf("Buku yang ditambahkan dapat dilihat di 'Perpustakaan.txt'\n");
}