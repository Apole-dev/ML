//
// Created by Eren on 9/15/2024.
//

#include "KnnAlgorithm.h"

#include <cmath>

using namespace std;

Knn::Knn(DataHandler::DataHub *data_hub): data_hub(nullptr) {
    this->data_hub = data_hub;
    neighbors = vector<DataSet::Data*>();
}

void Knn::FindKnnNeighbors(int k) {
    if(k <= 0) {printf("K cannot be less than or equal to 0\n"); exit(1);}
    K_VALUE = k;

    printf("K: %d\n", K_VALUE);

    auto testDataSet = data_hub->GetTestData();
    auto trainDataSet = data_hub->GetTrainData();

    if (trainDataSet == nullptr || testDataSet == nullptr) {
        printf("Data is empty\n");
        exit(1);
    }

    multimap<double,DataSet::Data*> distances;

    for (const auto & i : *testDataSet) {
        vector<uint8_t>* testDataVector = i->GetFeatureVector();

        for (int j = 0; j < trainDataSet->size(); ++j) {

            vector<uint8_t> *trainDataVector = trainDataSet->at(j)->GetFeatureVector();
            double distance = 0;
            for (int p = 0; p < testDataVector->size(); ++p) {
                distance += CalculateDistance(testDataVector->at(p), trainDataVector->at(p));
            }
            distances.insert(make_pair(distance,trainDataSet->at(j)));

        }

    }

    printf("testing cc");

    auto it = distances.begin();
    for (int i = 0; i < K_VALUE; ++i) {
        neighbors.push_back(it->second);
        ++it;
        printf("neighbors size: %d\n", neighbors.size());

    }

    neighbors.clear();

}

double Knn::CalculateDistance(uint8_t testDataPoint, uint8_t trainDataPoint) {
    double distance = 0;
    distance = pow((testDataPoint - trainDataPoint), 2);
    distance = sqrt(distance);

    return distance;
}



DataSet::LABEL Knn::GetMajorityLabel() {

    DataSet::LABEL best_label = {};

    int max_count = 0;

    for (auto &kv : classFrequency) {
        if (kv.second > max_count) {
            max_count = kv.second;
            best_label = kv.first;
        }
    }

    return best_label;
}

void Knn::Predict(int k) {

    FindKnnNeighbors(k);
    printf("neighbors size: %d\n" , neighbors.size());
    for (int i = 0; i < neighbors.size(); ++i) {
        DataSet::LABEL label = neighbors.at(i)->GetLabel_Indicator();
        if (classFrequency.find(label) == classFrequency.end()) {
            classFrequency.insert({label,1});
        } else {
            classFrequency[label]++;
        }
    }

    std::map<uint8_t, double> class_probabilities;
    for (auto &kv : classFrequency) {
        double probability = (static_cast<double>(kv.second) / neighbors.size()) * 100;
        class_probabilities[kv.first] = probability;
    }

    printf("Class probabilities:\n");
    for (auto &kv : class_probabilities) {
        printf("Class %d: %.2f%%\n", kv.first, kv.second);
    }

}


