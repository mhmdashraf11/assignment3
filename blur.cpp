#include "Image_Class.h"
#include <iostream>
#include <vector>

using namespace std;

void summed_table(Image& img, vector<vector<int>>& prefixSumR, vector<vector<int>>& prefixSumG, vector<vector<int>>& prefixSumB) {
    int width = img.width;
    int height = img.height;

    prefixSumR.assign(width, vector<int>(height, 0));
    prefixSumG.assign(width, vector<int>(height, 0));
    prefixSumB.assign(width, vector<int>(height, 0));

    // Compute prefix sums for each color channel separately
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            prefixSumR[i][j] = img(i, j, 0);
            prefixSumG[i][j] = img(i, j, 1);
            prefixSumB[i][j] = img(i, j, 2);

            if (i > 0) {
                prefixSumR[i][j] += prefixSumR[i - 1][j];
                prefixSumG[i][j] += prefixSumG[i - 1][j];
                prefixSumB[i][j] += prefixSumB[i - 1][j];
            }
            if (j > 0) {
                prefixSumR[i][j] += prefixSumR[i][j - 1];
                prefixSumG[i][j] += prefixSumG[i][j - 1];
                prefixSumB[i][j] += prefixSumB[i][j - 1];
            }
            if (i > 0 && j > 0) {
                prefixSumR[i][j] -= prefixSumR[i - 1][j - 1];
                prefixSumG[i][j] -= prefixSumG[i - 1][j - 1];
                prefixSumB[i][j] -= prefixSumB[i - 1][j - 1];
            }
        }
    }
}

void Blur(Image& img) {
    int width = img.width;
    int height = img.height;

    vector<vector<int>> prefixSumR, prefixSumG, prefixSumB;
    summed_table(img, prefixSumR, prefixSumG, prefixSumB);

    int radius = 21; // Blur radius
    int area = (2 * radius + 1) * (2 * radius + 1); // Total pixels in the blur area

    for (int i = radius; i < width - radius; i++) {
        for (int j = radius; j < height - radius; j++) {
            // Check if the blur region is within the bounds of the image
            if (i + radius < width && j + radius < height && i - radius - 1 >= 0 && j - radius - 1 >= 0) {
                int sumR = prefixSumR[i + radius][j + radius] - prefixSumR[i - radius - 1][j + radius] - prefixSumR[i + radius][j - radius - 1] + prefixSumR[i - radius - 1][j - radius - 1];
                int sumG = prefixSumG[i + radius][j + radius] - prefixSumG[i - radius - 1][j + radius] - prefixSumG[i + radius][j - radius - 1] + prefixSumG[i - radius - 1][j - radius - 1];
                int sumB = prefixSumB[i + radius][j + radius] - prefixSumB[i - radius - 1][j + radius] - prefixSumB[i + radius][j - radius - 1] + prefixSumB[i - radius - 1][j - radius - 1];

                // Calculate average
                int avgR = sumR / area;
                int avgG = sumG / area;
                int avgB = sumB / area;

                img(i, j, 0) = avgR;
                img(i, j, 1) = avgG;
                img(i, j, 2) = avgB;
            }
        }
    }
}



