#ifndef HEADER_H
#define HEADER_H

struct Buku {
    char judul[50];
    char penulis[50];
    int tahun;
};

extern struct Buku daftar[100];
extern int jumlahBuku;

void tambahBuku();
void tampilkanBuku();
void keluar();

#endif
