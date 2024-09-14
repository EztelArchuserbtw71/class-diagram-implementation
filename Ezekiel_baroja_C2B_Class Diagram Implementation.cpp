#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <ctime>

using namespace std;

//use to manipulate text, but some are not working
namespace Text 
{
    inline void ToUpper(string& str) 
	{
        for (char& c : str) {
            c = toupper(c);
        }
    }

    inline void RemoveExtraSpaces(string& str) 
	{
        str.erase(unique(str.begin(), str.end(), [](char a, char b) { return isspace(a) && isspace(b); }), str.end());
        if(str.front() == ' ') str.erase(str.begin());
        if(str.back() == ' ') str.pop_back();
    }
}

// this is for input of Address and also use in the shipping
class Address 
{
public:
    string block, houseName, city, province;

    void setAddress() 
	{
        cout<<"house block : ";
        cin.ignore();
        getline(cin, block);
        cout<<"house name  : ";
        getline(cin, houseName);
        cout<<"city        : ";
        getline(cin, city);
        cout<<"Province    : ";
        getline(cin, province);
    }

    string getFullAddress() const 
	{
        return block + ", " + houseName + ", " + city + ", " + province;
    }
};

class Product 
{
public:
    string productId;
    string productName;
    float unitCost;

    Product(string id = "", string name = "", float cost = 0.0) : productId(id), productName(name), unitCost(cost) {}

    void display() const 
	{
        cout << setw(10)<<productId<<setw(15)<<productName<<setw(10)<<unitCost << endl;
    }
};

// Shopping Cart to store ar remove what you buy
class ShoppingCart 
{
public:
    vector<pair<Product, int>> cartItems;

    void addToCart(const Product& product, int quantity) 
	{
        cartItems.push_back(make_pair(product, quantity));
        cout<<"Product added successfully!\n";
    }

    void viewCart() const 
	{
        cout<<setw(10)<<"Product ID"<< setw(15)<<"Name"<<setw(10)<<"Price"<<setw(10)<<"Quantity"<<endl;
        for (const auto& item : cartItems) 
		{
            cout << setw(10) << item.first.productId << setw(15) << item.first.productName << setw(10) << item.first.unitCost << setw(10) << item.second << endl;
        }
    }

    float calculateTotal() const 
	{
        float total = 0;
        for (const auto& item : cartItems) 
		{
            total += item.first.unitCost * item.second;
        }
        return total;
    }

    void removeProductById(string id) 
	{
        for(auto it = cartItems.begin(); it != cartItems.end(); ++it) 
		{
            if(it->first.productId == id) 
			{
                cartItems.erase(it);
                cout<<"Successfully removed!\n";
                return;
            }
        }
        cout<<"Product not found!\n";
    }

    void checkout() const 
	{
        cout<<"\nCheckout Items:\n";
        viewCart();
        cout<<"Total Amount: " << calculateTotal() << endl;
        cout<<"You have successfully checked out the products!\n";
    }
};

//total its cash so its automatic payment no more choices
class Payment 
{
public:
    void processPayment(float totalAmount) {
        cout<<"Processing payment of "<<totalAmount<<"...\n";
        cout<<"Payment successful!\n";
    }
};

// Shipping confirmation after the address
class Shipping 
{
public:
    void processShipping() 
	{
        cout<<"Processing shipping...\n";
        cout<<"Shipping details confirmed.\n";
    }
};

// Register Class is to input name, address and phone, so it will appear on noivice
class Register 
{
public:
    string fullname, phoneNumber, password;
    Address address;

    void registerUser() 
	{
        cout << "Enter your full name: ";
        cin.ignore();
        getline(cin, fullname);
        cout<<"Enter your password: ";
        cin>>password;
        cout<<"Enter your phone number: ";
        cin>>phoneNumber;
        cout<<"Enter your shipping address:\n";
        address.setAddress();
    }

    string getFullName() 
	{
        return fullname;
    }

    string getPhoneNo() 
	{
        return phoneNumber;
    }

    string getAddress() 
	{
        return address.getFullAddress();
    }
};

// Customer Class imherits the register
class Customer : public Register 
{
public:
    ShoppingCart cart;
    Payment payment;
    Shipping shipping;

    void viewCart() const 
	{
        cart.viewCart();
    }

