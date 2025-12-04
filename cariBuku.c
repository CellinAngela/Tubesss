#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>
#include "include/buku.h"
#include "include/ansi.h"

extern struct Buku daftar[100];
extern int jumlahBuku;

static void toLower(char *str)
{
    for (int i = 0; str[i]; i++)
    {
        str[i] = tolower((unsigned char)str[i]);
    }
}

int cariBukuByJudulDanPenulis(char *judulCari, char *penulisC)
{
    char judulLower[100];
    char penulisLower[100];
    strncpy(judulLower, judulCari, sizeof(judulLower) - 1);
    judulLower[sizeof(judulLower) - 1] = '\0';
    strncpy(penulisLower, penulisC, sizeof(penulisLower) - 1);
    penulisLower[sizeof(penulisLower) - 1] = '\0';
    toLower(judulLower);
    toLower(penulisLower);

    for (int i = 0; i < jumlahBuku; i++)
    {
        char judulTmp[100];
        char penulisTemp[100];
        strncpy(judulTmp, daftar[i].judul, sizeof(judulTmp) - 1);
        judulTmp[sizeof(judulTmp) - 1] = '\0';
        strncpy(penulisTemp, daftar[i].penulis, sizeof(penulisTemp) - 1);
        penulisTemp[sizeof(penulisTemp) - 1] = '\0';
        toLower(judulTmp);
        toLower(penulisTemp);

        if (strstr(judulTmp, judulLower) != NULL && strstr(penulisTemp, penulisLower) != NULL)
        {
            return i;
        }
    }
    return -1;
}

int cariBukuByJudul(char *judulCari)
{
    char judulLower[100];
    strncpy(judulLower, judulCari, sizeof(judulLower) - 1);
    judulLower[sizeof(judulLower) - 1] = '\0';
    toLower(judulLower);

    for (int i = 0; i < jumlahBuku; i++)
    {
        char judulTmp[100];
        strncpy(judulTmp, daftar[i].judul, sizeof(judulTmp) - 1);
        judulTmp[sizeof(judulTmp) - 1] = '\0';
        toLower(judulTmp);

        if (strstr(judulTmp, judulLower) != NULL)
        {
            return i;
        }
    }
    return -1;
}

void tampilkanBukuDetail(int indeks)
{
    printf("Judul  : %s\n", daftar[indeks].judul);
    printf("Penulis: %s\n", daftar[indeks].penulis);
    printf("Tahun  : %d\n", daftar[indeks].tahun);
    printf("Stok   : %d\n", daftar[indeks].stok);
    printf("Dipinjam: %d\n", daftar[indeks].dipinjam);

    int tersedia = daftar[indeks].stok - daftar[indeks].dipinjam;
    if (tersedia > 0)
    {
        printf("Status : Tersedia (\"%d\" tersedia untuk dipinjam)\n", tersedia);
    }
    else if (daftar[indeks].dipinjam > 0)
    {
        printf("Status : Tidak Tersedia\n");
        if (daftar[indeks].tanggal_kembali[0] != '\0')
        {
            printf("Tanggal Tersedia Kembali : %s\n", daftar[indeks].tanggal_kembali);
        }
    }
    else
    {
        printf("Status : Tidak tersedia\n");
    }
}

void cariBuku()
{
    system("cls");
    printf(COLOR_BLUE);
    printf("======================================\n");
    printf("|         CARI DATA BUKU (MENU)      |\n");
    printf("======================================\n");
    printf(COLOR_RESET);

    if (jumlahBuku == 0)
    {
        printf("Tidak ada buku dalam daftar.\n");
        printf(COLOR_CYAN);
        printf("\nTekan ENTER untuk kembali...");
        getchar();
        printf(COLOR_RESET);
        return;
    }

    printf("\nPilih metode pencarian:\n");
    printf("1. Cari berdasarkan Judul dan Penulis\n");
    printf("2. Cari berdasarkan Judul\n");
    printf("0. Kembali\n");
    printf("Pilihan: ");

    int pilihan;
    scanf("%d", &pilihan);
    getchar();

    if (pilihan == 0)
        return;

    if (pilihan == 1)
    {
        char judulCari[100];
        char penulisC[100];
        printf("\nMasukkan Judul buku yang ingin dicari: ");
        fgets(judulCari, sizeof(judulCari), stdin);
        judulCari[strcspn(judulCari, "\n")] = 0;

        printf("Masukkan Nama Penulis: ");
        fgets(penulisC, sizeof(penulisC), stdin);
        penulisC[strcspn(penulisC, "\n")] = 0;

        int indeks = cariBukuByJudulDanPenulis(judulCari, penulisC);
        if (indeks != -1)
        {
            printf("\n======================================\n");
            printf("|              BUKU DITEMUKAN        |\n");
            printf("======================================\n");
            tampilkanBukuDetail(indeks);
            printf("======================================\n");
        }
        else
        {
            printf("\nBuku dengan judul '%s' dan penulis '%s' tidak ditemukan.\n", judulCari, penulisC);
        }
    }
    else if (pilihan == 2)
    {
        char judulCari[100];
        printf("\nMasukkan Judul buku yang ingin dicari: ");
        fgets(judulCari, sizeof(judulCari), stdin);
        judulCari[strcspn(judulCari, "\n")] = 0;

        char judulLower[100];
        strncpy(judulLower, judulCari, sizeof(judulLower) - 1);
        judulLower[sizeof(judulLower) - 1] = '\0';
        toLower(judulLower);

        int found = 0;
        printf("\n======================================\n");
        printf("|         HASIL PENCARIAN JUDUL       |\n");
        printf("======================================\n");

        for (int i = 0; i < jumlahBuku; i++)
        {
            char judulTmp[100];
            strncpy(judulTmp, daftar[i].judul, sizeof(judulTmp) - 1);
            judulTmp[sizeof(judulTmp) - 1] = '\0';
            toLower(judulTmp);

            if (strstr(judulTmp, judulLower) != NULL)
            {
                found++;
                printf("\n--- Buku %d ---\n", found);
                tampilkanBukuDetail(i);
            }
        }

        if (found == 0)
        {
            printf("Tidak ada buku dengan judul '%s'.\n", judulCari);
        }
        printf("======================================\n");
    }
    else
    {
        printf("\nPilihan tidak valid.\n");
    }

    printf(COLOR_CYAN);
    printf("\nTekan ENTER untuk kembali");
    getchar();
    printf(COLOR_RESET);
}