#include "Silpo order.h"

SilpoOrder::SilpoOrder(string id) {
    orderId = id;
    status = UNPAID;
    payment = NOT_SELECTED;
    deliveryDate = "Not set";
    discount = 0.0;
    promoCode = "None";
}

void SilpoOrder::addProduct(string name, double price, int qty) {  
    for (size_t i = 0; i < cart.size(); i++) {
        if (cart[i].getName() == name) {  //перевірка на дублікати
            cart[i].setQuantity(cart[i].getQuantity() + qty);
            cout << "Updated existing product quantity." << endl; 
            return;
        }
    }
    cart.push_back(Product(name, price, qty));
    cout << "Product added to cart." << endl;
}

void SilpoOrder::removeProduct(string name) {
    for (size_t i = 0; i < cart.size(); i++) {
        if (cart[i].getName() == name) {
            cart.erase(cart.begin() + i);
            cout << "Product removed." << endl;
            return;
        }
    }
    cout << "Product not found." << endl;
}

void SilpoOrder::updateQuantity(string name, int newQty) {
    if (newQty <= 0) { 
        removeProduct(name);
        return;
    }
    for (size_t i = 0; i < cart.size(); i++) {
        if (cart[i].getName() == name) {
            cart[i].setQuantity(newQty);
            cout << "Quantity updated." << endl;
            return;
        }
    }
}

void SilpoOrder::applyPromo(string code) {
    if (code == "RACCOON_HERO") {
        discount = 0.20;
        promoCode = code;
        cout << "Promo applied: 20% off!" << endl;
    }
    else if (code == "BORSCH") {
        discount = 0.15;
        promoCode = code;
        cout << "Promo applied: 15% off!" << endl;
    }
    else {
        cout << "Invalid promo code." << endl;
    }
}

void SilpoOrder::setDeliveryDate(string date) {
    deliveryDate = date;
    cout << "Delivery date set." << endl;
}

void SilpoOrder::setStatus(OrderStatus newStatus) {
    status = newStatus;
    cout << "Status updated." << endl;
}

void SilpoOrder::setPaymentMethod(PaymentMethod method) {
    payment = method;
    cout << "Payment method updated." << endl;
}

//Розрахунок загальної вартості
double SilpoOrder::calculateTotal() const {
    double total = 0;
    for (size_t i = 0; i < cart.size(); i++) {
        int qty = cart[i].getQuantity();
        double price = cart[i].getPrice();
        // Акція "1+1=3"
        int payableQty = qty - (qty / 3);
        // Акція "Товар дня"
        if (cart[i].getName() == ITEM_OF_THE_DAY) {
            price = price * (1.0 - ITEM_OF_THE_DAY_DISCOUNT);
        }

        total += price * payableQty;
    }
    // Загальний промокод на весь чек
    return total * (1.0 - discount);
}

// Вивід чеку на екран
void SilpoOrder::showOrder() const {
    string statusStr[] = { "Unpaid", "Paid", "Completed", "Cancelled" };
    string paymentStr[] = { "Not Selected", "Online", "Upon Receipt" };

    cout << "\n=========================================" << endl;
    cout << "          SILPO ONLINE ORDER             " << endl;
    cout << "=========================================" << endl;
    cout << "Order ID: " << orderId << endl;
    cout << "Status: " << statusStr[status] << endl;
    cout << "Payment: " << paymentStr[payment] << endl;
    cout << "Delivery: " << deliveryDate << endl;
    cout << "Promo Code: " << promoCode << endl;
    cout << "-----------------------------------------" << endl;

    for (size_t i = 0; i < cart.size(); i++) {
        cout << "- " << cart[i].getName() << " x" << cart[i].getQuantity() << " @ " << cart[i].getPrice() << " UAH";

        //Акції
        if (cart[i].getName() == ITEM_OF_THE_DAY) {
            cout << " [PROMO -30%]";
        }
        if (cart[i].getQuantity() >= 3) {
            cout << " [1+1=3 FREE!]";
        }
        cout << endl;
    }

    cout << "-----------------------------------------" << endl;
    cout << "TOTAL TO PAY: " << fixed << setprecision(2) << calculateTotal() << " UAH" << endl;
    cout << "=========================================\n" << endl;
}

// Збереження даних у файл
void SilpoOrder::saveToFile(string filename) const {
    ofstream file(filename);
    if (file.is_open()) {
        file << orderId << "\n" << deliveryDate << "\n" << status << "\n" << payment << "\n" << promoCode << "\n" << discount << "\n";
        file << cart.size() << "\n";

        for (size_t i = 0; i < cart.size(); i++) {
            file << cart[i].getName() << "\n" << cart[i].getPrice() << "\n" << cart[i].getQuantity() << "\n";
        }
        file.close();
        cout << "Order saved to " << filename << endl;
    }
    else {
        cout << "Error opening file for saving." << endl;
    }
}

// Завантаження даних з файлу
void SilpoOrder::loadFromFile(string filename) {
    ifstream file(filename);
    if (file.is_open()) {
        int s, p, count;

        getline(file, orderId);
        getline(file, deliveryDate);
        file >> s >> p >> promoCode >> discount >> count;
        status = (OrderStatus)s;
        payment = (PaymentMethod)p;

        cart.clear();

        for (int i = 0; i < count; i++) {
            string n; double price; int q;
            file.ignore();
            getline(file, n);
            file >> price >> q;
            cart.push_back(Product(n, price, q));
        }
        file.close();
        cout << "Order loaded from " << filename << endl;
    }
    else {
        cout << "Could not open file for loading. Starting fresh." << endl;
    }
}