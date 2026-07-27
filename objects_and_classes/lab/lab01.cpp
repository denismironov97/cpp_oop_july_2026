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

// Task can be completed with nested classes
//  but for sake of ease two instanced objects will interact with each other
class WordBox
{
private:
    // fields and private member functions/methods
    string input_str;
    stringstream str_stream;
    vector<string> words_collection;

public:
    // properties, public methods, c-tors and de-c-tor

    //  c-tor
    // WordBox();
    // ~WordBox();

    // getters
    const string &getInputString() const;
    const stringstream &getStringStream() const;
    const vector<string> &getWordsCollection() const;

    // setters
    void setInputString();
    void setStringStream();
    void setWordsCollection(const string &str_val);

    // helper member functions/methods
    void parseWordsFromStream();
};

class WordProcessor
{
private:
    vector<char> occurrence_order;
    map<char, set<string>> dict;

    const set<string> getLettersMatchList(const char &curr_read_char,
                                          const WordBox &word_box_obj_ref);

public:
    // c-tor
    // WordProcessor();

    void readCharsOccOrder();
    void runWordProcessor(const WordBox &word_box_obj_ref);
    void printMatchList();
};

void WordProcessor::readCharsOccOrder()
{
    char curr_read_char;
    while (std::cin >> curr_read_char && curr_read_char != '.')
    {
        curr_read_char = std::tolower(curr_read_char);
        this->occurrence_order.push_back(curr_read_char);
    }
}

void WordProcessor::runWordProcessor(const WordBox &word_box_obj_ref)
{
    vector<char>::iterator iter_counter;
    for (iter_counter = this->occurrence_order.begin(); iter_counter != this->occurrence_order.end(); ++iter_counter)
    {
        const char &curr_letter_key = (*iter_counter);
        const set<string> &matchlist = this->getLettersMatchList(curr_letter_key, word_box_obj_ref);

        std::pair<char, set<string>> curr_created_pair(curr_letter_key, matchlist);
        this->dict.insert(curr_created_pair);
    }
}

void WordProcessor::printMatchList()
{
    for (const char &curr_occurred_char_key : this->occurrence_order)
    {
        const set<string> &value_coll = this->dict[curr_occurred_char_key];
        if (value_coll.empty())
        {
            std::cout << "---" << std::endl;
            continue;
        }

        for (const string &curr_word : this->dict[curr_occurred_char_key])
        {
            std::cout << curr_word << " ";
        }

        std::cout << std::endl;
    }
}

const string &WordBox::getInputString() const
{
    return this->input_str;
}

const stringstream &WordBox::getStringStream() const
{
    return this->str_stream;
}

const vector<string> &WordBox::getWordsCollection() const
{
    return this->words_collection;
}

void WordBox::setInputString()
{
    std::getline(std::cin, this->input_str);
}

void WordBox::setStringStream()
{
    this->str_stream << this->getInputString();
}

void WordBox::setWordsCollection(const string &str_val)
{
    this->words_collection.push_back(str_val);
}

void WordBox::parseWordsFromStream()
{
    string curr_str_val;
    while (this->str_stream >> curr_str_val)
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

        this->setWordsCollection(str_stream_buffer.str());
    }
}

const set<string> WordProcessor::getLettersMatchList(const char &curr_read_char,
                                                     const WordBox &word_box_obj_ref)
{
    char char_mask = std::toupper(curr_read_char);

    set<string> letters_matchlist;
    for (int i = 0; i < word_box_obj_ref.getWordsCollection().size(); i++)
    {
        const string &curr_word = word_box_obj_ref.getWordsCollection()[i];

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

/*
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
*/

int main()
{
    WordBox word_box_u;
    word_box_u.setInputString();
    word_box_u.setStringStream();
    word_box_u.parseWordsFromStream();

    WordProcessor word_processor_u;
    word_processor_u.readCharsOccOrder();
    word_processor_u.runWordProcessor(word_box_u);
    word_processor_u.printMatchList();

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
