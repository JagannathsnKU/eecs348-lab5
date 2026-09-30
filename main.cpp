/*
 * Name: Jagannath Sritinath Nair
 * Assignment: Lab 5
 * Purpose: Reads N x N matrices from file and performs matrix arithmetic 
 *          (addition, multiplication), diagonal sums, row/column swaps, and element updates.
 * Date: September 30, 2026
 */



#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

using Matrix = vector<vector<int>>;

// helper function to print a matrix with right alignd formatting
void printMatrix(const Matrix& mat) {
    for (const auto& row : mat) {
        for (int val : row) {
            cout << setw(4) << val;
        }
        cout << "\n";
    }
}

// 1. read matrices from a file
bool readMatricesFromFile(const string& filename, int& N, Matrix& A, Matrix& B) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return false;
    }

    if (!(inFile >> N) || N <= 0) {
        cerr << "Error: Invalid matrix size N in file." << endl;
        return false;
    }

    A.assign(N, vector<int>(N));
    B.assign(N, vector<int>(N));

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            inFile >> A[i][j];
        }
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            inFile >> B[i][j];
        }
    }

    inFile.close();
    return true;
}

// 2. adding two matrices
Matrix addMatrices(const Matrix& A, const Matrix& B, int N) {
    Matrix result(N, vector<int>(N));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
    return result;
}

// 3. multiply two matrices
Matrix multiplyMatrices(const Matrix& A, const Matrix& B, int N) {
    Matrix result(N, vector<int>(N, 0));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            for (int k = 0; k < N; ++k) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
    return result;
}

// 4. calculates and displays diagonal sums
void printDiagonalSums(const Matrix& A, int N) {
    int mainSum = 0;
    int secondarySum = 0;
    for (int i = 0; i < N; ++i) {
        mainSum += A[i][i];
        secondarySum += A[i][N - 1 - i];
    }
    cout << "Diagonal sums for Matrix A:\n";
    cout << "Main diagonal sum: " << mainSum << "\n";
    cout << "Secondary diagonal sum: " << secondarySum << "\n\n";
}

// 5. swaps two matrix rows
void swapRows(Matrix A, int row1, int row2, int N) {
    if (row1 >= 0 && row1 < N && row2 >= 0 && row2 < N) {
        swap(A[row1], A[row2]);
        cout << "Problem 5 - Rows " << row1 << " and " << row2 << " swapped:\n";
        printMatrix(A);
        cout << "\n";
    } else {
        cout << "Error: Row index out of bounds.\n\n";
    }
}

// 6. swaps two matrix columns
void swapColumns(Matrix A, int col1, int col2, int N) {
    if (col1 >= 0 && col1 < N && col2 >= 0 && col2 < N) {
        for (int i = 0; i < N; ++i) {
            swap(A[i][col1], A[i][col2]);
        }
        cout << "Problem 6 - Columns " << col1 << " and " << col2 << " swapped:\n";
        printMatrix(A);
        cout << "\n";
    } else {
        cout << "Error: Column index out of bounds.\n\n";
    }
}

// 7. updates matrix element
void updateElement(Matrix A, int row, int col, int newValue, int N) {
    if (row >= 0 && row < N && col >= 0 && col < N) {
        A[row][col] = newValue;
        cout << "Problem 7 - Updated matrix:\n";
        printMatrix(A);
        cout << "\n";
    } else {
        cout << "Error: Element index out of bounds.\n\n";
    }
}

int main() {
    string filename;
    cout << "Enter input filename: ";
    cin >> filename;

    int N;
    Matrix A, B;

    if (!readMatricesFromFile(filename, N, A, B)) {
        return 1;
    }

    // Problem 1: Display loaded matrices
    cout << "Matrix A:\n";
    printMatrix(A);
    cout << "\nMatrix B:\n";
    printMatrix(B);
    cout << "\n";

    // Problem 2: Addition
    cout << "A + B:\n";
    printMatrix(addMatrices(A, B, N));
    cout << "\n";

    // Problem 3: Multiplication
    cout << "A * B:\n";
    printMatrix(multiplyMatrices(A, B, N));
    cout << "\n";

    // Problem 4: Diagonal Sums
    printDiagonalSums(A, N);

    // Problem 5: Swap Rows 0 and 2
    swapRows(A, 0, 2, N);

    // Problem 6: Swap Columns 0 and 2
    swapColumns(A, 0, 2, N);

    // Problem 7: Update row 1, col 2 to 99
    updateElement(A, 1, 2, 99, N);

    return 0;
}
