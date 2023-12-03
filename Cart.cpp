#include "Cart.h"
#include <iostream>
#include <iomanip>

using namespace std;

float Cart::get_total_price(void)
{
    float total_price = 0;

    Store& store = Store::get_instance();

    for(auto storeProductPtr = store.products.begin(); storeProductPtr != store.products.end(); ++storeProductPtr)
    {
        for(auto itemsPtr = this->items.begin(); itemsPtr != this->items.end(); ++itemsPtr)
        {
            if(storeProductPtr->get_id() == itemsPtr->first)
            {
                total_price += (storeProductPtr->get_price() * itemsPtr->second);
            }
        }
    }

    return total_price;
}

void Cart::add(int product_id, int quantity)
{
    if(quantity >= 0)
    {
        if(this->items.find(product_id) != this->items.end())
        {
            this->items[product_id] += quantity;
        }
        else
            this->items[product_id] = quantity;
    }
    else
        throw out_of_range("Quantity must be greater than 0.");

    cout << "Item added successfully in Customer's cart!" << endl;
}

void Cart::remove_item(int product_id)
{
    if(this->items.find(product_id) != this->items.end())
        this->items.erase(product_id);
    else
        throw invalid_argument("Product ID not found.");

    cout << "Item removed successfully from Customer's cart!" << endl;
}

void Cart::reset(void) { this->items.clear(); cout << "Customer's cart reset successfully!" << endl; }

void Cart::print(void)
{
    Store& store = Store::get_instance();

    for(auto storeProductPtr = store.products.begin(); storeProductPtr != store.products.end(); ++storeProductPtr)
    {
        for(auto itemsPtr = this->items.begin(); itemsPtr != this->items.end(); ++itemsPtr)
        {
            if(storeProductPtr->get_id() == itemsPtr->first)
            {
                cout << "ID: " << storeProductPtr->get_id() << endl;
                cout << "Name: " << storeProductPtr->get_name() << endl;
                cout << "Price: " << storeProductPtr->get_price() << endl;
                cout << "Brand: " << storeProductPtr->get_brand() << endl;
                cout << "Expire date: " << setfill('0')
                                        << setw(2) << storeProductPtr->get_expire_date().getYear() << '/'
                                        << setw(2) << storeProductPtr->get_expire_date().getMonth() << endl;
                cout << "Quantity in cart: " << itemsPtr->second << endl << endl;
            }
        }
    }
}

const map<int, int> Cart::get_items(void) const { return this->items; }