// File name:
// Purpose: photoshop
/* Authors:
 * 1) Mohamed Ashraf Mohamed Hassan, ID: 20230321,Filters taken: Invert image, Rotate image, the menu 
 * 2) Bassam Yasser Mohamed Hassan, ID: 20230089,Filters taken: Gray scale
 * 3) Basmala Mamdouh Esmail Abdelhamid, ID: 20230092,Filters taken: Black and white, flip
 */
/* Emails:
 * 1) mohamed4ashraf2019@gmail.com
 * 2) bassamyasser12@gmail.com
 * 3) basmalamamdouh97@gmail.com
 */

#include <iostream>
#include "Image_Class.h"
using namespace std;
bool isValidFilename(const string& filename) {   //from Image_class.h
    const char* extension = strrchr(filename.c_str(), '.');
    if (extension == nullptr) {
        cout << "Invalid filename: " << filename << ", try again." <<endl;
        return false;
    }

    return true;
}

Image input(){ // to take the image and check the validation of its name and extension
    string filename;
    cout << "Enter the image name to upload: ";
    cin >> filename;
    while(!isValidFilename(filename)){
        cin >> filename;
    }
    Image newimg;
    try{
        newimg.loadNewImage(filename);
    }
    catch(invalid_argument){
        cout << "Please enter a valid image." <<endl;
        input();
    }

    return newimg;
}
string SaveMenu(){
    string choice;
    cout << "Do you want to save it?" << endl;
    cout <<"1. yes\n2. no\n";
    cin >> choice;
    return choice;
}
void filter3(Image& img){ //invert image

    for(int i=0; i<img.width; i++){
        for(int j=0; j<img.height; j++){
            img(i,j,0) = 255-img(i,j,0);  // getting the complement of the pixels
            img(i,j,1) = 255-img(i,j,1);
            img(i,j,2) = 255-img(i,j,2);
        }
    }
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

void rotate90(Image& img) {
    // Swap width and height for a 270-degree rotation
    int newWidth = img.height;
    int newHeight = img.width;

    // Create a temporary buffer to store pixel values during rotation
    unsigned char* tempBuffer = new unsigned char[newWidth * newHeight * img.channels];

    // Iterate over the image pixels and perform the rotation in-place
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            // Calculate the new coordinates after rotation
            int newX = img.height - y - 1;
            int newY = x;

            // Copy pixel values to the temporary buffer
            for (int k = 0; k < img.channels; k++) {
                tempBuffer[(newY * newWidth + newX) * img.channels + k] = img.getPixel(x, y, k);
            }
        }
    }

    // Update the dimensions of the image
    img.width = newWidth;
    img.height = newHeight;

    // Copy the rotated pixel values back to the image
    for (int i = 0; i < newWidth * newHeight * img.channels; i++) {
        img.imageData[i] = tempBuffer[i];
    }

    // Free the temporary buffer
    delete[] tempBuffer;
}



void rotate180(Image& img) {
    Image rotatedImage(img.width, img.height);
    // Uncomment the line below if you want to initialize img with the correct dimensions
    // img = Image(img.width, img.height);

    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            int newX = img.width - x - 1;  // make the coordinates upside down
            int newY = img.height - y - 1;
            for (int k = 0; k < 3; k++) {
                rotatedImage.setPixel(newX, newY, k, img.getPixel(x, y, k));
            }
        }
    }

    // Copy rotatedImage to img
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            for (int k = 0; k < 3; k++) {
                img.setPixel(x, y, k, rotatedImage.getPixel(x, y, k));
            }
        }
    }
}
void rotate270(Image& img){
    rotate180(img);// to make the total rotate equals 270 degree
    rotate90(img);
}

void rotateMenu(Image& img){
    int choice;
    cout << "Please choose the rotate angle:\n";
    cout << "1. 90\n";
    cout << "2. 180\n";
    cout << "3. 270\n";
    cin >> choice;
    switch(choice){
        case 1 :
            rotate90(img);
            break;
        case 2 :
            rotate180(img);
            break;
        case 3 :
            rotate270(img);
            break;
        default :
            cout << "Please enter a number from 1 to 3."<<endl;
            rotateMenu(img);
    }
}



void mainmenu(Image &image){
    string choice;
    cout << "=>Choose the filter\n";
    cout << "1. Gray scale\n";
    cout << "2. Black and white\n";
    cout << "3. Invert image\n";
    cout << "4. Flip image\n";
    cout << "5. rotate image\n";
    cout<< "6. exit\n";
    cin >> choice;
    if(cin.fail() || (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice !="6")){
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
        rotateMenu( image);
//        merge(image);
    }
    else if(choice == "4"){
        choice_flip(image);
    }
    else if(choice == "6"){
        cout << "Thanks for your time!\n";
        exit(0);
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
        if(choice2 == "1" ){
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
            if(choice2 == "1") {
                string ImageName;
                cout << "Enter the image name and its extension to save:\n";
                cout << "<e.x.ImageName.jpg>\n";
                cout << "*if you want save it in the same file enter the same image name*\n";
                cin >> ImageName;
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
