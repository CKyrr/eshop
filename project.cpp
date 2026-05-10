#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
#include<vector>
#include<sstream>
#include<map>
#include<set>
#include<algorithm>

using namespace std;


class Product{
    private:
        string titlos;
        string perigrafi;
        string katigoria;
        string ipokatigoria;
        double timi;
        string unit;
        int posotita;

        string kena(const string& s) const { 
            size_t first = s.find_first_not_of(' '); 
            if (first == string::npos) return ""; 
            size_t last = s.find_last_not_of(' '); 
            return s.substr(first, last - first + 1); 
        }

    public:
        Product() : titlos(""),perigrafi(""),katigoria(""),ipokatigoria(""),timi(0.0),unit(""),posotita(0){}

        Product(string titlos1, string perigrafi1, string katigoria1, string ipokatigoria1, double timi1, string unit1, int posotita1)
            : titlos(titlos1), perigrafi(perigrafi1), katigoria(katigoria1), ipokatigoria(ipokatigoria1), timi(timi1), unit(unit1), posotita(posotita1) {}

        string gettitlos()const{
            return kena(titlos);
        }
        string getperigrafi()const{
            return kena(perigrafi);
        }
        string getkatigoria()const{
            return kena(katigoria);
        }
        string getipokatigoria()const{
            return kena(ipokatigoria);
        }
        double gettimi()const{
            return timi;
        }
        string getunit()const{
            return kena(unit);
        }
        int& getposotita(){
            return posotita;
        }
        const int& getposotita()const{
            return posotita;
        }

        void settitlos(const string& newtitlos){
            titlos= newtitlos;
        }
        void setperigrafi(const string& newperigrafi){
            perigrafi= newperigrafi;
        }
        void setkatigoria(const string& newperigrafi){
            perigrafi= newperigrafi;
        }
        void setipokatigoria(const string& newipokatigoria){
            katigoria= newipokatigoria;
        }
        void settimi(double newtimi){
            timi= newtimi;
        }
        void setunit(const string& newunit){
            unit= newunit;
        }
        void setposotita(int newposotita){
            posotita= newposotita;
        }

        void show() const{
            cout<<"-----"<<kena(titlos)<<"-----"<<endl;
            cout<<"Description: "<<kena(perigrafi)<<endl;
            cout<<"Category: "<<kena(katigoria)<<endl;
            cout<<"Subcategory: "<<kena(ipokatigoria)<<endl;
            if(kena(unit) == "Unit"){
                cout<<"Price per unit: "<<timi<<"€"<<endl; 
            } else if(kena(unit) == "Kg"){
                cout<<"Price per Kg: "<<timi<<"€"<<endl;
            }
            cout<<"Total units available: "<<posotita<<endl;
        }          
};


class Eshop;

class User{
    private:
       string username;
       string password;
       bool isAdmin;

    public:
        
        User(string username1, string password1, bool isAdmin1) 
        : username(username1), password(password1) , isAdmin(isAdmin1) {}
        
        string getusername()const{
            return username;
        }
        string getpassword()const{
            return password;
        }
        bool getisAdmin()const{
            return isAdmin;
        }

        virtual void showmenu(Eshop& eshop) =0;
};


class Cart{
    public:
        vector<Product> products;

        void addProduct(Product product, int posotita){
            product.setposotita(posotita);
            products.push_back(product);
        }

        void removeProduct(const string& titlos){
            products.erase(remove_if(products.begin(), products.end(), 
            [&](Product& product) {
                return product.gettitlos() == titlos;
                }));

        }

        void updatePosotita(const string& titlos, int newposotita){
            for(auto& product : products){
                if(product.gettitlos() == titlos){
                    product.setposotita(newposotita);
                }
            }
        }

        void displayCart(){
            cout<<endl;
            cout<< "---CART START---" <<endl;
            for(auto& product : products){
                cout<<product.getposotita()<<" "<<product.gettitlos()<<endl;
            }
            cout<<"---CART END---"<<endl;
        }

        double calculatetotal(){
            double total=0;
            for(auto& product : products){
                total+= product.gettimi() * product.getposotita();
            }
            return total;
        }
};


class Order{
    public:
        vector<Product> products;
        double sinolo;

        Order (vector<Product> products1, double sinolo1): products(products1), sinolo(sinolo1){}

        void addproduct(const Product& product){
            products.push_back(product);
        }


        void showOrder(){
            //cout<<endl;
            cout<<"---CART START---"<<endl;
            for (auto& product : products){
                cout<<product.getposotita()<<" "<<product.gettitlos()<<endl;
            }
            cout<<"---CART END---"<<endl;
            cout<<"Total Cost: "<<sinolo<<endl;
            cout<<endl;
        }
};


