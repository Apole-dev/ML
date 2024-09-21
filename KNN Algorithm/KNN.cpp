//
// Created by Eren on 9/20/2024.
//

#include "KNN.h"

#include <cmath>


namespace ML_ALGORITHMS {

    KNN::KNN(DataHandler::DataHub dataHub,int k) : KNN_DataHub(dataHub)  {
    }


    void KNN::FindNearestNeighbors() {
        if(K <= 0) {printf("K value must be greater than 0\n"); exit(1);}
        nearestNeighbors.clear();

        vector<DataSet::Data*> *testDataSet = KNN_DataHub.GetTestData(); //10k
        vector<DataSet::Data*> *trainDataSet = KNN_DataHub.GetTrainData(); //60k

        uint32_t imagePixels = KNN_DataHub.COLUMNS * KNN_DataHub.ROWS;

        //TODO : Optimize this
        for (int i = 0; i < testDataSet->size(); ++i) {
            for (int k = 0; k < trainDataSet->size() ; ++k) {
                for (int l = 0; l < imagePixels; ++l) {
                    double result = CalculateDistance(testDataSet->at(i)->GetFeatureVector()->at(l), trainDataSet->at(k)->GetFeatureVector()->at(k));
                    distanceMap.insert( make_pair(result, trainDataSet->at(i)) );
                }
            }
        }
        printf("Done\n");


    }
    void SetLabel();
    DataSet::LABEL GetLabel();
    double CalculateDistance(uint8_t data1, uint8_t data2) {
        return sqrt(pow(data1 - data2, 2));
    };
    void Predict();
    void KNN::UpdateK(int k) {
        if (k <= 0) {printf("K value must be greater than 0\n"); exit(1);}
        K = k;
    }

}
