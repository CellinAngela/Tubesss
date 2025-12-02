#ifndef HAPUSBUKU_H
#define HAPUSBUKU_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "buku.h"
#include "ansi.h"

void hapusBuku() {
    system("cls");
    char judulHapus[100];
    int ditemukan = 0;

    printf(COLOR_BLUE);
    printf("\n================= HAPUS BUKU =================\n\n");
    printf(COLOR_RESET);
    printf("Masukkan judul buku yang ingin dihapus: ");
    fgets(judulHapus, sizeof(judulHapus), stdin);
    judulHapus[strcspn(judulHapus, "\n")] = 0;

    FILE *file = fopen("Perpustakaan.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (!file) {
    printf("\nData buku masih kosong\n");
    printf(COLOR_CYAN);
    printf("Tekan ENTER untuk kembali");
    getchar();
    printf(COLOR_RESET);
    return;
    }

    char line[100];
    char judulLower[100];
    strncpy(judulLower, judulHapus, sizeof(judulLower)-1); judulLower[sizeof(judulLower)-1] = '\0';
    for (int k = 0; judulLower[k]; k++) judulLower[k] = tolower((unsigned char)judulLower[k]);

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, "Judul Buku", 10) == 0) {
            char lineLower[100];
            strncpy(lineLower, line, sizeof(lineLower)-1); lineLower[sizeof(lineLower)-1] = '\0';
            for (int k = 0; lineLower[k]; k++) lineLower[k] = tolower((unsigned char)lineLower[k]);
            if (strstr(lineLower, judulLower) != NULL) {
                ditemukan = 1;
                fgets(line, sizeof(line), file);
                fgets(line, sizeof(line), file);
                continue;
            }
        }
        fputs(line, temp);
    }  

    fclose(file);
    fclose(temp);

    remove("Perpustakaan.txt");
    rename("temp.txt", "Perpustakaan.txt");

    if (ditemukan) {
    printf(COLOR_GREEN);
    printf("\n==============================================");
    printf("\n|            BUKU BERHASIL DIHAPUS           |");
    printf("\n==============================================\n");
    printf(COLOR_RESET);
    } else {
    printf("\n============= BUKU TIDAK DITEMUKAN =============\n");
    }

    printf(COLOR_CYAN);
    printf("\nTekan ENTER untuk kembali");
    getchar();
    printf(COLOR_RESET);
}

#endif
