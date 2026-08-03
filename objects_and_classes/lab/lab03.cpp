#include <iostream>
#include <sstream>
#include <string>
#include <array>
#include <list>
#include <iomanip>

using std::array;
using std::list;
using std::string;

const int TOKENS_LENGTH = 3;

const array<string, TOKENS_LENGTH> getExtractedTokens(const string &curr_input_line, const char &delimeter);
bool is_simple_float_num(const string &str_value);

void setPrintDigitPrecision(int digits = 10)
{
    // approach 1
    //  #include <iomanip>
    std::cout << std::fixed << std::setprecision(digits);

    // approach 2
    //  std::cout.setf(std::ios::fixed);
    //  std::cout.precision(digits);
}

class GeoBox
{
    // forward declaring GeoLoc class to have access to internally
public:
    class GeoLoc;

private:
    list<GeoLoc> geo_loc_box;

public:
    // nested class
    class GeoLoc
    {
    private:
        string latitude_coords;
        string longitude_coords;
        string place_name;

    public:
        GeoLoc(string latitude_coords, string longitude_coords, string place_name);

        // getters and setters
        const string getLatitude() const;
        const string getLongitude() const;
        const string getPlaceName() const;
    };

    void addGeoLoc(const GeoLoc &obj_instance);

    // search methods
    // by name_of_place
    list<GeoLoc> getMatchesByPlaceName(const string &place_name);
    // by coords of latitude and longitude
    list<GeoLoc> getMatchesByCoords(const string &latitude, const string &longitude);

    // single match queries
    const GeoLoc *getSpecificMatchPlaceName(const string &place_name) const;
    const GeoLoc *getSpecificMatchCoords(const string &latitude, const string &longitude) const;

    // getters and setters
    const list<GeoLoc> getGeoBoxCollection() const;
};

GeoBox::GeoLoc::GeoLoc(string latitude_coords, string longitude_coords, string place_name)
{
    this->latitude_coords = latitude_coords;
    this->longitude_coords = longitude_coords;
    this->place_name = place_name;
}

const string GeoBox::GeoLoc::getLatitude() const
{
    return this->latitude_coords;
}

const string GeoBox::GeoLoc::getLongitude() const
{
    return this->longitude_coords;
}

const string GeoBox::GeoLoc::getPlaceName() const
{
    return this->place_name;
}

void GeoBox::addGeoLoc(const GeoLoc &obj_instance)
{
    this->geo_loc_box.push_back(obj_instance);
}

const list<GeoBox::GeoLoc> GeoBox::getGeoBoxCollection() const
{
    return this->geo_loc_box;
}

list<GeoBox::GeoLoc> GeoBox::getMatchesByPlaceName(const string &place_name)
{
    list<GeoBox::GeoLoc> matches_list;

    for (list<GeoBox::GeoLoc>::iterator curr_iter = this->geo_loc_box.begin(); curr_iter != this->geo_loc_box.end(); ++curr_iter)
    {
        bool is_place_match = (*curr_iter).getPlaceName() == place_name;
        if (is_place_match)
        {
            matches_list.push_back(*curr_iter);
        }
    }

    return matches_list;
}

const GeoBox::GeoLoc *GeoBox::getSpecificMatchPlaceName(const string &place_name) const
{
    for (list<GeoBox::GeoLoc>::const_iterator curr_iter = this->geo_loc_box.begin(); curr_iter != this->geo_loc_box.end(); ++curr_iter)
    {
        bool is_place_match = (*curr_iter).getPlaceName() == place_name;
        if (is_place_match)
        {
            return &(*curr_iter);
        }
    }

    return nullptr;

    /*
    for (const GeoBox::GeoLoc &current_geo_loc : this->geo_loc_box)
    {
        if (current_geo_loc.getPlaceName() == place_name)
        {
            return &current_geo_loc;
        }
    }

    return nullptr;
    */
}

const GeoBox::GeoLoc *GeoBox::getSpecificMatchCoords(const string &latitude, const string &longitude) const
{
    for (const GeoBox::GeoLoc &curr_geo_loc_obj : this->geo_loc_box)
    {
        bool do_coords_match = curr_geo_loc_obj.getLatitude() == latitude &&
                               curr_geo_loc_obj.getLongitude() == longitude;
        if (do_coords_match)
        {
            return &curr_geo_loc_obj;
        }
    }

    return nullptr;
}

