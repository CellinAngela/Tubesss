#include <stdio.h>
#include <string.h>
#include "buku.h"

void tambahBuku() {
    char temp[100];
    int jumlahKata = 0;

    getchar();
    printf("\n=== TAMBAH BUKU ===\n");
    printf("Masukkan Judul Buku: ");
    fgets(daftar[jumlahBuku].judul, 50, stdin);
    daftar[jumlahBuku].judul[strcspn(daftar[jumlahBuku].judul, "\n")] = 0;

    do {
        jumlahKata = 0;
        printf("Masukkan Nama Penulis (minimal 2 kata): ");
        fgets(temp, 100, stdin);
        temp[strcspn(temp, "\n")] = 0;

        for(int i = 0; temp[i] != '\0'; i++) {
            if(temp[i] == ' ') jumlahKata++;
        }

        if(jumlahKata < 1)
            printf("⚠ Penulis minimal 2 kata!\n");
        else
            strcpy(daftar[jumlahBuku].penulis, temp);

    } while (jumlahKata < 1);

    printf("Masukkan Tahun Terbit: ");
    scanf("%d", &daftar[jumlahBuku].tahun);

    jumlahBuku++;
    printf("✔ Buku berhasil ditambahkan!\n");
}
