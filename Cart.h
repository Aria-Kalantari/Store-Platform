#ifndef CART_H
#define CART_H

#pragma once

#include <map>
#include "Store.h"

class Cart
{
    friend class Store;
    friend class Customer;
    
public:
    float get_total_price(void);
    void add(int, int);
    void remove_item(int);
    void print(void);
    void reset(void);

    const std::map<int, int> get_items(void) const; 

private:
    std::map<int, int> items;
};

#endif