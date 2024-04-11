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
#include <vector>
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
void merge(Image& image1){
    cout << "=>Please enter the second image's name\n";
    Image image2 = input();

    int width1 = image1.width;
    int height1 = image1.height;

    int width2 = image2.width;
    int height2 = image2.height;

    if(width1 > width2 && height1 > height2){
        double r1 = static_cast<double>(width2) / width1;
        double r2 = static_cast<double>(height2) / height1;

        for (int i = 0; i < width1; ++i) {
            for (int j = 0; j < height1; ++j) {
                for (int k = 0; k < 3; ++k) {
                    image1(i, j, k) = 0.5 * image2(floor(i*r1), floor(j*r2), k) + 0.5 * image1(i, j, k);
                    if(image1(i, j, k) > 255){
                        image1(i, j, k) = 255;
                    }
                }
            }
        }
    }
    else if(width2 > width1 && height2 > height1){
        double r1 = static_cast<double>(width1) / width2;
        double r2 = static_cast<double>(height1) / height2;

        for (int i = 0; i < width2; ++i) {
            for (int j = 0; j < height2; ++j) {
                for (int k = 0; k < 3; ++k) {
                    image1(i, j, k) = 0.5 * image2(i, j, k) + 0.5 * image1(floor(i*r1), floor(j*r2), k);
                    if(image1(i, j, k) > 255){
                        image1(i, j, k) = 255;
                    }
                }
            }
        }
    }
    else if ((width2 > width1 && height1 > height2) || (width1 > width2 && height2 > height1)){
        int min_width = min(width1, width2);
        int min_height = min(height1, height2);

        for (int i = 0; i < min_width; ++i) {
            for (int j = 0; j < min_height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    image1(i, j, k) = 0.5 * image1(i, j, k) + 0.5 * image2(i, j, k);
                }
            }
        }
    }
}
void infrared(Image& img){
    filter1(img); // Gray scale
    for (int y = 0; y < img.height; ++y) {
        for (int x = 0; x < img.width; ++x) {
            for(int h = 0; h < 3; ++h) {
                int g = img(x,y,1);
                int b = img(x,y,2);
                img(x,y,0)=255;
                img(x,y,1)=255-b;
                img(x,y,2)=255-g;
            }
        }
    }
}
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
void resize(Image& img) {
    cout << "Enter new width:\n";
    int newWidth;
    cin >> newWidth;

    cout << "Enter new height:\n";
    int newHeight;
    cin >> newHeight;

    double r1 = static_cast<double>(img.width) / newWidth;
    double r2 = static_cast<double>(img.height) / newHeight;

    // Create temporary buffer for resized image data
    unsigned char* resizedImageData = new unsigned char[newWidth * newHeight * img.channels];

    for (int i = 0; i < newWidth; ++i) {
        for (int j = 0; j < newHeight; ++j) {
            for (int k = 0; k < img.channels; ++k) {
                int originalX = static_cast<int>(i * r1);
                int originalY = static_cast<int>(j * r2);

                // Ensure original coordinates are within bounds
                originalX = std::max(0, std::min(originalX, img.width - 1));
                originalY = std::max(0, std::min(originalY, img.height - 1));

                // Calculate the index in the original image data
                int originalIndex = (originalY * img.width + originalX) * img.channels + k;

                // Calculate the index in the resized image data
                int resizedIndex = (j * newWidth + i) * img.channels + k;

                // Copy pixel value from original image data to resized image data
                resizedImageData[resizedIndex] = img.imageData[originalIndex];
            }
        }
    }

    // Update image properties
    img.width = newWidth;
    img.height = newHeight;
    delete[] img.imageData; // Free previous image data
    img.imageData = resizedImageData;

    cout << "Image resized successfully.\n";
}
void SRedFrame(Image& img){
    for(int i=0; i<img.width; i++){
        for(int j=0; j<img.height/50; j++){
            img(i,j,0) = 255;
            img(i,j,1) = 0;
            img(i,j,2) = 0;
        }
    }
    for(int j = 0;j<img.height;j++){
        for(int i = 0;i<img.width/50;i++){
            img(i,j,0) = 255;
            img(i,j,1) = 0;
            img(i,j,2) = 0;
        }
    }
    for(int i=0; i<img.width; i++){
        for(int j=img.height-img.height/50; j<img.height; j++){
            img(i,j,0) = 255;
            img(i,j,1) = 0;
            img(i,j,2) = 0;
        }
    }
    for(int j = 0;j<img.height;j++){
        for(int i = img.width-img.width/50;i<img.width;i++){
            img(i,j,0) = 255;
            img(i,j,1) = 0;
            img(i,j,2) = 0;
        }
    }
}
void SGreenFrame(Image& img){
    for(int i=0; i<img.width; i++){
        for(int j=0; j<img.height/50; j++){
            img(i,j,0) = 0;
            img(i,j,1) = 255;
            img(i,j,2) = 0;
        }
    }
    for(int j = 0;j<img.height;j++){
        for(int i = 0;i<img.width/50;i++){
            img(i,j,0) = 0;
            img(i,j,1) = 255;
            img(i,j,2) = 0;
        }
    }
    for(int i=0; i<img.width; i++){
        for(int j=img.height-img.height/50; j<img.height; j++){
            img(i,j,0) = 0;
            img(i,j,1) = 255;
            img(i,j,2) = 0;
        }
    }
    for(int j = 0;j<img.height;j++){
        for(int i = img.width-img.width/50;i<img.width;i++){
            img(i,j,0) = 0;
            img(i,j,1) = 255;
            img(i,j,2) = 0;
        }
    }
}
void SBlueFrame(Image &img){
    for(int i=0; i<img.width; i++){
        for(int j=0; j<img.height/50; j++){
            img(i,j,0) = 0;
            img(i,j,1) = 0;
            img(i,j,2) = 255;
        }
    }
    for(int j = 0;j<img.height;j++){
        for(int i = 0;i<img.width/50;i++){
            img(i,j,0) = 0;
            img(i,j,1) = 0;
            img(i,j,2) = 255;
        }
    }
    for(int i=0; i<img.width; i++){
        for(int j=img.height-img.height/50; j<img.height; j++){
            img(i,j,0) = 0;
            img(i,j,1) = 0;
            img(i,j,2) = 255;
        }
    }
    for(int j = 0;j<img.height;j++){
        for(int i = img.width-img.width/50;i<img.width;i++){
            img(i,j,0) = 0;
            img(i,j,1) = 0;
            img(i,j,2) = 255;
        }
    }
}
void SBlackFrame(Image &img){
    for(int i=0; i<img.width; i++){
        for(int j=0; j<img.height/50; j++){
            img(i,j,0) = 0;
            img(i,j,1) = 0;
            img(i,j,2) = 0;
        }
    }
    for(int j = 0;j<img.height;j++){
        for(int i = 0;i<img.width/50;i++){
            img(i,j,0) = 0;
            img(i,j,1) = 0;
            img(i,j,2) = 0;
        }
    }
    for(int i=0; i<img.width; i++){
        for(int j=img.height-img.height/50; j<img.height; j++){
            img(i,j,0) = 0;
            img(i,j,1) = 0;
            img(i,j,2) = 0;
        }
    }
    for(int j = 0;j<img.height;j++){
        for(int i = img.width-img.width/50;i<img.width;i++){
            img(i,j,0) = 0;
            img(i,j,1) = 0;
            img(i,j,2) = 0;
        }
    }
}
void SWhiteFrame(Image &img){
    for(int i=0; i<img.width; i++){
        for(int j=0; j<img.height/50; j++){
            img(i,j,0) = 255;
            img(i,j,1) = 255;
            img(i,j,2) = 255;
        }
    }
    for(int j = 0;j<img.height;j++){
        for(int i = 0;i<img.width/50;i++){
            img(i,j,0) = 255;
            img(i,j,1) = 255;
            img(i,j,2) = 255;
        }
    }
    for(int i=0; i<img.width; i++){
        for(int j=img.height-img.height/50; j<img.height; j++){
            img(i,j,0) = 255;
            img(i,j,1) = 255;
            img(i,j,2) = 255;
        }
    }
    for(int j = 0;j<img.height;j++){
        for(int i = img.width-img.width/50;i<img.width;i++){
            img(i,j,0) = 255;
            img(i,j,1) = 255;
            img(i,j,2) = 255;
        }
    }
}
void SimpleFrameFilter(Image& img){
    cout << "Choose the frame color\n";
    cout << "1. Red\n2. Green\n3. Blue\n4. Black\n5. white";
    string choice;
    cin >> choice;
    if(choice == "1"){
        SRedFrame(img);
    }
    else if(choice == "2"){
        SGreenFrame(img);
    }
    else if(choice == "3"){
        SBlueFrame(img);
    }
    else if(choice == "4"){
        SBlackFrame(img);
    }
    else if(choice == "5"){
        SWhiteFrame(img);
    }
    else{
        cout << "Invalid input. try again.\n";
        SimpleFrameFilter(img);
    }
}
void FRedFrame(Image& img){
    SRedFrame(img);
    for(int i=0; i<img.width; i++){
        for(int j=img.height/100; j<img.height/50; j++){
            img(i,j,0) = 186;
            img(i,j,1) = 186;
            img(i,j,2) = 186;
        }
    }
    for(int i=0; i<img.width; i++){
        for(int j=(img.height/100)+50; j<(img.height/50)+40; j++){
            img(i,j,0) = 186;
            img(i,j,1) = 186;
            img(i,j,2) = 186;
        }
    }
    for(int j = 0;j<img.height;j++){
        for(int i = img.width/100;i<img.width/50;i++){
            img(i,j,0) = 186;
            img(i,j,1) = 186;
            img(i,j,2) = 186;
        }
    }
    for(int i = 0; i < img.width; i++){
        for(int j = (img.height * 49) / 50; j < img.height-img.height/100; j++){ // Adjusted loop range
            img(i, j, 0) = 186;
            img(i, j, 1) = 186;
            img(i, j, 2) = 186;
        }
    }
    for(int i=0; i<img.width; i++){
        for(int j=(img.height*49)/50-40; j<(img.height-img.height/100)-50; j++){
            img(i,j,0) = 186;
            img(i,j,1) = 186;
            img(i,j,2) = 186;
        }
    }
    for(int j = 0; j < img.height; j++){
        for(int i = (img.width * 49) / 50; i < (img.width-img.width/100); i++){ // Adjusted loop range
            img(i, j, 0) = 186;
            img(i, j, 1) = 186;
            img(i, j, 2) = 186;
        }
    }

}
void FWhiteFrame(Image& img){
    SWhiteFrame(img);
    for(int i=0; i<img.width; i++){
        for(int j=img.height/100; j<img.height/50; j++){
            img(i,j,0) = 0;
            img(i,j,1) = 0;
            img(i,j,2) = 0;
        }
    }
    for(int i=0; i<img.width; i++){
        for(int j=(img.height/100)+50; j<(img.height/50)+40; j++){
            img(i,j,0) = 0;
            img(i,j,1) = 0;
            img(i,j,2) = 0;
        }
    }
    for(int j = 0;j<img.height;j++){
        for(int i = img.width/100;i<img.width/50;i++){
            img(i,j,0) = 0;
            img(i,j,1) = 0;
            img(i,j,2) = 0;
        }
    }
    for(int i = 0; i < img.width; i++){
        for(int j = (img.height * 49) / 50; j < img.height-img.height/100; j++){ // Adjusted loop range
            img(i, j, 0) = 0;
            img(i, j, 1) = 0;
            img(i, j, 2) = 0;
        }
    }
    for(int i=0; i<img.width; i++){
        for(int j=(img.height*49)/50-40; j<(img.height-img.height/100)-50; j++){
            img(i,j,0) = 0;
            img(i,j,1) = 0;
            img(i,j,2) = 0;
        }
    }
    for(int j = 0; j < img.height; j++){
        for(int i = (img.width * 49) / 50; i < (img.width-img.width/100); i++){ // Adjusted loop range
            img(i, j, 0) = 0;
            img(i, j, 1) = 0;
            img(i, j, 2) = 0;
        }
    }

}
void FBlackFrame(Image& img){
    SBlackFrame(img);
    for(int i=0; i<img.width; i++){
        for(int j=img.height/100; j<img.height/50; j++){
            img(i,j,0) = 186;
            img(i,j,1) = 186;
            img(i,j,2) = 186;
        }
    }
    for(int i=0; i<img.width; i++){
        for(int j=(img.height/100)+50; j<(img.height/50)+40; j++){
            img(i,j,0) = 186;
            img(i,j,1) = 186;
            img(i,j,2) = 186;
        }
    }
    for(int j = 0;j<img.height;j++){
        for(int i = img.width/100;i<img.width/50;i++){
            img(i,j,0) = 186;
            img(i,j,1) = 186;
            img(i,j,2) = 186;
        }
    }
    for(int i = 0; i < img.width; i++){
        for(int j = (img.height * 49) / 50; j < img.height-img.height/100; j++){ // Adjusted loop range
            img(i, j, 0) = 186;
            img(i, j, 1) = 186;
            img(i, j, 2) = 186;
        }
    }
    for(int i=0; i<img.width; i++){
        for(int j=(img.height*49)/50-40; j<(img.height-img.height/100)-50; j++){
            img(i,j,0) = 186;
            img(i,j,1) = 186;
            img(i,j,2) = 186;
        }
    }
    for(int j = 0; j < img.height; j++){
        for(int i = (img.width * 49) / 50; i < (img.width-img.width/100); i++){ // Adjusted loop range
            img(i, j, 0) = 186;
            img(i, j, 1) = 186;
            img(i, j, 2) = 186;
        }
    }

}
void FBlueFrame(Image& img){
    SBlueFrame(img);
    for(int i=0; i<img.width; i++){
        for(int j=img.height/100; j<img.height/50; j++){
            img(i,j,0) = 186;
            img(i,j,1) = 186;
            img(i,j,2) = 186;
        }
    }
    for(int i=0; i<img.width; i++){
        for(int j=(img.height/100)+50; j<(img.height/50)+40; j++){
            img(i,j,0) = 186;
            img(i,j,1) = 186;
            img(i,j,2) = 186;
        }
    }
    for(int j = 0;j<img.height;j++){
        for(int i = img.width/100;i<img.width/50;i++){
            img(i,j,0) = 186;
            img(i,j,1) = 186;
            img(i,j,2) = 186;
        }
    }
    for(int i = 0; i < img.width; i++){
        for(int j = (img.height * 49) / 50; j < img.height-img.height/100; j++){ // Adjusted loop range
            img(i, j, 0) = 186;
            img(i, j, 1) = 186;
            img(i, j, 2) = 186;
        }
    }
    for(int i=0; i<img.width; i++){
        for(int j=(img.height*49)/50-40; j<(img.height-img.height/100)-50; j++){
            img(i,j,0) = 186;
            img(i,j,1) = 186;
            img(i,j,2) = 186;
        }
    }
    for(int j = 0; j < img.height; j++){
        for(int i = (img.width * 49) / 50; i < (img.width-img.width/100); i++){ // Adjusted loop range
            img(i, j, 0) = 186;
            img(i, j, 1) = 186;
            img(i, j, 2) = 186;
        }
    }

}
void FGreenFrame(Image& img){
    SGreenFrame(img);
    for(int i=0; i<img.width; i++){
        for(int j=img.height/100; j<img.height/50; j++){
            img(i,j,0) = 186;
            img(i,j,1) = 186;
            img(i,j,2) = 186;
        }
    }
    for(int i=0; i<img.width; i++){
        for(int j=(img.height/100)+50; j<(img.height/50)+40; j++){
            img(i,j,0) = 186;
            img(i,j,1) = 186;
            img(i,j,2) = 186;
        }
    }
    for(int j = 0;j<img.height;j++){
        for(int i = img.width/100;i<img.width/50;i++){
            img(i,j,0) = 186;
            img(i,j,1) = 186;
            img(i,j,2) = 186;
        }
    }
    for(int i = 0; i < img.width; i++){
        for(int j = (img.height * 49) / 50; j < img.height-img.height/100; j++){ // Adjusted loop range
            img(i, j, 0) = 186;
            img(i, j, 1) = 186;
            img(i, j, 2) = 186;
        }
    }
    for(int i=0; i<img.width; i++){
        for(int j=(img.height*49)/50-40; j<(img.height-img.height/100)-50; j++){
            img(i,j,0) = 186;
            img(i,j,1) = 186;
            img(i,j,2) = 186;
        }
    }
    for(int j = 0; j < img.height; j++){
        for(int i = (img.width * 49) / 50; i < (img.width-img.width/100); i++){ // Adjusted loop range
            img(i, j, 0) = 186;
            img(i, j, 1) = 186;
            img(i, j, 2) = 186;
        }
    }

}


