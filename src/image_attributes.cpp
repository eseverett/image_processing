#include "image_attributes.h"
#include "H5cpp.h"

#include <iostream>
#include <filesystem>
#include <regex>


using namespace H5;

ImageAttributes::ImageAttributes() {
    peaks_file_path = "images/peaks";
    water_file_path = "images/water";
    overlay_file_path = "images/overlay";
    sub_files[0] = "01";
    sub_files[1] = "02";
    sub_files[2] = "03";
    sub_files[3] = "04";
    sub_files[4] = "05";
    sub_files[5] = "06";
    sub_files[6] = "07";
    sub_files[7] = "08";
    sub_files[8] = "09";
    camera_length_map["01"] = "0.15";
    camera_length_map["02"] = "0.25";
    camera_length_map["03"] = "0.35";
}

void ImageAttributes::write_attributes(ImageType image_type) {

    bool peak_val;
    string file_path;
    string current_file_path;
    regex pattern("img_([0-9]+)keV_clen([0-9]+)_");
    smatch matches;

    string photon_energy;
    string camera_length;

    switch (image_type) {
        case peaks: 
            cout << "Writing peaks image attributes" << endl;
            peak_val = true;
            file_path = peaks_file_path;
            break;
        case water:
            cout << "Writing water image attributes" << endl;
            peak_val = false;
            file_path = water_file_path;
            break;
        case overlay:
            cout << "Writing overlay image attributes" << endl;
            peak_val = true;
            file_path = overlay_file_path;
            break;
        default:
            throw invalid_argument("Invalid image type");
    }

    for (const auto& sub : sub_files) {
        current_file_path = file_path + "/" + sub;
        cout << "Directory : " << current_file_path << endl;
        for (const auto& entry : filesystem::directory_iterator(current_file_path)) {
            auto current_file = entry.path().string();
            if (regex_search(current_file, matches, pattern)) {
                photon_energy = matches[1];
                camera_length = matches[2];
                
                camera_length = camera_length_key(camera_length);
                cout << "Photon Energy : " << photon_energy << "keV" << endl;   
                cout << "Clen Category : " << camera_length << "m" << endl; 
            } else {
                cout << "No match found" << endl;
            }

            H5File file(current_file, H5F_ACC_RDWR);

        }   
    }
}

string ImageAttributes::camera_length_key(string clen_val) {
    map<string, string>::iterator it = camera_length_map.begin();
    
    while (it != camera_length_map.end()) {
        if (it->first == clen_val) {
            return it->second;
        }
        it++;
    }
    return clen_val;
}

void ImageAttributes::read_attributes() {
    cout << "Reading image attributes" << endl;
}