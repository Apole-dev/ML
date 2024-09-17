//
// Created by Eren on 9/15/2024.
//

#ifndef KNNALGORITHM_H
#define KNNALGORITHM_H
#include <cstdint>
#include <vector>

#include "../Data Hub/DataHub.h"
#include "../Data/Data.h"

using namespace std;
#endif //KNNALGORITHM_H

class Knn {

public:
    int K_VALUE = 0;
    DataHandler::DataHub *data_hub;


    Knn(DataHandler::DataHub *data_hub);
    vector<DataSet::Data*> neighbors;
    map<DataSet::LABEL,int> classFrequency;

    void FindKnnNeighbors(int k);
    double CalculateDistance(uint8_t testDataPoint, uint8_t trainDataPoin);
    DataSet::LABEL GetMajorityLabel();
    void Predict(int k);
};


