#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 100

typedef struct {
    char id[20];
    char name[100];
    char author[100];
    double price;
    char category[50];
} Book;

int bookCount = 0;

void inputBooks(Book books[]) {
    printf("Nhap so luong sach: ");
    scanf("%d", &bookCount);
    getchar();
    for (int i = 0; i < bookCount; i++) {
        printf("Nhap thong tin sach thu %d:\n", i + 1);
        printf("Ma sach: ");
        fgets(books[i].id, sizeof(books[i].id), stdin);
        books[i].id[strcspn(books[i].id, "\n")] = 0;
        printf("Ten sach: ");
        fgets(books[i].name, sizeof(books[i].name), stdin);
        books[i].name[strcspn(books[i].name, "\n")] = 0;
        printf("Tac gia: ");
        fgets(books[i].author, sizeof(books[i].author), stdin);
        books[i].author[strcspn(books[i].author, "\n")] = 0;
        printf("Gia tien: ");
        scanf("%lf", &books[i].price);
        getchar();
        printf("The loai: ");
        fgets(books[i].category, sizeof(books[i].category), stdin);
        books[i].category[strcspn(books[i].category, "\n")] = 0;
    }
}

void displayBooks(const Book books[]) {
    for (int i = 0; i < bookCount; i++) {
        printf("Ma sach: %s, Ten sach: %s, Tac gia: %s, Gia tien: %.2f, The loai: %s\n",
               books[i].id, books[i].name, books[i].author, books[i].price, books[i].category);
    }
}

void addBook(Book books[]) {
    if (bookCount >= MAX_BOOKS) {
        printf("Khong the them sach moi.\n");
        return;
    }
    int position;
    printf("Nhap vi tri muon them (0 - %d): ", bookCount);
    scanf("%d", &position);
    getchar();
    if (position < 0 || position > bookCount) {
        printf("Vi tri khong hop le.\n");
        return;
    }
    for (int i = bookCount; i > position; i--) {
        books[i] = books[i - 1];
    }
    printf("Nhap thong tin sach moi:\n");
    printf("Ma sach: ");
    fgets(books[position].id, sizeof(books[position].id), stdin);
    books[position].id[strcspn(books[position].id, "\n")] = 0;
    printf("Ten sach: ");
    fgets(books[position].name, sizeof(books[position].name), stdin);
    books[position].name[strcspn(books[position].name, "\n")] = 0;
    printf("Tac gia: ");
    fgets(books[position].author, sizeof(books[position].author), stdin);
    books[position].author[strcspn(books[position].author, "\n")] = 0;
    printf("Gia tien: ");
    scanf("%lf", &books[position].price);
    getchar();
    printf("The loai: ");
    fgets(books[position].category, sizeof(books[position].category), stdin);
    books[position].category[strcspn(books[position].category, "\n")] = 0;
    bookCount++;
}

void deleteBook(Book books[]) {
    char id[20];
    printf("Nhap ma sach muon xoa: ");
    getchar();
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;
    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].id, id) == 0) {
            for (int j = i; j < bookCount - 1; j++) {
                books[j] = books[j + 1];
            }
            bookCount--;
            found = 1;
            printf("Da xoa sach co ma: %s\n", id);
            break;
        }
    }
    if (!found) {
        printf("Khong tim thay sach voi ma: %s\n", id);
    }
}

void updateBook(Book books[]) {
    char id[20];
    printf("Nhap ma sach muon cap nhat: ");
    getchar();
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;
    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strcmp(books[i].id, id) == 0) {
            printf("Nhap thong tin moi:\n");
            printf("Ten sach: ");
            fgets(books[i].name, sizeof(books[i].name), stdin);
            books[i].name[strcspn(books[i].name, "\n")] = 0;
            printf("Tac gia: ");
            fgets(books[i].author, sizeof(books[i].author), stdin);
            books[i].author[strcspn(books[i].author, "\n")] = 0;
            printf("Gia tien: ");
            scanf("%lf", &books[i].price);
            getchar();
            printf("The loai: ");
            fgets(books[i].category, sizeof(books[i].category), stdin);
            books[i].category[strcspn(books[i].category, "\n")] = 0;
            found = 1;
            printf("Da cap nhat thong tin sach.\n");
            break;
        }
    }
    if (!found) {
        printf("Khong tim thay sach voi ma: %s\n", id);
    }
}

void sortBooksByPrice(Book books[], int ascending) {
    for (int i = 0; i < bookCount - 1; i++) {
        for (int j = i + 1; j < bookCount; j++) {
            if ((ascending && books[i].price > books[j].price) ||
                (!ascending && books[i].price < books[j].price)) {
                Book temp = books[i];
                books[i] = books[j];
                books[j] = temp;
            }
        }
    }
}

void searchBookByName(Book books[]) {
    char name[100];
    printf("Nhap ten sach muon tim: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strstr(books[i].name, name) != NULL) {
            printf("Ma sach: %s, Ten sach: %s, Tac gia: %s, Gia tien: %.2f, The loai: %s\n",
                   books[i].id, books[i].name, books[i].author, books[i].price, books[i].category);
            found = 1;
        }
    }
    if (!found) {
        printf("Khong tim thay sach voi ten: %s\n", name);
    }
}

int main() {
    Book books[MAX_BOOKS];
    int choice;
    do {
        printf("\nMENU\n");
        printf("1. Nhap so luong va thong tin sach\n");
        printf("2. Hien thi thong tin sach\n");
        printf("3. Them sach vao vi tri\n");
        printf("4. Xoa sach theo ma sach\n");
        printf("5. Cap nhat thong tin sach theo ma sach\n");
        printf("6. Sap xep sach theo gia\n");
        printf("7. Tim kiem sach theo ten sach\n");
        printf("8. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                inputBooks(books);
                break;
            case 2:
                displayBooks(books);
                break;
            case 3:
                addBook(books);
                break;
            case 4:
                deleteBook(books);
                break;
            case 5:
                updateBook(books);
                break;
            case 6: {
                int ascending;
                printf("Nhap 1 de sap xep tang, 0 de sap xep giam: ");
                scanf("%d", &ascending);
                sortBooksByPrice(books, ascending);
                break;
            }
            case 7:
                searchBookByName(books);
                break;
            case 8:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
        }
    } while (choice != 8);
    return 0;
}