class Admin: public User{
    public:
        vector<Order> orders;

        Admin(string username, string password) : User(username, password, true) {}

        void addproduct(Eshop& eshop);
        void editproduct(Eshop& eshop);
        void removeproduct(Eshop& eshop);
        void searchproduct(Eshop& eshop);
        void showunavailableprod(Eshop& eshop);
        void showtopprod(Eshop& eshop);
        void showmenu(Eshop& eshop) override;

};


class Customer: public User{
    private:
        string lastdiscountedprod;
    public:
        Cart cart;
        vector <Order> orderHistory;

        Customer (string username1, string password1): User (username1, password1, false){}

        void searchprod(Eshop& eshop);
        void addtocart(Eshop& eshop);
        void updatecart(Eshop& eshop);
        void removefromcart();
        void completeorder(Eshop& eshop);
        void updateproductposotita(Eshop& eshop);
        void vieworderhistory();
        void viewcart();
        void saveorderhistory();
        void loadorderhistory();
        void showmenu(Eshop& eshop) override;

        bool isloyalcustomer() const; 
        bool iskatigoria(Eshop& eshop, string& katigoria, int& requiredposotita) const; 
        bool isproduct(string& producttitlos) const; 
        Product getfavproduct() const;

        string getlastdiscountedprod() const{
            return lastdiscountedprod;
        }
        void setlastdiscountedprod(const string& prod){
            lastdiscountedprod= prod;
        }
        bool loyalcustomerdiscountused;
        bool proddiscountapplied;
};


class Discount{
    public:
        static void applydiscounts(Customer& customer, Eshop& eshop);
        static void applyloyalcustomer(Customer& customer);
        static void applykatigoriadiscount(Customer& customer, Eshop& eshop, const string& katigoria);
        static void applyproddiscount(Customer& customer, const string& producttitlos);
};


class Eshop{
    public:
        vector<Product> products;
        vector<User*> users;
        vector<Order> orders;
        vector<string> katigories;
        vector<string> ipokatigories;
        map<string, vector<string>> katigoriamap;

        Eshop(const string& katigoriesfile, const string& productsfile, const string& usersfile){
            loadkatigories(katigoriesfile);
            loadproducts(productsfile);
            loadusers(usersfile);
        }

        ~Eshop(){
            saveusers("files/users.txt");
            saveproducts("files/products.txt");
        }

        void loadkatigories(const string& filename){
            ifstream arxio(filename);
            string grammi;
            
            while(getline(arxio, grammi)){
                stringstream x(grammi);
                string katigoria;
                string ipokatigoriespart;

                getline(x, katigoria, '(');
                katigoria = katigoria.substr(0, katigoria.find_last_not_of(" ") + 1);

                getline(x, ipokatigoriespart, ')');

                katigories.push_back(katigoria);

                stringstream ipokatstream(ipokatigoriespart);
                string ipokatigoria;
                vector<string>ipokatigories;

                while(getline(ipokatstream, ipokatigoria, '@')){
                    ipokatigoria = ipokatigoria.substr(ipokatigoria.find_first_not_of(" "), ipokatigoria.find_last_not_of(" ") - ipokatigoria.find_first_not_of(" ") + 1);
                    ipokatigories.push_back(ipokatigoria);
                }
                katigoriamap[katigoria]= ipokatigories;
            }
        }

        vector<string> getipokat(const string& katigoria){
            if(katigoriamap.find(katigoria) != katigoriamap.end()){
                return katigoriamap[katigoria];
            }
            return vector<string>();
        }

        void loadproducts(const string& filename){
            ifstream arxio(filename);
            string grammi;

            while(getline(arxio,grammi)){
                stringstream x(grammi);
                string titlos, perigrafi, katigoria, ipokatigoria, unit;
                double timi;
                int posotita;

                getline(x, titlos, '@');
                getline(x, perigrafi, '@');
                getline(x, katigoria, '@');
                getline(x, ipokatigoria, '@');
                x>>timi;
                x.ignore(1, '@');
                getline(x, unit, '@');
                x>>posotita;
                products.push_back(Product(titlos,perigrafi, katigoria, ipokatigoria,timi, unit,posotita));
            }
        }

        void loadusers(const string& filename){
            ifstream arxio(filename);
            string grammi;

            while(getline(arxio,grammi)){
                stringstream x(grammi);
                string username, password;
                bool isAdmin;
                getline(x, username, ',');
                getline(x, password, ',');
                x>>isAdmin;
                
                if(isAdmin){
                    users.push_back(new Admin(username, password));
                } else{
                    users.push_back(new Customer(username, password));
                }
            }
        }

