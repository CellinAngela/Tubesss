#ifndef HAPUSBUKU_H
#define HAPUSBUKU_H

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "buku.h"

void hapusBuku() {
    system("cls");
    char judulHapus[100];
    int ditemukan = 0;

    printf("\n================= HAPUS BUKU =================\n\n");
    printf("Masukkan judul buku yang ingin dihapus: ");
    fgets(judulHapus, sizeof(judulHapus), stdin);
    judulHapus[strcspn(judulHapus, "\n")] = 0;

    FILE *file = fopen("Perpustakaan.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!file) {
    printf("\nData buku masih kosong\n");
    printf("Tekan ENTER untuk kembali");
    getchar();
    return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Judul Buku", 10) == 0 && strstr(line, judulHapus)) {  
            ditemukan = 1;
            fgets(line, sizeof(line), file);
            fgets(line, sizeof(line), file);
            continue;
        }
        fputs(line, temp);
    }  

    fclose(file);
    fclose(temp);

    remove("Perpustakaan.txt");
    rename("temp.txt", "Perpustakaan.txt");

    if (ditemukan) {
    printf("\n==============================================");
    printf("\n|            BUKU BERHASIL DIHAPUS           |");
    printf("\n==============================================\n");
    } else {
    printf("\n============= BUKU TIDAK DITEMUKAN =============\n");
    }


    printf("\nTekan ENTER untuk kembali");
    getchar();
}

#endif