list<GeoBox::GeoLoc> GeoBox::getMatchesByCoords(const string &latitude, const string &longitude)
{
    list<GeoBox::GeoLoc> matches_list;
    for (list<GeoBox::GeoLoc>::iterator curr_iter = this->geo_loc_box.begin(); curr_iter != this->geo_loc_box.end(); ++curr_iter)
    {
        bool do_coords_match = curr_iter->getLatitude() == latitude && curr_iter->getLongitude() == longitude;
        if (do_coords_match)
        {
            matches_list.push_back(*curr_iter);
        }
    }

    return matches_list;
}

int main()
{
    GeoBox *geo_box = new GeoBox();

    string curr_input_line;
    const char delimeter = ',';
    while (std::getline(std::cin, curr_input_line) && curr_input_line != ".")
    {
        const array<string, TOKENS_LENGTH> &tokens_data = getExtractedTokens(curr_input_line, delimeter);
        const string &place_name = tokens_data[0];
        const string &latitude_str = tokens_data[1];
        const string &longitude_str = tokens_data[2];

        GeoBox::GeoLoc *ptr_geo_loc_obj = new GeoBox::GeoLoc(latitude_str, longitude_str, place_name);

        (*geo_box).addGeoLoc(*ptr_geo_loc_obj);

        // clearing pointers
        delete ptr_geo_loc_obj;
        ptr_geo_loc_obj = nullptr;
    }

    string search_str_line;
    list<GeoBox::GeoLoc> res_list;
    while (std::getline(std::cin, search_str_line) && search_str_line != ".")
    {
        const array<string, TOKENS_LENGTH> &read_tokens = getExtractedTokens(search_str_line, ' ');

        // const GeoBox::GeoLoc *point_match_obj;
        list<GeoBox::GeoLoc> tmp_list;
        bool is_float_num = is_simple_float_num(read_tokens[0]);
        if (is_float_num)
        {
            // user entered coordinates
            // long double curr_latitude = std::stold(read_tokens[0]);
            // long double curr_longitude = std::stold(read_tokens[1]);

            // point_match_obj = geo_box->getSpecificMatchCoords(curr_latitude, curr_longitude);

            tmp_list = geo_box->getMatchesByCoords(read_tokens[0], read_tokens[1]);
        }
        else
        {
            string place_name = read_tokens[0];

            // point_match_obj = geo_box->getSpecificMatchPlaceName(place_name);
            tmp_list = geo_box->getMatchesByPlaceName(place_name);
        }

        // if (point_match_obj != nullptr)
        // {
        //     res_list.push_back(*point_match_obj);
        // }

        if (!tmp_list.empty())
        {
            for (const GeoBox::GeoLoc &curr_obj : tmp_list)
            {
                res_list.push_back(curr_obj);
            }
        }
    }

    // printing result data
    for (const GeoBox::GeoLoc &curr_obj : res_list)
    {
        std::cout << curr_obj.getPlaceName() << ',' << curr_obj.getLatitude() << ',' << curr_obj.getLongitude() << std::endl;
    }

    // clearing pointers
    delete geo_box;
    geo_box = nullptr;

    return 0;
}

const array<string, TOKENS_LENGTH> getExtractedTokens(const string &curr_input_line, const char &delimeter)
{
    array<string, TOKENS_LENGTH> tokens_data;

    std::stringstream str_stream(curr_input_line);
    string curr_read_token;
    int c_index = 0;
    while (std::getline(str_stream, curr_read_token, delimeter))
    {
        tokens_data[c_index] = curr_read_token;
        c_index++;
    }

    return tokens_data;
}

bool is_simple_float_num(const string &str_value)
{
    for (int curr_index = 0; curr_index < str_value.length(); curr_index++)
    {
        char curr_symbol = str_value[curr_index];

        if (curr_symbol != '-' && curr_symbol != '.' && !(std::isdigit(curr_symbol)))
        {
            return false;
        }
    }

    return true;
}
