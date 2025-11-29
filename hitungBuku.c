#include "hitungBuku.h"
#include <stdio.h>

int hitungTotalBuku(Book data[], int n) {
int total = 0;
for (int i = 0; i < n; i++) {
total += data[i].qty;
}
return total;
}

int hitungTotalNilai(Book data[], int n) {
int total = 0;
for (int i = 0; i < n; i++) {
total += data[i].qty * data[i].price;
}
return total;
}

void menuFitur5(Book data[], int n) {
int pilih;
do {
printf("\nMenu\n");
printf("1. Tampilkan total jumlah buku\n");
printf("2. Tampilkan total nilai buku\n");
printf("0. Kembali\n");
printf("Pilih: ");
scanf("%d", &pilih);

    switch (pilih) {
        case 1: {
            int t = hitungTotalBuku(data, n);
            printf("Total jumlah buku: %d\n", t);
            break;
        }
        case 2: {
            int v = hitungTotalNilai(data, n);
            printf("Total nilai buku: %d\n", v);
            break;
        }
        case 0:
            break;
        default:
            printf("Menu tidak ada\n");
    }
} while (pilih != 0);


}

