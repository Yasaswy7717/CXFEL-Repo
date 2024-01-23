#include <stdlib.h>
#include <stdio.h>
#include "read_h5.h"

int main() {
     // Get the value of CXFEL_ROOT environment variable
    const char* cxfel_root_c = getenv("CXFEL_ROOT_C");
    if (cxfel_root_c == NULL) {
        fprintf(stderr, "Error: CXFEL_ROOT environment variable not set.\n");
        return EXIT_FAILURE;
    }

    // Construct the filename
    char filename[256]; // Adjust the size based on your needs
    snprintf(filename, sizeof(filename), "%s/data/DM_Spiral.mat", cxfel_root_c);


    const char* variable = "Y";
    int h5 = 1; // Set to 1 if using HDF5, 0 if using other format
    int transpose = 1; // Set to 1 if you want to transpose the data

    H5Data result = read_h5(filename, variable, h5, transpose);

    // Process or print the data as needed
    printf("Data dimensions: %llu x %llu\n", result.dims[0], result.dims[1]);

    // Free allocated memory
    free_h5_data(&result);

    return 0;
}