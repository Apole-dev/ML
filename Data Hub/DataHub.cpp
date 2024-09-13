//
// Created by Eren on 9/11/2024.
//

#include "DataHub.h"
using namespace DataSet; //DataSet::Data
using namespace DataHub; //DataHub::DataHub
//TODO : Print in a better way

namespace DataHub {
    int numberOfImages = 0;//TODO FİX THIS

    DataHub::DataHub() = default;

    DataHub::~DataHub() {

    }


    vector<uint8_t>  DataHub::ReadImageData(const string &path) {
        if(path.empty()) return {};
        printf("------------------------------------------------------------\n");
        printf("Data Set Path: %s\n", path.c_str()); //Debug to show the path of the data set

        uint32_t magicNum;
        uint32_t imageNum;
        uint32_t numberOfRows; // 28 pixels in this dataset
        uint32_t numberOfColumns; // 28 pixels in this dataset


        FILE* dataFile = fopen(path.c_str(), "rb");
        if(dataFile == nullptr ){ printf("File not found: %s\n", path.c_str() ); exit(1); } // to check if file is found

        /*Fread do not read from same location twice it continues until file is closed*/

        fread(&magicNum, sizeof(uint32_t), 1, dataFile); //NTMS
        magicNum = ConvertToLittleEndian(reinterpret_cast<unsigned char*>(&magicNum));
        printf("Magic Number for Image: %u\n", magicNum);
        if(magicNum != MAGIC_IMAGE_NUMBER) { printf("Wrong Magic Number at ReadImageData : %u\n", magicNum); exit(1); }


        fread(&imageNum, sizeof(uint32_t), 1, dataFile);
        imageNum = ConvertToLittleEndian(reinterpret_cast<unsigned char*>(&imageNum));
        numberOfImages = imageNum;
        printf("Number of Image : %u\n", imageNum); // Output the image number

        fread(&numberOfRows, sizeof(uint32_t), 1, dataFile);
        numberOfRows = ConvertToLittleEndian(reinterpret_cast<unsigned char*>(&numberOfRows));
        fread(&numberOfColumns, sizeof(uint32_t), 1, dataFile);
        numberOfColumns = ConvertToLittleEndian(reinterpret_cast<unsigned char *>(&numberOfColumns));
        printf("Number of Rows: %u, Number of Columns: %u\n", numberOfRows, numberOfColumns); // Output the number of columns

        vector<uint8_t> pixels((numberOfRows * numberOfColumns)*imageNum);
        size_t result = fread(pixels.data(), sizeof(uint8_t),pixels.size(), dataFile);
        if(result != pixels.size()) { printf("Error reading file: %s\n", path.c_str() ); exit(1); }

        fclose(dataFile);
        return pixels;
    }

#pragma region ReadLabelData

    vector<uint8_t>  DataHub::ReadLabelData(const string &path) {
        if(path.empty()) return {};

        uint32_t magicNum;
        uint32_t itemNum;

        printf("------------------------------------------------------------\n");
        printf("Data Set Path: %s\n", path.c_str()); //Debug to show the path of the data set

        FILE* dataFile = fopen(path.c_str(), "rb");
        if(dataFile == nullptr ){ printf("File not found: %s\n", path.c_str() ); exit(1); }

        /*Fread do not read from same location twice it continues until file is closed*/

        // Read the magic number (4 bytes = 32-bit integer)
        fread(&magicNum, sizeof(uint32_t), 1, dataFile);
        magicNum = ConvertToLittleEndian(reinterpret_cast<unsigned char*>(&magicNum));
        if(magicNum != MAGIC_LABLE_NUMBER) { printf("Wrong Magic Number at ReadLabelData : %u\n", magicNum); exit(1); }
        printf("Magic Number for Labels: %u\n", magicNum); // Output the magic number


        // Read the number of items (4 bytes = 32-bit integer) to assign to array capacity
        fread(&itemNum, sizeof(uint32_t), 1, dataFile);
        itemNum = ConvertToLittleEndian(reinterpret_cast<unsigned char*>(&itemNum));
        printf("Number of Labels: %u\n", itemNum); // Output the number of images


        vector<uint8_t> labels(itemNum);
        size_t result = fread(labels.data(), sizeof(uint8_t), itemNum, dataFile);
        if (result != itemNum) {
            printf("Error reading label data\n");
            exit(1);
        }

        fclose(dataFile); // Close the file after reading

        //ControlReadedLabels(&labels, itemNum);
        return labels;


    }
    void DataHub::ControlReadedLabels(const vector<uint8_t> *labels, const uint32_t itemNum) {
        for (int i = 0; i < itemNum; i *= 400 ) {
            printf("Label %zu: %hhu \n", i, (*labels)[i]); //NTMS
        }
    }

#pragma endregion

