#include <iostream>
#include <cmath>
#include "Image_Class.h"

using namespace std;

void GaussianBlur(Image &image, int kernelSize, float sigma) {
    int halfKernelSize = kernelSize / 2;
    float *kernel = new float[kernelSize * kernelSize];
    float sum = 0;

    // Calculate Gaussian kernel
    for (int i = -halfKernelSize; i <= halfKernelSize; i++) {
        for (int j = -halfKernelSize; j <= halfKernelSize; j++) {
            float x = i * i + j * j;
            kernel[(i + halfKernelSize) * kernelSize + j + halfKernelSize] = exp(-x / (2 * sigma * sigma)) / (2 * M_PI * sigma * sigma);
            sum += kernel[(i + halfKernelSize) * kernelSize + j + halfKernelSize];
        }
    }

    // Normalize kernel
    for (int i = 0; i < kernelSize * kernelSize; i++) {
        kernel[i] /= sum;
    }

    // Apply Gaussian blur to image
    for (int y = 0; y < image.height; y++) {
        for (int x = 0; x < image.width; x++) {
            float r = 0, g = 0, b = 0;
            for (int i = -halfKernelSize; i <= halfKernelSize; i++) {
                for (int j = -halfKernelSize; j <= halfKernelSize; j++) {
                    if (x + j >= 0 && x + j < image.width && y + i >= 0 && y + i < image.height) {
                        r += image.getPixel(x + j, y + i, 0) * kernel[(i + halfKernelSize) * kernelSize + j + halfKernelSize];
                        g += image.getPixel(x + j, y + i, 1) * kernel[(i + halfKernelSize) * kernelSize + j + halfKernelSize];
                        b += image.getPixel(x + j, y + i, 2) * kernel[(i + halfKernelSize) * kernelSize + j + halfKernelSize];
                    }
                }
            }
            image.setPixel(x, y, 0, r);
            image.setPixel(x, y, 1, g);
            image.setPixel(x, y, 2, b);
        }
    }

    delete[] kernel;
}

int main() {
    Image image("building.jpg");
    GaussianBlur(image, 59, 30.0);
    image.saveImage("more_blurred_mario.jpg");
    return 0;
}