        void saveusers(const string& filename){
            ofstream arxio(filename);
            for(const User* user: users){
                arxio<<user->getusername()<<","<<user->getpassword()<<","<<(user->getisAdmin() ? 1:0)<<endl;
            }
        }

        void saveproducts(const string& filename){
            ofstream arxio(filename);
            for(size_t i=0; i<products.size(); ++i){
                const Product& product= products[i];
                arxio<<product.gettitlos()<<" @ "
                <<product.getperigrafi()<<" @ "
                <<product.getkatigoria()<<" @ "
                <<product.getipokatigoria()<<" @ "
                <<fixed<<setprecision(2)<<product.gettimi()<<" @ "
                <<product.getunit()<<" @ "
                <<product.getposotita();

                if(i != products.size() -1){
                    arxio<<endl;
                }
            }
        }

        User* login(const string& username, const string& password){
            for(User* user: users){
                if(user->getusername() == username &&
                user->getpassword() == password){
                    return user;
                }
            }
            return nullptr;
        }

        bool registeruser(const string& username, const string& password, bool isAdmin){
            for(const User* user: users){
                if(user->getusername() == username){
                    cout<<"Username already exits."<<endl;
                    return false;
                }
            }
            if(isAdmin){
                users.push_back(new Admin(username, password));
            }else{
                users.push_back(new Customer(username, password));
            }
            return true;
        }

        void displayusers(){
            for(const User* user: users){
                cout<<"Username: "<<user->getusername()<<", Admin: "<<(user->getisAdmin() ? "Yes":"No")<<endl;
            }
        }

        void displayproducts(){
            for(const Product& product: products){
                product.show();
            }
        }

        void searchproduct(const string& keyword){
            bool p=false;
            for(const Product& product: products){
                if(product.gettitlos().find(keyword) != string::npos){
                    p=true;
                    product.show();
                }
            }
            if(p==false){
                cout<<"Product not found"<<endl;
            }
            cout<<endl;

        }

        void showallproducts(){
            for(const Product& product: products){
                cout<<"\""<<product.gettitlos()<<"\" ";
            }
            cout<<endl;
        }

    friend class Admin;        

};


void Admin::addproduct(Eshop& eshop){
           string titlos, perigrafi, katigoria, ipokatigoria, unit;
           int posotita;
           double timi;
           cout<<"Give product title: ";
           getline(cin, titlos); 
           cout<<"Give product description: ";
           getline(cin, perigrafi); 

           cout<<"Give one of the following categories: ";
            for (auto cat = eshop.katigories.rbegin(); cat != eshop.katigories.rend(); ++cat) { 
                cout << *cat << " "; 
            }
            cout<<endl; 
            getline(cin, katigoria); 
            vector<string> ipokatigories= eshop.getipokat(katigoria);
            cout<<"Give one of the following subcategories: "; 
            for(const auto& subcat: ipokatigories){
                 cout<<subcat<<" ";
            }
            cout<<endl;
            getline(cin, ipokatigoria);
            cout<<"Give product price: ";
            cin>>timi;
            cin.ignore();
            cout<<"Give measurement type[Kg/Unit]: ";
            cin>>unit;
            cin.ignore();
            cout<<"Give amount of Unit: ";
            cin>>posotita;
            cin.ignore();
            Product newproduct(titlos, perigrafi, katigoria, ipokatigoria, timi, unit, posotita);
            eshop.products.push_back(newproduct);
            cout<<"Product added sucessfully!"<<endl;
}


