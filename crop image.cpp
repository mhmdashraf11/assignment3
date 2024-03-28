#include <iostream>
#include <limits>
#include "Image_Class.h"

using namespace std;

// Function to cropped filtering
void cropped_filter() {
    int x, y, width, height;
    string imagename;

    while (true) {   // loop to check the input is numbers only
        cout << "Please enter your new starting point (x,y): ";
        if (cin >> x >> y) {
            break;
        } else {
            cout << "Invalid input. Please enter integers only." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

    }

    while (true) {  // loop to check the input is numbers only
        cout << "Please enter new width and height: ";
        if (cin >> width >> height) {
            break;
        } else {
            cout << "Invalid input. Please enter an integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //
        }
    }

    if(x <= 0 || y <= 0 || width <= 0 || height <= 0){
        cout << "Please enter a positive numbers.\n";
        cin.ignore();
        return cropped_filter();
    }

    cout << "Please enter the image name to process: ";
    cin >> imagename;
    cin.ignore();

    Image image(imagename);
    Image cropped_image(width, height);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < image.channels; k++) {
                if (x >= 0 && x < image.width && y >= 0 && y < image.height && i + x < image.height && j + y < image.width) { // Bounds checking
                    cropped_image(i, j, k) = image(i + x, j + y, k);
                } else {
                    cout << "Invalid dimensions. Please enter again." << endl;
                    return cropped_filter(); // call the function to repeat input
                }
            }
        }
    }

    cout << "Please enter the image name to store the new image (with extension .jpg, .png): ";
    cin >> imagename;
    cropped_image.saveImage(imagename);
    cout << "Cropped image saved successfully." << endl;
}

int main() {
    cropped_filter();
    return 0;
}
