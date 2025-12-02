// main.c
#include <stdio.h>
#include <windows.h>
#include "include/buku.h"
#include "include/tambahBuku.h"
#include "include/tampilkanBuku.h"
#include "include/hitungBuku.h"
#include "include/cariBuku.h"
#include "include/editBuku.h"
#include "include/hapusBuku.h"
#include "include/pinjamBuku.h"
#include "include/kembalikanBuku.h"


struct Buku daftar[100];      
int jumlahBuku = 0;

// Load data from Perpustakaan.txt into daftar[] at startup
static void trim(char *s) {
   // remove trailing newline and carriage return
   size_t len = strlen(s);
   while (len > 0 && (s[len-1] == '\n' || s[len-1] == '\r')) { s[--len] = '\0'; }
   // remove leading spaces
   char *start = s;
   while (*start == ' ' || *start == '\t') start++;
   if (start != s) memmove(s, start, strlen(start) + 1);
}

void loadPerpustakaan(){
   FILE *f = fopen("Perpustakaan.txt", "r");
   if (!f) return;

   char line[256];
   struct Buku temp;
   // initialize temp
   temp.isbn[0] = '\0'; temp.judul[0] = '\0'; temp.penulis[0] = '\0'; temp.tahun = 0; temp.stok = 1; temp.dipinjam = 0; temp.tanggal_kembali[0] = '\0';
   int hasAny = 0;

   while (fgets(line, sizeof(line), f)){
      trim(line);
      if (line[0] == '\0'){
         // blank line -> end of entry
         if (hasAny && jumlahBuku < 100){
            daftar[jumlahBuku++] = temp;
         }
         // reset temp
         temp.isbn[0] = '\0'; temp.judul[0] = '\0'; temp.penulis[0] = '\0'; temp.tahun = 0; temp.stok = 1; temp.dipinjam = 0; temp.tanggal_kembali[0] = '\0';
         hasAny = 0;
         continue;
      }

      char *colon = strchr(line, ':');
      if (!colon) continue;
      // split key and value
      *colon = '\0';
      char *key = line;
      char *value = colon + 1;
      trim(key); trim(value);

      if (strstr(key, "ISBN") != NULL){
         strncpy(temp.isbn, value, sizeof(temp.isbn)-1);
         temp.isbn[sizeof(temp.isbn)-1] = '\0';
         hasAny = 1;
      } else if (strstr(key, "Judul") != NULL){
         strncpy(temp.judul, value, sizeof(temp.judul)-1);
         temp.judul[sizeof(temp.judul)-1] = '\0';
         hasAny = 1;
      } else if (strstr(key, "Penulis") != NULL || strstr(key, "Nama Penulis") != NULL){
         strncpy(temp.penulis, value, sizeof(temp.penulis)-1);
         temp.penulis[sizeof(temp.penulis)-1] = '\0';
         hasAny = 1;
      } else if (strstr(key, "Tahun") != NULL){
         temp.tahun = atoi(value);
         hasAny = 1;
      } else if (strstr(key, "Stok") != NULL){
         temp.stok = atoi(value);
         hasAny = 1;
      } else if (strstr(key, "Dipinjam") != NULL){
         temp.dipinjam = atoi(value);
         hasAny = 1;
      } else if (strstr(key, "Tanggal Kembali") != NULL || strstr(key, "tanggal_kembali") != NULL){
         strncpy(temp.tanggal_kembali, value, sizeof(temp.tanggal_kembali)-1);
         temp.tanggal_kembali[sizeof(temp.tanggal_kembali)-1] = '\0';
         hasAny = 1;
      }
   }
   // last entry (no trailing blank line)
   if (hasAny && jumlahBuku < 100){
      daftar[jumlahBuku++] = temp;
   }

   fclose(f);
}

// Save daftar[] back to Perpustakaan.txt
void savePerpustakaan(){
   FILE *f = fopen("Perpustakaan.txt", "w");
   if (!f) {
      printf("Gagal membuka file untuk menyimpan.\n");
      return;
   }

   for (int i = 0; i < jumlahBuku; i++){
      fprintf(f, "ISBN : %s\n", daftar[i].isbn);
      fprintf(f, "Judul Buku     : %s\n", daftar[i].judul);
      fprintf(f, "Nama Penulis   : %s\n", daftar[i].penulis);
      fprintf(f, "Tahun Terbit   : %d\n", daftar[i].tahun);
      fprintf(f, "Stok : %d\n", daftar[i].stok);
      fprintf(f, "Dipinjam : %d\n", daftar[i].dipinjam);
      fprintf(f, "Tanggal Kembali : %s\n", daftar[i].tanggal_kembali);
      fprintf(f, "\n");
   }

   fclose(f);
}

void tampilanFitur(){
   system("cls");
   printf("======================================");
   printf("\n|   SELAMAT DATANG DI PERPUSTAKAAN   |\n");
   printf("======================================\n");
   printf("| 1.Tambah Buku                      |\n");
   printf("| 2.Tampilkan Buku                   |\n");
   printf("| 3.Hitung Buku                      |\n");
   printf("| 4.Hapus Buku                       |\n");
   printf("| 5.Peminjaman Buku                  |\n");
   printf("| 6.Pengembalian Buku                |\n");
   printf("| 7.Cari Buku                        |\n");
   printf("| 8.Edit Buku                        |\n");
   printf("| 0.Keluar                           |\n");
   printf("======================================\n");
}

int main(){
   loadPerpustakaan();
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
      case 5:
         pinjamBuku();
         break;
      case 8:
         editBuku();
         break;
      case 7:
         cariBuku();
         break;
      case 6:
         kembalikanBuku();
         break;
      case 2:
         tampilkanBuku();
         break;
      case 3:
         hitungBuku();
         break;
      case 4:
         hapusBuku();
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