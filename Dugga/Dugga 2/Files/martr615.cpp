/*****************************************************************************
* TNG033: Dugga 2, ht2/2017                                                  *
* Name: Martin Tran                                                          *
* Personal number: 930201-5616                                               *
* ****************************************************************************/

#include <iostream>
#include <string>
#include <set>
#include <iterator>
#include <algorithm>

using namespace std;  //feel free to open std namespace


/****************************************
* Class Shop                            *
*****************************************/
class Shop
{
public:



    virtual ~Shop() {} //abstrakt destructor

    //It should not be possible to create copies of instances of the class.
    Shop(const Shop&) = delete;
    Shop& operator=(const Shop&) = delete;

    //function
    string get_name() const { return shopName; } //function to get name

    virtual void update(double d) = 0;

protected:

    //constructor
    Shop(const string& name, double price)
        : shopName(name), productPrice(price)
    {
        cout<< " shop created: "
            << shopName << ", start price = "
            << productPrice << endl;
    }

    const string shopName; //cant modify the shop name when init
    double productPrice;
};



/****************************************
* Class Vip_Shop                        *
*****************************************/
class Vip_Shop : public Shop
{
public:
    //constructor
    Vip_Shop(const string& name, double price) //måste ta bort ostream här
        : Shop(name, price)
    {
        priceFactor = 1;
    }

    ~Vip_Shop() = default;

    Vip_Shop(const Shop&) = delete;
    Vip_Shop& operator=(const Shop&) = delete;

    //Function
    void set_price_factor(int n);

protected:

    int priceFactor;

};

void Vip_Shop::set_price_factor(int n)
{
   double sum;
   priceFactor = n;

   sum = n * productPrice;

   cout<<"Vip shop:: " << shopName << " updated price from "
                << productPrice << ".00"
                << " to "
                << sum << ".00"
                << endl;
}



/****************************************
* Class Outlet_Shop                     *
*****************************************/
class Outlet_Shop : public Shop
{
public:
    //constructor
    Outlet_Shop(const string& name, double price)
        : Shop(name, price)
    {
        discount = 0.0;
    }

    ~Outlet_Shop() = default;

    Outlet_Shop(const Shop&) = delete;
    Outlet_Shop& operator=(const Shop&) = delete;

    //function
    void set_discount(double n);

protected:
    double discount;
};

//is test phase 3 displaying wrong result?
//shouldn't discount make the final price smaller rather than larger?
void Outlet_Shop::set_discount(double n)
{
   double sum;
   discount = n;

   sum = productPrice - (n*productPrice);

   cout<<"Outlet shop:: " << shopName << " updated price from "
                << productPrice << ".00"
                << " to "
                << sum << ".00"
                << endl;

}


/****************************************
* Class Brand_Manager                   *
*****************************************/
class Brand_Manager
{

public:
    //constructor
    //måste göra något med reference price
    Brand_Manager(const string& name)
        : brandName(name)
    {}

    ~Brand_Manager() = default; //destructor

    //It should not be possible to create copies of Brand_Manager.
    Brand_Manager(const Brand_Manager&) = delete;

    //functions
    string get_name() const { return brandName; } //get_name
    void register_shop(const Shop& rs); //register_shop
    void display_registered_shops(); //display_registered_shop
    void set_reference_price(int n); //was about to start to implement but time is ending

protected:
    const string brandName;
    set<string> reg_shop;
};


void Brand_Manager::register_shop(const Shop& rs)
{
    string nameOfShop;
    nameOfShop = rs.get_name();
    reg_shop.insert(nameOfShop); //save the shop name in a set
                                //set doesn't save duplicates (the same shop is not registered twice)
}

void Brand_Manager::display_registered_shops()
{
    //display the vector
    copy(reg_shop.begin(), reg_shop.end(), ostream_iterator<string>(cout, " "));
    cout << endl;
}



/**************************
* MAIN: do not modify     *
***************************/

void f1(Brand_Manager m);
void f2(Brand_Manager& m);


int main()
{
    //The log output stream used in this test code is std::cout
    //so all log messages go directly to the screen

    /*************************************
    * TEST PHASE 1                       *
    * Create some Shops                  *
    **************************************/

    std::cout << "\nTEST PHASE 1\n" << "\n";

    Vip_Shop gant("Gant", 1000);
    Outlet_Shop cubus("Cubus", 100);

    Shop* V[3] = {&gant, &cubus, new Outlet_Shop("Vero Moda", 200)};

    std::cout << "\nShop names: ";

    for(int i = 0; i < 3; i++)
    {
        std::cout << "Shop " << V[i]->get_name() << " ";
    }


    /*************************************
    * TEST PHASE 2                       *
    * Create a Brand_Manager and         *
    * register some shops                *
    **************************************/
    std::cout << "\n\nTEST PHASE 2\n" << "\n";

    Brand_Manager M("Clothes of Sweden");

    M.register_shop(*V[0]);
    M.register_shop(*V[1]);
    M.register_shop(*V[2]);

    std::cout << "Shops registered at "
         << M.get_name() << ": ";

    M.display_registered_shops();

    /******************************************
    * TEST PHASE 3                            *
    * Notify the shops to update their prices *
    *******************************************/
    std::cout << "\nTEST PHASE 3\n" << "\n";

    gant.set_price_factor(2);
    cubus.set_discount(0.2);

//    M.set_reference_price(1500);

//    M.notify();

    /************************************************
    * TEST PHASE 4                                  *
    * Notify the shops to update their prices again *
    *************************************************/
    std::cout << "\nTEST PHASE 4\n" << "\n";

    cubus.set_discount(0.5);

//    M.set_reference_price(2000);
//
//    M.notify();
//
//    /************************************************
//    * TEST PHASE 5                                  *
//    * Brand_Manager copy constructor                *
//    *************************************************/
    std::cout << "\nTEST PHASE 5\n" << "\n";

    //f1(M);    //should not compile

    f2(M);

    delete V[2];

    return 0;
}


void f1(Brand_Manager m)
{
    std::cout << m.get_name() << "- You shouldn't see this!!" << "\n";
}

void f2(Brand_Manager& m)
{
    std::cout << m.get_name() << "- You should see this!!" << "\n";
}

