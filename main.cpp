#include <iostream>
#include <string>
#include "Data/Data.h"
#include "Data Hub/DataHub.h"
#include "windows.h"
#include "KNN Algorithm/KNN.h"


/*
 * Known Issues:
 * - There are some unresolved bugs(I dont know actually what they are).
 * - The system is currently functional for reading MNIST dataset.
 *
 * Overview:
 * - The DataHub class is used to handle the loading and management of dataset files.
 * - The Data class is used for storing and classifying the data once it has been read.
 *
 * Dataset:
 * - The system is designed to work with a handwritten digit dataset (e.g., MNIST).
 * - It reads image and label data, and associates them for classification tasks.
 *
 * TODO:
 * - Fix issues related to handling complex datasets (e.g., larger image sizes, more diverse data types).
 * - Optimize the performance for larger datasets and improve error handling.
 * - Improve the robustness and generalization of the data parsing functions.
 */


using namespace std;

int main() {

#ifdef _WIN32
    char buffer[MAX_PATH];
    GetCurrentDirectory(sizeof(buffer), buffer);
    std::string current_directory(buffer);
    const string cmake_build_debug = "\\cmake-build-debug";
    current_directory.erase(current_directory.find(cmake_build_debug), cmake_build_debug.length());
    std::cout << "Current working directory: " << current_directory << std::endl;
    //Show the current working directory without the "cmake-build-debug" part
#endif


    DataHandler::DataHub dataHub;

    const string testImagePath = R"(C:\Users\Eren\CLionProjects\ML\archive\t10k-images.idx3-ubyte)";
    const string testLabelPath = R"(C:\Users\Eren\CLionProjects\ML\archive\t10k-labels.idx1-ubyte)";

    constexpr DataHandler::DATA_SET_TYPE dataType_Test  = DataHandler::TEST;
    dataHub.AssosicateData(dataType_Test, testImagePath, testLabelPath);



    const string trainImagePath = R"(C:\Users\Eren\CLionProjects\ML\archive\train-images.idx3-ubyte)";
    const string trainLabelPath = R"(C:\Users\Eren\CLionProjects\ML\archive\train-labels.idx1-ubyte)";

    constexpr DataHandler::DATA_SET_TYPE dataType_Train = DataHandler::TRAIN;
    dataHub.AssosicateData(dataType_Train, trainImagePath, trainLabelPath);



    ML_ALGORITHMS::KNN KNN(dataHub);
    KNN.FindNearestNeighbors(3);



    return 0;
}