void Admin::editproduct (Eshop& eshop){
            string titlos;
            cout<<"Enter product title you wish to edit: ";
            cin.ignore();
            getline(cin,titlos);

            bool found= false;
            for (auto& product : eshop.products){
                if(product.gettitlos().find(titlos) != string::npos){
                    string perigrafi, katigoria, ipokatigoria;
                    double timi;
                    int posotita;
                    int choice;
                    string input;

                    cout<<"Enter number of field you want to edit: 1.Title 2.Description 3.Category and Subcategory 4.Price 5.Available Kg 6.Nothing"<<endl;
                    cin>>choice;
                    cin.ignore();
                    Product newproduct= product;

                    switch (choice){
                            case 1:{
                                cout<<"Enter new title: ";
                                getline(cin,titlos);
                                newproduct.settitlos(titlos);
                                break;
                            }
                            case 2: {
                                cout<<"Enter new product description: ";
                                getline(cin,perigrafi);
                                newproduct.setperigrafi(perigrafi);
                                break;
                            }
                            case 3 :{
                                cout<<"Enter new category: ";
                                getline(cin,katigoria);
                                newproduct.setkatigoria(katigoria);
                                cout<<"Enter new subcategory: ";
                                getline(cin,ipokatigoria);
                                newproduct.setipokatigoria(ipokatigoria);
                                break;
                            }
                            case 4 : {
                                cout<<"Enter new price: ";
                                getline(cin,input);
                                timi= stod(input);
                                newproduct.settimi(timi);
                                break;
                            }
                            case 5 : {
                                cout<<"Enter available Kg: ";
                                getline(cin,input);
                                posotita= stoi(input);
                                newproduct.setposotita(posotita);
                                break;
                            }
                            case 6 : {
                                break;
                            }
                            default:
                                cout <<"Invalid choice"<<endl;
                        }
                    product= newproduct;
                    found=true;
                    cout<<"Product updated!"<<endl;
                    break;
                }
            }
            if (found) { 
                ofstream arxio("files/products.txt"); 
                if (arxio.is_open()) { 
                    for (const auto& product : eshop.products) { 
                        arxio<<product.gettitlos()<<" @ " 
                        <<product.getperigrafi()<<" @ " 
                        <<product.getkatigoria()<<" @ " 
                        <<product.getipokatigoria()<<" @ " 
                        <<fixed<<setprecision(2)<<product.gettimi()<<" @ " 
                        <<product.getunit()<<" @ " 
                        <<product.getposotita()<<endl; 
                    }arxio.close(); 
                }
            }
}


void Admin::removeproduct(Eshop& eshop){
            string titlos;
            cout<<"Enter product title you wish to remove: ";
            getline(cin, titlos);

            auto at= remove_if(eshop.products.begin(), eshop.products.end(), [&](Product& product){ 
                return product.gettitlos() == titlos;
            });
            if(at!= eshop.products.end()){
                eshop.products.erase(at, eshop.products.end());
                cout<<"Product removed!"<<endl;
            } else{
                cout<<"Product not found!"<<endl;
            }
}


void Admin::searchproduct(Eshop& eshop){
    cout<<endl;
    cout<<"Product Search Options:"<<endl;
    cout<<"1. Search for a specific product (by title)."<<endl;
    cout<<"2. View the products of a specific category."<<endl;
    cout<<"3. View the products of a specific title and category."<<endl;
    cout<<"4. Show all the available products."<<endl;
    int choice;
    cin>>choice;
            
    if (choice==1) {
        cout<<"Enter a title to search: ";
        cin.ignore();
        string titlos;
        getline(cin,titlos);
        bool found=false;

        for (const Product& product : eshop.products){
            if (product.gettitlos().find(titlos) != string::npos){
                found=true;
                product.show();
                cout<<endl;
            }
        }
        if (!found){
            cout<<"Product not found"<<endl;
        }
    }
    else if (choice==2) {
        cout<<"Enter a category to search: ";
        cin.ignore();
        string katigoria;
        getline(cin,katigoria);
        cout<<"Do you want to specify a subcategory? (yes/no): ";
        string response;
        getline(cin,response);
        bool found=false;

        if(response == "yes"){
            cout<<"Enter a subcategory to search: ";
            string ipokatigoria;
            getline(cin,ipokatigoria);
            for(const Product& product: eshop.products){
                if(product.getkatigoria().find(katigoria) != string::npos &&
                    product.getipokatigoria().find(ipokatigoria) != string::npos){
                    found=true;
                    product.show();
                    cout<<endl;    
                }
            }
        } else if(response =="no"){
            for(const Product& product: eshop.products){
                if(product.getkatigoria().find(katigoria) != string::npos){
                    found= true;
                    product.show();
                    cout<<endl;
                }
            }
        }
        if (!found){
            cout<<"No products found in this category"<<endl;
        }
    }
    else if (choice==3){
        cout<<"Enter a title to search: ";
        cin.ignore();
        string katigoria,titlos;
        getline(cin,titlos);
        cout<<"Enter a category to search: ";
        cin.ignore();
        getline(cin,katigoria);
        bool found= false;

        for(const Product& product: eshop.products){
            if(product.getkatigoria().find(katigoria) != string::npos &&
                product.gettitlos().find(titlos) != string::npos){
                found=true;
                product.show();
                cout<<endl;                
            }
        }
        if (!found){
            cout<<"Product not found"<<endl;
        }
    }
    else if(choice==4){
        cout<<"Results: ";
        eshop.showallproducts();
        cout<<"Select a product title: ";
        cin.ignore();
        string keyword;
        getline(cin, keyword);
        bool found=false;

        for(const Product& product: eshop.products){
            if(product.gettitlos().find(keyword) != string::npos){
                found=true;
                product.show();
                cout<<endl;
            }
        }
        if(found==false){
            cout<<"Product not found!"<<endl;
        }
    }
}


