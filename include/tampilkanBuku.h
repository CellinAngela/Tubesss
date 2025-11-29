// fitur/tampilkanBuku.h
#ifndef TAMPILKANBUKU_H
#define TAMPILKANBUKU_H

#include <stdio.h>
#include <windows.h>
#include "buku.h"

void tampilkanBuku(){
    system("cls");

    if (jumlahBuku == 0){
        printf("\n==============================================");
        printf("\n            Data Buku Masih Kosong\n");
        printf("             Silakan tambah buku dulu   \n");
        printf("================================================\n");
        printf("\nTekan ENTER untuk kembali");
        getchar();
        return;
    }

    printf("\nData buku dapat dilihat di 'Perpustakaan.txt'");
    printf("\nTekan ENTER untuk kembali");
    getchar();
}

#endif