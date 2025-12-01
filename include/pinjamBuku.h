// fitur/pinjamBuku.h
#ifndef PINJAMBUKU_H
#define PINJAMBUKU_H

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "buku.h"

void pinjamBuku() {
    system("cls");
    char judul[100];
    char penulis[100];

    printf("\n================= PEMINJAMAN BUKU =================\n\n");
    printf("Masukkan Judul Buku : ");
    fgets(judul, sizeof(judul), stdin);
    judul[strcspn(judul, "\n")] = 0;

    printf("Masukkan Nama Penulis : ");
    fgets(penulis, sizeof(penulis), stdin);
    penulis[strcspn(penulis, "\n")] = 0;

    FILE *file = fopen("Perpustakaan.txt", "r");
    if (!file) {
        printf("\nData buku masih kosong. Silakan tambah buku dulu.\n");
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
            // check next lines for penulis
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

    // check if already dipinjam between this entry and next blank line
    int j = foundIndex;
    int isBorrowed = 0;
    while (j < n && strlen(lines[j]) > 1) {
        if (strstr(lines[j], "Status: Sedang dipinjam") != NULL) {
            isBorrowed = 1;
            break;
        }
        j++;
    }

    if (isBorrowed) {
        printf("\nMaaf, buku ini saat ini UNAVAILABLE (sedang dipinjam).\n");
        printf("Tekan ENTER untuk kembali");
        getchar();
        return;
    }

    int lama;
    printf("\nBerapa lama peminjaman (hari)?: ");
    scanf("%d", &lama);
    getchar();

    // compute dates
    time_t t = time(NULL);
    struct tm tm_now = *localtime(&t);
    char tanggalPinjam[20];
    char tanggalKembali[20];
    strftime(tanggalPinjam, sizeof(tanggalPinjam), "%d-%m-%Y", &tm_now);

    tm_now.tm_mday += lama;
    mktime(&tm_now);
    strftime(tanggalKembali, sizeof(tanggalKembali), "%d-%m-%Y", &tm_now);

    // prepare to write new file with insertion
    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Gagal membuat file sementara.\n");
        printf("Tekan ENTER untuk kembali");
        getchar();
        return;
    }

    for (int i = 0; i < n; i++) {
        fputs(lines[i], temp);
        if (i == foundIndex) {
            // copy the next lines (Nama Penulis, Tahun Terbit) until blank line
            int k = i + 1;
            int end = k;
            while (end < n && strlen(lines[end]) > 1) end++;

            // write lines between foundIndex and blank line (skip they were already written in first fputs of loop)
            for (int j = i + 1; j < end; j++) {
                fputs(lines[j], temp);
            }

            // after writing those lines, insert status block
            fprintf(temp, "Status: Sedang dipinjam\n");
            fprintf(temp, "Tanggal Pinjam : %s\n", tanggalPinjam);
            fprintf(temp, "Lama Peminjaman : %d hari\n", lama);
            fprintf(temp, "Tanggal Kembali : %s\n", tanggalKembali);
            if (end < n) fprintf(temp, "\n");

            // skip the lines we just wrote in main loop
            i = end - 1;
        }
    }

    fclose(temp);

    // replace original file
    remove("Perpustakaan.txt");
    rename("temp.txt", "Perpustakaan.txt");

    printf("\nBerhasil meminjam buku.\n");
    printf("Tanggal Pinjam : %s\n", tanggalPinjam);
    printf("Lama Peminjaman : %d hari\n", lama);
    printf("Tanggal Kembali : %s\n", tanggalKembali);
    printf("\nTekan ENTER untuk kembali");
    getchar();
}

#endif
