#include <vector>
#include <iostream>

class DataVector // Class has UDT DataVector which represents one data point (Mathematically a vector)
{
    std::vector<double> v; // store the attributes of a vector

public:
    DataVector();                                  // default constructor
    DataVector(int dimension);                     // Constructor Overload if dimension of data is provided
    ~DataVector();                                 // Destructor
    DataVector(const DataVector &other);           // Copy contructor to copy upon initialisation from a pre existing DataVector
    DataVector operator=(const DataVector &other); // Assignment operator
    void setDimension(int dimension);              // Function to change the dimension of the DataVector
    DataVector operator+(const DataVector &other); // Overload operator + to add to vectors mmathematically
    DataVector operator-(const DataVector &other); // Overload operator - to subtract to vectors mmathematically
    double &operator[](int i);
    double operator*(const DataVector &other); // Overload operator * to take Scalar product of to vectors mmathematically
    double norm();                             // Returns length of the vector
    double dist(const DataVector &other);      // Returns distance between this and other vectors
    void push_data(double data);               // Pushes Data into the vector data
    int size();
};