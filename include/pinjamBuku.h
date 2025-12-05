#ifndef PINJAMBUKU_H
#define PINJAMBUKU_H

#include <stdio.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include "buku.h"
#include "ansi.h"

void pinjamBuku(){
    system("cls");
    char judul[100];
    char penulis[100];

    printf(COLOR_BLUE);
    printf("\n================= PEMINJAMAN BUKU =================\n\n");
    printf(COLOR_RESET);

    printf(COLOR_RED);
    printf("Format Penulisan:\n");
    printf(" - Judul dan Penulis harus ditulis PERSIS sama\n");
    printf("   Judul Buku: The Metamorphosis ------- benar\n");
    printf("   Judul Buku: the metamorphosis ------- salah\n\n");
    printf(COLOR_RESET);

    printf("Masukkan Judul Buku   : ");
    fgets(judul, sizeof(judul), stdin);
    judul[strcspn(judul, "\n")] = 0;

    printf("Masukkan Nama Penulis : ");
    fgets(penulis, sizeof(penulis), stdin);
    penulis[strcspn(penulis, "\n")] = 0;

    FILE *file = fopen("Perpustakaan.txt", "r");
    if (!file){
        printf("\nData buku masih kosong. Silakan tambah buku dulu.\n");
        printf(COLOR_CYAN);
        printf("Tekan ENTER untuk kembali");
        getchar();
        printf(COLOR_RESET);
        return;
    }

    char lines[2000][256];
    int n = 0;
    while (fgets(lines[n], sizeof(lines[n]), file) != NULL && n < 1999){
        n++;
    }
    fclose(file);

    int foundIndex = -1;
    for (int i = 0; i < n; i++){
        if (strstr(lines[i], "Judul Buku") != NULL && strstr(lines[i], judul) != NULL){
            if (i + 1 < n && strstr(lines[i + 1], "Nama Penulis") != NULL && strstr(lines[i + 1], penulis) != NULL){
                foundIndex = i;
                break;
            }
        }
    }

    if (foundIndex == -1){
        printf("\nJudul atau penulis tidak ditemukan\n");
        printf(COLOR_CYAN);
        printf("Tekan ENTER untuk kembali");
        getchar();
        printf(COLOR_RESET);
        return;
    }

    int isBorrowed = 0;
    for (int j = foundIndex; j < n && strlen(lines[j]) > 1; j++){
        if (strstr(lines[j], "Status") != NULL && strstr(lines[j], "dipinjam") != NULL){
            isBorrowed = 1;
            break;
        }
    }

    if (isBorrowed){
        printf("\nMaaf, buku ini sedang dipinjam\n");
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
    if (!temp){
        printf("Gagal membuat file sementara.\n");
        printf(COLOR_CYAN);
        printf("Tekan ENTER untuk kembali");
        getchar();
        printf(COLOR_RESET);
        return;
    }

    int endIndex = foundIndex + 1;
    while (endIndex < n && strlen(lines[endIndex]) > 1){
        endIndex++;
    }

    for (int i = 0; i < n; i++){
        if (i >= foundIndex && i < endIndex){
            fputs(lines[i], temp);
        }else if (i == endIndex - 1){
            fprintf(temp, "Status: dipinjam\n");
            fprintf(temp, "Tanggal Pinjam: %s\n", tanggalPinjam);
            fprintf(temp, "Tanggal Kembali: %s\n", tanggalKembali);
            if (endIndex < n){
                fprintf(temp, "\n");
            }
        }else{
            fputs(lines[i], temp);
        }
    }

    fclose(temp);
    remove("Perpustakaan.txt");
    rename("temp.txt", "Perpustakaan.txt");

    printf("\nBerhasil meminjam buku\n");
    printf("Tanggal Kembali: %s\n", tanggalKembali);
    printf(COLOR_CYAN);
    printf("Tekan ENTER untuk kembali");
    getchar();
    printf(COLOR_RESET);
}

#endif