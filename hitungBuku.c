#include "hitungBuku.h"
#include <stdio.h>
#include <windows.h>
#include <string.h>

int hitungTotalBuku(struct Buku data[], int n) {
    return n;
}

int hitungJudulBukuDariFile() {
    FILE *file = fopen("Perpustakaan.txt", "r");
    if (file == NULL) {
        return 0;
    }
    
    int count = 0;
    char line[256];
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, "Judul Buku") != NULL || strstr(line, "Judul   :") != NULL) {
            count++;
        }
    }
    
    fclose(file);
    return count;
}

void hitungBuku(){
    system("cls");
    printf("\n==============================================\n");
    printf("|          HITUNG JUMLAH BUKU              |\n");
    printf("==============================================\n");

    int totalJudul = hitungJudulBukuDariFile();
    int totalBuku = hitungTotalBuku(daftar, jumlahBuku);
    
    printf("\nJumlah Buku yang Ditambahkan: %d\n", totalBuku);
    printf("Total Jumlah Buku di Perpustakaan: %d\n", totalJudul);
    
    printf("\n==============================================\n");
    printf("\nTekan ENTER untuk kembali");
    getchar();
}

