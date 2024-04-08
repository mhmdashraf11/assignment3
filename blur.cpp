#include "Image_Class.h"
#include <iostream>
using namespace std;

void Blur(Image& img){
    int avgR, avgG, avgB;
    for (int i = 21; i < img.width - 21; i++) {
        for (int j = 21; j < img.height - 21; j++) {
            int sumR = 0, sumG = 0, sumB = 0;
            for (int m = -21; m <= 21; m++) {
                for (int n = -21; n <= 21; n++) {
                
                    sumR += img(i + m, j + n, 0);
                    sumG += img(i + m, j + n, 1);
                    sumB += img(i + m, j + n, 2);
                    
                }
            }
            avgR = sumR / 1849;
            avgG = sumG / 1849;
            avgB = sumB / 1849;
            img(i, j, 0) = avgR;
            img(i, j, 1) = avgG;
            img(i, j, 2) = avgB;
        }
        
    }
}

int main() {
    Image img("building.jpg");
    int i = 0;
    Blur(img);
    img.saveImage("blur.jpg");

    return 0;
}
