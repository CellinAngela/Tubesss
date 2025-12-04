#include "include/hitungBuku.h"
#include "include/ansi.h"
#include <stdio.h>
#include <windows.h>
#include <string.h>

int hitungJudulBukuDariFile() {
    FILE *file = fopen("Perpustakaan.txt", "r");
    if (!file) return 0;

    int count = 0;
    char line[256];

    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;

        if (strncmp(line, "Judul Buku", 10) == 0) {
            count++;
        }
    }

    fclose(file);
    return count;
}

void hitungBuku() {
    system("cls");

    printf(COLOR_BLUE);
    printf("\n==============================================\n");
    printf("|             HITUNG JUMLAH BUKU             |\n");
    printf("==============================================\n");
    printf(COLOR_RESET);

    int total = hitungJudulBukuDariFile();

    printf("\nTotal Buku di Rak              : %d\n", total);

    printf("\n==============================================\n");
    printf(COLOR_CYAN);
    printf("\nTekan ENTER untuk kembali");
    fflush(stdin);
    getchar();
    printf(COLOR_RESET);
}