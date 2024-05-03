#ifndef PROCESS_PATHS_H
#define PROCESS_PATHS_H

#include <string>

using namespace std;

class ProcessPaths {
    public:
    
    ProcessPaths();

    void read_data_file_paths();
    void show_data_file_paths();
    void create_image_directories();
    void rename_files();

    private:

    string config_path;
    string preprocessed_peaks_file_path;
    string water_background_file_path;
};

#endif // PROCESS_PATHS