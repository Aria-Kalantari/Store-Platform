#include "Product.h"

using namespace std;

int Product::get_id(void) const { return this->id; }

string Product::get_name(void) const { return this->name; }

float Product::get_price(void) const { return this->price; }

string Product::get_brand(void) const { return this->brand; }

Date Product::get_expire_date(void) const { return this->expire_date; }