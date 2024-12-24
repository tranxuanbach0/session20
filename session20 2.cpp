#include <stdio.h>
#include <string.h>

#define MAX_PRODUCTS 100

typedef struct {
    char id[20];
    char name[100];
    double importPrice;
    double sellPrice;
    int quantity;
} Product;

int productCount = 0;
double revenue = 0;

void inputProducts(Product products[]) {
    printf("Nhap so luong san pham: ");
    scanf("%d", &productCount);
    getchar();
    for (int i = 0; i < productCount; i++) {
        printf("Nhap thong tin san pham thu %d:\n", i + 1);
        printf("Ma san pham: ");
        fgets(products[i].id, sizeof(products[i].id), stdin);
        products[i].id[strcspn(products[i].id, "\n")] = 0;
        printf("Ten san pham: ");
        fgets(products[i].name, sizeof(products[i].name), stdin);
        products[i].name[strcspn(products[i].name, "\n")] = 0;
        printf("Gia nhap: ");
        scanf("%lf", &products[i].importPrice);
        printf("Gia ban: ");
        scanf("%lf", &products[i].sellPrice);
        printf("So luong: ");
        scanf("%d", &products[i].quantity);
        getchar();
        revenue -= products[i].quantity * products[i].importPrice;
    }
}

void displayProducts(const Product products[]) {
    for (int i = 0; i < productCount; i++) {
        printf("Ma san pham: %s, Ten san pham: %s, Gia nhap: %.2f, Gia ban: %.2f, So luong: %d\n",
               products[i].id, products[i].name, products[i].importPrice, products[i].sellPrice, products[i].quantity);
    }
}

void addProduct(Product products[]) {
    char id[20];
    printf("Nhap ma san pham muon nhap: ");
    getchar();
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;
    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].id, id) == 0) {
            int addQuantity;
            printf("San pham da ton tai. Nhap so luong muon them: ");
            scanf("%d", &addQuantity);
            products[i].quantity += addQuantity;
            revenue -= addQuantity * products[i].importPrice;
            return;
        }
    }
    if (productCount >= MAX_PRODUCTS) {
        printf("Khong the them san pham moi.\n");
        return;
    }
    Product newProduct;
    strcpy(newProduct.id, id);
    printf("Nhap ten san pham: ");
    getchar();
    fgets(newProduct.name, sizeof(newProduct.name), stdin);
    newProduct.name[strcspn(newProduct.name, "\n")] = 0;
    printf("Gia nhap: ");
    scanf("%lf", &newProduct.importPrice);
    printf("Gia ban: ");
    scanf("%lf", &newProduct.sellPrice);
    printf("So luong: ");
    scanf("%d", &newProduct.quantity);
    getchar();
    products[productCount++] = newProduct;
    revenue -= newProduct.quantity * newProduct.importPrice;
}

void updateProduct(Product products[]) {
    char id[20];
    printf("Nhap ma san pham muon cap nhat: ");
    getchar();
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;
    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].id, id) == 0) {
            printf("Nhap ten san pham: ");
            fgets(products[i].name, sizeof(products[i].name), stdin);
            products[i].name[strcspn(products[i].name, "\n")] = 0;
            printf("Gia nhap: ");
            scanf("%lf", &products[i].importPrice);
            printf("Gia ban: ");
            scanf("%lf", &products[i].sellPrice);
            printf("So luong: ");
            scanf("%d", &products[i].quantity);
            getchar();
            printf("Cap nhat thanh cong.\n");
            return;
        }
    }
    printf("Khong tim thay san pham voi ma: %s\n", id);
}

void sortProductsByPrice(Product products[], int ascending) {
    for (int i = 0; i < productCount - 1; i++) {
        for (int j = i + 1; j < productCount; j++) {
            if ((ascending && products[i].sellPrice > products[j].sellPrice) ||
                (!ascending && products[i].sellPrice < products[j].sellPrice)) {
                Product temp = products[i];
                products[i] = products[j];
                products[j] = temp;
            }
        }
    }
}

void searchProduct(const Product products[]) {
    char name[100];
    printf("Nhap ten san pham muon tim: ");
    getchar();
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
    for (int i = 0; i < productCount; i++) {
        if (strstr(products[i].name, name) != NULL) {
            printf("Ma san pham: %s, Ten san pham: %s, Gia nhap: %.2f, Gia ban: %.2f, So luong: %d\n",
                   products[i].id, products[i].name, products[i].importPrice, products[i].sellPrice, products[i].quantity);
        }
    }
}

void sellProduct(Product products[]) {
    char id[20];
    int sellQuantity;
    printf("Nhap ma san pham muon ban: ");
    getchar();
    fgets(id, sizeof(id), stdin);
    id[strcspn(id, "\n")] = 0;
    for (int i = 0; i < productCount; i++) {
        if (strcmp(products[i].id, id) == 0) {
            printf("Nhap so luong muon ban: ");
            scanf("%d", &sellQuantity);
            if (products[i].quantity == 0) {
                printf("San pham da het hang.\n");
                return;
            } else if (sellQuantity > products[i].quantity) {
                printf("Khong du hang de ban.\n");
                return;
            }
            products[i].quantity -= sellQuantity;
            revenue += sellQuantity * products[i].sellPrice;
            printf("Ban thanh cong.\n");
            return;
        }
    }
    printf("Khong tim thay san pham voi ma: %s\n", id);
}

int main() {
    Product products[MAX_PRODUCTS];
    int choice;
    do {
        printf("\nMENU\n");
        printf("1. Nhap so luong va thong tin san pham\n");
        printf("2. Hien thi danh sach san pham\n");
        printf("3. Nhap san pham\n");
        printf("4. Cap nhat thong tin san pham\n");
        printf("5. Sap xep san pham theo gia\n");
        printf("6. Tim kiem san pham\n");
        printf("7. Ban san pham\n");
        printf("8. Doanh thu hien tai\n");
        printf("9. Thoat\n");
        printf("Lua chon cua ban: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                inputProducts(products);
                break;
            case 2:
                displayProducts(products);
                break;
            case 3:
                addProduct(products);
                break;
            case 4:
                updateProduct(products);
                break;
            case 5: {
                int ascending;
                printf("Nhap 1 de sap xep tang, 0 de sap xep giam: ");
                scanf("%d", &ascending);
                sortProductsByPrice(products, ascending);
                break;
            }
            case 6:
                searchProduct(products);
                break;
            case 7:
                sellProduct(products);
                break;
            case 8:
                printf("Doanh thu hien tai: %.2f\n", revenue);
                break;
            case 9:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le.\n");
        }
    } while (choice != 9);
    return 0;
}

