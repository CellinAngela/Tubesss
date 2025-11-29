// main.c
#include <stdio.h>
#include <windows.h>
#include "buku.h"
#include "tambahBuku.h"
#include "tampilkanBuku.h"
#include "hitungBuku.h"

struct Buku daftar[100];      
int jumlahBuku = 0;

void tampilanFitur(){
   system("cls");
   printf("======================================");
   printf("\n|   SELAMAT DATANG DI PERPUSTAKAAN   |\n");
   printf("======================================\n");
   printf("| 1.Tambah Buku                      |\n");
   printf("| 2.Tampilkan Buku                   |\n");
   printf("| 0.Keluar                           |\n");
   printf("======================================\n");
}

int main(){
   int pilihan;

   while (1){
      tampilanFitur();
      printf("Pilih fitur: ");
      scanf("%d", &pilihan);
      getchar();

      switch (pilihan){
      case 1:
         tambahBuku();
         break;
      case 2:
         tampilkanBuku();
         break;
      case 0:
         system("cls");
         printf("==============================================\n");
         printf("|  Terimakasih Telah Datang ke Perpustakaan  |\n");
         printf("|              Datang Lagi Yaaa              |\n");
         printf("==============================================\n");
         return 0;
      default:
         printf("Fitur yang kamu pilih tidak valid\n");
         getchar();
      }
   }
}