void Admin::showunavailableprod(Eshop& eshop){
    cout<<"Unavailable Products: "<<endl;
            for(const auto& product : eshop.products){
                if(product.getposotita() == 0){
                    product.show();
                    cout<<endl;
                }
            }
}


void Admin::showtopprod(Eshop& eshop) {
    map<string, int> ProdCounts;
    for (const auto& user: eshop.users){
        if (!user->getisAdmin()){
            Customer* customer=dynamic_cast<Customer*>(user);
            customer->loadorderhistory();
            for (const auto& order : customer->orderHistory) {
                set<string> uniqueProducts;
                for (const auto& product : order.products) { 
                    uniqueProducts.insert(product.gettitlos());
                }
                for(const auto& productTitle : uniqueProducts){
                    ProdCounts[productTitle]++;
                } 
            } 
        }
    } 
    vector<pair<string, int>> product_vector(ProdCounts.begin(), ProdCounts.end());
    sort(product_vector.begin(), product_vector.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return b.second < a.second; 
    });

    cout << "Top products:" << endl; 
    for (int i = 0; i < static_cast<int>(product_vector.size()); ++i) { 
        cout << (i + 1) << ". " << product_vector[i].first << " " << product_vector[i].second << endl; 
    }
    cout<<endl;
}


void Admin::showmenu(Eshop& eshop){

            while(true){
                cout<<"---Admin Menu---"<<endl;
                cout<<"1. Add Product"<<endl;
                cout<<"2. Edit Product"<<endl;
                cout<<"3. Remove Product"<<endl;
                cout<<"4. Search Product"<<endl;
                cout<<"5. Show Unavailable Products"<<endl;
                cout<<"6. Show Top 5 Products"<<endl;
                cout<<"7. Exit"<<endl;
                cout<<"Enter choice: ";
                int choice;
                cin>>choice;
                cin.ignore();

                switch (choice){
                    case 1 : {
                        addproduct(eshop);
                        break;
                    }
                    case 2 : {
                        editproduct(eshop);
                        break;
                    }
                    case 3 : {
                        removeproduct(eshop);
                        break;
                    }
                    case 4 : {
                        searchproduct(eshop);
                        break;
                    }
                    case 5 : {
                        showunavailableprod(eshop);
                        break;
                    }
                    case 6 : {
                        showtopprod(eshop);
                        break;
                    }
                    case 7 : {
                        cout<<"Goodbye!"<<endl;
                        return;
                    }
                    default :
                        cout<<"Invalid choice!"<<endl;
                } 
            }
}


void Customer::searchprod(Eshop& eshop){
            cout<<endl;
            cout<<"Product Search Options:"<<endl;
            cout<<"1. Search for a specific product (by title)."<<endl;
            cout<<"2. View the products of a specific category."<<endl;
            cout<<"3. Show all the available products."<<endl;
            int choice;
            cin>>choice;
            
                if (choice==1) {
                    cout<<"Enter a title to search: ";
                    cin.ignore();
                    string titlos;
                    getline(cin,titlos);
                    bool found=false;
                    for (const Product& product : eshop.products){
                            if (product.gettitlos().find(titlos) != string::npos){
                                found=true;
                                product.show();
                                cout<<endl;
                            }
                    }
                    if (!found){
                        cout<<"Product not found"<<endl;
                    }
                }
                else if (choice==2) {
                    cout<<"Enter a category to search: ";
                    cin.ignore();
                    string katigoria;
                    getline(cin,katigoria);
                    cout<<endl;
                    bool found=false;
                    for(const Product& product: eshop.products){
                        if(product.getkatigoria().find(katigoria) != string::npos){
                            product.show();
                            cout<<endl;
                        }
                    }
                    if (!found){
                        cout<<"Product not found"<<endl;
                    }
                }
                else if (choice==3){
                    cout<<"Results: ";
                    eshop.showallproducts();
                    cout<<"Select a product title: ";
                    cin.ignore();
                    string keyword;
                    getline(cin, keyword);
                    bool p;
                    for(const Product& product: eshop.products){
                        if(product.gettitlos().find(keyword) != string::npos){
                            p=true;
                            product.show();
                            cout<<endl;
                        }
                    }
                    if(p==false){
                        cout<<"Product not found!"<<endl;
                    }
                }
}


void Customer::addtocart (Eshop& eshop){
            string titlos;
            int posotita;
            cout<<"Which product do you want to add? ";
            cin.ignore();
            getline(cin,titlos);
            bool p;

            cout<<"Enter quantity: ";
            cin>>posotita;

            for(const auto& product: eshop.products){
                if(product.gettitlos().find(titlos) != string::npos){
                    p=true;
                    Product newproduct= product;
                    newproduct.setposotita(posotita);
                    cart.addProduct(newproduct, posotita);
                    }
            }
            if(p==false){
                cout<<"Product not found!"<<endl;
            }
            cout<<endl;
}


