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

        //Συναρτηση για αφαιρεση εξτρα κενων χαρακτηρων, για να περνουν τα τεστς
        string kena(const string& s) const { 
            size_t first = s.find_first_not_of(' '); 
            if (first == string::npos) return ""; 
            size_t last = s.find_last_not_of(' '); 
            return s.substr(first, last - first + 1); 
        }

    public:
        //Constructor για αρχικοποιηση μεταβλητων
        Product(string titlos1, string perigrafi1, string katigoria1, string ipokatigoria1, double timi1, string unit1, int posotita1)
            : titlos(titlos1), perigrafi(perigrafi1), katigoria(katigoria1), ipokatigoria(ipokatigoria1), timi(timi1), unit(unit1), posotita(posotita1) {}

        //Getters
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

        //Setters
        void settitlos(const string& newtitlos){
            titlos= newtitlos;
        }
        void setperigrafi(const string& newperigrafi){
            perigrafi= newperigrafi;
        }
        void setkatigoria(const string& newkatigoria){
            katigoria= newkatigoria;
        }
        void setipokatigoria(const string& newipokatigoria){
            ipokatigoria= newipokatigoria;
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

        //Συναρτηση για εμφανιση πληροφοριων
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
        //Constructor και χρηση initializer list για αρχικοποιηση των μελων
        User(string username1, string password1, bool isAdmin1) 
        : username(username1), password(password1) , isAdmin(isAdmin1) {}
        
        //Getters
        string getusername()const{
            return username;
        }
        string getpassword()const{
            return password;
        }
        bool getisAdmin()const{
            return isAdmin;
        }

        //Συναρτηση για εμφανιση του μενου στον χρηστη 
        virtual void showmenu(Eshop& eshop,const string& filename) =0;
};


class Cart{
    public:
        vector<Product> products; //Λιστα προιοντων στο καλαθι

        //Προσθηκη προιοντος και ζητουμενης ποσοτητας στο καλαθι
        void addProduct(Product product, int posotita){
            product.setposotita(posotita);
            products.push_back(product);
        }

        //Αφαιρεση προιοντος απο το καλαθι
        void removeProduct(const string& titlos){
            products.erase(remove_if(products.begin(), products.end(), 
            [&](Product& product) {
                return product.gettitlos() == titlos;
                }));

        }

        //Ενημερωση ποσοτητας προιοντος στο καλαθι
        void updatePosotita(const string& titlos, int newposotita){
            for(auto& product : products){
                if(product.gettitlos() == titlos){
                    product.setposotita(newposotita);
                }
            }
        }

        //Εμφανιση καλαθιου
        void displayCart(){
            cout<<endl;
            cout<< "---CART START---" <<endl;
            for(auto& product : products){
                cout<<product.getposotita()<<" "<<product.gettitlos()<<endl;
            }
            cout<<"---CART END---"<<endl;
        }

        //Συναρτηση που επιστρεφει το συνολικο κοστος του καλαθιου
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
        vector<Product> products; //Λιστα προιοντων της παραγγελιας
        double sinolo;

        //Constructor για αρχικοποιηση μεταβλητων παραγγελιας
        Order (vector<Product> products1, double sinolo1): products(products1), sinolo(sinolo1){}

        //Προσθηκη προιοντων
        void addproduct(const Product& product){
            products.push_back(product);
        }

        //Συναρτηση για εμφανιση προιοντων και συνολικου κοστους
        void showOrder(){
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
        //Λιστα πραγγελιων
        vector<Order> orders;

        Admin(string username, string password) : User(username, password, true) {}

        void addproduct(Eshop& eshop);
        void editproduct(Eshop& eshop, const string& filename);
        void removeproduct(Eshop& eshop);
        void searchproduct(Eshop& eshop);
        void showunavailableprod(Eshop& eshop);
        void showtopprod(Eshop& eshop);
        void showmenu(Eshop& eshop, const string& filename) override;

};


class Customer: public User{
    public:
        Cart cart; //Καλαθι του πελατη
        vector <Order> orderHistory; //Ιστορικο παραγγελιων του πελατη

