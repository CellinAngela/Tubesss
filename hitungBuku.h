typedef struct {
    char title[100];
    int qty;
    int price;
} Book;

void menuFitur5(Book data[], int n);
int hitungTotalBuku(Book data[], int n);
int hitungTotalNilai(Book data[], int n);
