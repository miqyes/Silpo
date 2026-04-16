#include "Silpo order.h"

void showMenu() {
    cout << "\n--- Silpo Online Menu ---" << endl;
    cout << "1. Add product" << endl;
    cout << "2. Remove product" << endl;
    cout << "3. Change quantity" << endl;
    cout << "4. Apply Promo Code" << endl;
    cout << "5. Set Delivery Date" << endl;
    cout << "6. Choose Payment Method" << endl;
    cout << "7. View Order" << endl;
    cout << "8. Save and Exit" << endl;
    cout << "Choose action: ";
}

int main() {
    SilpoOrder myOrder("ORD-777");
    myOrder.loadFromFile("last_order.txt");

    cout << "\n==============================================" << endl;
    cout << "           ATTENTION - STORE RULES            " << endl;
    cout << "==============================================" << endl;
    cout << " * Date format: NO SPACES! (e.g. 18-04-2026_14:00)" << endl;
    cout << " * Active Promos: RACCOON_HERO, BORSCH" << endl;
    cout << " * TODAY'S PROMO ITEM: 'Milk' (-30% OFF!)" << endl;
    cout << " * SUPER DEAL: Buy 3 identical items, pay for 2!" << endl;
    cout << "==============================================\n" << endl;

    int choice;
    do {
        showMenu();
        cin >> choice;

        if (choice == 1) {
            string name; double price; int qty;
            cout << "Enter product name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter price: "; cin >> price;
            cout << "Enter quantity: "; cin >> qty;

            myOrder.addProduct(name, price, qty);
        }
        else if (choice == 2) {
            string name;
            cout << "Name to remove: ";
            cin.ignore();
            getline(cin, name);

            myOrder.removeProduct(name);
        }
        else if (choice == 3) {
            string name; int qty;
            cout << "Product name: ";
            cin.ignore();
            getline(cin, name);
            cout << "New quantity: "; cin >> qty;

            myOrder.updateQuantity(name, qty);
        }
        else if (choice == 4) {
            string code;
            cout << "Enter promo: "; cin >> code;
            myOrder.applyPromo(code);
        }
        else if (choice == 5) {
            string date;
            cout << "Date: "; cin >> date;
            myOrder.setDeliveryDate(date);
        }
        else if (choice == 6) {
            int payChoice;
            cout << "1. Online\n2. Upon Receipt\nChoose: ";
            cin >> payChoice;
            if (payChoice == 1) myOrder.setPaymentMethod(ONLINE);
            else if (payChoice == 2) myOrder.setPaymentMethod(UPON_RECEIPT);
            else cout << "Invalid choice." << endl;
        }
        else if (choice == 7) {
            myOrder.showOrder();
        }

    } while (choice != 8);

    myOrder.saveToFile("last_order.txt");
    cout << "Have a nice day!" << endl;

    return 0;
}