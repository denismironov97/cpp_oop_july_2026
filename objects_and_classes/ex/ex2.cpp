#include <iostream>
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip>

void setPrintDigitPrecision(int digits);

class PointData
{
private:
    double x_coords;
    double y_coords;

public:
    // default c-tor
    PointData();
    // c-tor
    PointData(const double &x_coords, const double &y_coords);
    // copy-c-tor
    PointData(const PointData &point_obj);

    // assignment operator overload
    PointData &operator=(const PointData &point_data_obj);

    // getters and setters
    const double &getter_X_Coords() const;
    const double &getter_Y_Coords() const;
};
// default c-tor
PointData::PointData()
{
    this->x_coords = 0.0;
    this->y_coords = 0.0;
}

// ctor with explicit params
PointData::PointData(const double &x_coords, const double &y_coords)
{
    this->x_coords = x_coords;
    this->y_coords = y_coords;
}

// copy c-tor
PointData::PointData(const PointData &point_obj)
{
    this->x_coords = point_obj.getter_X_Coords();
    this->y_coords = point_obj.getter_Y_Coords();
}

// assignment operator overload
PointData &PointData::operator=(const PointData &point_data_obj)
{
    if (this != &point_data_obj)
    {
        this->x_coords = point_data_obj.getter_X_Coords();
        this->y_coords = point_data_obj.getter_Y_Coords();
    }

    return *this;
}

const double &PointData::getter_X_Coords() const
{
    return this->x_coords;
}

const double &PointData::getter_Y_Coords() const
{
    return this->y_coords;
}

class EuclideanDistance2D
{
private:
    PointData point_1_obj;
    PointData point_2_obj;
    double euclidean_distance;

    // helper private function members
    const double calcEuclideanDistance() const;

public:
    // c-tor
    EuclideanDistance2D(const PointData &point_1, const PointData &point_2);

    // getters and setters
    const double &getterEuclideanDist() const;
};

EuclideanDistance2D::EuclideanDistance2D(const PointData &point_1, const PointData &point_2)
{
    this->point_1_obj = point_1;
    this->point_2_obj = point_2;

    this->euclidean_distance = this->calcEuclideanDistance();
}

const double EuclideanDistance2D::calcEuclideanDistance() const
{
    const double tmp_num =
        ((this->point_1_obj.getter_X_Coords() - this->point_2_obj.getter_X_Coords()) *
         (this->point_1_obj.getter_X_Coords() - this->point_2_obj.getter_X_Coords())) +
        ((this->point_1_obj.getter_Y_Coords() - this->point_2_obj.getter_Y_Coords()) *
         (this->point_1_obj.getter_Y_Coords() - this->point_2_obj.getter_Y_Coords()));

    double distance = std::sqrt(tmp_num);

    return distance;
}

const double &EuclideanDistance2D::getterEuclideanDist() const
{
    return this->euclidean_distance;
}

int main()
{
    double point_x_coords;
    double point_y_coords;

    std::cin >> point_x_coords >> point_y_coords;
    PointData *ptr_point_obj_1 = new PointData(point_x_coords, point_y_coords);

    std::cin >> point_x_coords >> point_y_coords;
    PointData *ptr_point_obj_2 = new PointData(point_x_coords, point_y_coords);

    EuclideanDistance2D *ptr_ec_dist = new EuclideanDistance2D((*ptr_point_obj_1), (*ptr_point_obj_2));
    const double &euclidean_distance2D_res = ptr_ec_dist->getterEuclideanDist();

    setPrintDigitPrecision(3);
    std::cout << euclidean_distance2D_res << std::endl;

    delete ptr_point_obj_1;
    ptr_point_obj_1 = nullptr;

    delete ptr_point_obj_2;
    ptr_point_obj_2 = nullptr;

    delete ptr_ec_dist;
    ptr_ec_dist = nullptr;

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