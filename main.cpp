#include "Store.cpp"
#include "Customer.cpp"
#include "Product.cpp"
#include "Stock.cpp"
#include "Receipt.cpp"
#include "Cart.cpp"
#include "Date.cpp"

using namespace std;

void main_menu(void);
void customer_panel(void);
void cart_panel(void);
void stock_panel(void);

int main(void)
{
    Store& store = Store::get_instance();

    Date start_date;
    Date end_date;
    
    int choice;

    store.read_file();

    main_menu();

    cout << "--> ";  
    cin >> choice;

    while(choice != 8)
    {
        switch(choice)
        {
        case 1:
            system("CLS");
            main_menu();
            store.add_product();
            cout << endl << "--> ";
            cin >> choice;
            break;

        case 2:
            system("CLS");
            main_menu();
            store.add_customer();
            cout << endl << "--> ";
            cin >> choice;
            break;

        case 3:
            system("CLS");
            main_menu();
            store.view_products();
            cout << endl << "--> ";
            cin >> choice;
            break;

        case 4:
            cout << "Enter start date: ";
            cin >> start_date;

            cout << "Enter end date: ";
            cin >> end_date;

            cout << endl;

            store.sales_report(start_date, end_date);
            cout << endl << "--> ";
            cin >> choice;
            break;

        case 5:
            int id;
            cout << "Enter customer's ID: ";
            cin >> id;
            bool valid_id;
            valid_id = false;
            for(auto it = store.get_customers().begin(); it != store.get_customers().end(); ++it)
            {
                if(id == it->get_id())
                {
                    valid_id = true;
                    system("CLS");
                    customer_panel();

                    cout << endl << "--> ";
                    cin >> choice;

                    while(choice != 5)
                    {
                        switch(choice)
                        {
                        case 1:
                            system("CLS");
                            customer_panel();
                            store.check_out(*it);
                            cout << "--> ";
                            cin >> choice;
                            break;

                        case 2:
                            system("CLS");
                            customer_panel();
                            cout << endl << "Total purchase amount: "
                                 << it->get_total_purchase_amount() << endl;
                            cout << endl << "--> ";
                            cin >> choice;
                            break;

                        case 3:
                            system("CLS");
                            customer_panel();
                            if(it->get_history().empty())
                            {
                                cout << endl << "Customer doesn't have a history." << endl;
                                cout << endl << "--> ";
                                cin >> choice;
                                break;
                            }
                            for(auto receipt_ptr = it->get_history().begin(); receipt_ptr != it->get_history().end(); ++receipt_ptr)
                            {
                                cout << endl << "Date: " << receipt_ptr->get_date() << " -->" << endl;

                                for(auto items_ptr = receipt_ptr->get_items().begin(); items_ptr != receipt_ptr->get_items().end(); ++items_ptr)
                                {
                                    cout << "Product ID: " << items_ptr->first << ", "
                                         << "Quantity: " << items_ptr->second << endl;
                                }

                                cout << "Total price amount: " << receipt_ptr->get_total_price() << endl;
                            }
                            cout << endl << "--> ";
                            cin >> choice;
                            break;

                        case 4:
                            system("CLS");
                            cart_panel();
                            cout << endl << "--> ";
                            cin >> choice;

                            while(choice != 6)
                            {
                                switch(choice)
                                {
                                case 1:
                                    int product_id;
                                    int quantity;
                                    cout << "Enter Products ID: ";
                                    cin >> product_id;
                                    bool valid_id;
                                    valid_id = false;
                                    for(auto product_ptr = store.get_products().begin(); product_ptr != store.get_products().end(); ++it)
                                    {
                                        if(product_id == it->get_id())
                                        {
                                            valid_id = true;
                                            cout << "Enter item's quantity in customer's cart: ";
                                            cin >> quantity;
                                            if(quantity > store.get_stock().get_count(product_id))
                                            {
                                                system("CLS");
                                                customer_panel();
                                                cout << "there is a mistake in customer's product quantity or in product's quantity in store's stock." << endl;
                                                cout << endl << "--> ";
                                                cin >> choice;
                                                break;
                                            }
                                            system("CLS");
                                            cart_panel();
                                            cout << endl;
                                            it->get_cart().add(product_id, quantity);
                                            cout << endl << "--> ";
                                            cin >> choice;
                                            break;
                                        }
                                        if(valid_id == false && product_ptr == store.get_products().end() - 1)
                                        {
                                            system("CLS");
                                            customer_panel();
                                            cout << endl;
                                            cout << endl <<"ID not found." << endl;
                                            cout << endl << "--> ";
                                            cin >> choice;
                                            break;
                                        }
                                    }
                                    break;

                                case 2:
                                    cout << "Enter Products ID: ";
                                    cin >> product_id;
                                    valid_id = false;
                                    for(auto product_ptr = store.get_products().begin(); product_ptr != store.get_products().end(); ++it)
                                    {
                                        if(product_id == it->get_id())
                                        {
                                            valid_id = true;
                                            system("CLS");
                                            cart_panel();
                                            cout << endl;
                                            it->get_cart().remove_item(product_id);
                                            cout << endl << "--> ";
                                            cin >> choice;
                                            break;
                                        }
                                        if(valid_id == false && product_ptr == store.get_products().end() - 1)
                                        {
                                            system("CLS");
                                            customer_panel();
                                            cout << "ID not found." << endl;
                                            cout << endl << "--> ";
                                            cin >> choice;
                                            break;
                                        }
                                    }
                                    break;

                                case 3:
                                    system("CLS");
                                    cart_panel();
                                    cout << endl;
                                    it->get_cart().print();
                                    cout << endl << "--> ";
                                    cin >> choice;
                                    break;

                                case 4:
                                    system("CLS");
                                    cart_panel();
                                    cout << endl;
                                    it->get_cart().reset();
                                    cout << endl;
                                    cout << "--> ";
                                    cin >> choice;
                                    break;

                                case 5:
                                    system("CLS");
                                    cart_panel();
                                    cout << endl << "Total price: " << 
                                    it->get_cart().get_total_price() << endl << endl;
                                    cout << "--> ";
                                    cin >> choice;
                                    break;
                                }
                            }
                            system("CLS");
                            customer_panel();
                            cout << endl << "--> ";  
                            cin >> choice;
                            break;
                        }
                    }
                    system("CLS");
                    main_menu();
                    cout << "--> ";  
                    cin >> choice;
                    break;
                }
                if(valid_id == false && it == store.get_customers().end() - 1)
                {
                    system("CLS");
                    main_menu();
                    cout << "ID not found." << endl;
                    cout << endl << "--> ";
                    cin >> choice;
                    break;
                }
            }
            break;

        case 6:
            system("CLS");
            stock_panel();
            cout << endl << "--> ";
            cin >> choice;

            while(choice != 3)
            {
                switch (choice)
                {
                case 1:
                    int product_id;
                    cout << "Enter Products ID: ";
                    cin >> product_id;
                    bool valid_id;
                    valid_id = false;
                    for(auto it = store.get_products().begin(); it != store.get_products().end(); ++it)
                    {
                        if(id == it->get_id())
                        {
                            valid_id = true;
                            system("CLS");
                            stock_panel();
                            cout << endl << "Count of product with ID " << product_id << ": " 
                                 << store.get_stock().get_count(product_id) << endl;
                            cout << endl << "--> ";
                            cin >> choice;
                            break;
                        }
                        if(valid_id == false && it == store.get_products().end() - 1)
                        {
                            system("CLS");
                            customer_panel();
                            cout << "ID not found." << endl;
                            cout << endl << "--> ";
                            cin >> choice;
                            break;
                        }
                    } 
                    break;

                case 2:
                    for(auto it = store.get_stock().get_items().begin(); it != store.get_stock().get_items().end(); ++it)
                    {
                        cout << "ID:           " << it->first << endl;
                        cout << "Quantity:     " << it->second << endl << endl;
                    }
                    cout << "--> ";
                    cin >> choice; 
                    break;
                }
            }
            system("CLS");
            main_menu();
            cout << endl << "--> ";
            cin >> choice;            

        case 7:
            system("CLS");
            main_menu();
            store.save_to_file();
            cout << "--> ";  
            cin >> choice;
            break;  
        }
    }

    system("CLS");
    main_menu();
    store.save_to_file();
    return 0;
}

