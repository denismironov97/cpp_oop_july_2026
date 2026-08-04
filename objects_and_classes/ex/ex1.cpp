#include <iostream>
#include <sstream>
#include <string>

using std::string;

class WordBox
{
private:
    std::stringstream str_streamy;
    const int SHIFT_POSITIONS;

    const int ARR_LENGTH;
    string *dyn_str_arr;
    string *dyn_str_arr_copy;

    // private function members
    int getInputStrSize(const string &str_input);
    void buildStrArray(string *point_dyn_arr, const int &arr_length, std::stringstream &str_stream);
    void copyContentsArr(string *arr_source, string *arr_destination, int arr_length);

public:
    // c-tor
    WordBox(const string &input_line, const int &shift_positions);
    // de-c-tor
    ~WordBox();

    void printArrNewLine();
    void performCircularArrayShifting();
};

WordBox::WordBox(const string &str_val, const int &shift_positions)
    : ARR_LENGTH(this->getInputStrSize(str_val)), str_streamy(str_val), SHIFT_POSITIONS(shift_positions)
{
    this->dyn_str_arr = new string[this->ARR_LENGTH];
    this->dyn_str_arr_copy = new string[this->ARR_LENGTH];

    this->buildStrArray(this->dyn_str_arr, this->ARR_LENGTH, str_streamy);
}

WordBox::~WordBox()
{
    delete[] this->dyn_str_arr;
    this->dyn_str_arr = nullptr;

    delete[] this->dyn_str_arr_copy;
    this->dyn_str_arr_copy = nullptr;
}

int WordBox::getInputStrSize(const string &str_input)
{
    int array_length = 0;
    std::stringstream str_stream(str_input);
    string curr_read_str;
    const char delimeter = ' ';
    while (std::getline(str_stream, curr_read_str, delimeter))
    {
        array_length++;
    }

    return array_length;
}

void WordBox::buildStrArray(string *point_dyn_arr, const int &arr_length, std::stringstream &str_stream)
{
    for (int indx = 0; indx < arr_length; indx++)
    {
        str_stream >> *(point_dyn_arr + indx);
    }

    this->str_streamy.clear();
}

void WordBox::performCircularArrayShifting()
{
    for (int curr_index = 0; curr_index < ARR_LENGTH; curr_index++)
    {
        int target_index = (curr_index + this->SHIFT_POSITIONS) % this->ARR_LENGTH;

        this->dyn_str_arr_copy[target_index] = this->dyn_str_arr[curr_index];
    }
}

void WordBox::copyContentsArr(string *arr_source, string *arr_destination, int arr_length)
{
    if (arr_length == 0)
    {
        return;
    }

    *arr_destination = *arr_source;

    copyContentsArr(++arr_source, ++arr_destination, (arr_length - 1));
}

void WordBox::printArrNewLine()
{
    for (int idx = 0; idx < this->ARR_LENGTH; idx++)
    {
        std::cout << this->dyn_str_arr_copy[idx] << std::endl;
    }
}

int main()
{
    string input_line;
    std::getline(std::cin, input_line);

    int shift_pos;
    std::cin >> shift_pos;

    WordBox *point_word_box = new WordBox(input_line, shift_pos);
    point_word_box->performCircularArrayShifting();
    point_word_box->printArrNewLine();

    delete point_word_box;

    return 0;
}
