#ifndef TAMPILKANBUKU_H
#define TAMPILKANBUKU_H

#include <stdio.h>
#include <windows.h>
#include "buku.h"

void tampilkanBuku(){
    system("cls");

    FILE *file = fopen("Perpustakaan.txt", "r");
    if (file == NULL){
        printf("\n==============================================");
        printf("\n            Data Buku Masih Kosong\n");
        printf("             Silakan tambah buku dulu   \n");
        printf("================================================\n");
        printf(COLOR_CYAN);
        printf("\nTekan ENTER untuk kembali");
        getchar();
        printf(COLOR_RESET);
        return;
    }

    printf(COLOR_BLUE);
    printf("\n==============================================\n");
    printf("|           DAFTAR BUKU PERPUSTAKAAN         |\n");
    printf("==============================================\n");
    printf(COLOR_RESET);

    char line[256];
    while (fgets(line, sizeof(line), file) != NULL){
        printf("%s", line);
    }

    fclose(file);
    printf("\n==============================================\n");
    printf(COLOR_CYAN);
    printf("\nTekan ENTER untuk kembali");
    getchar();
    printf(COLOR_RESET);
}

#endif