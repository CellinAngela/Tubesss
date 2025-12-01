#ifndef TAMBAHBUKU_H
#define TAMBAHBUKU_H

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "buku.h"

void tambahBuku(){
    system("cls");

    int jumlahInput;
    printf("\n================= TAMBAH BUKU =================\n");
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
        printf("================= Buku ke-%d =================\n\n", i + 1);

        printf("Judul Buku     : ");
        fgets(daftar[jumlahBuku].judul, 100, stdin);
        daftar[jumlahBuku].judul[strcspn(daftar[jumlahBuku].judul, "\n")] = 0;

        printf("Nama Penulis   : ");
        fgets(daftar[jumlahBuku].penulis, 100, stdin);
        daftar[jumlahBuku].penulis[strcspn(daftar[jumlahBuku].penulis, "\n")] = 0;

        printf("Tahun Terbit   : ");
        scanf("%d", &daftar[jumlahBuku].tahun);
        getchar();

        fprintf(file, "Judul Buku     : %s\n", daftar[jumlahBuku].judul);
        fprintf(file, "Nama Penulis   : %s\n", daftar[jumlahBuku].penulis);
        fprintf(file, "Tahun Terbit   : %d\n\n", daftar[jumlahBuku].tahun);

        jumlahBuku++;
    }

    fclose(file);

    printf("\n==============================================");
    printf("\n|            BUKU BERHASIL DITAMBAH          |");
    printf("\n==============================================\n");

    printf("\nTekan ENTER untuk kembali");
    getchar();
}

#endif