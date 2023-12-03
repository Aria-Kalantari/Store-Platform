#include "Receipt.h"

float Receipt::get_total_price(void) const
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


const map<int, int>& Receipt::get_items(void) const { return this->items; }

const Date& Receipt::get_date(void) const { return this->date; }