//
// Created by Eren on 10/9/2024.
//

/* NOTES:
 * Validation Data : To make sure the model is not overfitting
 * Test Data : To test the model with new data or unseen data
 */

// ReSharper disable CppFunctionIsNotImplemented
#ifndef DATAHUB_H
#define DATAHUB_H
#include <map>
#include <vector>
#include "../Data/Data.h"

using namespace std; // i hate " ::std "


namespace DataHandler {

enum DATA_SET_TYPE {
    TRAIN = 0,
    TEST = 1,
    VALIDATION = 2
};

class DataHub {

protected:
    void ControlReadedLabels(const vector<uint8_t> *labels, const uint32_t itemNum);
    void ControlReadedImages(const vector<uint8_t> *images, const uint32_t itemNum);
    //TODO REDUCE FUNCTION COUNT


public:
    DataHub();
    ~DataHub();

    uint8_t NumberOfClasses{}; //Number of classes in the dataset
    uint8_t NumberOfFeatures{}; //Feature vector size
    map<uint8_t,DataSet::LABEL> LabelMap; //Maps class labels to their indexes


    //Magic number in the dataset to check if it is a valid dataset
    const int MAGIC_LABLE_NUMBER = 2049;
    const int MAGIC_IMAGE_NUMBER = 2051;


    const double VALIDATION_PERCENT = 0.10;

    vector<DataSet::Data*> *TrainData{}; //label and image datas
    vector<DataSet::Data*> *TestData{}; //label and image datas
    vector<DataSet::Data*> *ValidationData{};


    vector<uint8_t>  ReadLabelData(const string &path);
    vector<uint8_t>  ReadImageData(const string &path);
    uint32_t ConvertToLittleEndian(unsigned char* bytes);
    void AssosicateData(DATA_SET_TYPE type, const string &ImagePath, const string &Labelpath);

    vector<DataSet::Data*> *GetLabelData();
    vector<DataSet::Data*> *GetTestData();
    vector<DataSet::Data*> *GetTrainData();
    vector<DataSet::Data*> *GetValidationData();

    bool ControlData(vector<DataSet::Data *> *data);

};

} // DataHub

#endif //DATAHUB_H
