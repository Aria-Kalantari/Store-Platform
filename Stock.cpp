#include "Stock.h"

int Stock::get_count(int product_id) { return this->items[product_id]; }

void Stock::change_count_by(int product_id, int count)
{
    if(count < 0 && this->items[product_id] < (-1 * count))
        throw out_of_range("Count of product is smaller than the count that was given to change it by.");
    else
        this->items[product_id] += count;
}

const map<int, int>& Stock::get_items(void) const { return this->items; }