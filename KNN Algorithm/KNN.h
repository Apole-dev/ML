//
// Created by Eren on 9/20/2024.
//

#ifndef KNN_H
#define KNN_H
#include <vector>

#include "../Data Hub/DataHub.h"
#include "../Data/Data.h"

namespace ML_ALGORITHMS {
    class KNN {

    public:
        std::vector<DataSet::Data> nearestNeighbors;
        map<double,DataSet::Data*> distanceMap;
        DataHandler::DataHub KNN_DataHub;

        KNN(DataHandler::DataHub);
        void FindNearestNeighbors(int k);
        void SetLabel();
        DataSet::LABEL GetLabel();
        double CalculateDistance(uint8_t, uint8_t);
        void Predict();
    };

}

#endif //KNN_H
