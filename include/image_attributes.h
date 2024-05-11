#ifndef IMAGE_ATTRIBUTES_H
#define IMAGE_ATTRIBUTES_H

#include <string>
#include <map>
#include <array>

using namespace std;

enum ImageType {
    peaks,
    water,
    overlay,
    labels
};


class ImageAttributes {

    public:

    ImageAttributes();

    void write_attributes(ImageType image_type);
    string camera_length_key(string clen_val);
    void read_attributes();
    int* open_h5(string file_path);

    private:

    string peaks_file_path;
    string water_file_path;
    string overlay_file_path;
    string sub_files[9];
    map<string, string> camera_length_map;
};



#endif // IMAGE_ATTRIBUTES_H