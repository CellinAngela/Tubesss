#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "include/buku.h"
#include "include/ansi.h"

struct Buku daftar[100];
int jumlahBuku;

// Cari buku berdasarkan judul dan penulis, mengembalikan indeks atau -1 jika tidak ditemukan
// strstr untuk mencari substring di dalam string yang lebih besar.
int cariBukuByJudulDanPenulis(char *judulCari, char *penulisC){
    for (int i = 0; i < jumlahBuku; i++){
        if (strstr(daftar[i].judul, judulCari) != NULL && strstr(daftar[i].penulis, penulisC) != NULL){
            return i;
        }
    }
    return -1;
}

int cariBukuByJudul(char *judulCari){
    for (int i = 0; i < jumlahBuku; i++){
        if (strstr(daftar[i].judul, judulCari) != NULL){
            return i;
        }
    }
    return -1;
}

int cariBukuByPenulis(char *penulisC){
    for (int i = 0; i < jumlahBuku; i++){
        if (strstr(daftar[i].penulis, penulisC) != NULL){
            return i;
        }
    }
    return -1;
}

void tampilkanBukuDetail(int indeks){
    printf("Judul    : %s\n", daftar[indeks].judul);
    printf("Penulis  : %s\n", daftar[indeks].penulis);
    printf("Tahun    : %d\n", daftar[indeks].tahun);
    printf("Stok     : %d\n", daftar[indeks].stok);
    printf("Dipinjam : %d\n", daftar[indeks].dipinjam);

    int tersedia = daftar[indeks].stok - daftar[indeks].dipinjam;
    if (tersedia > 0){
        printf("Status  : Tersedia (\"%d\" tersedia untuk dipinjam)\n", tersedia);
    }
    else if (daftar[indeks].dipinjam > 0){
        printf("Status  : Tidak Tersedia\n");
        if (daftar[indeks].tanggal_kembali[0] != '\0'){
            printf("Tanggal Tersedia Kembali : %s\n", daftar[indeks].tanggal_kembali);
        }
    }
    else{
        printf("Status  : Tidak tersedia\n");
    }
}

void cariBuku(){
    system("cls");
    printf(COLOR_BLUE);
    printf("======================================\n");
    printf("|         CARI DATA BUKU (MENU)      |\n");
    printf("======================================\n");
    printf(COLOR_RESET);

    printf(COLOR_RED);
    printf("Format Penulisan:\n");
    printf(" - Judul dan Penulis harus ditulis PERSIS sama\n");
    printf("   Judul Buku: The Metamorphosis ------- benar\n");
    printf("   Judul Buku: the metamorphosis ------- salah\n\n");
    printf(COLOR_RESET);
    
    if (jumlahBuku == 0){
        printf("Tidak ada buku dalam daftar\n");
        printf(COLOR_CYAN);
        printf("\nTekan ENTER untuk kembali...");
        getchar();
        printf(COLOR_RESET);
        return;
    }

    printf("\nPilih metode pencarian:\n");
    printf("1. Cari berdasarkan Judul\n");
    printf("2. Cari berdasarkan Penulis\n");
    printf("0. Kembali\n");
    printf("Pilihan: ");

    int pilihan;
    scanf("%d", &pilihan);
    getchar();

    if (pilihan == 0)
        return;

    if (pilihan == 1){
        char judulCari[100];
        printf("\nMasukkan Judul buku yang ingin dicari: ");
        fgets(judulCari, sizeof(judulCari), stdin);
        judulCari[strcspn(judulCari, "\n")] = 0;

        int indeks = cariBukuByJudul(judulCari);
        if (indeks != -1){
            printf("\n======================================\n");
            printf("|            BUKU DITEMUKAN          |\n");
            printf("======================================\n");
            tampilkanBukuDetail(indeks);
            printf("======================================\n");
        }
        else{
            printf("\nBuku dengan judul '%s' tidak ditemukan\n", judulCari);
        }
    }
    else if (pilihan == 2){
        char penulisC[100];
        printf("\nMasukkan Nama Penulis buku yang ingin dicari: ");
        fgets(penulisC, sizeof(penulisC), stdin);
        penulisC[strcspn(penulisC, "\n")] = 0;

        int indeks = cariBukuByPenulis(penulisC);
        if (indeks != -1){
            printf("\n======================================\n");
            printf("|            BUKU DITEMUKAN          |\n");
            printf("======================================\n");
            tampilkanBukuDetail(indeks);
            printf("======================================\n");
        }
        else{
            printf("\nBuku dengan penulis '%s' tidak ditemukan\n", penulisC);
        }
    }
    else{
        printf("\nPilihan tidak valid.\n");
    }

    printf(COLOR_CYAN);
    printf("\nTekan ENTER untuk kembali");
    getchar();
    printf(COLOR_RESET);
}