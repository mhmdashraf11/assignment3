#include "Image_Class.h"
#include <iostream>
using namespace std;

void filter1(Image& image){ //Gray scale
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int avg = 0;
            for (int k = 0; k < 3; ++k) {
                avg += image(i,j,k);
            }
            avg = avg / 3;
            for (int k = 0; k < 3; ++k) {
                image(i,j,k) = avg;
            }
        }
    }
    // image.saveImage("GrayscaleImage.png");
}
int main() {
    Image img("samurai.jpg");
    filter1(img);
    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            for(int h = 0; h < 3; ++h) {
                if (img(x,y,h) >= 100 && img(x,y,h) <= 255) {
                // img(x,y,0)= 255;
                    int g = img(x,y,1);
                    int b = img(x,y,2);
                    img(x,y,0)=255;
                    img(x,y,1)=255-b;
                    img(x,y,2)=255-g;
                }
                if (img(x,y,0) < 100 && img(x,y,1) < 100 && img(x,y,2) < 100) {
                    img(x,y,0) = 219;
                    img(x,y,1) = 150;
                    img(x,y,2) = 176;
                }
            }
        }
    }
    
    
    img.saveImage("blur.jpg");

    return 0;
}
