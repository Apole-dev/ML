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


    Knn(DataHandler::DataHub *data_hub);

    vector<DataSet::Data*> neighbors;

    void FindKnn(int k);
    double CalculateDistance(uint8_t *data);
    double GetDistance();
    void SetDistance(double distance);
};


