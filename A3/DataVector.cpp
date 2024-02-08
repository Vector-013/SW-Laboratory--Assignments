#include <iostream>
#include <cmath>
#include "DataVector.h"

DataVector::DataVector(int dimension = 0)
{
    v.resize(dimension, 0);
}

DataVector::DataVector()
{
    v.resize(0, 0);
}

int DataVector::size()
{
    return v.size();
}

DataVector::DataVector(const DataVector &other)
{
    v = std::move(other.v);
}

DataVector DataVector::operator=(const DataVector &other)
{
    // if (&other == this)
    //     return *this; // Check for self-assignmeng

    // v = std::move(other.v);

    // return *this;
    (*this).v.resize(other.v.size());
    (*this).v = other.v;
    return *this;
}

void DataVector::setDimension(int dimension)
{
    std::cout << "i" << v.size() << std::endl;
    v.resize(dimension, 0);
    std::cout << v.size() << std::endl;
}

DataVector DataVector::operator+(const DataVector &other)
{
    if (v.size() != other.v.size())
    {
        std::cout << "[VECTORS OF DIFFERENT SIZE]\n";
        throw std::invalid_argument("Vectors must have the same size for concatenation.");
    }
    DataVector result(v.size());

    for (int i = 0; i < other.v.size(); ++i)
    {
        result.v[i] = v[i] + other.v[i];
    }

    return result;
}

DataVector DataVector::operator-(const DataVector &other)
{
    if (v.size() != other.v.size())
    {
        std::cout << v.size() << " " << other.v.size() << "sub[VECTORS OF DIFFERENT SIZE]\n";
        throw std::invalid_argument("Vectors must have the same size for concatenation.");
    }
    DataVector result(v.size());

    for (int i = 0; i < other.v.size(); ++i)
    {
        result.v[i] = v[i] - other.v[i];
    }

    return result;
}

double DataVector::operator*(const DataVector &other)
{
    if (v.size() != other.v.size())
    {
        std::cout << "[VECTORS OF DIFFERENT SIZE]\n";
        throw std::invalid_argument("Vectors must have the same size for concatenation.");
    }

    double result = 0.0;
    for (int i = 0; i < other.v.size(); ++i)
    {
        result += v[i] * other.v[i];
    }

    return result;
}

double DataVector::norm()
{
    return sqrt((*this) * (*this));
}

double DataVector::dist(const DataVector &other)
{
    return sqrt((*this - other) * (*this - other));
}

void DataVector::push_data(double data)
{
    v.push_back(data);
}

double &DataVector::operator[](int i)
{
    if (i < 0 || i >= v.size())
    {
        throw std::out_of_range("Index out of bounds");
    }
    return v[i];
}

DataVector::~DataVector()
{
}