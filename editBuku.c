#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "include/buku.h"
#include "include/cariBuku.h"

extern struct Buku daftar[100];
extern int jumlahBuku;
extern void savePerpustakaan();

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

    printf("\nPilih metode pencarian buku yang ingin diedit:\n");
    printf("1. Cari berdasarkan ISBN\n");
    printf("2. Cari berdasarkan Judul\n");
    printf("0. Kembali\n");
    printf("Pilihan: ");
    
    int pilihanCari;
    scanf("%d", &pilihanCari);
    getchar();
    
    if (pilihanCari == 0) return;
    
    int indeks = -1;
    
    if (pilihanCari == 1) {
        char isbnCari[20];
        printf("\nMasukkan ISBN buku yang ingin diedit: ");
        scanf("%19s", isbnCari);
        getchar();
        indeks = cariBukuByISBN(isbnCari);
    } else if (pilihanCari == 2) {
        char judulCari[100];
        printf("\nMasukkan Judul buku yang ingin diedit: ");
        fgets(judulCari, sizeof(judulCari), stdin);
        judulCari[strcspn(judulCari, "\n")] = 0;
        
        // Cari buku dengan judul yang matching
        for (int i = 0; i < jumlahBuku; i++) {
            if (strstr(daftar[i].judul, judulCari) != NULL) {
                indeks = i;
                break;
            }
        }
    } else {
        printf("Pilihan tidak valid.\n");
        printf("\nTekan ENTER untuk kembali");
        getchar();
        return;
    }

    if (indeks != -1) {
        int pilihanEdit;

        printf("\nBuku Ditemukan:\n");
        printf("ISBN: %s\n", daftar[indeks].isbn);
        printf("Judul saat ini: %s\n", daftar[indeks].judul);
        printf("Penulis saat ini: %s\n", daftar[indeks].penulis);
        printf("Tahun: %d\n", daftar[indeks].tahun);
        printf("Stok saat ini: %d\n", daftar[indeks].stok);
        printf("Dipinjam: %d\n", daftar[indeks].dipinjam);
        
        printf("\n--- Pilih Data yang akan Diedit ---\n");
        printf("1. Edit Judul\n");
        printf("2. Edit Penulis\n");
        printf("3. Edit Tahun\n");
        printf("4. Edit Stok (Jumlah Buku)\n");
        printf("5. Edit Dipinjam\n");
        printf("0. Batal Edit\n");
        printf("Pilihan: ");
        scanf("%d", &pilihanEdit);
        getchar(); 
        
        int changed = 0;
        
        switch (pilihanEdit) {
            case 1:
                printf("Masukkan Judul Baru (max 100 karakter): ");
                fgets(daftar[indeks].judul, 100, stdin);
                daftar[indeks].judul[strcspn(daftar[indeks].judul, "\n")] = 0;
                printf("\nJudul buku berhasil diubah.\n");
                changed = 1;
                break;
            case 2:
                printf("Masukkan Penulis Baru (max 100 karakter): ");
                fgets(daftar[indeks].penulis, 100, stdin);
                daftar[indeks].penulis[strcspn(daftar[indeks].penulis, "\n")] = 0;
                printf("\nNama Penulis berhasil diubah.\n");
                changed = 1;
                break;
            case 3:
                printf("Masukkan Tahun Baru: ");
                scanf("%d", &daftar[indeks].tahun);
                getchar();
                printf("\nTahun buku berhasil diubah.\n");
                changed = 1;
                break;
            case 4:
                printf("Masukkan Stok Buku Baru: ");
                scanf("%d", &daftar[indeks].stok);
                getchar();
                printf("\nStok buku berhasil diubah.\n");
                changed = 1;
                break;
            case 5:
                printf("Masukkan Jumlah Dipinjam: ");
                scanf("%d", &daftar[indeks].dipinjam);
                getchar();
                printf("\nJumlah dipinjam berhasil diubah.\n");
                changed = 1;
                break;
            case 0:
                printf("\nProses edit dibatalkan.\n");
                break;
            default:
                printf("\nPilihan tidak valid. Proses edit dibatalkan.\n");
                break;
        }
        
        if (changed) {
            savePerpustakaan();
            printf("Perubahan telah disimpan ke Perpustakaan.txt.\n");
        }

    } else {
        printf("\nBuku tidak ditemukan. Gagal Edit.\n");
    }

    printf("\nTekan ENTER untuk kembali");
    getchar();
}