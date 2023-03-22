//setw, left functions taken from https://en.cppreference.com/w/cpp/io/manip/left

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

class Item {
public:
    Item(const string& name, double price, char tax, int quantity) :
        name(name), price(price), tax(tax), quantity(quantity) {}

    double get_net_price() const {
        return price * quantity;
    }

    double get_tax_amount() const {
        switch (tax) {
            case 'A':
                return 0.23 * get_net_price();
            case 'B':
                return 0.08 * get_net_price();
            case 'C':
                return 0.0;
            default:
                return 0.0;
        }
    }

    double get_total_price() const {
        return get_net_price() + get_tax_amount();
    }

    friend std::ostream& operator<<(std::ostream& os, const Item& item) {
        os << setw(16) << setfill(' ') << item.name << "|"
           << setw(4) << setfill(' ') << item.price << "  " << item.tax << " |"
           << setw(5) << setfill(' ') << item.quantity << " |"
           << setw(6) << setfill(' ') << fixed << setprecision(2) << item.get_net_price() << " |"
           << setw(6) << setfill(' ') << fixed << setprecision(2) << item.get_total_price();
        return os;
    }

private:
    string name;
    double price;
    char tax;
    int quantity;
};

class Invoice {
public:
    Invoice(long long seller_nip, long long buyer_nip) :
        seller_nip_(seller_nip), buyer_nip_(buyer_nip) {}

    void add_item(const Item& item) {
        items.push_back(item);
    }

    double get_total_net_price() const {
        double total = 0.0;
        for (const auto& item : items) {
            total += item.get_net_price();
        }
        return total;
    }

    double get_total_tax_amount() const {
        double total = 0.0;
        for (const auto& item : items) {
            total += item.get_tax_amount();
        }
        return total;
    }

    double get_total_price() const {
        double total = 0.0;
        for (const auto& item : items) {
            total += item.get_total_price();
        }
        return total;
    }

    friend std::ostream& operator<<(std::ostream& os, const Invoice& invoice) {
        os << "------------------VAT invoice------------------" << endl;
        os << "===============================================" << endl;
        os << "Seller: " << setw(10)  << invoice.seller_nip_
           << "      Buyer: " << setw(10) << invoice.buyer_nip_ << endl;
        os << endl;
        os << setw(16) << setfill(' ') << left << "Name" << " c.j. VAT  il.    net    total" << endl;
        os << string(51, '-') << endl;
        for (const auto& item : invoice.items) {
            os << item << endl;
        }
        os << string(51, '-') << endl;
        os << setw(32) << setfill(' ') << "TOTAL" << "|"
           << setw(6) << setfill(' ') << fixed << setprecision(2) << invoice.get_total_net_price() << " |"
           << setw(6) << setfill(' ') << fixed << setprecision(2) << invoice.get_total_price();
        return os;
    }

private:
    long long seller_nip_;
    long long buyer_nip_;
    vector<Item> items;
};

int main()
{
    Invoice inv(7770003699, 1123456789); //idk how to do it to let 0 be in the first position
    inv.add_item(Item("M3 screw", 0.37, 'A', 100));
    inv.add_item(Item("2 mm drill", 2.54, 'B', 2));
    cout << inv << endl;
    return 0;
}
