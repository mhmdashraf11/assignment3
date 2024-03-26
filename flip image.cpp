#include <iostream>
#include "Image_Class.h"
using namespace std;

void flip_vertical(){
    string imagename;
    cout << "Pls enter an image to flip: ";
    cin >> imagename;
    Image image(imagename);
    for (int j = 0; j < image.height / 2; ++j) {
        // Swap entire row data between the top and bottom rows
        for (int i = 0; i < image.width; ++i) {
            for (int k = 0; k < image.channels; ++k) {
                unsigned char temp = image(i, j, k);
                image(i, j, k) = image(i, image.height - 1 - j, k);
                image(i, image.height - 1 - j, k) = temp;
            }
        }
    }
    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .png: ";

    cin >> imagename;
    image.saveImage(imagename);
    cout << "Image flipped vertically." << endl;
}

void flip_horizontal(){
    string imagename;
    cout << "Pls enter an image to flip: ";
    cin >> imagename;
    Image image(imagename);
    for (int j = 0; j < image.height ; ++j) {
        // Swap entire row data between the top and bottom rows
        for (int i = 0; i < image.width/2 ; ++i) {
            for (int k = 0; k < image.channels ; ++k) {
                unsigned char temp = image(i, j, k);
                image(i, j, k) = image(image.width - 1 - i, j, k);
                image(image.width - 1 - i, j, k) = temp;
            }
        }
    }
    cout << "Pls enter image name to store new image\n";
    cout << "and specify extension .jpg, .png: ";

    cin >> imagename;
    image.saveImage(imagename);
    cout << "Image flipped Horizontal." << endl;
}

void choice_flip(){
    while(true){
        cout << "What type of flip do you need?\n";
        cout << "1)Flip vertical\n2)Flip horizontal\n";
        string choice;
        cin >> choice;
        cin.ignore(); // Clear the newline character from the input buffer

        if(choice == "1"){
            flip_vertical();
            break;
        }else if(choice == "2"){
            flip_horizontal();
            break;
        }else{
            cout << "Invalid choice,Please enter a valid choice." << endl << endl;
            return choice_flip();
        }
    }
}

int main() {
    choice_flip();
}
