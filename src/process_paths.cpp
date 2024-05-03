#include "process_paths.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <filesystem>
#include <boost/algorithm/string.hpp>
#include <regex>

using namespace boost::algorithm;


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
                trim_left(row[1]);
                trim_right(row[1]);
                preprocessed_peaks_file_path = row[1];
                cout << "Set path for preprocessed peaks file" << endl;
            } else if (row[0].compare("water_background") == 0) {
                trim_left(row[1]);
                trim_right(row[1]);
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

void ProcessPaths::rename_files() {
    cout << "Getting files from : " << preprocessed_peaks_file_path << endl;

    string peak_path = "images/peaks";
    string prev_dataset = "01";
    int index = 1;
    string new_dataset;

    regex pattern("([0-9]+)_([0-9]+)keV_clen([0-9]+)_");
    smatch matches;

    for (const auto& entry : filesystem::directory_iterator(preprocessed_peaks_file_path)) {
        auto current_file = entry.path().string();
        cout << "old file name : " << current_file << endl;
        if (regex_search(current_file, matches, pattern)) {
            cout << "Dataset : " << matches[1] << endl;
            cout << "Photon Energy : " << matches[2] << "keV" << endl;   
            cout << "Clen Category : " << matches[3]  << endl;  

            if (matches[1].str().compare(prev_dataset) != 0) {
                index = 1;
                prev_dataset = matches[1].str();
            } 
            for (int i = 0; i < 5 - to_string(index).length(); i++) {
                new_dataset += "0";
            }
            new_dataset += to_string(index);
            index++;
            

            string new_file_name = "img_" + matches[2].str() + "keV_clen" + matches[3].str() + "_" + new_dataset + ".h5";

            try {
                filesystem::rename(current_file, peak_path + "/" + matches[1].str() + "/" + new_file_name);
                cout << "Moved file : " << new_file_name << endl;
            } catch (const exception& e) {
                cerr << "Standard exception : " << e.what()  << endl;
            }

            new_dataset = "";

        } else {
            cout << "No match found." << endl;;
        }
    }
}