void main_menu(void)
{
                    cout << "|---------------------------------------------------------------------------------------------|";
    cout << endl << "|-----------------------------------------" << " MAIN MENU " << "-----------------------------------------|" << endl;
                    cout << "|---------------------------------------------------------------------------------------------|"; 
    cout << endl;

    cout << endl << "Enter your choice: " << endl << endl;
    cout << "1) Add product" << endl;
    cout << "2) Add customer" << endl;
    cout << "3) View product" << endl;
    cout << "4) Sales report" << endl;
    cout << "5) Customer panel" << endl;
    cout << "6) Stock panel" << endl;
    cout << "7) Save to file" << endl;
    cout << "8) Exit" << endl << endl;  
}

void customer_panel(void)
{
                cout << "|---------------------------------------------------------------------------------------------|";
    cout << endl << "|---------------------------------------" << " CUSTOMER PANEL " << "--------------------------------------|" << endl;
                cout << "|---------------------------------------------------------------------------------------------|"; 
    cout << endl;

    cout << endl << "Enter your choice: " << endl << endl;
    cout << "1) Check out" << endl;
    cout << "2) Get total purchase amount" << endl;
    cout << "3) Customer's history" << endl;
    cout << "4) Cart panel" << endl;
    cout << "5) Main menu" << endl;
}

void cart_panel(void)
{
                cout << "|---------------------------------------------------------------------------------------------|";
    cout << endl << "|-----------------------------------------" << " CART PANEL " << "----------------------------------------|" << endl;
                cout << "|---------------------------------------------------------------------------------------------|"; 
    cout << endl;

    cout << endl << "Enter your choice: " << endl << endl;
    cout << "1) Add item" << endl;
    cout << "2) Remove item" << endl;
    cout << "3) Print customer's cart" << endl;
    cout << "4) Reset customer's cart" << endl;
    cout << "5) Get total price" << endl;
    cout << "6) Customer panel" << endl; 
}

void stock_panel(void)
{
                cout << "|---------------------------------------------------------------------------------------------|";
    cout << endl << "|----------------------------------------" << " STOCK PANEL " << "----------------------------------------|" << endl;
                cout << "|---------------------------------------------------------------------------------------------|"; 
    cout << endl;

    cout << endl << "Enter your choice: " << endl << endl;
    cout << "1) Get count of product" << endl;
    cout << "2) View items in store's stock" << endl;
    cout << "3) Main menu" << endl;
}