void Customer::updatecart(Eshop& eshop){
            string titlos;
            int newposotita;

            cout<<"Which product do you want to update? ";
            getline(cin,titlos);

            cout<<"Enter new quantity: ";
            cin>>newposotita;

            for(const auto& product : cart.products){
                if(product.gettitlos().find(titlos) != string::npos){
                    for(const auto& eshopproduct : eshop.products){
                        if(eshopproduct.gettitlos().find(product.gettitlos()) != string::npos){
                            if(newposotita <= eshopproduct.getposotita()){
                                cart.updatePosotita(product.gettitlos(), newposotita);
                            } else{
                                cout<<"The requested quantity is not available. Available quantity: "<<eshopproduct.getposotita()<<endl;
                            }
                            break;
                        }
                    }
                    break;
                }
            }
            cout<<endl;
}


void Customer::removefromcart(){
            string titlos;
            cout<<"Which product do you want to remove from your cart? ";
            getline(cin,titlos);
            cart.removeProduct(titlos);
            cout<<endl;
}


void Customer::completeorder(Eshop& eshop){
    cout << "Cart before discounts: " << endl; 
    viewcart();

            double total= cart.calculatetotal();
            Discount::applydiscounts(*this,eshop);

            cout << "Cart after discounts: " << endl; 
            viewcart();

            total=cart.calculatetotal();
            orderHistory.push_back(Order(cart.products, total));
            updateproductposotita(eshop);
            cart.products.clear();
            saveorderhistory();
            //if(!cart.products.empty()){
            //    lastdiscountedprod= cart.products[0].gettitlos();
            //}
            cout<<"Order Completed!"<<endl;
            cout<<endl;

            loyalcustomerdiscountused= false;
            proddiscountapplied= false;
}

void Customer::updateproductposotita(Eshop& eshop){
    for(auto& product : cart.products){
        for(auto& eshopproduct : eshop.products){
            if(eshopproduct.gettitlos().find(product.gettitlos()) != string::npos){
                int newposotita= eshopproduct.getposotita()- product.getposotita();
                eshopproduct.setposotita(newposotita);
                break;
            }
        }
    }

    ofstream productsfile("files/products.txt");
    for(const auto& product : eshop.products){
        productsfile<<product.gettitlos()<<" @ "
        <<product.getperigrafi()<<" @ "
        <<product.getkatigoria()<<" @ "
        <<product.getipokatigoria()<<" @ "
        <<fixed<<setprecision(2)<<product.gettimi()<<" @ "
        <<product.getunit()<<" @ "
        <<product.getposotita()<<endl;
    }
    productsfile.close();
}


void Customer::vieworderhistory(){
    for(size_t i=0; i<orderHistory.size(); i++){
        cout<<"---CART "<<i+1<<" START---"<<endl;
            for (auto& product: orderHistory[i].products){
                cout<<product.getposotita()<<" "<<product.gettitlos()<<endl;
            }
        cout<<"---CART "<<i+1<<" END---"<<endl;
        cout<<"Total Cost: "<<orderHistory[i].sinolo<<endl;
        cout<<endl;
    }
}


void Customer::viewcart(){
            cart.displayCart();
            cout<<"Total Cost: "<<cart.calculatetotal()<<endl;
            cout<<endl;
}


void Customer::saveorderhistory(){
    ofstream arxio("files/order_history/" + getusername() + "_history.txt");
    for(size_t i=0; i<orderHistory.size(); i++){
        if(i>0){
            arxio<<endl;
        }
        arxio<<"---CART "<<i+1<<" START---"<<endl;
        for(auto& product : orderHistory[i].products){
            arxio<<product.getposotita()<<" "<<product.gettitlos()<<endl;
        }
        arxio<<"---CART "<<i+1<<" END---"<<endl;
        arxio<<"Total Cost: "<<orderHistory[i].sinolo;
        if(i < orderHistory.size() -1){
            arxio<<endl;
        }
    }
}


void Customer::loadorderhistory(){
    ifstream arxio("files/order_history/" + getusername() + "_history.txt");
    string grammi;
    while(getline(arxio,grammi)){
        if(grammi.find("---CART") != string::npos){
            vector<Product> products;
            double totalcost=0;
            while(getline(arxio,grammi) && grammi.find("Total Cost:") == string::npos){
                if(grammi.find("---CART") != string::npos) continue;
                stringstream x(grammi);
                int posotita;
                string titlos;
                x>>posotita;
                getline(x,titlos);
                if(!titlos.empty() && titlos[0] == ' ') titlos.erase(0,1);
                products.push_back(Product(titlos, "", "", "", 0.0, "", posotita));
            }
            stringstream x(grammi);
            string temp;
            x>>temp>>temp>>totalcost;
            orderHistory.push_back(Order(products, totalcost));
        }
    }
}


