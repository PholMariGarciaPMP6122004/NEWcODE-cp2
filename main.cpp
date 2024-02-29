#include <iostream>
#include <string>

using namespace std;


struct Product {
    string name;
    double productCost;
    int productQuantity;
};

struct Store {
    Product* products;
    int productCount;

    Store() : products(nullptr), productCount(0) {}

    void CleanUp() {
        delete[] products;
    }

    void DisplayMenu() const {
        cout << "1. Add Product\n";
        cout << "2. Delete Product\n";
        cout << "3. Update Product\n";
        cout << "4. Display Products\n";
        cout << "5. Compute Total Cost\n";
        cout << "6. Exit\n";
    }

    void AddProduct() {
        Product newProduct;
        cout << "Enter Product Name: ";
        cin >> newProduct.name;
        cout << "\n";
        cout << "Enter Product Cost: ";
        cin >> newProduct.productCost;
        cout << "\n";
        cout << "Enter Product Quantity: ";
        cin >> newProduct.productQuantity;
        cout << "\n";

        Product* newProducts = new Product[productCount + 1];
        for (int i = 0; i < productCount; ++i) {
            newProducts[i] = products[i];
        }
        newProducts[productCount++] = newProduct;

        delete[] products;
        products = newProducts;

        cout << "Product added successfully!\n";
        system("PAUSE");
        system("CLS");
    }

    void DeleteProduct() {
        string productName;
        cout << "Enter Product Name to delete: ";
        cin >> productName;
        cout << "\n";

        for (int i = 0; i < productCount; ++i) {
            if (products[i].name == productName) {
                for (int j = i; j < productCount - 1; ++j) {
                    products[j] = products[j + 1];
                }
                --productCount;

                cout << "Product deleted successfully!\n";
                system("PAUSE");
                system("CLS");
                return;
            }
        }

        cout << "Product not found.\n";
    }

    void UpdateProduct() {
        string productName;
        cout << "Enter Product Name to update: ";
        cin >> productName;
        cout << "\n";

        for (int i = 0; i < productCount; ++i) {
            if (products[i].name == productName) {
                cout << "Enter new Product Name: ";
                cin >> products[i].name;
                cout << "Enter new Product Cost: ";
                cin >> products[i].productCost;
                cout << "Enter new Product Quantity: ";
                cin >> products[i].productQuantity;

                cout << "Product updated successfully!\n";
                system("PAUSE");
                system("CLS");
                return;
            }
        }

        cout << "Product not found.\n";
    }

    void DisplayProducts() const {
        const int PRODUCTS_PER_PAGE = 5;  // Adjust this value as needed
        int totalPages = (productCount + PRODUCTS_PER_PAGE - 1) / PRODUCTS_PER_PAGE;
        int currentPage = 0;

        while (true) {
            cout << "Page " << currentPage + 1 << "/" << totalPages << "\n";

            int startIdx = currentPage * PRODUCTS_PER_PAGE;
            int endIdx = min((currentPage + 1) * PRODUCTS_PER_PAGE, productCount);

            for (int i = startIdx; i < endIdx; ++i) {
                cout << "Name: " << products[i].name << ", Cost: " << products[i].productCost
                    << ", Quantity: " << products[i].productQuantity << endl;
            }

            cout << "\nOptions: (P)revious, (N)ext, (Q)uit pagination\n";
            char option;
            cin >> option;

            switch (option) {
            case 'P':
            case 'p':
                if (currentPage > 0) {
                    --currentPage;
                }
                else {
                    cout << "You are already on the first page.\n";
                }
                break;
            case 'N':
            case 'n':
                if (currentPage < totalPages - 1) {
                    ++currentPage;
                }
                else {
                    cout << "You are already on the last page.\n";
                }
                break;
            case 'Q':
            case 'q':
                return;
            default:
                cout << "Invalid option. Please try again.\n";
            }

            // Clear the screen
            system("CLS");
        }
    }

    double ComputeTotalCost() const {
        double totalCost = 0;
        for (int i = 0; i < productCount; ++i) {
            totalCost += products[i].productCost * products[i].productQuantity;
        }
        return totalCost;
    }
};

int main() {
    Store store;

    int userChoice;
    do {
        store.DisplayMenu();
        cout << "Enter your choice: ";
        cin >> userChoice;
        system("CLS");

        switch (userChoice) {
        case 1:
            store.AddProduct();
            break;
        case 2:
            store.DeleteProduct();
            break;
        case 3:
            store.UpdateProduct();
            break;
        case 4:
            store.DisplayProducts();
            break;
        case 5:
            cout << "Total Cost: $" << store.ComputeTotalCost() << endl;
            break;
        case 6:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (userChoice != 6);

    store.CleanUp();

    return 0;
}
