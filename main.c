#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "buku.h"
#include "tambahBuku.h"
#include "tampilkanBuku.h"
#include "hitungBuku.h"
#include "keluar.h"

struct Buku daftar[100];
int jumlahBuku = 0;

void tampilanPerpus()
{
   printf("======================================");
   printf("\n|   SELAMAT DATANG DI PERPUSTAKAAN   |\n");
   printf("======================================\n");
   printf("| 1.Tambah Buku                      |\n");
   printf("| 2.Tampilkan Buku                   |\n");
   printf("| 0.Keluar                           |\n");
   printf("======================================\n");
}

int main()
{
   int fiturPerpus, loopFitur;
   system("cls");
      tampilanPerpus();
      printf("Pilih fitur yang kamu mau");
   
   do{
      loopFitur = 0;
      printf("\n[1-2-0]: ");
      if (scanf("%d", &fiturPerpus) != 1){
         printf("Fitur yang dipilih tidak valid\n");
         fflush(stdin);
      }

      switch (fiturPerpus){
      case 1:
         tambahBuku();
         break;

      case 2:
         tampilkanBuku();
         break;

      case 0:
         keluar();
         break;

      default:
         printf("Fitur yang kamu pilih tidak valid\n");
         loopFitur = 1;
      }
   } while (loopFitur == 1);
   return 0;
}