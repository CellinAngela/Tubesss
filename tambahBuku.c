#include <stdio.h>
#include <string.h>
#include "buku.h"

void tambahBuku() {
    char temp[100];
    int jumlahKata = 0;
    
    printf("\n=== TAMBAH BUKU ===\n");

    getchar();  // membersihkan buffer

    // Input Judul Buku
    printf("Masukkan Judul Buku: ");
    fgets(daftar[jumlahBuku].judul, 50, stdin);
    daftar[jumlahBuku].judul[strcspn(daftar[jumlahBuku].judul, "\n")] = 0;

    // Input Penulis (TANPA VALIDASI)
    printf("Masukkan Nama Penulis: ");
    fgets(daftar[jumlahBuku].penulis, 50, stdin);
    daftar[jumlahBuku].penulis[strcspn(daftar[jumlahBuku].penulis, "\n")] = 0;

    // Input Tahun Terbit
    printf("Masukkan Tahun Terbit: ");
    scanf("%d", &daftar[jumlahBuku].tahun);

    jumlahBuku++;   // Tambah jumlah buku
    printf("✔ Buku berhasil ditambahkan!\n");
}
