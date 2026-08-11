#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <iomanip>

using std::string;

void setPrintDigitPrecision(int digits);

class Sale
{
private:
    string city_name;
    string product_type;
    double price_per_unit;
    double quantity;

public:
    // def c-tor
    // Sale();
    // c-tor
    // params c-tor
    Sale(const string &city_name, const string &product_type,
         const double &price_per_unit, const double &quantity);
    // copy-c-tor
    Sale(const Sale &obj_data);
    // assignment operator overload
    Sale &operator=(const Sale &obj_data);

    // getters and setters
    const string &getterCityName() const;
    const string &getterProductType() const;
    const double &getterPricePerUnit() const;
    const double &getterQuantity() const;

    void setterProductQuantity(const double &value_variable);
};

Sale::Sale(const string &city_name, const string &product_type,
           const double &price_per_unit, const double &quantity)
{
    this->city_name = city_name;
    this->product_type = product_type;
    this->price_per_unit = price_per_unit;
    this->quantity = quantity;
}

Sale::Sale(const Sale &obj_data)
{
    this->city_name = obj_data.city_name;
    this->product_type = obj_data.product_type;
    this->price_per_unit = obj_data.price_per_unit;
    this->quantity = obj_data.quantity;
}

Sale &Sale::operator=(const Sale &obj_data)
{
    if (this != &obj_data)
    {
        this->city_name = obj_data.city_name;
        this->product_type = obj_data.product_type;
        this->price_per_unit = obj_data.price_per_unit;
        this->quantity = obj_data.quantity;
    }

    return *this;
}

const string &Sale::getterCityName() const
{
    return this->city_name;
}

const string &Sale::getterProductType() const
{
    return this->product_type;
}

const double &Sale::getterPricePerUnit() const
{
    return this->price_per_unit;
}

const double &Sale::getterQuantity() const
{
    return this->quantity;
}

void Sale::setterProductQuantity(const double &value_variable)
{
    this->quantity = value_variable;
}

class ProfitTracker
{
private:
    std::map<string, std::vector<Sale>> inner_cont;

    Sale *getExistingProduct(std::vector<Sale> &curr_product_cont, const Sale &obj_inst);

public:
    void insertSaleToProfitTracker(const Sale &obj_inst);
    void printProfitData();
};

void ProfitTracker::insertSaleToProfitTracker(const Sale &obj_inst)
{
    std::map<string, std::vector<Sale>>::iterator iter_specific_obj =
        this->inner_cont.find(obj_inst.getterCityName());

    bool does_key_exist = iter_specific_obj != this->inner_cont.end();
    if (!does_key_exist)
    {
        std::pair<string, std::vector<Sale>> curr_pair(obj_inst.getterCityName(), std::vector<Sale>{obj_inst});

        std::pair<std::map<std::string, std::vector<Sale>>::iterator, bool> iter_kvp =
            this->inner_cont.insert(curr_pair);
    }
    else
    {
        const string &kvp_key = iter_specific_obj->first;
        std::vector<Sale> &kvp_value = iter_specific_obj->second;

        Sale *ptr_existing_obj = this->getExistingProduct(kvp_value, obj_inst);
        if (ptr_existing_obj != nullptr)
        {
            ptr_existing_obj->setterProductQuantity(ptr_existing_obj->getterQuantity() + obj_inst.getterQuantity());
        }
        else
        {
            kvp_value.push_back(obj_inst);
        }
    }
}

Sale *ProfitTracker::getExistingProduct(std::vector<Sale> &curr_product_cont,
                                        const Sale &obj_inst)
{
    for (int idx = 0; idx < curr_product_cont.size(); idx++)
    {
        Sale &curr_obj = curr_product_cont[idx];
        if (curr_obj.getterProductType() == obj_inst.getterProductType())
        {
            return &curr_obj;
        }
    }

    /*
    for (Sale curr_obj : curr_product_cont)
    {
        if (curr_obj.getterProductType() == obj_inst.getterProductType())
        {
            return &curr_obj;
        }
    }
    */

    return nullptr;
}

void ProfitTracker::printProfitData()
{
    for (const std::pair<string, std::vector<Sale>> &curr_kvp : this->inner_cont)
    {
        const string &kvp_key = curr_kvp.first;
        const std::vector<Sale> &kvp_val = curr_kvp.second;

        double district_total_profit = 0;
        for (const Sale &curr_obj : kvp_val)
        {
            double curr_product_total = curr_obj.getterPricePerUnit() * curr_obj.getterQuantity();
            district_total_profit += curr_product_total;
        }

        std::cout << kvp_key << " -> " << district_total_profit << std::endl;
    }
}

int main()
{
    ProfitTracker *ptr_profit_tracker = new ProfitTracker();

    int num_lines;
    std::cin >> num_lines;
    std::cin.ignore();

    for (int idx = 0; idx < num_lines; idx++)
    {
        string curr_data_line;
        std::getline(std::cin, curr_data_line);
        std::stringstream str_stream(curr_data_line);

        string curr_city_name;
        string curr_product_type;
        double curr_price_per_unit;
        double curr_quantity;

        str_stream >> curr_city_name >> curr_product_type >> curr_price_per_unit >> curr_quantity;

        Sale *ptr_sale_inst = new Sale(curr_city_name, curr_product_type, curr_price_per_unit, curr_quantity);
        // Sale sale_obj(curr_city_name, curr_product_type, curr_price_per_unit, curr_quantity);

        ptr_profit_tracker->insertSaleToProfitTracker(*ptr_sale_inst);
        // ptr_profit_tracker->insertSaleToProfitTracker(sale_obj);

        delete ptr_sale_inst;
        ptr_sale_inst = nullptr;
    }

    setPrintDigitPrecision(2);
    ptr_profit_tracker->printProfitData();

    // removing pointers
    delete ptr_profit_tracker;
    ptr_profit_tracker = nullptr;

    return 0;
}

void setPrintDigitPrecision(int digits)
{
    // approach 1
    //  #include <iomanip>
    std::cout << std::fixed << std::setprecision(digits);

    // approach 2
    //  std::cout.setf(std::ios::fixed);
    //  std::cout.precision(digits);
}