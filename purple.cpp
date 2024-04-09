#include <iostream>
#include "Image_Class.h"
using namespace std;

void purple_image(){
    string imagename;
    cout << "Pls enter your image: ";
    cin >> imagename;
    Image image(imagename);
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            // Decrease green channel and possibly adjust red and blue channels
            image(i, j, 1) *= .73;
        }
    }

    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .png: ";

    cin >> imagename;
    image.saveImage(imagename);
}
int main() {
    purple_image();

    return 0;
}
