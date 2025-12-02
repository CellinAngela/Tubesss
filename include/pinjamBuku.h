#ifndef PINJAMBUKU_H
#define PINJAMBUKU_H

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include "buku.h"
#include "ansi.h"

void pinjamBuku() {
    system("cls");
    char judul[100];
    char penulis[100];

    printf(COLOR_BLUE);
    printf("\n================= PEMINJAMAN BUKU =================\n\n");
    printf(COLOR_RESET);
    printf("Masukkan Judul Buku : ");
    fgets(judul, sizeof(judul), stdin);
    judul[strcspn(judul, "\n")] = 0;

    printf("Masukkan Nama Penulis : ");
    fgets(penulis, sizeof(penulis), stdin);
    penulis[strcspn(penulis, "\n")] = 0;

    FILE *file = fopen("Perpustakaan.txt", "r");
    if (!file) {
        printf("\nData buku masih kosong. Silakan tambah buku dulu.\n");
        printf(COLOR_CYAN);
        printf("Tekan ENTER untuk kembali");
        getchar();
        printf(COLOR_RESET);
        return;
    }

    char lines[2000][256];
    int n = 0;
    while (fgets(lines[n], sizeof(lines[n]), file) != NULL && n < 1999) {
        n++;
    }
    fclose(file);

    int foundIndex = -1;
    char judulLower[100];
    char penulisLower[100];
    strncpy(judulLower, judul, sizeof(judulLower)-1); judulLower[sizeof(judulLower)-1] = '\0';
    strncpy(penulisLower, penulis, sizeof(penulisLower)-1); penulisLower[sizeof(penulisLower)-1] = '\0';
    for (int k = 0; judulLower[k]; k++) judulLower[k] = tolower((unsigned char)judulLower[k]);
    for (int k = 0; penulisLower[k]; k++) penulisLower[k] = tolower((unsigned char)penulisLower[k]);

    for (int i = 0; i < n; i++) {
        if (strncmp(lines[i], "Judul Buku", 10) == 0) {
            char lineLower[256];
            strncpy(lineLower, lines[i], sizeof(lineLower)-1); lineLower[sizeof(lineLower)-1] = '\0';
            for (int k = 0; lineLower[k]; k++) lineLower[k] = tolower((unsigned char)lineLower[k]);

            if (strstr(lineLower, judulLower) != NULL) {
                if (i+1 < n && strncmp(lines[i+1], "Nama Penulis", 12) == 0) {
                    char penulisLineLower[256];
                    strncpy(penulisLineLower, lines[i+1], sizeof(penulisLineLower)-1); penulisLineLower[sizeof(penulisLineLower)-1] = '\0';
                    for (int k = 0; penulisLineLower[k]; k++) penulisLineLower[k] = tolower((unsigned char)penulisLineLower[k]);
                    if (strstr(penulisLineLower, penulisLower) != NULL) {
                        foundIndex = i;
                        break;
                    }
                }
            }
        }
    }

    if (foundIndex == -1) {
        printf("\nJudul atau penulis tidak ditemukan di data buku.\n");
        printf(COLOR_CYAN);
        printf("Tekan ENTER untuk kembali");
        getchar();
        printf(COLOR_RESET);
        return;
    }

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
        printf(COLOR_CYAN); 
        printf("Tekan ENTER untuk kembali");
        getchar();
        printf(COLOR_RESET);
        return;
    }

    int lama;
    printf("\nBerapa lama peminjaman (hari)?: ");
    scanf("%d", &lama);
    getchar();

    time_t t = time(NULL);
    struct tm tm_now = *localtime(&t);
    char tanggalPinjam[20];
    char tanggalKembali[20];
    strftime(tanggalPinjam, sizeof(tanggalPinjam), "%d-%m-%Y", &tm_now);

    tm_now.tm_mday += lama;
    mktime(&tm_now);
    strftime(tanggalKembali, sizeof(tanggalKembali), "%d-%m-%Y", &tm_now);

    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        printf("Gagal membuat file sementara.\n");
        printf(COLOR_CYAN);
        printf("Tekan ENTER untuk kembali");
        getchar();
        printf(COLOR_RESET);
        return;
    }

    for (int i = 0; i < n; i++) {
        fputs(lines[i], temp);
        if (i == foundIndex) {
            int k = i + 1;
            int end = k;
            while (end < n && strlen(lines[end]) > 1) end++;

            for (int j = i + 1; j < end; j++) {
                fputs(lines[j], temp);
            }

            fprintf(temp, "Status: Sedang dipinjam\n");
            fprintf(temp, "Tanggal Pinjam : %s\n", tanggalPinjam);
            fprintf(temp, "Lama Peminjaman : %d hari\n", lama);
            fprintf(temp, "Tanggal Kembali : %s\n", tanggalKembali);
            if (end < n) fprintf(temp, "\n");

            i = end - 1;
        }
    }

    fclose(temp);

    
    remove("Perpustakaan.txt");
    rename("temp.txt", "Perpustakaan.txt");

    printf("\nBerhasil meminjam buku.\n");
    printf("Tanggal Pinjam : %s\n", tanggalPinjam);
    printf("Lama Peminjaman : %d hari\n", lama);
    printf("Tanggal Kembali : %s\n", tanggalKembali);
    printf(COLOR_CYAN);
    printf("\nTekan ENTER untuk kembali");
    getchar();
    printf(COLOR_RESET);
}

#endif
