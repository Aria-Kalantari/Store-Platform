#ifndef RECEIPT_H
#define RECEIPT_H

#pragma once

#include <map>
#include "Date.h"
#include "Store.h"
#include "Customer.h"

class Receipt
{
    friend class Store;
    friend class Customer;

public:
    float get_total_price(void) const;

    const std::map<int, int>& get_items(void) const;
    const Date& get_date(void) const;

private:
    std::map<int, int> items;
    Date date;    
};

#endif