#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <vector>

using std::map;
using std::string;
using std::vector;

int getSymbolIndexInStr(const string &str_val, const char &symbol);
void removeSelectedSymbolFromStr(string &curr_str_val, const int &symbol_index);
string str_tolower(string str_copy);

int main()
{
    map<char, vector<string>> char_str_occurrence;

    string text;
    std::getline(std::cin, text);

    std::stringstream str_stream(text);

    vector<char> letters;
    // reading letters until a dot is encountered
    char curr_read_letter;
    while (std::cin >> curr_read_letter && curr_read_letter != '.')
    {
        letters.push_back(curr_read_letter);
    }

    string curr_str_val;
    while (str_stream >> curr_str_val)
    {
        // std::size_t dot_index_curr_str = curr_str_val.find('.');
        // int dot_index_curr_str = curr_str_val.find('.');

        int symbol_index = getSymbolIndexInStr(curr_str_val, '.');
        removeSelectedSymbolFromStr(curr_str_val, symbol_index);

        for (vector<char>::iterator curr_iter = letters.begin(); curr_iter != letters.end(); ++curr_iter)
        {
            char curr_char = (*curr_iter);
            bool is_curr_char_lowercase = std::islower(curr_char);

            char lower_char;
            char upper_char;
            if (is_curr_char_lowercase)
            {
                lower_char = curr_char;
                upper_char = std::toupper(curr_char);
            }
            else
            {
                lower_char = std::tolower(curr_char);
                upper_char = curr_char;
            }

            int index_lower = curr_str_val.find(lower_char);
            int index_upper = curr_str_val.find(upper_char);

            if (index_lower != -1 || index_upper != -1)
            {
                auto iter_insertion_res = char_str_occurrence.insert(std::pair<char, vector<string>>(curr_char, {curr_str_val}));

                if (iter_insertion_res.second == false)
                {
                    iter_insertion_res.first->second.push_back(curr_str_val);
                }
            }
        }
    }

    // printing result
    map<char, vector<string>>::iterator map_iter_counter = char_str_occurrence.begin();
    while (map_iter_counter != char_str_occurrence.end())
    {
        const char &curr_key = map_iter_counter->first;
        const vector<string> &curr_val = map_iter_counter->second;

        for (const string &curr_str : curr_val)
        {
            std::cout << curr_str << " ";
        }

        std::cout << std::endl;

        ++map_iter_counter;
    }

    return 0;
}

int getSymbolIndexInStr(const string &str_val, const char &symbol)
{
    int symbol_index = str_val.find(symbol);

    return symbol_index;
}

void removeSelectedSymbolFromStr(string &curr_str_val, const int &symbol_index)
{
    if (symbol_index == -1)
    {
        return;
    }

    curr_str_val.erase(symbol_index, 1);
}

string str_tolower(string str_copy)
{
    std::transform(str_copy.begin(), str_copy.end(), str_copy.begin(),
                   // static_cast<int(*)(int)>(std::tolower)         // wrong
                   // [](int c){ return std::tolower(c); }           // wrong
                   // [](char c){ return std::tolower(c); }          // wrong
                   [](unsigned char c)
                   { return std::tolower(c); } // correct
    );

    return str_copy;
}