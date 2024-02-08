#include "VectorDataSet.h"
#include <queue>
#include <chrono>

double distance(DataVector v1, DataVector v2)
{
    return v1.dist(v2);
}

class Compare
{
    DataVector test;

public:
    Compare(DataVector &testvec)
    {
        test = testvec;
    }
    bool operator()(DataVector d1, DataVector d2)
    {
        return (d1.dist(test) < d2.dist(test));
    }
};

VectorDataset kNearestNeighbours(DataVector test, VectorDataset data, int k)
{
    std::priority_queue<DataVector, std::vector<DataVector>, Compare> pq{Compare(test)};

    for (int i = 0; i < k; i++)
    {
        pq.push(data[i]);
    }

    for (int i = k; i < data.size(); i++)
    {
        DataVector dv = pq.top();

        if (data[i].dist(test) < dv.dist(test))
        {
            pq.pop();
            pq.push(data[i]);
        }
    }

    VectorDataset result;

    for (int i = 0; i < k; i++)
    {
        DataVector dv = pq.top();

        result.push(dv);
        // std::cout << result[i].dist(test) << std::endl;
        pq.pop();
    }

    return result;
}

int main()
{
    int rows, cols, k = 5;
    std::chrono::time_point<std::chrono::system_clock> start, end;

    VectorDataset data(60001, 784);
    data.ReadDataset("fmnist-train.csv");
    VectorDataset tests(10001, 784);
    tests.ReadDataset("fmnist-test.csv");

    VectorDataset ans;

    start = std::chrono::system_clock::now();
    for (int i = 0; i < 100; i++)
    {
        ans = kNearestNeighbours(tests[i], data, k);
    }
    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "TIME: " << elapsed_seconds.count() << std::endl;
}

// 152.538 sec