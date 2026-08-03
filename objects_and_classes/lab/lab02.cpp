#include <iostream>
#include <sstream>
#include <string>

class RustMatrix
{
private:
    const int LENGTH = 10;
    char **ptr_pointers_dyn_arr;
    int rust_ticks;

    // private methods
    void allocateInnerArr();
    void readDynMatrix();
    void applyRustMaskPerTick();
    bool isOutOfBounds(const int row_index, const int col_index);
    void rustCellMask(const int &row_coords, const int &col_coords);
    void applyDeMasking();

public:
    // c-tor
    RustMatrix();

    // de-c-tor
    ~RustMatrix();

    // public methods
    void printMatrix();
    void startRustProcess(int rust_ticks);

    // getters and setters
    int getRustTicks() const;
    void setRustTicks(int ticks);
};

RustMatrix::RustMatrix()
{
    this->ptr_pointers_dyn_arr = new char *[this->LENGTH];

    this->allocateInnerArr();

    this->readDynMatrix();
}

RustMatrix::~RustMatrix()
{
    for (int curr_row = 0; curr_row < this->LENGTH; curr_row++)
    {
        delete[] this->ptr_pointers_dyn_arr[curr_row];
        this->ptr_pointers_dyn_arr[curr_row] = nullptr;
    }

    delete[] this->ptr_pointers_dyn_arr;
    this->ptr_pointers_dyn_arr = nullptr;
}

void RustMatrix::allocateInnerArr()
{
    for (int curr_row = 0; curr_row < this->LENGTH; curr_row++)
    {
        this->ptr_pointers_dyn_arr[curr_row] = new char[this->LENGTH];
    }
}

void RustMatrix::readDynMatrix()
{
    for (int curr_row = 0; curr_row < this->LENGTH; curr_row++)
    {
        for (int curr_col = 0; curr_col < this->LENGTH; curr_col++)
        {
            char tmp_read_val;
            std::cin >> tmp_read_val;

            this->ptr_pointers_dyn_arr[curr_row][curr_col] = tmp_read_val;
        }
    }
}

void RustMatrix::printMatrix()
{
    for (int curr_row = 0; curr_row < this->LENGTH; curr_row++)
    {
        for (int curr_col = 0; curr_col < this->LENGTH; curr_col++)
        {
            char tmp_variable = this->ptr_pointers_dyn_arr[curr_row][curr_col];
            std::cout << tmp_variable;
        }
        std::cout << std::endl;
    }
}

// Recursion Jutsu technique
void RustMatrix::startRustProcess(int rust_ticks)
{
    if (this->rust_ticks == 0)
    {
        return;
    }

    this->applyRustMaskPerTick();
    this->rust_ticks--;

    return this->startRustProcess(this->rust_ticks);
}

bool RustMatrix::isOutOfBounds(const int row_index, const int col_index)
{
    return row_index < 0 || row_index >= this->LENGTH || col_index < 0 || col_index >= this->LENGTH;
}

void RustMatrix::applyRustMaskPerTick()
{
    for (int curr_row = 0; curr_row < this->LENGTH; curr_row++)
    {
        for (int curr_col = 0; curr_col < this->LENGTH; curr_col++)
        {
            char curr_elem = this->ptr_pointers_dyn_arr[curr_row][curr_col];

            if (curr_elem == '!')
            {
                // column manipulation-left
                this->rustCellMask(curr_row, curr_col - 1);

                // column manipulation-right
                this->rustCellMask(curr_row, curr_col + 1);

                // row manipulation-down
                this->rustCellMask(curr_row + 1, curr_col);

                // row manipulation-up
                this->rustCellMask(curr_row - 1, curr_col);
            }
        }
    }

    this->applyDeMasking();
}

void RustMatrix::rustCellMask(const int &row_coords, const int &col_coords)
{
    bool is_index_out_of_bounds = this->isOutOfBounds(row_coords, col_coords);
    if (is_index_out_of_bounds)
    {
        return;
    }

    char curr_symbol_to_rust = this->ptr_pointers_dyn_arr[row_coords][col_coords];
    // guard clause
    if (curr_symbol_to_rust == '!' || curr_symbol_to_rust == '#')
    {
        return;
    }

    // aplying the rust mask technique
    char rust_mask_symbol = 'M';
    this->ptr_pointers_dyn_arr[row_coords][col_coords] = rust_mask_symbol;
}

void RustMatrix::applyDeMasking()
{
    for (int cur_row = 0; cur_row < this->LENGTH; cur_row++)
    {
        for (int cur_col = 0; cur_col < this->LENGTH; cur_col++)
        {
            char curr_symbol = this->ptr_pointers_dyn_arr[cur_row][cur_col];
            bool is_mask_symbol = curr_symbol == 'M';
            if (is_mask_symbol)
            {
                this->ptr_pointers_dyn_arr[cur_row][cur_col] = '!';
            }
        }
    }
}

int RustMatrix::getRustTicks() const
{
    return this->rust_ticks;
}

void RustMatrix::setRustTicks(int ticks)
{
    // data validation before setting value from outside to a field data of obj instance
    if (ticks < 0)
    {
        ticks = 0;
    }

    this->rust_ticks = ticks;
}

int main()
{
    RustMatrix *ptr_rust_matrix = new RustMatrix();

    int rust_ticks;
    std::cin >> rust_ticks;

    (*ptr_rust_matrix).setRustTicks(rust_ticks);

    (*ptr_rust_matrix).startRustProcess((*ptr_rust_matrix).getRustTicks());

    (*ptr_rust_matrix).printMatrix();

    delete ptr_rust_matrix;
    ptr_rust_matrix = nullptr;

    return 0;
}
