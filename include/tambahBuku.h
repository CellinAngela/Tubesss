#ifndef TAMBAHBUKU_H
#define TAMBAHBUKU_H

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "ansi.h"
#include "buku.h"

void tambahBuku(){
    system("cls");

    int jumlahInput;
    printf(COLOR_BLUE);
    printf("\n================= TAMBAH BUKU =================\n");
    printf(COLOR_RESET);
    printf("Berapa buku yang ingin ditambahkan?: ");
    scanf("%d", &jumlahInput);
    getchar();

    FILE *file = fopen("Perpustakaan.txt", "a");
    if (!file){
        printf("Gagal membuka file\n");
        getchar();
        return;
    }

    for (int i = 0; i < jumlahInput; i++){
        system("cls");
        printf(COLOR_CYAN);
        printf("================= Buku ke-%d =================\n\n", i + 1);
        printf(COLOR_RESET);

        printf("Judul Buku      : ");
        fgets(daftar[jumlahBuku].judul, 100, stdin);
        daftar[jumlahBuku].judul[strcspn(daftar[jumlahBuku].judul, "\n")] = 0;

        printf("Nama Penulis    : ");
        fgets(daftar[jumlahBuku].penulis, 100, stdin);
        daftar[jumlahBuku].penulis[strcspn(daftar[jumlahBuku].penulis, "\n")] = 0;

        printf("Tahun Terbit    : ");
        scanf("%d", &daftar[jumlahBuku].tahun);

        printf("Stok            : ");
        scanf("%d", &daftar[jumlahBuku].stok);
        getchar();

        fprintf(file, "Judul Buku      : %s\n", daftar[jumlahBuku].judul);
        fprintf(file, "Nama Penulis    : %s\n", daftar[jumlahBuku].penulis);
        fprintf(file, "Tahun Terbit    : %d\n", daftar[jumlahBuku].tahun);
        fprintf(file, "Stok            : %d\n\n", daftar[jumlahBuku].stok);

        jumlahBuku++;
    }

    fclose(file);

    printf("\n");
    printf(COLOR_GREEN);
    printf("==============================================");
    printf("\n|            BUKU BERHASIL DITAMBAH          |");
    printf("\n==============================================\n");
    printf(COLOR_RESET);

    printf(COLOR_CYAN);
    printf("\nTekan ENTER untuk kembali");
    getchar();
    printf(COLOR_RESET);
}

#endif