// buku.h
#ifndef BUKU_H
#define BUKU_H

struct Buku {
    char judul[50];
    char penulis[50];
    int tahun;
};

extern struct Buku daftar[100]; // variabel global
extern int jumlahBuku;          // variabel global

void tambahBuku();
void tampilkanBuku();

#endif
