#include "Image_Class.h"
#include <algorithm>
using namespace std;


int main(){



    string filename1;
    string filename2;

    cout << "Please enter two images name:\n";

    cin >> filename1;
    cin >> filename2;

    Image image1(filename1);
    Image image2(filename2);


    int width1 = image1.width;
    int height1 = image1.height;

    int width2 = image2.width;
    int height2 = image2.height;

    if(width1 > width2 && height1 > height2){


        Image image2new(width1,height1);

        double r1 = static_cast<double>(width2) / width1;
        double r2 = static_cast<double>(height2) / height1;

        for (int i = 0; i < width1; ++i) {
            for (int j = 0; j < height1; ++j) {
                for (int k = 0; k < 3; ++k) {
                    image2new(i,j,k) = image2(floor(i*r1),floor(j*r2),k);
                }
            }
        }

        Image newimage(width1,height1);

        for (int i = 0; i < width1; ++i) {
            for (int j = 0; j < height1; ++j) {
                for (int k = 0; k < 3; ++k) {

                    newimage(i,j,k) = 0.5 * image2new(i,j,k) + 0.5 * image1(i,j,k);

                    if(newimage(i,j,k) > 255){
                        newimage(i,j,k) = 255;
                    }
                }
            }
        }
        newimage.saveImage("Merged.jpg");

    }
    else if(width2 > width1 && height2 > height1){

        Image image1new(width2,height2);

        double r1 = static_cast<double>(width1) / width2;
        double r2 = static_cast<double>(height1) / height2;

        for (int i = 0; i < width2; ++i) {
            for (int j = 0; j < height2; ++j) {
                for (int k = 0; k < 3; ++k) {
                    image1new(i,j,k) = image1(floor(i*r1),floor(j*r2),k);
                }
            }
        }


        Image newimage(width2,height2);

        for (int i = 0; i < width2; ++i) {
            for (int j = 0; j < height2; ++j) {
                for (int k = 0; k < 3; ++k) {

                    newimage(i,j,k) = 0.5 * image2(i,j,k) + 0.5 * image1new(i,j,k);

                    if(newimage(i,j,k) > 255){
                        newimage(i,j,k) = 255;
                    }
                }
            }
        }
        newimage.saveImage("Merged.jpg");
    }


    else if ((width2 > width1 && height1 > height2)||(width1 > width2 && height2 > height1)){
        Image newimage(min(width1,width2),min(height1,height2));

        for (int i = 0; i < min(width1,width2); ++i) {
            for (int j = 0; j < min(height1,height2); ++j) {
                for (int k = 0; k < 3; ++k) {
                    newimage(i,j,k) = 0.5 * image1(i,j,k) + 0.5 * image2(i,j,k);
                }

            }

        }
        newimage.saveImage("Merged.jpg");

    }


    return 0;
}
