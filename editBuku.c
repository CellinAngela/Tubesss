#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "include/buku.h"
#include "include/cariBuku.h"

extern struct Buku daftar[100];
extern int jumlahBuku;

void editBuku() {
    system("cls");
    printf("======================================\n");
    printf("|           EDIT DATA BUKU           |\n");
    printf("======================================\n");

    if (jumlahBuku == 0) {
        printf("Tidak ada buku yang bisa diedit.\n");
        printf("\nTekan ENTER untuk kembali...");
        getchar();
        return;
    }

    char isbnCari[20];
    printf("Masukkan ISBN buku yang ingin diedit: ");
    scanf("%19s", isbnCari);
    getchar(); 

    int indeks = cariBukuByISBN(isbnCari);

    if (indeks != -1) {
        int pilihanEdit;

        printf("\nBuku Ditemukan:\n");
        printf("Judul saat ini: %s\n", daftar[indeks].judul);
        printf("Penulis saat ini: %s\n", daftar[indeks].penulis);
        printf("Stok saat ini: %d\n", daftar[indeks].stok);
        
        printf("\n--- Pilih Data yang akan Diedit ---\n");
        printf("1. Edit Judul\n");
        printf("2. Edit Penulis\n");
        printf("3. Edit Stok (Jumlah Buku)\n");
        printf("0. Batal Edit\n");
        printf("Pilihan: ");
        scanf("%d", &pilihanEdit);
        getchar(); 
        switch (pilihanEdit) {
            case 1:
                printf("Masukkan Judul Baru (max 100 karakter): ");
                
                fgets(daftar[indeks].judul, 100, stdin);
               
                daftar[indeks].judul[strcspn(daftar[indeks].judul, "\n")] = 0;
                printf("\nJudul buku berhasil diubah.\n");
                break;
            case 2:
                printf("Masukkan Penulis Baru (max 50 karakter): ");
                fgets(daftar[indeks].penulis, 50, stdin);
                daftar[indeks].penulis[strcspn(daftar[indeks].penulis, "\n")] = 0;
                printf("\nNama Penulis berhasil diubah.\n");
                break;
            case 3:
                printf("Masukkan Stok Buku Baru: ");
                scanf("%d", &daftar[indeks].stok);
                getchar();
                printf("\nStok buku berhasil diubah.\n");
                break;
            case 0:
                printf("\nProses edit dibatalkan.\n");
                break;
            default:
                printf("\nPilihan tidak valid. Proses edit dibatalkan.\n");
                break;
        }

    } else {
        printf("\nBuku dengan ISBN %s tidak ditemukan. Gagal Edit.\n", isbnCari);
    }

    printf("\nTekan ENTER untuk kembali");
    getchar();
}
