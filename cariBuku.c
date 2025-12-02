#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "include/buku.h"

extern struct Buku daftar[100];
extern int jumlahBuku;

// Convert string to lowercase
static void toLower(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower((unsigned char)str[i]);
    }
}

int cariBukuByISBN(char *isbnCari) {
    for (int i = 0; i < jumlahBuku; i++) {
        if (strcmp(daftar[i].isbn, isbnCari) == 0) {
            return i; 
        }
    }
    return -1; 
}

int cariBukuByJudul(char *judulCari) {
    char judulLower[100];
    strncpy(judulLower, judulCari, sizeof(judulLower)-1);
    judulLower[sizeof(judulLower)-1] = '\0';
    toLower(judulLower);
    
    for (int i = 0; i < jumlahBuku; i++) {
        char judulTmp[100];
        strncpy(judulTmp, daftar[i].judul, sizeof(judulTmp)-1);
        judulTmp[sizeof(judulTmp)-1] = '\0';
        toLower(judulTmp);
        
        if (strstr(judulTmp, judulLower) != NULL) {
            return i; 
        }
    }
    return -1; 
}

void tampilkanBukuDetail(int indeks) {
    printf("ISBN   : %s\n", daftar[indeks].isbn);
    printf("Judul  : %s\n", daftar[indeks].judul);
    printf("Penulis: %s\n", daftar[indeks].penulis);
    printf("Tahun  : %d\n", daftar[indeks].tahun);
    printf("Stok   : %d\n", daftar[indeks].stok);
    printf("Dipinjam: %d\n", daftar[indeks].dipinjam);

    int tersedia = daftar[indeks].stok - daftar[indeks].dipinjam;
    if (tersedia > 0) {
        printf("Status : Tersedia (\"%d\" tersedia untuk dipinjam)\n", tersedia);
    } else if (daftar[indeks].dipinjam > 0) {
        printf("Status : Tidak Tersedia\n");
        if (daftar[indeks].tanggal_kembali[0] != '\0') {
            printf("Tanggal Tersedia Kembali : %s\n", daftar[indeks].tanggal_kembali);
        }
    } else {
        printf("Status : Tidak tersedia\n");
    }
}

void cariBuku() {
    system("cls");
    printf("======================================\n");
    printf("|         CARI DATA BUKU (MENU)      |\n");
    printf("======================================\n");

    if (jumlahBuku == 0) {
        printf("Tidak ada buku dalam daftar.\n");
        printf("\nTekan ENTER untuk kembali...");
        getchar();
        return;
    }

    printf("\nPilih metode pencarian:\n");
    printf("1. Cari berdasarkan ISBN\n");
    printf("2. Cari berdasarkan Judul\n");
    printf("3. Cari berdasarkan keduanya (ISBN dan Judul)\n");
    printf("0. Kembali\n");
    printf("Pilihan: ");
    
    int pilihan;
    scanf("%d", &pilihan);
    getchar();

    if (pilihan == 0) return;

    if (pilihan == 1) {
        char isbnCari[20];
        printf("\nMasukkan ISBN buku yang ingin dicari: ");
        scanf("%19s", isbnCari);
        getchar();
        
        int indeks = cariBukuByISBN(isbnCari);
        if (indeks != -1) {
            printf("\n======================================\n");
            printf("|              BUKU DITEMUKAN        |\n");
            printf("======================================\n");
            tampilkanBukuDetail(indeks);
            printf("======================================\n");
        } else {
            printf("\nBuku dengan ISBN %s tidak ditemukan.\n", isbnCari);
        }

    } else if (pilihan == 2) {
        char judulCari[100];
        printf("\nMasukkan Judul buku yang ingin dicari: ");
        fgets(judulCari, sizeof(judulCari), stdin);
        judulCari[strcspn(judulCari, "\n")] = 0;
        
        char judulLower[100];
        strncpy(judulLower, judulCari, sizeof(judulLower)-1);
        judulLower[sizeof(judulLower)-1] = '\0';
        toLower(judulLower);
        
        int found = 0;
        printf("\n======================================\n");
        printf("|         HASIL PENCARIAN JUDUL       |\n");
        printf("======================================\n");
        
        for (int i = 0; i < jumlahBuku; i++) {
            char judulTmp[100];
            strncpy(judulTmp, daftar[i].judul, sizeof(judulTmp)-1);
            judulTmp[sizeof(judulTmp)-1] = '\0';
            toLower(judulTmp);
            
            if (strstr(judulTmp, judulLower) != NULL) {
                found++;
                printf("\n--- Buku %d ---\n", found);
                tampilkanBukuDetail(i);
            }
        }
        
        if (found == 0) {
            printf("Tidak ada buku dengan judul '%s'.\n", judulCari);
        }
        printf("======================================\n");

    } else if (pilihan == 3) {
        char isbnCari[20], judulCari[100];
        printf("\nMasukkan ISBN buku yang ingin dicari (atau tekan ENTER untuk skip): ");
        fgets(isbnCari, sizeof(isbnCari), stdin);
        isbnCari[strcspn(isbnCari, "\n")] = 0;
        
        printf("Masukkan Judul buku yang ingin dicari (atau tekan ENTER untuk skip): ");
        fgets(judulCari, sizeof(judulCari), stdin);
        judulCari[strcspn(judulCari, "\n")] = 0;
        
        char judulLower[100];
        if (judulCari[0] != '\0') {
            strncpy(judulLower, judulCari, sizeof(judulLower)-1);
            judulLower[sizeof(judulLower)-1] = '\0';
            toLower(judulLower);
        }
        
        int found = 0;
        printf("\n======================================\n");
        printf("|      HASIL PENCARIAN (ISBN & JUDUL) |\n");
        printf("======================================\n");
        
        for (int i = 0; i < jumlahBuku; i++) {
            int matchISBN = (isbnCari[0] == '\0') || (strcmp(daftar[i].isbn, isbnCari) == 0);
            
            int matchJudul = 0;
            if (judulCari[0] == '\0') {
                matchJudul = 1;
            } else {
                char judulTmp[100];
                strncpy(judulTmp, daftar[i].judul, sizeof(judulTmp)-1);
                judulTmp[sizeof(judulTmp)-1] = '\0';
                toLower(judulTmp);
                matchJudul = (strstr(judulTmp, judulLower) != NULL);
            }
            
            if (matchISBN && matchJudul) {
                found++;
                printf("\n--- Buku %d ---\n", found);
                tampilkanBukuDetail(i);
            }
        }
        
        if (found == 0) {
            printf("Tidak ada buku yang sesuai dengan kriteria pencarian.\n");
        }
        printf("======================================\n");
    } else {
        printf("\nPilihan tidak valid.\n");
    }

    printf("\nTekan ENTER untuk kembali");
    getchar();
}