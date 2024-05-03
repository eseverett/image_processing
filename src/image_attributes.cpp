#include "image_attributes.h"

#include <iostream>
#include <filesystem>
#include <regex>

ImageAttributes::ImageAttributes() {}

void ImageAttributes::write_attributes(ImageType image_type) {

    bool peak_val;

    switch (image_type) {
        case peaks:
            cout << "Writing peaks image attributes" << endl;
            peak_val = true;
            break;
        case water:
            cout << "Writing water image attributes" << endl;
            peak_val = false;
            break;
        case overlay:
            cout << "Writing overlay image attributes" << endl;
            peak_val = true;
            break;
        default:
            throw invalid_argument("Invalid image type");
    }
}

void ImageAttributes::read_attributes() {
    cout << "Reading image attributes" << endl;
}