        //Constructor και χρηση initializer list για αρχικοποιηση των μελων
        Customer (string username1, string password1): User (username1, password1, false){}

        void searchprod(Eshop& eshop);
        void addtocart(Eshop& eshop);
        void updatecart(Eshop& eshop);
        void removefromcart();
        void completeorder(Eshop& eshop,const string& filename);
        void updateproductposotita(Eshop& eshop,const string& filename);
        void vieworderhistory();
        void viewcart();
        void saveorderhistory();
        void loadorderhistory();
        void showmenu(Eshop& eshop,const string& filename) override;

        //Συναρτησεις για το συστημα εκπτωσεων
        bool ekptosi(const string& producttitlos) const;
        bool ekptosikatigorias(const string& katigoria, int epipedo) const;
        bool pistospelatis() const;
        string getfavouriteprod() const;
        double totalwithdiscounts(Customer& customer , const vector<Product>& cartprod, const map<string, int>& discounts);

};

//Συναρτηση για αναγνωση εκπτωσεων απο αρχειο και αποθηκευση σε map
map<string, int> readdiscounts() {
    map<string, int> discounts; //Map στο οποιο θα αποθηκευτουν οι εκπτωσεις
    ifstream file("files/discounts.txt");
    string grammi;
    while (getline(file, grammi)) {
        stringstream x(grammi);
        string katigoria;
        char space;
        int posotita;
        if (x>>katigoria>>space>>posotita) {
            discounts[katigoria] = posotita;//Aποθηκευση εκπτωσης στο map 
        }
    }
    return discounts; //Επιστροφη map με εκπτωσεις
}


class Eshop{
    public:
        vector<Product> products; //Λιστα προιοντων
        vector<User*> users; //Λιστα χρηστων
        vector<Order> orders; //Λιστα παραγγελιων
        vector<string> katigories; //Λιστα κατηγοριων προιοντων
        vector<string> ipokatigories; //Λιστα υποκατηγοριων προιοντων
        map<string, vector<string>> katigoriamap; //Χαρτης κατηγοριων και υποκατηγοριων

