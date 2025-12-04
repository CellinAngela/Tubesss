#include <stdio.h>
#include <string.h>
#include <windows.h>
#include "include/buku.h"
#include "include/cariBuku.h"
#include "include/ansi.h"

extern struct Buku daftar[100];
extern int jumlahBuku;
extern void savePerpustakaan();

void editBuku()
{
    system("cls");
    printf(COLOR_BLUE);
    printf("======================================\n");
    printf("|           EDIT DATA BUKU           |\n");
    printf("======================================\n");
    printf(COLOR_RESET);

    if (jumlahBuku == 0)
    {
        printf("Tidak ada buku yang bisa diedit.\n");
        printf(COLOR_CYAN);
        printf("\nTekan ENTER untuk kembali...");
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
    scanf("%d", &pilihanCari);
    getchar();

    if (pilihanCari == 0)
        return;

    int indeks = -1;
    char judulCari[100];
    char penulisC[100];

    if (pilihanCari == 1)
    {
        printf("\nMasukkan Judul buku yang ingin diedit: ");
        fgets(judulCari, sizeof(judulCari), stdin);
        judulCari[strcspn(judulCari, "\n")] = 0;

        for (int i = 0; i < jumlahBuku; i++)
        {
            if (strstr(daftar[i].judul, judulCari) != NULL)
            {
                indeks = i;
                break;
            }
        }
    }
    else if (pilihanCari == 2)
    {
        printf("\nMasukkan Nama Penulis buku yang ingin diedit: ");
        fgets(penulisC, sizeof(penulisC), stdin);
        penulisC[strcspn(penulisC, "\n")] = 0;

        for (int i = 0; i < jumlahBuku; i++)
        {
            if (strstr(daftar[i].penulis, penulisC) != NULL)
            {
                indeks = i;
                break;
            }
        }
    }
    else
    {
        printf("\nPilihan tidak valid.\n");
        printf(COLOR_CYAN);
        printf("\nTekan ENTER untuk kembali");
        getchar();
        printf(COLOR_RESET);
        return;
    }

    if (indeks != -1)
    {
        int pilihanEdit;

        printf("\nBuku Ditemukan:\n");
        printf("Judul saat ini: %s\n", daftar[indeks].judul);
        printf("Penulis saat ini: %s\n", daftar[indeks].penulis);
        printf("Tahun: %d\n", daftar[indeks].tahun);
        printf("Stok saat ini: %d\n", daftar[indeks].stok);
        printf("Dipinjam: %d\n", daftar[indeks].dipinjam);

        printf("\n--- Pilih Data yang akan Diedit ---\n");
        printf("1. Edit Judul\n");
        printf("2. Edit Penulis\n");
        printf("3. Edit Tahun\n");
        printf("4. Edit Stok (Jumlah Buku)\n");
        printf("5. Edit Dipinjam\n");
        printf("6. Hapus Buku\n");
        printf("0. Batal Edit\n");
        printf("Pilihan: ");
        scanf("%d", &pilihanEdit);
        getchar();

        int changed = 0;

        switch (pilihanEdit)
        {
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
            scanf("%d", &daftar[indeks].tahun);
            getchar();
            printf(COLOR_GREEN);
            printf("\nTahun buku berhasil diubah.\n");
            printf(COLOR_RESET);
            changed = 1;
            break;
        case 4:
            printf("Masukkan Stok Buku Baru: ");
            scanf("%d", &daftar[indeks].stok);
            getchar();
            printf("\nStok buku berhasil diubah.\n");
            changed = 1;
            break;
        case 5:
            printf("Masukkan Jumlah Dipinjam: ");
            scanf("%d", &daftar[indeks].dipinjam);
            getchar();
            printf("\nJumlah dipinjam berhasil diubah.\n");
            changed = 1;
            break;
        case 6:
        {
            char confirm;
            printf("\n" COLOR_RED);
            printf("======== PERHATIAN: HAPUS BUKU ========\n");
            printf(COLOR_RESET);
            printf("Anda yakin ingin menghapus buku ini?\n");
            printf("Judul: %s\n", daftar[indeks].judul);
            printf("Penulis: %s\n", daftar[indeks].penulis);
            printf("Ketik 'y' untuk hapus, atau apapun untuk batal: ");
            scanf("%c", &confirm);
            getchar();

            if (confirm == 'y' || confirm == 'Y')
            {
                // Hapus dari array dengan shift
                for (int i = indeks; i < jumlahBuku - 1; i++)
                {
                    daftar[i] = daftar[i + 1];
                }
                jumlahBuku--;
                printf(COLOR_GREEN);
                printf("==============================================\n");
                printf("|            BUKU BERHASIL DIHAPUS           |\n");
                printf("==============================================\n");
                printf(COLOR_RESET);
                changed = 1;
            }
            else
            {
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

        if (changed)
        {
            savePerpustakaan();
            printf(COLOR_GREEN);
            printf("==============================================");
            printf("\n|            BUKU BERHASIL DIPERBAHARUI       |");
            printf("\n==============================================\n");
            printf(COLOR_RESET);
        }
    }
    else
    {
        printf("\nBuku tidak ditemukan. Gagal Edit.\n");
    }
    printf(COLOR_CYAN);
    printf("\nTekan ENTER untuk kembali");
    getchar();
    printf(COLOR_RESET);
}