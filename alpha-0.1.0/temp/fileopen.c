#include "C:\Users\yasaswy\AppData\Local\Programs\Python\Python310\include\Python.h"

int main() {
    // Initialize the Python interpreter
    Py_Initialize();

    // Run your Python code
    PyRun_SimpleString(
        "import sys\n"
        "sys.path.insert(0, 'C:/ResearchAideProjects/enhanced-information-retrieval-C/alpha-0.1.0/temp/read_h5_')\n"
        "from read_h5_ import read_h5\n"
        "result = read_h5('DM_Spiral.mat', 'Y', False, True)\n"
        "print(result)\n"
    );

    // Finalize the Python interpreter
    Py_Finalize();
    return 0;
}