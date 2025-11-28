#include <stdio.h>
#include "buku.h"

struct Buku daftar[100];
int jumlahBuku = 0;

int main() {
    int pilihan;

    while (1) {
        printf("\n=== MENU PERPUSTAKAAN ===\n");
        printf("1. Tambah Buku\n");
        printf("2. Tampilkan Buku\n");
        printf("0. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1: tambahBuku(); break;
            case 2: tampilkanBuku(); break;
            case 0: return 0;
            default: printf("Menu tidak valid\n");
        }
    }
}
// deymmmmmmmmmmmmmmmmmmm