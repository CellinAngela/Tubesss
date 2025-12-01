// fitur/kembalikanBuku.h
#ifndef KEMBALIKANBUKU_H
#define KEMBALIKANBUKU_H

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "buku.h"

void kembalikanBuku() {
    system("cls");
    char judul[100];
    char penulis[100];

    printf("\n================= PENGEMBALIAN BUKU =================\n\n");
    printf("Masukkan Judul Buku : ");
    fgets(judul, sizeof(judul), stdin);
    judul[strcspn(judul, "\n")] = 0;

    printf("Masukkan Nama Penulis : ");
    fgets(penulis, sizeof(penulis), stdin);
    penulis[strcspn(penulis, "\n")] = 0;

    FILE *file = fopen("Perpustakaan.txt", "r");
    if (!file) {
        printf("\nData buku masih kosong.\n");
        printf("Tekan ENTER untuk kembali");
        getchar();
        return;
    }

    // Read all lines into memory
    char lines[2000][256];
    int n = 0;
    while (fgets(lines[n], sizeof(lines[n]), file) != NULL && n < 1999) {
        n++;
    }
    fclose(file);

    int foundIndex = -1;
    for (int i = 0; i < n; i++) {
        if (strncmp(lines[i], "Judul Buku", 10) == 0 && strstr(lines[i], judul) != NULL) {
            if (i+1 < n && strncmp(lines[i+1], "Nama Penulis", 12) == 0 && strstr(lines[i+1], penulis) != NULL) {
                foundIndex = i;
                break;
            }
        }
    }

    if (foundIndex == -1) {
        printf("\nJudul atau penulis tidak ditemukan di data buku.\n");
        printf("Tekan ENTER untuk kembali");
        getchar();
        return;
    }

    // Check for status lines after the book block
    int i = foundIndex + 1;
    // find end of book block (blank line or next Judul Buku)
    while (i < n && strlen(lines[i]) > 1 && strncmp(lines[i], "Judul Buku", 10) != 0) i++;

    // Now scan between foundIndex and i for status
    int statusLineIndex = -1;
    for (int j = foundIndex; j < i; j++) {
        if (strstr(lines[j], "Status: Sedang dipinjam") != NULL) {
            statusLineIndex = j;
            break;
        }
    }

    if (statusLineIndex == -1) {
        printf("\nBuku ini tidak sedang dipinjam (tidak ada status peminjaman).\n");
        printf("Tekan ENTER untuk kembali");
        getchar();
        return;
    }

    // Create temp file without the status block (assume 4 lines: Status, Tanggal Pinjam, Lama Peminjaman, Tanggal Kembali)
    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Gagal membuat file sementara.\n");
        printf("Tekan ENTER untuk kembali");
        getchar();
        return;
    }

    for (int k = 0; k < n; k++) {
        if (k == statusLineIndex) {
            // skip up to 4 lines (and possibly an extra blank line)
            int skip = 0;
            int kk = k;
            while (kk < n && skip < 6) {
                // stop skipping when reach blank line indicating block end
                if (strlen(lines[kk]) <= 1) { kk++; break; }
                kk++; skip++;
            }
            k = kk - 1;
            continue;
        }
        fputs(lines[k], temp);
    }

    fclose(temp);

    remove("Perpustakaan.txt");
    rename("temp.txt", "Perpustakaan.txt");

    printf("\nBuku berhasil dikembalikan dan status dipulihkan.\n");
    printf("Tekan ENTER untuk kembali");
    getchar();
}

#endif
