#include "Image_Class.h"
#include <iostream>
using namespace std;

void blackandwhite(){
    string imagename;
    cout << "Pls enter an image to flip: ";
    cin >> imagename;
    Image image(imagename);

    // Convert image to grayscale
    for(int i = 0; i < image.width; ++i) {
        for(int j = 0; j < image.height; ++j) {
            // Calculate grayscale value (average of RGB channels)
            unsigned int avg = 0;
            for(int k = 0; k < image.channels; ++k) {
                avg += image(i, j, k);
            }
            avg /= image.channels;

            // Assign grayscale value to all color channels
            for(int k = 0; k < image.channels; ++k) {
                image(i, j, k) = avg;
            }
        }
    }

    for(int i = 0; i < image.width; ++i) {
        for(int j = 0; j < image.height; ++j) {
            // Calculate average grayscale value for each pixel
            unsigned int gray = 0;
            for(int k = 0; k < image.channels; ++k) {
                gray += image(i, j, k);
            }
            gray /= image.channels;

            if(gray < 128) {
                // Set pixel to black
                for(int k = 0; k < image.channels; ++k) {
                    image(i, j, k) = 0;
                }
            } else {
                // Set pixel to white
                for(int k = 0; k < image.channels; ++k) {
                    image(i, j, k) = 255;
                }
            }
        }
    }

    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .png: ";

    cin >> imagename;
    image.saveImage(imagename);

    cout << "Image converted to black and white." << endl;
}

int main() {
    blackandwhite();
    return 0;
}