        //Φορτωση κατηγοριων και υποκατηγοριων απο ενα αρχειο
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
                    ipokatigoria = ipokatigoria.substr(ipokatigoria.find_first_not_of(" "), 
                                ipokatigoria.find_last_not_of(" ") - ipokatigoria.find_first_not_of(" ") + 1);
                    ipokatigories.push_back(ipokatigoria);
                }
                katigoriamap[katigoria]= ipokatigories;
            }
        }

        //Ληψη υποκατηγοριων για μια δεδομενη κατηγορια
        vector<string> getipokat(const string& katigoria){
            if(katigoriamap.find(katigoria) != katigoriamap.end()){
                return katigoriamap[katigoria];
            }
            return vector<string>();
        }

        //Φορτωση προιοντων απο ενα αρχειο
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

        //Φορτωση χρηστων απο ενα αρχειο
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

        //Αποθηκευση χρηστων σε ενα αρχειο
        void saveusers(const string& filename){
            ofstream arxio(filename);
            for(const User* user: users){
                arxio<<user->getusername()<<","<<user->getpassword()<<","<<(user->getisAdmin() ? 1:0)<<endl;
            }
        }

        //Αποθηκευση προιοντων σε ενα αρχειο
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

        //Συνδεση υπαρχων χρηστη στο καταστημα
        User* login(const string& username, const string& password){
            for(User* user: users){
                if(user->getusername() == username &&
                    user->getpassword() == password){
                    return user;
                }
            }
            return nullptr;
        }

        //Εγγραφη καινουργιου χρηστη
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

        //Εμφανιση ολων των χρηστων
        void displayusers(){
            for(const User* user: users){
                cout<<"Username: "<<user->getusername()<<", Admin: "<<(user->getisAdmin() ? "Yes":"No")<<endl;
            }
        }

        //Εμφανιση ολων των προιοντων
        void displayproducts(){
            for(const Product& product: products){
                product.show();
            }
        }

        //Εμφανιση ολων των τιτλων των προιοντων
        void showallproducts(){
            for(const Product& product: products){
                cout<<"\""<<product.gettitlos()<<"\" ";
            }
            cout<<endl;
        }

    //Κλαση φιλη για να εχει προσβαση στα ιδιωτικα μελη της βασικης κλασης
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

            //Εμφανιση των διαθεσιμων κατηγοριων για να διαλεξει ο χρηστης μια
            cout<<"Give one of the following categories: ";
            for (auto cat = eshop.katigories.rbegin(); cat != eshop.katigories.rend(); ++cat) { 
                cout << *cat << " "; 
            }
            cout<<endl; 
            getline(cin, katigoria);

            //Παιρνουμε τις υποκατηγοριες της επιλεγμενης κατηγοριας
            vector<string> ipokatigories= eshop.getipokat(katigoria);
            //Εμφανιζει τις υποκατηγοριες για να διαλεξει ο χρηστης μια
            cout<<"Give one of the following subcategories: "; 
            for(const auto& subcat: ipokatigories){
                 cout<<subcat<<" ";
            }
            cout<<endl;
            getline(cin, ipokatigoria);
            cout<<"Give product price: ";
            cin>>timi;
            cout<<"Give measurement type[Kg/Unit]: ";
            cin>>unit;
            cout<<"Give amount of Unit: ";
            cin>>posotita;
            //Δημιουργια νεου αντικειμενου με τις τιμες που δινει ο χρηστης
            Product newproduct(titlos, perigrafi, katigoria, ipokatigoria, timi, unit, posotita);
            //Προσθετουμε το νεο προιον στην λιστα προιοντων
            eshop.products.push_back(newproduct);
            cout<<"Product added sucessfully!"<<endl;
}


