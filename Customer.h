#ifndef CUSTOMER_H
#define CUSTOMER_H

#pragma once

#include <string>
#include "Receipt.h"
#include "Cart.h"
#include <vector>

class Customer
{
    friend class Store;

public:
    void convert_cart_to_receipt(void);
    float get_total_purchase_amount(void);

    int get_id(void) const;
    const std::string& get_name(void) const;
    const std::string& get_phone_numer(void) const;
    const std::string& get_address(void) const;
    float get_balance(void) const;
    const std::vector<Receipt>& get_history(void) const;
    Cart& get_cart(void);

private:
    int id;
    std::string name;
    std::string phone_number;
    std::string address;
    float balance;
    std::vector<Receipt> history;
    Cart cart;
};

#endif
