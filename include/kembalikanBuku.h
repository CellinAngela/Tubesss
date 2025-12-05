
#ifndef KEMBALIKANBUKU_H
#define KEMBALIKANBUKU_H

#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "buku.h"
#include "ansi.h"

void kembalikanBuku(){
    system("cls");
    char judul[100];
    char penulis[100];

    printf(COLOR_BLUE);
    printf("\n================= PENGEMBALIAN BUKU =================\n\n");
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
        printf("\nData buku masih kosong.\n");
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
        printf("\nJudul atau penulis tidak ditemukan.\n");
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

    int statusFound = 0;
    for (int j = foundIndex; j < endIndex; j++){
        if (strstr(lines[j], "Status") != NULL && strstr(lines[j], "dipinjam") != NULL){
            statusFound = 1;
            break;
        }
    }

    if (!statusFound){
        printf("\nBuku ini tidak sedang dipinjam.\n");
        printf(COLOR_CYAN);
        printf("Tekan ENTER untuk kembali");
        getchar();
        printf(COLOR_RESET);
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (!temp){
        printf("Gagal membuat file sementara.\n");
        printf(COLOR_CYAN);
        printf("Tekan ENTER untuk kembali");
        getchar();
        printf(COLOR_RESET);
        return;
    }

    for (int i = 0; i < n; i++){
        if (i >= foundIndex && i < endIndex){
            if (strstr(lines[i], "Status") == NULL){
                fputs(lines[i], temp);
            }
        }else{
            fputs(lines[i], temp);
        }
    }

    fclose(temp);

    remove("Perpustakaan.txt");
    rename("temp.txt", "Perpustakaan.txt");

    printf("\nBuku berhasil dikembalikan dan status dipulihkan.\n");
    printf(COLOR_CYAN);
    printf("Tekan ENTER untuk kembali");
    getchar();
    printf(COLOR_RESET);
}

#endif