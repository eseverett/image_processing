#include "process_paths.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <filesystem>


ProcessPaths::ProcessPaths()
: config_path("conf/conf.csv"), preprocessed_peaks_file_path("empty"), water_background_file_path("empty") {}

void ProcessPaths::read_data_file_paths() {
    fstream fin;
    fin.open(config_path, ios::in); 

    if (!fin.is_open()) {
        cerr << "Failed to open file: " << config_path << endl;
        return;
    }

    vector<string> row;
    string line, word;

    while (getline(fin, line)) {
        row.clear();
        stringstream s(line);

        while (getline(s, word, ',')) {
            row.push_back(word);
        }

        try {

            cout << row[0] << " : " << row[1] << endl;

            if (row[0].compare("preprocessed_peaks") == 0) {
                preprocessed_peaks_file_path = row[1];
                cout << "Set path for preprocessed peaks file" << endl;
            } else if (row[0].compare("water_background") == 0) {
                water_background_file_path = row[1];
                cout << "Set path for water background file" << endl;
            } else {
                cerr << "Unknown file path type : " << row[0] << endl;
            }

        } catch (const exception& e) {
            cerr << "Standard exception : " << e.what()  << endl;
        }
    }

    fin.close(); 
}

void ProcessPaths::show_data_file_paths() {
    cout << "preprocessed peak file path : " << preprocessed_peaks_file_path << endl;

    cout << "water background file path : " << water_background_file_path << endl;
}

void ProcessPaths::create_image_directories() {
    string major_directories[4] = {"peaks", "labels", "water", "overlay"};
    string minor_directories[9] = {"01", "02", "03", "04", "05", "06", "07", "08", "09"};

    string parent_image_directory = "images";
    filesystem::create_directory(parent_image_directory);

    for (const auto& maj_dir : major_directories) {
        cout << "Creating directory : " << maj_dir << endl;
        
        for (const auto& min_dir : minor_directories) {
            cout << "Creating directory : " << min_dir << endl;
            filesystem::create_directories(parent_image_directory + "/" + maj_dir + "/" + min_dir);
        }
    }
}