#include "DataVector.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class VectorDataset
{
    std::vector<DataVector> data; // Vector of datavectors to store all datapoints

public:
    VectorDataset(int rows = 0, int cols = 0) // Constructor to initailise the vector to required dimensions
    {
        data.resize(rows, DataVector(cols));
    }

    ~VectorDataset() // Default destructor
    {
    }

    std::vector<DataVector> GetVector() // returns the Dataset of vectors
    {
        return data;
    }
    void SetVector(std::vector<DataVector> param) // sets dataset to a existing dataset of vectors
    {
        data = param;
    }

    void ReadDataset(const std::string &filename) // Function to read from the csv files to create the dataset
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            std::cerr << "Error opening file: " << filename << std::endl;
            return;
        }

        int row_idx = 0, col_idx = 0;
        std::string line;
        while (std::getline(file, line)) // reads till the end of file
        {

            std::stringstream ss(line);
            std::string value;
            DataVector row;

            while (std::getline(ss, value, ','))
            {
                // Handle potential errors during parsing
                try
                {
                    data[row_idx][col_idx] = std::stod(value);
                }
                catch (const std::exception &e) // Error handling
                {
                    std::cerr << "Error parsing value: " << value << std::endl;
                }
                col_idx++;
            }
            row_idx++;
            col_idx = 0;
        }
    }

    DataVector operator[](int i) // Operator overload to access points in the vector by indexing
    {
        if (i < 0 || i >= data.size()) // check in range
        {
            throw std::out_of_range("Index out of bounds");
        }
        return data[i];
    }

    int size() // returns number of datapoints in the Dataset
    {
        return data.size();
    }

    void push(DataVector v) // Pushes a new datapoint into the Dataset
    {
        data.push_back(v);
    }
};