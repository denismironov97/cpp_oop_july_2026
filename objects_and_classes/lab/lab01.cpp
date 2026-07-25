#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <cctype>

using std::map;
using std::set;
using std::string;
using std::stringstream;
using std::vector;

bool endsWithPunctuation(const string &word);
const set<string> getLettersMatchList(const char &curr_read_char, const vector<string> &words_collection);

int main()
{
    string input_str;
    std::getline(std::cin, input_str);

    stringstream str_stream(input_str);

    string curr_str_val;
    vector<string> words_collection;
    while (str_stream >> curr_str_val)
    {
        // guard clause for empty string since string stream skips one spacing by default
        if (curr_str_val.empty())
        {
            continue;
        }

        stringstream str_stream_buffer;
        for (int curr_index = 0; curr_index < curr_str_val.length(); curr_index++)
        {
            const char &curr_symbol = curr_str_val[curr_index];
            bool is_symbol_alphabet =
                std::isalpha(static_cast<unsigned char>(curr_symbol));

            if (!is_symbol_alphabet)
            {
                break;
            }

            str_stream_buffer << curr_symbol;
        }

        words_collection.push_back(str_stream_buffer.str());
    }

    char curr_read_char;
    vector<char> occurrence_order;
    while (std::cin >> curr_read_char && curr_read_char != '.')
    {
        curr_read_char = std::tolower(curr_read_char);
        occurrence_order.push_back(curr_read_char);
    }

    map<char, set<string>> dict;
    vector<char>::iterator iter_counter;
    for (iter_counter = occurrence_order.begin(); iter_counter != occurrence_order.end(); ++iter_counter)
    {
        const char &curr_letter_key = (*iter_counter);
        const set<string> &matchlist = getLettersMatchList(curr_letter_key, words_collection);

        std::pair<char, set<string>> curr_created_pair(curr_letter_key, matchlist);
        dict.insert(curr_created_pair);
    }

    for (const char &curr_occurred_char_key : occurrence_order)
    {
        const set<string> &value_coll = dict[curr_occurred_char_key];
        if (value_coll.empty())
        {
            std::cout << "---" << std::endl;
            continue;
        }

        for (const string &curr_word : dict[curr_occurred_char_key])
        {
            std::cout << curr_word << " ";
        }

        std::cout << std::endl;
    }

    return 0;
}

bool endsWithPunctuation(const string &word)
{
    if (word.empty())
    {
        return false;
    }

    const string punctuation_symbols = ".,?!";

    return punctuation_symbols.find(word.back()) != string::npos;
}

const set<string> getLettersMatchList(const char &curr_read_char, const vector<string> &words_collection)
{
    // since curr_read_char will always be lower case char;
    // bool is_upper_char = std::isupper(static_cast<unsigned int>(curr_read_char));
    /*
    char char_mask;

    if (is_upper_char)
    {
        char_mask = std::tolower(curr_read_char);
    }
    else
    {
        char_mask = std::toupper(curr_read_char);
    }
    */

    char char_mask = std::toupper(curr_read_char);

    set<string> letters_matchlist;
    for (int i = 0; i < words_collection.size(); i++)
    {
        const string &curr_word = words_collection[i];

        int pos_index = curr_word.find(curr_read_char);
        int mask_index = curr_word.find(char_mask);

        // guard clause == neither curr char or mask(upper or lower variant) are present in curr string
        if (pos_index == -1 && mask_index == -1)
        {
            continue;
        }

        letters_matchlist.insert(curr_word);
    }

    return letters_matchlist;
}
