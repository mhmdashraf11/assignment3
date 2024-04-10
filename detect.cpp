#include <iostream>
#include <cmath>
#include <vector>
#include "Image_Class.h"
using namespace std;

void detect_image(Image &image){
    // Convert image to grayscale
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            // Calculate grayscale value (average of RGB channels)
            unsigned int avg = 0;
            for (int k = 0; k < image.channels; ++k) {
                avg += image(i, j, k);
            }
            avg /= image.channels;

            // Assign grayscale value to all color channels
            for (int k = 0; k < image.channels; ++k) {
                image(i, j, k) = avg;

            }
        }
    }

    // Apply Sobel operator
    int rows = image.height - 2;
    int cols = image.width - 2;
    vector<vector<int>> new_Ix(rows, vector<int>(cols));
    vector<vector<int>> new_Iy(rows, vector<int>(cols));
    vector<vector<int>> new_matrix(rows, vector<int>(cols));

    int Ix[3][3] = {
            {-1, 0, 1},
            {-2, 0, 2},
            {-1, 0, 1}
    };

    int Iy[3][3] = {
            {1, 2, 1},
            {0, 0, 0},
            {-1, -2, -1}
    };

    // Convolve with Sobel filters
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            int sumIx = 0;
            int sumIy = 0;
            for (int m = 0; m < 3; ++m) {
                for (int n = 0; n < 3; ++n) {
                    sumIx += image(i + m, j + n, 0) * Ix[m][n];
                    sumIy += image(i + m, j + n, 0) * Iy[m][n];
                }
            }
            new_Ix[j][i] = sumIx;
            new_Iy[j][i] = sumIy;
        }
    }

    double sum_mat = 0.0;
    for(int i = 0; i < cols; ++i){
        for(int j = 0; j < rows; ++j){
            int sum = sqrt((new_Ix[j][i] * new_Ix[j][i]) + (new_Iy[j][i] * new_Iy[j][i])); // corrected indices
            new_matrix[j][i] = sum; // corrected indices
            sum_mat += sum;
        }
    }
    double avg = ceil(sum_mat / (rows * cols));

    for(int i = 0; i < cols; ++i){
        for(int j = 0; j < rows; ++j) {
            if (new_matrix[j][i] > avg) {
                for (int k = 0; k < image.channels; ++k) {
                    image(i + 1, j + 1, k) = 0;
                }
            } else {
                for (int k = 0; k < image.channels; ++k) {
                    image(i + 1, j + 1, k) = 255;
                }
            }
        }
    }


}

int main() {
    string imagename;
    cout << "Pls enter an image to detect: ";
    cin >> imagename;
    Image image(imagename);
    detect_image(image);
    // Save the processed image
    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .png: ";
    cin >> imagename;
    image.saveImage(imagename);
    return 0;
}