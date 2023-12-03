#include "Customer.h"
#include <ctime>
#include <stdexcept>

using namespace std;

void Customer::convert_cart_to_receipt(void)
{
    time_t today = time(0);
    tm* local_time = localtime(&today);

    Receipt newReceipt;
    newReceipt.date.setDay(local_time->tm_mday);
    newReceipt.date.setMonth(1 + local_time->tm_mon);
    newReceipt.date.setYear(1900 + local_time->tm_year);

    newReceipt.items = this->cart.items;

    this->cart.items.clear();

    if(this->balance >= newReceipt.get_total_price())
        this->balance -= newReceipt.get_total_price();
    else
        throw out_of_range("Balance must be greater than Customer's total price.");

    history.push_back(newReceipt);
}

float Customer::get_total_purchase_amount(void)
{
    float total_purchase_amount = 0;

    for(auto it = history.begin(); it != history.end(); ++it)
    {
        total_purchase_amount += it->get_total_price();
    }

    return total_purchase_amount;
}


int Customer::get_id(void) const { return this->id; }

const std::string& Customer::get_name(void) const { return this->name; }

const std::string& Customer::get_phone_numer(void) const { return this->phone_number; }

const std::string& Customer::get_address(void) const { return this->address; }

float Customer::get_balance(void) const { return this->balance; }

const vector<Receipt>& Customer::get_history(void) const { return this->history; }

Cart& Customer::get_cart(void) { return this->cart; }