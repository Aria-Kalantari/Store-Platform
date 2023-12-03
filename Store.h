#ifndef STORE_H
#define STORE_H

#pragma once

#include "Product.h"
#include "Stock.h"
#include "Customer.h"
#include "Cart.h"
#include "Date.h"
#include <vector>

class Store
{
    friend class Cart;
    friend class Receipt;

public:
    static Store& get_instance(void)
    {
        static Store instance;
        return instance;
    }

    void check_out(Customer&);
    void add_customer(void);
    void add_product(void);
    void view_products(void) const;
    void save_to_file(void) const;
    void read_file(void);
    void read_product_temp(void);
    void read_customer_temp(void);
    void read_stock_temp(void);
    void sales_report(Date, Date);

    std::vector<Product>& get_products(void);
    Stock& get_stock(void);
    std::vector<Customer>& get_customers(void); 

private:
    Store(void) = default;
    Store(const Store&) = delete;
    void operator=(const Store&) = delete;

    std::vector<Product> products;
    Stock stock;
    std::vector<Customer> customers;
};

#endif