    void DataHub::AssosicateData(DATA_SET_TYPE type,const string &ImagePath, const string &Labelpath ){

        vector<uint8_t> labelData = ReadLabelData(Labelpath);
        vector<uint8_t> imageData = ReadImageData(ImagePath);

        if (labelData.size() != numberOfImages) {
            printf("Mismatch between label data size and image data size\n");
            return;
        }

        switch (type) {
            case TRAIN:
                printf("Train case\n");
                for (size_t i = 0; i < labelData.size(); ++i) {
                    Data* data = new Data();
                    data->AppendElementToFeatureVector(imageData[i]);
                    data->SetLabel(labelData[i]);
                    data->SetLabel_Indicator(static_cast<LABEL>(labelData[i]));
                    LabelMap.insert({labelData[i], static_cast<LABEL>(labelData[i])});
                    TrainData->push_back(data);
                }
                printf("Train Case data added\n");
            break;
            case TEST:
                for (size_t i = 0; i < labelData.size(); ++i) {
                    Data* data = new Data();
                    data->AppendElementToFeatureVector(imageData[i]);
                    data->SetLabel(labelData[i]);
                    data->SetLabel_Indicator(static_cast<LABEL>(labelData[i]));
                    LabelMap.insert({labelData[i], static_cast<LABEL>(labelData[i])});
                    TestData->push_back(data);
                }
            printf("Test Case data added\n");
            break;
            case VALIDATION: {
                //TODO SPLIT VALIDATION DATA
                int validationSize = labelData.size() * VALIDATION_PERCENT;
                for (int i = validationSize; i < labelData.size(); ++i) {
                    Data* data = new Data();
                    data->AppendElementToFeatureVector(imageData[i]);
                    data->SetLabel(labelData[i]);
                    data->SetLabel_Indicator(static_cast<LABEL>(labelData[i]));
                    LabelMap.insert({labelData[i], static_cast<LABEL>(labelData[i])});
                    ValidationData->push_back(data);
                }
                printf("Validation Case data added\n");
            }
            break;
            default: printf("Default segment called\n");
        }
        printf("Successfully loaded data\n");
    }



    /*Convert to data Big Endian to Little Endian,
     *Most modern systems, including Intel and AMD processors, use the little-endian format
     *so we dont need to use it.*/
    uint32_t DataHub::ConvertToLittleEndian(unsigned char* bytes) {
        return (static_cast<uint32_t>(bytes[0]) << 24) |
       (static_cast<uint32_t>(bytes[1]) << 16) |
       (static_cast<uint32_t>(bytes[2]) << 8)  |
       static_cast<uint32_t>(bytes[3]);
    }


    //TODO I AM NOT SURE FOR THAT
    vector<Data*> *DataHub::GetLabelData() {
    }
    vector<Data*> *DataHub::GetTestData() {
        if (ControlData(TestData)) return TestData;

        return nullptr;
    }
    vector<Data*> *DataHub::GetTrainData() {
        if (ControlData(TrainData)) return TrainData;

        return nullptr;
    }
    vector<Data*> *DataHub::GetValidationData() {
        if (ControlData(ValidationData)) return ValidationData;

        return nullptr;
    }

    bool DataHub::ControlData(vector<Data*> *data) {
        if(data->empty()){printf("Data is empty\n"); return false;};
        return true;
    }

} // DataHub