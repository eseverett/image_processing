#ifndef IMAGE_ATTRIBUTES_H
#define IMAGE_ATTRIBUTES_H

#include <string>

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
    void read_attributes();
};



#endif // IMAGE_ATTRIBUTES_H