void fancymenu(Image& img){

    cout << "Choose the frame color\n";
    cout << "1. Red\n2. Green\n3. Blue\n4. Black\n5. white"<<endl;
    string choice;
    cin >> choice;
    if(choice == "1"){
        FRedFrame(img);
    }
    else if(choice == "2"){
        FGreenFrame(img);
    }
    else if(choice == "3"){
        FBlueFrame(img);
    }
    else if(choice == "4"){
        FBlackFrame(img);
    }
    else if(choice == "5"){
        FWhiteFrame(img);
    }
    else{
        cout << "Invalid input. try again.\n";
        SimpleFrameFilter(img);
    }
}
void MainFrame(Image& img){
    cout << "What do you want?\n";
    cout << "1) Simple frame\n2) Fancy frame" << endl;
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            SimpleFrameFilter(img);
            break;
        case 2:
            fancymenu(img);
            break;
        default:
            cout << "Please enter a valid input.\n";
            MainFrame(img);
    }
}
void cropped_filter(Image& image) {
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

    if(x < 0 || y < 0 || width < 0 || height < 0 || x + width > image.width || y + height > image.height){
        cout << "Please enter valid dimensions.\n";
        cin.ignore();
        return cropped_filter(image);
    }

    // Create a temporary image to store the cropped area
    Image temp_image(width, height);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            for (int k = 0; k < image.channels; k++) {
                temp_image(i, j, k) = image(y + i, x + j, k);
            }
        }
    }

    // Resize the original image to the cropped dimensions
    image.width = width;
    image.height = height;
    image.imageData = (unsigned char*)realloc(image.imageData, width * height * image.channels);

    // Copy the cropped area back to the original image
    memcpy(image.imageData, temp_image.imageData, width * height * image.channels);
}
void Darken_and_Lighten(Image& before){

    cout << "Do you want to Darken or Lighten the image?\n1)Lighten\n2)Darken\n";

    string choice;
    cin >> choice;

    while (choice != "1" && choice != "2"){
        cout << "Please enter a valid option:";
        cin >> choice;
    }
    if (choice == "1") {
        for (int i = 0; i < before.width; ++i) {
            for (int j = 0; j < before.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    int new_value = static_cast<int>(before(i,j,k)*1.2);
                    before(i,j,k) = min(new_value, 255);
                }
            }
        }
    }

    else if (choice == "2"){
        for (int i = 0; i < before.width; ++i) {
            for (int j = 0; j < before.height; ++j) {
                for (int k = 0; k < 3; ++k) {
                    before (i,j,k) = before (i,j,k)*0.5;
                }
            }
        }
    }
}
void detect_image(Image &image){
    // Convert image to grayscale
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            // Calculate grayscale value (average of RGB channels)
            unsigned int avg = 0;
            for (int k = 0; k < image.channels; ++k) {
                avg += image(i, j, k);
            }
            avg /= image.channels;

            // Assign grayscale value to all color channels
            for (int k = 0; k < image.channels; ++k) {
                image(i, j, k) = avg;

            }
        }
    }

    // Apply Sobel operator
    int rows = image.height - 2;
    int cols = image.width - 2;
    vector<vector<int>> new_Ix(rows, vector<int>(cols));
    vector<vector<int>> new_Iy(rows, vector<int>(cols));
    vector<vector<int>> new_matrix(rows, vector<int>(cols));

    int Ix[3][3] = {
            {-1, 0, 1},
            {-2, 0, 2},
            {-1, 0, 1}
    };

    int Iy[3][3] = {
            {1, 2, 1},
            {0, 0, 0},
            {-1, -2, -1}
    };

    // Convolve with Sobel filters
    for (int i = 0; i < cols; ++i) {
        for (int j = 0; j < rows; ++j) {
            int sumIx = 0;
            int sumIy = 0;
            for (int m = 0; m < 3; ++m) {
                for (int n = 0; n < 3; ++n) {
                    sumIx += image(i + m, j + n, 0) * Ix[m][n];
                    sumIy += image(i + m, j + n, 0) * Iy[m][n];
                }
            }
            new_Ix[j][i] = sumIx;
            new_Iy[j][i] = sumIy;
        }
    }

    double sum_mat = 0.0;
    for(int i = 0; i < cols; ++i){
        for(int j = 0; j < rows; ++j){
            int sum = sqrt((new_Ix[j][i] * new_Ix[j][i]) + (new_Iy[j][i] * new_Iy[j][i])); // corrected indices
            new_matrix[j][i] = sum; // corrected indices
            sum_mat += sum;
        }
    }
    double avg = ceil(sum_mat / (rows * cols));

    for(int i = 0; i < cols; ++i){
        for(int j = 0; j < rows; ++j) {
            if (new_matrix[j][i] > avg) {
                for (int k = 0; k < image.channels; ++k) {
                    image(i + 1, j + 1, k) = 0;
                }
            } else {
                for (int k = 0; k < image.channels; ++k) {
                    image(i + 1, j + 1, k) = 255;
                }
            }
        }
    }
}
void purple_image(Image& image){
    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            // Decrease green channel and possibly adjust red and blue channels
            image(i, j, 1) *= 0.73;
        }
    }
}
void mainmenu(Image &image){
    string choice;
    cout << "=>Choose the filter\n";
    cout << "1. Gray scale\n";
    cout << "2. Black and white\n";
    cout << "3. Invert image\n";
    cout << "4. Flip image\n";
    cout << "5. Rotate image\n";
    cout << "6. Merge images\n";
    cout << "7. Infrared filter\n";
    cout << "8. Blur filter\n";
    cout << "9. Resize\n";
    cout << "10. Frame filter\n";
    cout << "11. Crop image\n";
    cout << "12. Darken and lighten\n";
    cout << "13. Detect image\n";
    cout << "14. Purple image\n";
    cout<< "15. exit\n";
    cin >> choice;
    if(choice == "1"){
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
    }
    else if(choice == "4"){
        choice_flip(image);
    }
    else if(choice == "6"){
        merge(image);
    }
    else if(choice == "7"){
        infrared(image);
    }
    else if(choice == "8"){
        cout << "Please wait it could take afew minutes.\n";
        Blur(image);
    }
    else if(choice == "9"){
        resize(image);
    }
    else if(choice == "10"){
        MainFrame(image);
    }
    else if(choice == "11"){
        cropped_filter(image);
    }
    else if(choice == "12"){
        Darken_and_Lighten(image);
    }
    else if(choice == "13"){
        detect_image(image);
    }
    else if(choice == "14"){
        purple_image(image);
    }
    else if(choice == "15"){
        cout << "Thanks for your time!\n";
        exit(0);
    }
    else{
        cout << "Please enter a number between 1 and 15\n";
        return mainmenu(image);
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