    void checkout() 
	{
        cart.checkout();
        payment.processPayment(cart.calculateTotal());
        shipping.processShipping();
    }
};

// Admin the one add and remove products on catalog
class Admin 
{
private:
    string adminID;
    vector<Product>& productCatalog;

public:
    Admin(string id, vector<Product>& catalog):adminID(id), productCatalog(catalog) {}

    void addProduct() 
	{
        string id, name;
        float price;
        cout<< "Enter Product ID: ";
        cin>> id;
        cout<<"Enter Product Name: ";
        cin>> name;
        cout<<"Enter Product Price: ";
        cin >> price;
        productCatalog.push_back(Product(id, name, price));
        cout<<"Product added to catalog.\n";
    }
//to remove product only admin can do
    void removeProduct() 
	{
        string id;
        cout<<"Enter Product ID to remove: ";
        cin>>id;
        auto it =remove_if(productCatalog.begin(), productCatalog.end(),
            [&](const Product& p) { return p.productId == id; });
        if(it !=productCatalog.end()) 
		{
            productCatalog.erase(it);
            cout<<"Product removed from catalog.\n";
        } 
		else 
		{
            cout<<"Product not found!\n";
        }
    }
};

// this one is to display product catalog
void displayProducts(const vector<Product>& products) 
{
    cout<<setw(10)<<"Product ID"<<setw(15)<< "Name"<< setw(10)<<"Price" << endl;
    for(const auto& product : products) 
	{
        product.display();
    }
}

// here is already products and function
int main() 
{
    vector<Product> products =
	 {
        Product("QWE","Pencil", 10.00),
        Product("TRE","Paper", 20.00),
        Product("bll","Ballpen", 50.00),
        Product("ylp","Yellow Paper", 25.00),
        Product("shp","Short Paper", 25.00)
    };

    int choice;
    Customer customer;
    Admin admin("admin", products);

    while (true) 
	{
        cout<<"\nDear user, you want to register/login as:\n";
        cout<<"(1) Administrator\n";
        cout<<"(2) Customer\n";
        cout<<"(3) Exit\n";
        cout<<"Please choose an option: ";
        cin>> choice;

        if(choice == 1) 
		{
            string adminID;
            cout<<"Enter your staff ID: ";
            cin>>adminID;
            if (adminID == "eztel" || adminID == "sir" || adminID == "c2b") //the admins that are only allowed
			{
                int adminChoice;
                while (true) {
                    cout<<"\nDear Admin\n";
                    cout<<"(1) Add product\n";
                    cout<<"(2) Remove product\n";
                    cout<<"(3) Logout\n";
                    cout<<"Choose an option: ";
                    cin>>adminChoice;

                    if(adminChoice == 1) 
					{
                        admin.addProduct();
                    } 
					else if(adminChoice == 2) 
					{
                        admin.removeProduct();
                    } 
					else if(adminChoice == 3)
					 {
                        break;
                    }
                }
            } 
			else 
			{
                cout<<"Invalid Admin ID!\n";
            }
        } 
		else if (choice == 2) 
		{
            customer.registerUser();

            int customerChoice;
            while(true) 
			{
                cout<<"\nProduct Catalog\n";
                displayProducts(products);
                cout<<"\n(1) Add product to cart\n";
                cout<<"(2) View cart\n";
                cout<<"(3) Checkout\n";
                cout<<"(4) Logout\n";
                cout<<"Choose an option: ";
                cin>> customerChoice;

                if(customerChoice == 1) 
				{
                    string productId;
                    displayProducts(products);
                    cout<<"Enter the ID of the product to add to cart: ";
                    cin>>productId;
                    auto it= ind_if(products.begin(), products.end(), [&](const Product& p) { return p.productId == productId; });
                    if(it !=products.end()) {
                        int quantity;
                        cout<<"Enter quantity: ";
                        cin>>quantity;
                        customer.cart.addToCart(*it, quantity);
                    } 
					else 
					{
                        cout << "Product not found!\n";
                    }
                } else if (customerChoice == 2) 
				{
                    customer.viewCart();
                } else if (customerChoice == 3) 
				{
                    customer.checkout();
                } else if (customerChoice == 4) 
				{
                    break;
                }
            }
        } 
		else if (choice == 3) {
            return 0;
        } 
		else 
		{
            cout << "Invalid option!\n";
        }
    }

    return 0;
}
