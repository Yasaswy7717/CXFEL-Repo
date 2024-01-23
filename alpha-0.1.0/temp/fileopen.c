#include <stdio.h>
#include <stdlib.h>
#include <matio.h>

int main() {
    // Open the MATLAB file
    mat_t *matfp = Mat_Open("DM_Spiral.mat", MAT_ACC_RDONLY);
    if (matfp == NULL) {
        fprintf(stderr, "Error opening file.\n");
        return EXIT_FAILURE;
    }

    // Read a variable from the file (replace "variable_name" with the actual variable name)
    matvar_t *matvar = Mat_VarRead(matfp, "variable_name");
    if (matvar == NULL) {
        fprintf(stderr, "Error reading variable from file.\n");
        Mat_Close(matfp);
        return EXIT_FAILURE;
    }

    // Access the data (assuming the variable is numeric)
    double *data = (double *)matvar->data;
    size_t numel = matvar->nbytes / sizeof(double);

    // Print the data (assuming a 1D array)
    printf("Data:\n");
    for (size_t i = 0; i < numel; ++i) {
        printf("%f ", data[i]);
    }
    printf("\n");

    // Release resources
    Mat_VarFree(matvar);
    Mat_Close(matfp);

    return EXIT_SUCCESS;
}
