#include "Store.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <stdexcept>

using namespace std;

void Store::check_out(Customer& customer)
{
    if(customer.cart.items.empty())
    {
        cout << endl << "Customer's cart is empty" << endl;
        return;
    }

    for(auto it = customer.cart.items.begin(); it != customer.cart.items.end(); ++it)
    {
        this->stock.change_count_by(it->first, -1 * (it->second));
    }

    customer.convert_cart_to_receipt();

    cout << endl << "Customer checked out successfully!" << endl << endl;
}

void Store::add_customer(void)
{
    Customer newCustomer;

    cout << "add customer" << endl;

    string id;
    string name;
    string phone_number;
    string address;
    string balance;
    
    cin.ignore();

    cout << "ID: ";
    getline(cin, id);
    newCustomer.id = stoi(id);
    for(auto it = this->customers.begin(); it != this->customers.end(); ++it)
    {
        if(newCustomer.id == it->id)
            throw runtime_error("Customer with this ID  exists.");
    }

    cout << "Name: ";
    getline(cin, name);

    cout << "Phone number: ";
    getline(cin, phone_number);

    cout << "Address: ";
    getline(cin, address);

    cout << "Balance: ";
    getline(cin, balance);

    newCustomer.name = name;
    newCustomer.phone_number = phone_number;
    newCustomer.address = address;
    newCustomer.balance = stof(balance);

    this->customers.push_back(newCustomer);

    cout << "Customer added successfully to store!" << endl;
}

void Store::add_product(void)
{
    Product newProduct;

    string id;
    string name;
    string price;
    string brand;
    string expire_date;
    string num_in_stock;

    cout << "add product" << endl;

    cin.ignore();

    cout << "ID: "; 
    getline(cin, id);
    newProduct.id = stoi(id);

    for(auto it = this->products.begin(); it != this->products.end(); ++it)
    {
        if(newProduct.id == it->id)
        {
            cout << "Product with ID: " << it->id << " exists" << endl;
            cout << "-" << "In stock: ";
            getline(cin, num_in_stock);
            if(stoi(num_in_stock) >= 0)
                this->stock.items[newProduct.id] = stoi(num_in_stock);
            else
                throw out_of_range("Count of stock must be greater than 0.");
            cout << "Changed the quantity of product in stock successfully" << endl;
            return;
        }
    }

    cout << "Name: ";
    getline(cin, name);

    cout << "Price: ";
    getline(cin, price);

    cout << "Brand: ";
    getline(cin, brand);

    cout << "Expire date: ";
    getline(cin, expire_date);

    cout << "-" << "In stock: ";
    getline(cin, num_in_stock);

    newProduct.name = name;
    newProduct.price = stof(price);
    newProduct.brand = brand;
    newProduct.expire_date.setYear(stoi(expire_date.substr(0, 4)));
    newProduct.expire_date.setMonth(stoi(expire_date.substr(5)));
    
    if(stoi(num_in_stock) >= 0)
        this->stock.items[newProduct.id] = stoi(num_in_stock);
    else
        throw out_of_range("Count of stock must be greater than 0.");

    this->products.push_back(newProduct);

    cout << "Product added successfully to store!" << endl;
}

void Store::view_products(void) const
{
    cout << endl << "---------------------------------------" << " PRODUCTS " << "---------------------------------------" << endl;
    for(auto it = this->products.begin(); it < this->products.end(); ++it)
    {
        cout << "ID:          " << it->id << endl;
        cout << "Name:        " << it->name << endl;
        cout << "Price:       " << it->price << endl;
        cout << "Brand:       " << it->brand << endl;
        cout << "Expire date: " << setfill('0')
                                << setw(2) << it->expire_date.getYear() << '/'
                                << setw(2) << it->expire_date.getMonth() << endl <<endl;
    }
}

void Store::save_to_file(void) const
{
    fstream file("store.txt", ios::trunc | ios::out);
    fstream product_temp("product.txt", ios::trunc | ios::out);
    fstream customer_temp("customer.txt", ios::trunc | ios::out);
    fstream stock_temp("stock.txt", ios::trunc | ios::out);
    fstream receipt_temp("receipt.txt", ios::trunc | ios::out);
    fstream date_temp("date.txt", ios::trunc | ios::out);

    file << endl << "---------------------------------------" << " PRODUCTS " << "----------------------------------------" << endl;
    for(auto it = this->products.begin(); it < this->products.end(); ++it)
    {
        file << "ID:           " << it->id << endl;
        file << "Name:         " << it->name << endl;
        file << "Price:        " << it->price << endl;
        file << "Brand:        " << it->brand << endl;
        file << "Expire date:  " << setfill('0')
                                << setw(2) << it->expire_date.getYear() << '/'
                                << setw(2) << it->expire_date.getMonth() << endl << endl;

        product_temp << it->id << endl << it->name << endl
                     << it->price << endl << it->brand << endl;
    }

    file << endl << "---------------------------------------" << " CUSTOMERS " << "---------------------------------------" << endl;
    for(auto customer_ptr = this->customers.begin(); customer_ptr < this->customers.end(); ++customer_ptr)
    {
        file << "ID:           " << customer_ptr->id << endl;
        file << "Name:         " << customer_ptr->name << endl;
        file << "Phone number: " << customer_ptr->phone_number << endl;
        file << "Address:      " << customer_ptr->address << endl;
        file << "Balance:      " << customer_ptr->balance << endl;
        file << "History:      " << endl << endl;
        for(auto receipt_ptr = customer_ptr->history.begin(); receipt_ptr != customer_ptr->history.end(); ++receipt_ptr)
        {
            file << "Date: " << receipt_ptr->date << "-->" << endl;

            date_temp << receipt_ptr->items.size() << endl << receipt_ptr->date << endl;

            for(auto items_ptr = receipt_ptr->items.begin(); items_ptr != receipt_ptr->items.end(); ++items_ptr)
            {
                file << "\tProduct ID: " << items_ptr->first  << ", "
                     << "\tQuantity: " << items_ptr->second << endl;

                receipt_temp << items_ptr->first << endl << items_ptr->second << endl;
            }
        }

        customer_temp << customer_ptr->id << endl << customer_ptr->name << endl << customer_ptr->phone_number << endl
                      << customer_ptr->address << endl << customer_ptr->balance << endl;
    }

    file << endl << "-----------------------------------------" << " STOCK " << "-----------------------------------------" << endl;
    for(auto it = this->stock.items.begin(); it != this->stock.items.end(); ++it)
    {
        file << "ID:           " << it->first << endl;
        file << "Quantity:     " << it->second << endl << endl;

        stock_temp << it->first << endl << it->second << endl;
    }

    file.close();
    product_temp.close();
    customer_temp.close();
    date_temp.close();
    receipt_temp.close();
    stock_temp.close();

    cout << "File saved successfully!" << endl << endl;
}

