#include <iostream>
#include <filesystem>

#include "process_paths.h"
#include "image_attributes.h"

using namespace std;


int main() {
    cout << "----- Starting Image Processing -----" << endl;

    cout << "Current path: " << filesystem::current_path() << endl;

    ProcessPaths process_paths;
    process_paths.read_data_file_paths();
    process_paths.show_data_file_paths();
    process_paths.create_image_directories();
    process_paths.rename_files();   

    ImageAttributes image_attributes;

    return 0;
}