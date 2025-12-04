#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "include/buku.h"
#include "include/cariBuku.h"
#include "include/ansi.h"

extern struct Buku daftar[100];
extern int jumlahBuku;
extern void savePerpustakaan();

void editBuku(){
    system("cls"); // clear screen
    printf(COLOR_BLUE);
    printf("======================================\n");
    printf("|           EDIT DATA BUKU           |\n");
    printf("======================================\n");
    printf(COLOR_RESET);
    printf("Format Penulisan:\n");
    printf(" - Judul dan Penulis harus ditulis PERSIS sama\n");
    printf("   Judul Buku: The Metamorphosis ------- benar\n");
    printf("   Judul Buku: the metamorphosis ------- salah\n\n");

    if (jumlahBuku == 0){
        printf("Tidak ada buku yang bisa diedit.\n");
        printf(COLOR_CYAN);
        printf("\nTekan ENTER untuk kembali");
        getchar();
        printf(COLOR_RESET);
        return;
    }

    printf("\nPilih metode pencarian buku yang ingin diedit:\n");
    printf("1. Cari berdasarkan Judul\n");
    printf("2. Cari berdasarkan Penulis\n");
    printf("0. Kembali\n");
    printf("Pilihan: ");

    int pilihanCari;
    if (scanf("%d", &pilihanCari) != 1){
        int c; // variabel sementara
        while ((c = getchar()) != '\n' && c != EOF) // membuang input yang tidak valid
        {
        }
        return;
    }
    getchar();

    if (pilihanCari == 0)
        return;

    int indeks = -1;
    char judulCari[100] = {0};
    char penulisC[100] = {0};

    if (pilihanCari == 1){
        printf("\nMasukkan Judul buku yang ingin diedit: ");
        fgets(judulCari, sizeof(judulCari), stdin); // stdin untuk membaca inputan dan disimpan ke judulCari
        judulCari[strcspn(judulCari, "\n")] = 0; // strcspn untuk menghapus baris baru char

        for (int i = 0; i < jumlahBuku; i++){
            if (strstr(daftar[i].judul, judulCari) != NULL){ // strstr untuk mencari apakah judul buku ada di daftar
                indeks = i;
                break;
            }
        }
    }
    else if (pilihanCari == 2){
        printf("\nMasukkan Nama Penulis buku yang ingin diedit: ");
        fgets(penulisC, sizeof(penulisC), stdin);
        penulisC[strcspn(penulisC, "\n")] = 0;

        for (int i = 0; i < jumlahBuku; i++){
            if (strstr(daftar[i].penulis, penulisC) != NULL){
                indeks = i;
                break;
            }
        }
    }
    else{
        printf("\nPilihan tidak valid.\n");
        printf(COLOR_CYAN);
        printf("\nTekan ENTER untuk kembali");
        getchar();
        printf(COLOR_RESET);
        return;
    }

    if (indeks == -1){ // untuk mengecek apakah data buku tidak ditemukan
        printf("\nBuku tidak ditemukan. Gagal Edit\n");
        printf(COLOR_CYAN);
        printf("\nTekan ENTER untuk kembali");
        getchar();
        printf(COLOR_RESET);
        return;
    }

    int pilihanEdit;

    printf("\nBuku Ditemukan :\n");
    printf("Judul saat ini   : %s\n", daftar[indeks].judul);
    printf("Penulis saat ini : %s\n", daftar[indeks].penulis);
    printf("Tahun            : %d\n", daftar[indeks].tahun);
    printf("Stok saat ini    : %d\n", daftar[indeks].stok);
    printf("Dipinjam         : %d\n", daftar[indeks].dipinjam);

    printf("\n--- Pilih Data yang akan Diedit ---\n");
    printf("1. Edit Judul\n");
    printf("2. Edit Penulis\n");
    printf("3. Edit Tahun\n");
    printf("4. Edit Stok (Jumlah Buku)\n");
    printf("5. Edit Dipinjam\n");
    printf("6. Hapus Buku\n");
    printf("0. Batal Edit\n");
    printf("Pilihan: ");
    if (scanf("%d", &pilihanEdit) != 1){ //mengecek input berupa angka atau tidak
        int c;
        while ((c = getchar()) != '\n' && c != EOF)
        {
        }
        return;
    }
    getchar();

    int changed = 0;

    switch (pilihanEdit){
    case 1:
        printf("Masukkan Judul Baru (max 100 karakter): ");
        fgets(daftar[indeks].judul, 100, stdin);
        daftar[indeks].judul[strcspn(daftar[indeks].judul, "\n")] = 0;
        printf("\nJudul buku berhasil diubah.\n");
        changed = 1;
        break;
    case 2:
        printf("Masukkan Penulis Baru (max 100 karakter): ");
        fgets(daftar[indeks].penulis, 100, stdin);
        daftar[indeks].penulis[strcspn(daftar[indeks].penulis, "\n")] = 0;
        printf("\nNama Penulis berhasil diubah.\n");
        changed = 1;
        break;
    case 3:
        printf("Masukkan Tahun Baru: ");
        if (scanf("%d", &daftar[indeks].tahun) == 1){
            getchar();
        }
        printf("\nTahun buku berhasil diubah.\n");
        changed = 1;
        break;
    case 4:
        printf("Masukkan Stok Buku Baru: ");
        if (scanf("%d", &daftar[indeks].stok) == 1){
            getchar();
        }
        printf("\nStok buku berhasil diubah.\n");
        changed = 1;
        break;
    case 5:
        printf("Masukkan Jumlah Dipinjam: ");
        if (scanf("%d", &daftar[indeks].dipinjam) == 1){
            getchar();
        }
        printf("\nJumlah dipinjam berhasil diubah.\n");
        changed = 1;
        break;
    case 6:{
        char confirm;
        printf("\n" COLOR_RED);
        printf("======== PERHATIAN: HAPUS BUKU ========\n");
        printf(COLOR_RESET);
        printf("Anda yakin ingin menghapus buku ini?\n");
        printf("Judul   : %s\n", daftar[indeks].judul);
        printf("Penulis : %s\n", daftar[indeks].penulis);
        printf("Ketik 'y' untuk hapus, atau apapun untuk batal: ");
        if (scanf(" %c", &confirm) == 1){
            getchar();
        }

        if (confirm == 'y' || confirm == 'Y'){
            for (int j = indeks; j < jumlahBuku - 1; j++){
                daftar[j] = daftar[j + 1];
            }
            jumlahBuku--; // mengurangi total 1 buku setiap kali dihapus
            printf(COLOR_GREEN);
            printf("==============================================\n");
            printf("|            BUKU BERHASIL DIHAPUS           |\n");
            printf("==============================================\n");
            printf(COLOR_RESET);
            changed = 1;
        }
        else{
            printf("Penghapusan dibatalkan.\n");
        }
        break;
    }
    case 0:
        printf("\nProses edit dibatalkan.\n");
        break;
    default:
        printf("\nPilihan tidak valid. Proses edit dibatalkan.\n");
        break;
    }

    if (changed){
        savePerpustakaan();
        printf(COLOR_GREEN);
        printf("==============================================\n");
        printf("|            BUKU BERHASIL DIPERBAHARUI      |\n");
        printf("==============================================\n");
        printf(COLOR_RESET);
    }

    printf(COLOR_CYAN);
    printf("\nTekan ENTER untuk kembali");
    getchar();
    printf(COLOR_RESET);
}