void Customer::showmenu(Eshop& eshop){
            while(true){
                cout<<"---Customer Menu---"<<endl;
                cout<<"1. Search for a product"<<endl;
                cout<<"2. Add product to cart"<<endl;
                cout<<"3. Update product from cart"<<endl;
                cout<<"4. Remove product from cart"<<endl;
                cout<<"5. Complete order"<<endl;
                cout<<"6. View order history"<<endl;
                cout<<"7. View cart"<<endl;
                cout<<"8. Exit"<<endl;

                cout<<"Enter your choice: ";
                int choice;
                cin>>choice;
                cin.ignore();

                switch (choice) {
                    case 1 : {
                        searchprod(eshop);
                        break;
                    }
                    case 2 : {
                        addtocart(eshop);
                        break;
                    }
                    case 3 : {
                        updatecart(eshop);
                        break;
                    }
                    case 4 : {
                        removefromcart();
                        break;
                    }
                    case 5 : {
                        completeorder(eshop);
                        break;
                    }
                    case 6 : {
                        vieworderhistory();
                        break;
                    }
                    case 7 : {
                        viewcart();
                        break;
                    }
                    case 8 : {
                        cout<<"Goodbye!"<<endl;
                        return;
                    }
                    default :
                        cout<<"Invalid choice!"<<endl;
                }
            }
}


bool Customer::isloyalcustomer() const{ 
    return orderHistory.size() >= 5 && !loyalcustomerdiscountused; 
}


bool Customer::iskatigoria(Eshop& eshop, string& katigoria, int& requiredposotita) const{ 
    ifstream discountsfile("files/discounts.txt"); 
    if(!discountsfile){ 
        cout<<"Error loading discounts file"<<endl; 
        return false; 
    } 
    map<string, int> katigoriaepipedo; 
    string grammi; 
    while(getline(discountsfile, grammi)){ 
        stringstream x(grammi); 
        string cat; 
        int epipedo; 
        x>>katigoria>>epipedo; 
        katigoriaepipedo[cat]= epipedo; 
    } 
    for(const auto& [cat, epipedo] : katigoriaepipedo){ 
        int totalposotita = 0; 
        for(const auto& order : orderHistory){ 
            for(const auto& product : order.products){ 
                if (product.getkatigoria().find(cat) != string::npos){ 
                    totalposotita += product.getposotita();
                }
            } 
        } 
        if(totalposotita >= epipedo && !proddiscountapplied){ 
            katigoria= cat; 
            requiredposotita= epipedo; 
            return true; 
        } 
    } 
    return false; 
}

                        
bool Customer::isproduct(string& producttitlos) const{
    if(orderHistory.size() <3){ 
        return false; 
    }
    int sinexomenesorders=0;
    for(size_t i= orderHistory.size() -3; i<orderHistory.size(); ++i){ 
        const auto& lastorderprod= orderHistory[i].products;
        if(find_if(lastorderprod.begin(), lastorderprod.end(), [&producttitlos](const Product& product){ 
            return (product.gettitlos().find(producttitlos) != string::npos); }
            ) != lastorderprod.end()){ 
                sinexomenesorders++;
            } else{
                return false;
            }
    } 
    //return !proddiscountapplied;
    cout << "consecutiveOrders: " << sinexomenesorders << endl;
    return sinexomenesorders == 3;
} 


Product Customer::getfavproduct() const{ 
    map<string, int> plithos; 
    for(const auto& order : orderHistory){ 
        for(const auto& product : order.products){ 
            plithos[product.gettitlos()] += product.getposotita(); 
        }
    }

    string favprodtitlos; 
    int max= 0; 
    for(const auto& isodos : plithos){ 
        if(isodos.second > max){ 
            favprodtitlos= isodos.first; 
            max= isodos.second; 
        } 
    } 
    for(const auto& order : orderHistory){ 
        for(const auto& product : order.products){ 
            if(product.gettitlos().find(favprodtitlos) != string::npos){ 
                return product; 
            }
        }
    }
    return Product(); 
}


