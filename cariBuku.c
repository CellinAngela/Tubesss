#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "include/buku.h"


extern struct Buku daftar[100];
extern int jumlahBuku;

int cariBukuByISBN(char *isbnCari) {
    for (int i = 0; i < jumlahBuku; i++) {
        
        if (strcmp(daftar[i].isbn, isbnCari) == 0) {
            return i; 
        }
    }
    return -1; 
}


void cariBuku() {
    system("cls");
    printf("======================================\n");
    printf("|            CARI DATA BUKU          |\n");
    printf("======================================\n");

    if (jumlahBuku == 0) {
        printf("Tidak ada buku dalam daftar.\n");
        printf("\nTekan ENTER untuk kembali...");
        getchar();
        return;
    }

    char isbnCari[20];
    printf("Masukkan ISBN buku yang ingin dicari: ");
    scanf("%19s", isbnCari);
    getchar(); 

    int indeks = cariBukuByISBN(isbnCari);

    if (indeks != -1) {
        printf("\n======================================\n");
        printf("|              BUKU DITEMUKAN        |\n");
        printf("======================================\n");
        printf("ISBN   : %s\n", daftar[indeks].isbn);
        printf("Judul  : %s\n", daftar[indeks].judul);
        printf("Penulis: %s\n", daftar[indeks].penulis);
        printf("Stok   : %d\n", daftar[indeks].stok);
        printf("Dipinjam: %d\n", daftar[indeks].dipinjam);
        printf("======================================\n");
    } else {
        printf("\nBuku dengan ISBN %s tidak ditemukan.\n", isbnCari);
    }

    printf("\nTekan ENTER untuk kembali");
    getchar();
}