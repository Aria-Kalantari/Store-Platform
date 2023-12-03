#ifndef PRODUCT_H
#define PRODUCT_H

#pragma once

#include <string>
#include "Date.h"
#include "Store.h"

class Product
{
    friend class Store;

public:
    int get_id(void) const;
    std::string get_name(void) const;
    float get_price(void) const;
    std::string get_brand(void) const;
    Date get_expire_date(void) const;
 
private:
    int id;
    std::string name;
    float price;
    std::string brand;
    Date expire_date;
};  

#endif