//
// Created by Eren on 13/9/2024.
//

#ifndef DATA_H
#define DATA_H

#include <cstdint>
#include <vector>
using namespace  std;

namespace DataSet {
    enum LABEL {
        ZERO = 0,
        ONE = 1,
        TWO = 2,
        THREE = 3,
        FOUR = 4,
        FIVE = 5,
        SIX = 6,
        SEVEN = 7,
        EIGHT = 8,
        NINE = 9
    };

    class Data {

    private:
        vector<uint8_t> *featureVector; //store the data of pixels in the image 28*28
        uint8_t label; //Indcates the label of the image
        LABEL label_Indicator ; //To store labels with Enum

    public:
        Data();
        ~Data();
        void InitFeatureVector(vector<uint8_t>* featureVector);
        void AppendElementToFeatureVector(uint8_t element);
        void SetLabel(uint8_t label);
        void SetLabel_Indicator(LABEL label_Indicator);

        vector<uint8_t> *GetFeatureVector();
        unsigned GetFeatureVectorSize();
        LABEL GetLabel_Indicator();
    };


}

#endif //DATA_H
