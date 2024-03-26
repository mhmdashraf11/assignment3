
#include <iostream>
#include "Image_Class.h"
#include <algorithm>
#include <regex>
using namespace std;
bool isValidFilename(const string& filename) {   //from Image_class.h
    const char* extension = strrchr(filename.c_str(), '.');
    if (extension == nullptr) {
        cout << "Invalid filename: " << filename << ", try again." <<endl;
        return false;
    }

    return true;
}
Image input(){
    string filename;
    cout << "Enter the image name to upload: ";
    cin >> filename;
    Image newimg(filename);

    return newimg;
}
string SaveMenu(){
    string choice;
    cout << "Do you want to save it?" << endl;
    cout <<"1. yes\n2. no\n";
    cin >> choice;
    return choice;
}
void filter3(Image& img){

    for(int i=0; i<img.width; i++){
        for(int j=0; j<img.height; j++){
            img(i,j,0) = 255-img(i,j,0);  // getting the complement of the pixels
            img(i,j,1) = 255-img(i,j,1);
            img(i,j,2) = 255-img(i,j,2);
        }
    }
    // img.saveImage("mario.jpg");

}


void flip_vertical(Image& img){
    for (int j = 0; j < img.height / 2; ++j) {
        // Swap entire row data between the top and bottom rows
        for (int i = 0; i < img.width; ++i) {
            for (int k = 0; k < img.channels; ++k) {
                unsigned char temp = img(i, j, k);
                img(i, j, k) = img(i, img.height - 1 - j, k);
                img(i, img.height - 1 - j, k) = temp;
            }
        }
    }
}

void flip_horizontal(Image& image){

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

}

void choice_flip(Image& img){
    cout << "What type of flip do you need?\n";
    cout << "1)Flip vertical\n2)Flip horizontal\n";
    string choice;
    cin >> choice;
    cin.ignore(); // Clear the newline character from the input buffer

    if(choice == "1"){
        flip_vertical(img);
    }else if(choice == "2"){
        flip_horizontal(img);
    }else{
        cout << "Invalid choice,Please enter a valid choice." << endl << endl;
        return choice_flip(img);
    }
}

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
void bandw(Image& image){ // Black and white
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
}


void mainmenu(Image &image){
    string choice;
    cout << "Choose the filter\n";
    cout << "1. Gray scale\n";
    cout << "2. Black and white\n";
    cout << "3. Invert image\n";
    cout << "4. Merge images\n";
    cout << "5. Flip image\n";
    cin >> choice;
    if(cin.fail() || (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5")){
        cout << "Please enter a number between 1 and 5\n";
        return mainmenu(image);
    }
    else if(choice == "1"){
        filter1(image);
    }
    else if(choice == "2"){
        bandw(image);
    }
    else if(choice == "3"){
        filter3(image);
    }
    else if(choice == "5"){
        choice_flip(image);
    }
    cout << "Do you want to apply another filter?\n";
    cout << "1. Yes\n2. No\n";
    string choice4;
    cin >> choice4;
    if(choice4 == "1"){
        mainmenu(image);
    }
    else if(choice4 == "2"){
        string choice2;
        choice2 = SaveMenu();
        if(choice2 == "1"){
            string ImageName;
            cout << "Enter the image name and its extension to save:\n";
            cout << "<e.x.ImageName.jpg>\n";
            cin >> ImageName;

            if(image.saveImage(ImageName)){
                cout << "Image saved successfully\n";
            }
            else{
                cout << "failed!\n";
            }
        }
        else if(choice2 == "2"){
            return;
        }
        else{
            cout << "Invalid input. try again." << endl;
            while(choice2 != "1" && choice2 !="2"){
                choice2 = SaveMenu();
            }
        }
    }
}
int main();
void check(){
    cout << "Do you want to enter another image?"<<endl;
    cout << "1. Yes\n2. No\n";
    string choice;
    cin >> choice;
    if(choice == "1"){
        main();
    }
    else if(choice == "2"){
        cout << "Thanks for your time!";
        exit(0);
    }
    else{
        cout << "Invalid, please enter a valid input.";
        check();
    }
}




int main(){
    cout << "Ahlan ya user ya habibi\n";
    Image image = input();
    mainmenu(image);
    check();
    return 0;
}