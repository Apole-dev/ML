#include <iostream>
#include <string>
#include "Data/Data.h"
#include "Data Hub/DataHub.h"

/*
 * Some bugs have that i diidnt fix it yet;
 * System work for read simple data set but not for complex data set
 * I used DataHub to read data set
 * I used Data to classify data
 * HANDWRITEN DATA SET USED
 */

using namespace std;

int main() {

    DataHub::DataHub dataHub;

    std::string imagePath = R"(C:\Users\Eren\CLionProjects\ML\archive\t10k-images.idx3-ubyte)";
    std::string labelPath = R"(C:\Users\Eren\CLionProjects\ML\archive\t10k-labels.idx1-ubyte)";
    DataHub::DATA_SET_TYPE dataType = DataHub::TEST;
    dataHub.AssosicateData(dataType, imagePath, labelPath);
    vector<DataSet::Data*> *validatonData = dataHub.GetValidationData();

    printf("validation data size %u",validatonData->size());



    return 0;
}
