#include "Image_Class.h"
using namespace std;

int main(){

    string filename;
    cout << "Please enter colored image name to turn into Gray Scale:\n";
    cin >> filename;

    Image image(filename);



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

    image.saveImage("GrayscaleImage.png");


    return 0;
}