void Discount::applydiscounts(Customer& customer, Eshop& eshop){
    string katigoria;
    int requiredposotita;
    string producttitlos= customer.getlastdiscountedprod();
cout << "Checking discounts..." <<endl;
    if(customer.isloyalcustomer()){
        cout << "Applying loyal customer discount..." <<endl;
        applyloyalcustomer(customer);
        customer.loyalcustomerdiscountused= true;
    }else if(customer.iskatigoria(eshop,katigoria,requiredposotita)){
        cout << "Applying category discount..." <<endl;
        applykatigoriadiscount(customer, eshop,katigoria);
    }else if(customer.isproduct(producttitlos)){
        cout << "Applying product discount..." <<endl;
        applyproddiscount(customer, producttitlos);
        customer.setlastdiscountedprod(producttitlos);
        customer.proddiscountapplied= true;
    }
}


void Discount::applyloyalcustomer(Customer& customer) {
    Product favprod= customer.getfavproduct();
    if(customer.loyalcustomerdiscountused == false){
        cout<<"You get a 40% discount on your favorite product: "<<favprod.gettitlos()<<endl;
        for(auto& product : customer.cart.products){
            if(product.gettitlos().find(favprod.gettitlos()) != string::npos){
                product.settimi(product.gettimi() * 0.60);
                break;
            }
        }
        customer.loyalcustomerdiscountused= true;
    }
}


void Discount::applykatigoriadiscount(Customer& customer, Eshop& eshop, const string& katigoria) {
    vector<Product> katigoriaprod;
    for(const auto& product : eshop.products){
        if(product.getkatigoria().find(katigoria) != string::npos){
            katigoriaprod.push_back(product);
        }
    }

    if(customer.proddiscountapplied==false){
        Product& discountedprod= katigoriaprod[rand() % katigoriaprod.size()];
        cout<<"You get a 30% discount on a random product from the same category: "<<discountedprod.gettitlos()<<endl;
        for(auto& product : customer.cart.products){
            if(product.gettitlos().find(discountedprod.gettitlos()) != string::npos){
                product.settimi(product.gettimi() * 0.70);
                break;
            }
        }
        customer.proddiscountapplied= true;
    }
}


void Discount::applyproddiscount(Customer& customer, const string& producttitlos) {
    cout<<"You get a 20% discount on the same product: "<<producttitlos<<endl;
    for(auto& product : customer.cart.products){
        if(product.gettitlos().find(producttitlos) != string::npos){
            product.settimi(product.gettimi() * 0.80);
            break;
        }
    }
    customer.proddiscountapplied= true;
}


int main(){
    Eshop myeshop("files/categories.txt", "files/products.txt", "files/users.txt");
    
    cout<<"Welcome to the e-shop!!!"<<endl;
    cout<<"Do you want to login or register? (enter option): ";
    string epilogi;
    cin>>epilogi;
    cin.ignore();

    if(epilogi == "login"){
        string username, password;

        cout<<"Please enter your username: ";
        getline(cin, username);

        cout<<"Please enter your password: ";
        getline(cin, password);

        User* loggeduser= myeshop.login(username, password);
        if(loggeduser){
            if(Customer* customer= dynamic_cast<Customer*>(loggeduser)){
                cout<<endl;            
                cout<<"Welcome "<<loggeduser->getusername()<<"!"<<endl;
                cout<<endl;
                customer->loadorderhistory();
                customer->showmenu(myeshop);
            } else if(Admin* admin= dynamic_cast<Admin*>(loggeduser)){
                cout<<"Welcome "<<loggeduser->getusername()<<"!"<<endl;
                admin->showmenu(myeshop);
            }
        } else{
            cout<<"Login failed! Incorrect username or password."<<endl;
        }
    }else if(epilogi == "register"){
        string username, password;
        bool isAdmin;

        cout<<"Please enter your username: ";
        cin>>username;
        cout<<"Please enter your password: ";
        cin>>password;
        cout<<"Are you an admin user? (Y/N): ";
        char adminchoice;
        cin>>adminchoice;
        cin.ignore();

       isAdmin = (adminchoice == 'Y' || adminchoice == 'y');

        if(myeshop.registeruser(username, password, isAdmin)){
            cout<<"Thanks for signing up! You are automatically logged-in as "<<username<<endl;
            cout<<endl;
            
            User* newuser= myeshop.login(username, password);

            if(newuser && !isAdmin){
                Customer* customer= dynamic_cast<Customer*>(newuser);
                if(customer){
                    newuser->showmenu(myeshop);
                }
            } else if(newuser && isAdmin){
                Admin* admin= dynamic_cast<Admin*>(newuser);
                if(admin){
                    admin->showmenu(myeshop);
                }
            }
        } else{
            cout<<"User registration failed!"<<endl;
        }
    }
    else{
        cout<<"Invalid option!"<<endl;
    }
    return 0;
}