#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "buku.h"

void tambahBuku(){
    system("cls");
    int jumlahInput;
    getchar();

    printf("\n================ TAMBAH BUKU =================\n");
    printf(" Berapa buku yang ingin ditambahkan?: ");
    scanf("%d", &jumlahInput);
    getchar();

    for (int i = 0; i < jumlahInput; i++){
        system("cls");
        printf("\n================ TAMBAH BUKU =================\n");
        printf("------------------ Buku ke-%d -----------------\n", i + 1);
        printf(" Masukkan Judul Buku    : ");
        fgets(daftar[jumlahBuku].judul, 100, stdin);
        daftar[jumlahBuku].judul[strcspn(daftar[jumlahBuku].judul, "\n")] = 0;

        printf(" Masukkan Nama Penulis  : ");
        fgets(daftar[jumlahBuku].penulis, 100, stdin);
        daftar[jumlahBuku].penulis[strcspn(daftar[jumlahBuku].penulis, "\n")] = 0;

        printf(" Masukkan Tahun Terbit  : ");
        scanf("%d", &daftar[jumlahBuku].tahun);
        getchar();

        jumlahBuku++;

        printf("\n==============================================");
        printf("\n          Buku berhasil ditambahkan\n");
        printf("==============================================");
    }
}