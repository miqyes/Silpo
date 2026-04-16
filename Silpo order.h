#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

// Статуси замовлення
enum OrderStatus { UNPAID, PAID, COMPLETED, CANCELLED };

// Способи оплати
enum PaymentMethod { NOT_SELECTED, ONLINE, UPON_RECEIPT };

class Product {
private:
    string name;
    double price;
    int quantity;

public:
    Product(string n = "", double p = 0.0, int q = 0) : name(n), price(p), quantity(q) { }
    string getName() const { return name; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    void setQuantity(int q) { quantity = q; }
};

class SilpoOrder {
private:
    vector<Product> cart;
    string orderId;
    string deliveryDate;
    OrderStatus status;
    PaymentMethod payment;   
    double discount;  //загальна знижка
    string promoCode;  //назва знижки

    const string ITEM_OF_THE_DAY = "Milk";
    const double ITEM_OF_THE_DAY_DISCOUNT = 0.30; 

public:
    SilpoOrder(string id);

    // Робота з продуктами
    void addProduct(string name, double price, int qty);
    void removeProduct(string name);
    void updateQuantity(string name, int newQty);

    // Оформлення
    void applyPromo(string code);
    void setDeliveryDate(string date);
    void setStatus(OrderStatus newStatus);
    void setPaymentMethod(PaymentMethod method); // Новий метод

    double calculateTotal() const;
    void showOrder() const;

    void saveToFile(string filename) const;
    void loadFromFile(string filename);
};