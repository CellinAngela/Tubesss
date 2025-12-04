#ifndef BUKU_H
#define BUKU_H

struct Buku{
    char judul[100];
    char penulis[100];
    int tahun;
    int stok;
    int dipinjam;
    char tanggal_kembali[20];
};

extern struct Buku daftar[100];
extern int jumlahBuku;

#endif