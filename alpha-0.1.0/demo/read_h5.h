#ifndef READ_H5_H
#define READ_H5_H

#include <hdf5.h>

typedef struct {
    double* data;
    hsize_t dims[2];
} H5Data;

H5Data read_h5(const char* filename, const char* variable, int h5, int transpose);
void free_h5_data(H5Data* data);

#endif /* READ_H5_H */