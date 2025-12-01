// fitur/tampilkanBuku.h
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
        printf("\nTekan ENTER untuk kembali");
        getchar();
        return;
    }

    printf("\n==============================================\n");
    printf("|           DAFTAR BUKU PERPUSTAKAAN         |\n");
    printf("==============================================\n");

    char line[256];
    while (fgets(line, sizeof(line), file) != NULL){
        printf("%s", line);
    }

    fclose(file);
    printf("\n==============================================\n");
    printf("\nTekan ENTER untuk kembali");
    getchar();
}

#endif