void Store::read_file(void)
{
    fstream file("store.txt");

    if(file.peek() != EOF)
    {
        this->read_product_temp();
        this->read_customer_temp();
        this->read_stock_temp();
    }

    file.close();
}

void Store::read_product_temp(void)
{
    ifstream product_temp("product.txt");

    string product_id;
    string product_name;
    string product_price;
    string product_brand;
    string product_expire_date;

    string temp;

    while(!product_temp.eof())
    {
        Product product;

        getline(product_temp, product_id);
        getline(product_temp, product_name);
        getline(product_temp, product_price);
        getline(product_temp, product_brand);
        getline(product_temp, product_expire_date);

        product.id = stoi(product_id);
        product.name = product_name;
        product.brand = product_brand;
        product.expire_date.setYear(stoi(product_expire_date.substr(0, 4)));
        product.expire_date.setMonth(stoi(product_expire_date.substr(5, 7)));
        product.expire_date.setDay(stoi(product_expire_date.substr(8, 10)));

        this->products.push_back(product);
    }
    
    product_temp.close();
}

void Store::read_customer_temp(void)
{
    ifstream customer_temp("customer.txt");
    ifstream date_temp("date.txt");
    ifstream receipt_temp("receipt.txt");
   
    string customer_id;
    string customer_name;
    string customer_phone_number;
    string customer_address;
    string customer_balance;
    string customer_history_items_len;
    string customer_history_product_id;
    string customer_history_quantity;
    string customer_history_date;

    while(!customer_temp.eof())
    {
        Customer customer;

        customer_temp >> customer_id;
        getline(customer_temp, customer_name);
        customer_temp >> customer_phone_number;
        getline(customer_temp, customer_address);
        customer_temp >> customer_balance;

        customer.id = stoi(customer_id);
        customer.name = customer_name;
        customer.phone_number = customer_phone_number;
        customer.address = customer_address;
        customer.balance = stof(customer_balance);

        while(!date_temp.eof())
        {
            Receipt receipt;

            date_temp >> customer_history_items_len >> customer_history_date;

            receipt.date.setYear(stoi(customer_history_date.substr(0, 4)));
            receipt.date.setMonth(stoi(customer_history_date.substr(5, 7)));
            receipt.date.setDay(stoi(customer_history_date.substr(8, 10)));

            int count = stoi(customer_history_items_len);

            for(int i = 0; i < count; ++i)
            {
                receipt_temp >> customer_history_product_id >> customer_history_quantity;
                receipt.items[stoi(customer_history_product_id)] = stoi(customer_history_quantity);
            }

            customer.history.push_back(receipt);
        } 

        this->customers.push_back(customer);   
    }

    receipt_temp.close();
    date_temp.close();
    customer_temp.close();
}

void Store::read_stock_temp(void)
{
    ifstream stock_temp("stock.txt");

    string stock_product_id;
    string stock_product_quantity;

    Stock stock;

    while(!stock_temp.eof())
    {
        stock_temp >> stock_product_id >> stock_product_quantity;

        stock.items[stoi(stock_product_id)] = stoi(stock_product_quantity);
    }

    this->stock = stock;

    stock_temp.close();
}

void Store::sales_report(Date start, Date end)
{
    int count = 0;

    Date maxDate = start;

    float sale = 0;
    float totalSale = 0;
    float maxSale = 0;

    for(Date date = start; date <= end; ++date)
    {
        for(auto customerPtr = customers.begin(); customerPtr != customers.end(); ++customerPtr)
        {
            for(auto receiptHistoryPtr = customerPtr->history.begin(); receiptHistoryPtr != customerPtr->history.end(); ++receiptHistoryPtr)
            {
                if(receiptHistoryPtr->date == date)
                {
                    sale += receiptHistoryPtr->get_total_price();
                    totalSale += sale;
                }
            }
        }

        if(maxSale < sale)
        {
            maxSale = sale;
            maxDate = date;
        }

        count = static_cast<int>(sale) / 100;

        cout << setfill('0') 
             << setw(2) << date.getYear() << '.'
             << setw(2) << date.getMonth() << '.'
             << setw(2) << date.getDay() << ": ";

        for(int i = 0; i < count; ++i)
            cout << "++ ";
        cout << endl;

        count = 0;
        sale = 0;
    }

    cout << "Date with the max sale: " << maxDate << endl;
    cout << "Total Sale: " << totalSale << endl << endl;
}

vector<Product>& Store::get_products(void) { return this->products; }

Stock& Store::get_stock(void) { return this->stock; }

vector<Customer>& Store::get_customers(void) { return this->customers; }