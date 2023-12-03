#ifndef STOCK_H
#define STOCK_H

#pragma once

#include <map>
#include "Store.h" 

class Stock
{
    friend class Store;
    
public:
    int get_count(int);
    void change_count_by(int, int);

    const std::map<int, int>& get_items(void) const;

private:
    std::map<int, int> items;    
};

#endif