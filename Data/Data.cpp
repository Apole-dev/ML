//
// Created by Eren on 13/9/2024.
//

// ReSharper disable CppMemberFunctionMayBeConst
#include "Data.h"

namespace DataSet {
    Data::Data() : featureVector(nullptr), label(ZERO), label_Indicator(ZERO) {}

    Data::~Data() {
        // Freeing featureVector if it's not nullptr
        if (featureVector) {
            delete featureVector;
        }
    }

    void Data::InitFeatureVector(vector<uint8_t>* featureVector) {
        this->featureVector = featureVector;
    }
    void Data::AppendElementToFeatureVector(uint8_t element) {
        if (featureVector) {
            this->featureVector->push_back(element);
        }
    }

    void Data::SetLabel(uint8_t label) {
        this->label = label;
    }
    void Data::SetLabel_Indicator(LABEL label_Indicator) {
        this->label_Indicator = label_Indicator;
    }

    vector<uint8_t> *Data::GetFeatureVector()  {
        return this->featureVector;
    }
    unsigned  Data::GetFeatureVectorSize()  {
        return featureVector ? featureVector->size() : 0;
    }
    LABEL Data::GetLabel_Indicator() {
        return this->label_Indicator;
    }
}