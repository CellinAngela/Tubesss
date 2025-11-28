#ifndef BUKU_H
#define BUKU_H

struct Buku {
    char judul[100];
    char penulis[100];
    int tahun;
};

extern struct Buku daftar[100];
extern int jumlahBuku;

#endif