void Admin::editproduct (Eshop& eshop, const string& filename){
            string titlos;
            cout<<"Enter product title you wish to edit: ";
            getline(cin,titlos);

            bool found= false;
            //Αναζητηση προιοντος στην λιστα του eshop
            for (auto& product : eshop.products){
                //Ελεγχος αν ο τιτλος προιοντος περιεχει τον τιτλο που εδωσε ο χρηστης
                if(product.gettitlos().find(titlos) != string::npos){
                    string perigrafi, katigoria, ipokatigoria;
                    double timi;
                    int posotita;
                    int choice;
                    string input;

                    cout<<"Enter number of field you want to edit: 1.Title 2.Description 3.Category and Subcategory 4.Price 5.Available Kg 6.Nothing"<<endl;
                    cin>>choice;
                    cin.ignore();
                    Product newproduct= product; //Δημιουργια αντιγραφου του προιοντος

                    //Επιλογες του χρηστη για επεξεργασια προιοντος
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
                    product= newproduct; //Ενημερωση προιοντος στη λιστα
                    found=true;
                    cout<<"Product updated!"<<endl;
                    break;
                }
            }
            if (found) {
                //Ενημερωση του αρχειου με τα προιοντα
                ofstream arxio(filename); 
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

            //Αναζητηση προιοντος στη λιστα, επιστρεφουμε τον iterator εκει που βρεθηκε
            auto at= remove_if(eshop.products.begin(), eshop.products.end(), [&](Product& product){ 
                return product.gettitlos() == titlos;
            });
            //Αν βρεθηκε, διαγραφη του προιοντος απο τη λιστα
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
    cout<<"3. Show all the available products."<<endl;
    int choice;
    cin>>choice;

    //Αναζητηση βασει τιτλου    
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
    //Αναζητηση βασει κατηγοριας
    else if (choice==2) {
        cout<<"Enter a category to search: ";
        cin.ignore();
        string katigoria;
        getline(cin,katigoria);
        cout<<"Do you want to specify a subcategory? (yes/no): ";
        string response;
        getline(cin,response);
        bool found=false;

        //Αναζητηση βασει κατηγοριας-υποκατηγοριας
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
            //Αναζητηση βασει μονο κατηγοριας
        } else if(response == "no"){
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
    //Αναζητηση βασει ολων των προιοντων
    else if (choice==3){
        cout<<"Results: ";
        eshop.showallproducts(); //εμφανιση ολων των προιοντων
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
    bool p=false;

    //Ελεγχος των προιοντων με μηδενικη ποσοτητα
    for(const auto& product : eshop.products){
        if(product.getposotita() == 0){
            p=true;
            product.show(); //Εμφανιση λεπτομεριων προιοντος
            cout<<endl;
        }
    }
    //Μηνυμα αν δεν υπαρχουν μη-διαθεσιμα
    if(p==false){
        cout<<"They are no unavailable products!"<<endl;
        cout<<endl;
    }
}


void Admin::showtopprod(Eshop& eshop) {
    map<string, int> ProdCounts;

    //Μετρουμε τα προιοντα στις παραγγελιες ολων των πελατων
    for (const auto& user: eshop.users){
        if (!user->getisAdmin()){
            Customer* customer=dynamic_cast<Customer*>(user);
            customer->loadorderhistory();//Φορτωση ιστορικου παραγγελιων
            //Για καθε παραγγελια πελατη
            for (const auto& order : customer->orderHistory) {
                set<string> uniqueProducts;
                //Καταγραφουμε τους μοναδικους τιτλους στην παραγγελια
                for (const auto& product : order.products) { 
                    uniqueProducts.insert(product.gettitlos());
                }
                for(const auto& productTitle : uniqueProducts){
                    ProdCounts[productTitle]++;
                } 
            } 
        }
    } 
    //Αποθηκευση προιοντων και των μετρητων τους
    vector<pair<string, int>> product_vector(ProdCounts.begin(), ProdCounts.end());
    //Ταξινομηση προιοντων κατα ποσο εμφανιζονται
    sort(product_vector.begin(), product_vector.end(), [](const pair<string, int>& a, const pair<string, int>& b) {
        return b.second < a.second; 
    });

    cout<<"Top 5 products:"<<endl; 
    for(int i = 0; i < min(5,static_cast<int>(product_vector.size())); ++i) { 
        cout<<(i+1)<<". "<<product_vector[i].first<<" "<<product_vector[i].second<<endl; 
    }
    cout<<endl;
}


void Admin::showmenu(Eshop& eshop, const string& filename){
            while(true){
                //Εμφανιση μενου για τον διαχειριστη
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
                cin.ignore(); //Αφαιρεση χαρακτηρα νεας γραμμης

                switch (choice){
                    case 1 : {
                        //Προσθηκη προιοντος
                        addproduct(eshop);
                        break;
                    }
                    case 2 : {
                        //Επεξεργασια προιοντος
                        editproduct(eshop,filename);
                        break;
                    }
                    case 3 : {
                        //Διαγραφη προιοντος
                        removeproduct(eshop);
                        break;
                    }
                    case 4 : {
                        //Αναζητηση προιοντος
                        searchproduct(eshop);
                        break;
                    }
                    case 5 : {
                        //Μη-διαθεσιμα προιοντα
                        showunavailableprod(eshop);
                        break;
                    }
                    case 6 : {
                        //5 κορυφαια προιοντα
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
            //Εμφανιση μενου επιλογων για αναζητηση 
            cout<<"Product Search Options:"<<endl;
            cout<<"1. Search for a specific product (by title)."<<endl;
            cout<<"2. View the products of a specific category."<<endl;
            cout<<"3. Show all the available products."<<endl;
            int choice;
            cin>>choice;
            
                if (choice==1) {
                    //Αναζητηση συγκεκριμενου προιοντος βασει τιτλου
                    cout<<"Enter a title to search: ";
                    cin.ignore(); //Αφαιρεση χαρακτηρα νεας γραμμης
                    string titlos;
                    getline(cin,titlos);
                    bool found=false;
                    //Αναζητηση προιοντος στo Eshop 
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
                    //Αναζητηση προιοντων συγκεκριμενης κατηγοριας
                    cout<<"Enter a category to search: ";
                    cin.ignore();
                    string katigoria;
                    getline(cin,katigoria);
                    cout<<"Do you want to specify a subcategory? (yes/no): ";
                    string response;
                    getline(cin,response);
                    bool found=false;

                    if(response == "yes"){
                        //Αναζητηση προιοντων συγκεκριμενης κατηγοριας και υποκατηγοριας
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
                    } else if(response == "no"){
                        //Αναζητηση προιοντων μονο βασει κατηγοριας 
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
                    //Εμφανιση μονο των διαθεσιμων προιοντων
                    cout<<"Results: ";
                    eshop.showallproducts();
                    cout<<"Select a product title: ";
                    cin.ignore();
                    string keyword;
                    getline(cin, keyword);
                    bool p=false;
                    //Αναζητηση στο Eshop βασει τιτλου προιοντος
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
            getline(cin,titlos);
            bool p=false; //Ελεγχος αν βρεθηκε το προιον

            cout<<"Enter quantity: ";
            cin>>posotita;

            bool a=false; //Ελεγχος αν εχει χρησιμοποιηθει η εκπτωση προιοντος
            bool b=false; //Ελεγχος αν εχει χρησιμοποιηθει η εκπτωση κατηγοριας
            bool c=false; //Ελεγχος αν εχει χρησιμοποιηθει η εκπτωση πιστου πελατη
            string t,k,favorite; //μεταβλητες για τιτλο, κατηγορια και τιτλο αγαπημενου προιοντος 

            //Αναζητηση προιοντος στο Eshop 
            for(const auto& product: eshop.products){
                if(product.gettitlos().find(titlos) != string::npos){
                    p=true;
                    Product newproduct= product;
                    //Ελεγχος αν η ζητουμενη ποσοτητα ειναι διαθεσιμη
                    if(posotita <= product.getposotita()){
                        newproduct.setposotita(posotita);
                        //Προσθηκη στο καλαθι
                        cart.addProduct(newproduct, posotita);
                    } else{
                        cout<<"The requested quantity is not available. Available quantity: "<<product.getposotita()<<endl;
                        posotita= product.getposotita();
                        cart.addProduct(newproduct, posotita);
                    }
                }
            }
            //Αναγνωση εκπτωσεων
            map<string, int> discounts=readdiscounts(); 
            for(const auto& product: eshop.products){ 
                string katigoria=product.getkatigoria(); 
                if(ekptosi(product.gettitlos())){ 
                    a=true; 
                    t=product.gettitlos(); 
                } 
                else if(discounts.find(katigoria) != discounts.end() && ekptosikatigorias(katigoria, discounts.at(katigoria))){ 
                    b=true; 
                    k=katigoria; 
                } 
                else if(pistospelatis()){ 
                    favorite= getfavouriteprod();
                    c=true; 
                    } 
            }
            //Εμφανιση μηνυματων εκπτωσης αναλογα με την εκπτωση που δικαιουται ο πελατης
            if(a==true){ 
                cout<<"You are eligible for a 20% discount on the product: "<<t<<" on this order!"<<endl; 
            } 
            if(b==true){ 
                cout<<"You are eligible for a 30% discount on a random product in the category: "<<k<<" on this order!"<<endl; 
            } 
            if (c==true) { 
                cout<<"As a loyal customer, you are eligible for a 40% discount on your favorite product: "<<favorite<<" on this order!"<<endl;
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

            //Αναζητηση προιοντος στο καλαθι του πελατη
            for(const auto& product : cart.products){
                if(product.gettitlos().find(titlos) != string::npos){
                    //Αναζητηση προιοντος στο Eshop
                    for(const auto& eshopproduct : eshop.products){
                        if(eshopproduct.gettitlos().find(product.gettitlos()) != string::npos){
                            //Ελεγχος αν η νεα ποσοτητα ειναι διααθεσιμη στο Eshop 
                            if(newposotita <= eshopproduct.getposotita()){
                                cart.updatePosotita(product.gettitlos(), newposotita);
                            } else{
                                cout<<"The requested quantity is not available. Available quantity: "<<eshopproduct.getposotita()<<endl;
                                cart.updatePosotita(product.gettitlos(), eshopproduct.getposotita());
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
            cart.removeProduct(titlos); //Αφαιρεση προιοντος απο το καλαθι
            cout<<endl;
}


void Customer::completeorder(Eshop& eshop,const string& filename){
    map<string, int> discounts= readdiscounts(); 
    double totalwithdiscount= totalwithdiscounts(*this, cart.products, discounts); //Υπολογισμος συνολου
    orderHistory.push_back(Order(cart.products, totalwithdiscount)); //Προσθηκη παραγγελιας στο ιστορικο παραγγελιων
    updateproductposotita(eshop,filename); //Ενημερωση ποσοτητας στο Eshop
    cart.products.clear();
    saveorderhistory();
    cout<<"Order Completed!"<<endl;
    cout<<endl;
}


void Customer::updateproductposotita(Eshop& eshop,const string& filename){
    for(auto& product : cart.products){
        for(auto& eshopproduct : eshop.products){
            if(eshopproduct.gettitlos().find(product.gettitlos()) != string::npos){
                int newposotita= eshopproduct.getposotita()- product.getposotita();
                eshopproduct.setposotita(newposotita); //Ενημερωση ποσοτητας προιοντος στο Eshop
                break;
            }
        }
    }

    //Αποθηκευση των ενημερωμενων προιοντων σε αρχειο
    ofstream productsfile(filename);
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


//Εμφανιση ιστορικου παραγγελιων του πελατη
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


//Εμφανιση του καλαθιου του πελατη
void Customer::viewcart(){
            cart.displayCart();
            cout<<"Total Cost: "<<cart.calculatetotal()<<endl;
            cout<<endl;
}


//Αποθηκευση του ιστορικου παραγγελιων καθε πελατη σε αρχειο
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


//Φορτωση ιστορικου παραγγελιων απο ενα αρχειο
void Customer::loadorderhistory(){
    ifstream arxio("files/order_history/" + getusername() + "_history.txt"); // Ανοιγμα αρχειου ιστορικου παραγγελιων του πελατη
    string grammi;
    while(getline(arxio,grammi)){
        if(grammi.find("---CART") != string::npos){
            vector<Product> products; //Λιστα προιοντων 
            double totalcost=0;
            while(getline(arxio,grammi) && grammi.find("Total Cost:") == string::npos){
                if(grammi.find("---CART") != string::npos) continue; //Αγνοηση γραμμων που περιεχουν "---CART"
                stringstream x(grammi);
                int posotita;
                string titlos;
                x>>posotita;
                getline(x,titlos);
                if(!titlos.empty() && titlos[0] == ' ') titlos.erase(0,1); // Αφαιρεση κενων απο την αρχη του τιτλου
                products.push_back(Product(titlos, "", "", "", 0.0, "", posotita));
            }
            stringstream x(grammi);
            string temp;
            x>>temp>>temp>>totalcost;
            orderHistory.push_back(Order(products, totalcost)); // Προσθηκη της παραγγελιας στο ιστορικο παραγγελιων
        }
    }
}


void Customer::showmenu(Eshop& eshop, const string& filename){
            //Εμφανιση μενου για τον πελατη
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
                cin.ignore(); //Αφαιρεση χαρακτηρα νεας γραμμης

                switch (choice) {
                    case 1 : {
                        //Αναζητηση προιοντος
                        searchprod(eshop);
                        break;
                    }
                    case 2 : {
                        //Προσθηκη προιοντος στο καλαθι
                        addtocart(eshop);
                        break;
                    }
                    case 3 : {
                        //Ενημερωση καλαθιου
                        updatecart(eshop);
                        break;
                    }
                    case 4 : {
                        //Αφαιρεση προιοντος απο το καλαθι
                        removefromcart();
                        break;
                    }
                    case 5 : {
                        //Ολοκληρωση παραγγελιας 
                        completeorder(eshop,filename);
                        break;
                    }
                    case 6 : {
                        //Προβολη ιστορικου παραγγελιων
                        vieworderhistory();
                        break;
                    }
                    case 7 : {
                        //Προβολη καλαθιου
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


//Συναρτηση που ελεγχει αν ο πελατης δικαιουται την εκτωση προιοντος 
bool Customer::ekptosi(const string& producttitlos) const{
    int plithos= 0; //Πληθος παραγγελιων που περιεχουν το συγκεκριμενο προιον 
    for(auto i= orderHistory.rbegin(); i!= orderHistory.rend() && plithos< 3; ++i){
        bool found = false;
        for(const auto& product : i->products){
            if(product.gettitlos().find(producttitlos) != string::npos){
                found = true;
                break;
            }
        }
        if(found){
            ++plithos;
        } else{
            break;
        }
    }
    if(plithos == 3){
        return true;
    }
    return false;
}


//Συναρτηση που επιστρεφει αν ο χρηστης δικαιουται την εκπτωση κατηγοριας
bool Customer::ekptosikatigorias(const string& katigoria, int epipedo) const{
    int totalposotita= 0;
    for(const auto& order : orderHistory){
        for(const auto& product : order.products){
            if(product.getkatigoria().find(katigoria) != string::npos){
                totalposotita+= product.getposotita();
            }
        }
    }
    //Ελεγχος αν η συνολικη ποσοτητα προιοντων μιας κατηγοριας ειναι μεγαλυτερη ή ιση απο το επιπεδο
    if(totalposotita >= epipedo){
        return true; //δικαιωμα εκπτωσης κατηγοριας
    }
    return false;
}


//Συναρτηση που επιστεφει αν ενας πελατης ειναι πιστος
bool Customer::pistospelatis() const {
    return orderHistory.size() >= 5;
}


//Συναρτηση που επιστρεφει τον τιτλο του αγαπημενου προιοντος
string Customer::getfavouriteprod() const{
    map<string, int> plithosprod; //Map που αποθηκευει το πληθος καθε προιοντος
    for(const auto& order : orderHistory){
        for(const auto& product : order.products){
            plithosprod[product.gettitlos()] += product.getposotita();
        }
    }

    string favorite;
    int max= 0;
    //Ευρεση προιοντος με μεγιστη ποσοτητα σε ολες τις παραγγελιες
    for(const auto& pair : plithosprod){
        if(pair.second > max){
            favorite= pair.first;
            max= pair.second;
        }
    }
    return favorite;
}


//Συναρτηση που επιστρεφει το συνολικο κοστος της παραγγελιας με εκπτωσεις
double Customer::totalwithdiscounts(Customer& customer, const vector<Product>& cartprod, const map<string, int>& discounts){
    double total=0;
    set<string> discountedkatigories; //Οι κατηγοριες που εχουν εκπτωσεις
    map<string, double> discountrates; //Map με τις εκπτωσεις των προιοντων
    srand(time(0)); //Αρχικοποιηση τυχαιου αριθμου

    //Ελεγχος για την εκπτωση προιοντος
    for(const auto& product : cartprod){
        if(customer.ekptosi(product.gettitlos())){
            discountrates[product.gettitlos()]=0.8;
        }
    }

    //Ελεγχος για την εκπτωση κατηγοριας
    for(const auto& product : cartprod){
        string katigoria=product.getkatigoria();
        if(discounts.find(katigoria) != discounts.end() && 
            customer.ekptosikatigorias(katigoria, discounts.at(katigoria))) {
            if (discountedkatigories.find(katigoria) == discountedkatigories.end()) {
                int index= rand() % cartprod.size();
                const Product& random= cartprod[index];
                if (random.getkatigoria().find(katigoria) != string::npos) {
                    discountrates[random.gettitlos()] = 0.7;
                    discountedkatigories.insert(katigoria);
                }
            }
        }
    }

    //Ελεγχος αν ο πελατης ειναι πιστος
    if(customer.pistospelatis()){
        string favorite= customer.getfavouriteprod(); //Ευρεση αγαπημενου προιοντος
        discountrates[favorite]= 0.6;
    }

    //Αν υπαρχουν περισσοτερες απο μια εκπτωσεις , τοτε επιλεγεται και εφαρμοζεται μια τυχαια
    if(discountrates.size() > 1){
        int index= rand() % discountrates.size();
        auto i= discountrates.begin();
        advance(i, index);
        discountrates.clear();
        discountrates[i->first]= i->second;
    }

    //Υπολογισμος συνολικου ποσου με τις εκπτωσεις
    for(const auto& product : cartprod){
        double timi= product.gettimi();
        if (discountrates.find(product.gettitlos()) != discountrates.end()){
            timi *= discountrates[product.gettitlos()];
        }
        total+= timi* product.getposotita();
    }
    return total;
}


int main(int argc,char* argv[]){
    //Ελεγχος αριθμου ορισματων της γραμμης εντολων
    if(argc!=4){
        return 1;
    }
    Eshop myeshop;//Δημιουργια αντικειμενου Eshop
    //Φορτωση κατηγοριων,προιοντων και χρηστων απο αρχεια ορισματων
    myeshop.loadkatigories(argv[1]);
    myeshop.loadproducts(argv[2]);
    myeshop.loadusers(argv[3]);

    cout<<"Welcome to the e-shop!!!"<<endl;
    cout<<"Do you want to login or register? (enter option): ";
    string epilogi;
    cin>>epilogi;
    cin.ignore();

    //Διαχειριση επιλογης χρηστη για εγγραφη ή εισοδο
    if(epilogi == "login"){
        string username, password;

        cout<<"Please enter your username: ";
        getline(cin, username);

        cout<<"Please enter your password: ";
        getline(cin, password);

        //Ελεγχος συνδεσης χρηστη
        User* loggeduser= myeshop.login(username, password);
        if(loggeduser){
            if(Customer* customer= dynamic_cast<Customer*>(loggeduser)){
                //Υποδοχη πελατη
                cout<<endl;            
                cout<<"Welcome "<<loggeduser->getusername()<<"!"<<endl;
                cout<<endl;
                customer->loadorderhistory();
                customer->showmenu(myeshop,argv[2]);
            } else if(Admin* admin= dynamic_cast<Admin*>(loggeduser)){
                //Υποδοχη διαχειριστη
                cout<<"Welcome "<<loggeduser->getusername()<<"!"<<endl;
                admin->showmenu(myeshop,argv[2]);
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

        //Εγγραφη χρηστη και αυτοματη συνδεση
        if(myeshop.registeruser(username, password, isAdmin)){
            cout<<"Thanks for signing up! You are automatically logged-in as "<<username<<endl;
            cout<<endl;
            
            User* newuser= myeshop.login(username, password);

            if(newuser && !isAdmin){
                Customer* customer= dynamic_cast<Customer*>(newuser);
                if(customer){
                    newuser->showmenu(myeshop,argv[2]);
                }
            } else if(newuser && isAdmin){
                Admin* admin= dynamic_cast<Admin*>(newuser);
                if(admin){
                    admin->showmenu(myeshop,argv[2]);
                }
            }
        } else{
            cout<<"User registration failed!"<<endl;
        }
    }
    else{
        cout<<"Invalid option!"<<endl;
    }

    //Αποθηκευση χρηστων και προιοντων στα αρχεια
    myeshop.saveusers(argv[3]);
    myeshop.saveproducts(argv[2]);
    return 0;
}