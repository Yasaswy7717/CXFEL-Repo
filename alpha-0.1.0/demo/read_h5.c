#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <hdf5.h>

#define DATASET_NAME "Y"

typedef struct {
    double* data;
    hsize_t dims[2];
} H5Data;

H5Data read_h5(const char* filename, const char* variable, int h5, int transpose) {
    H5Data result;
    result.data = NULL;

    printf("HDF5 library version: %u.%u.%u\n", H5_VERS_MAJOR, H5_VERS_MINOR, H5_VERS_RELEASE);

    if (h5) {
        hid_t file_id, dataset_id, dataspace_id;
        herr_t status;

        // Open the HDF5 file
        file_id = H5Fopen(filename, H5F_ACC_RDONLY, H5P_DEFAULT);
        if (file_id < 0) {
            fprintf(stderr, "Error opening file: %s\n", filename);
            exit(EXIT_FAILURE);
        }

        // Open the dataset
        dataset_id = H5Dopen2(file_id, variable, H5P_DEFAULT);
        if (dataset_id < 0) {
            fprintf(stderr, "Error opening dataset: %s\n", variable);
            H5Fclose(file_id);
            exit(EXIT_FAILURE);
        }

        // Get the dataspace
        dataspace_id = H5Dget_space(dataset_id);
        if (dataspace_id < 0) {
            fprintf(stderr, "Error getting dataspace\n");
            H5Dclose(dataset_id);
            H5Fclose(file_id);
            exit(EXIT_FAILURE);
        }

        // Get dimensions
        int ndims = H5Sget_simple_extent_ndims(dataspace_id);
        if (ndims != 2) {
            fprintf(stderr, "Expected 2 dimensions in the dataset\n");
            H5Sclose(dataspace_id);
            H5Dclose(dataset_id);
            H5Fclose(file_id);
            exit(EXIT_FAILURE);
        }
        H5Sget_simple_extent_dims(dataspace_id, result.dims, NULL);

        // Allocate memory for the data
        result.data = (double*)malloc(result.dims[0] * result.dims[1] * sizeof(double));

        // Read the data
        status = H5Dread(dataset_id, H5T_NATIVE_DOUBLE, H5S_ALL, H5S_ALL, H5P_DEFAULT, result.data);
        if (status < 0) {
            fprintf(stderr, "Error reading data from dataset\n");
            free(result.data);
            result.data = NULL;
            H5Sclose(dataspace_id);
            H5Dclose(dataset_id);
            H5Fclose(file_id);
            exit(EXIT_FAILURE);
        }

        // Optionally transpose the data
        if (transpose) {
            double* transposed_data = (double*)malloc(result.dims[0] * result.dims[1] * sizeof(double));
            for (hsize_t i = 0; i < result.dims[0]; ++i) {
                for (hsize_t j = 0; j < result.dims[1]; ++j) {
                    transposed_data[j * result.dims[0] + i] = result.data[i * result.dims[1] + j];
                }
            }
            free(result.data);
            result.data = transposed_data;
        }

        // Close resources
        H5Sclose(dataspace_id);
        H5Dclose(dataset_id);
        H5Fclose(file_id);
    } else {
        // Implement the case when h5=False (using other libraries or methods)
        fprintf(stderr, "Unsupported format (h5=False) in C implementation\n");
        exit(EXIT_FAILURE);
    }

    return result;
}

void free_h5_data(H5Data* data) {
    if (data->data != NULL) {
        free(data->data);
        data->data = NULL;
    }
}