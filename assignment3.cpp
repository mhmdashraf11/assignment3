#include <iostream>
#include "Image_Class.h"
#include <algorithm>
#include <regex>
using namespace std;
Image image(){
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
void filter3(){
    Image img = image();
    for(int i=0; i<img.width; i++){
        for(int j=0; j<img.height; j++){
            img(i,j,0) = 255-img(i,j,0);  // getting the complement of the pixels
            img(i,j,1) = 255-img(i,j,1);
            img(i,j,2) = 255-img(i,j,2);
        }
    }
    // img.saveImage("mario.jpg"); 
    string choice =SaveMenu(); // menu to make the user choose if he wanna save it or not
    while(cin.fail() || (choice != "1" && choice != "2")){
        SaveMenu();
    }
    if(choice == "1"){
        cout << "Enter the name and the extension of your new image:\n";
        cout << "<ImageName.jpg>\n";
        string filename;
        cin >> filename;
        img.saveImage(filename);
    }
    
}



void rotate90() {
    Image img = image();
    int newWidth = img.height; // make the new dimentions
    int newHeight = img.width;
    Image rotatedImage(newWidth, newHeight);
    for (int y = 0; y < img.height; y++) { // loop on the original photo
        for (int x = 0; x < img.width; x++) {
            int newX = y;  // make the new coordinates
            int newY = img.width - x - 1;
            for(int k = 0; k < 3; k++) {
                rotatedImage.setPixel(newX, newY, k, img.getPixel(x, y, k)); 
            }
            
        }
    }

    string choice =SaveMenu();
    while(cin.fail() || (choice != "1" && choice != "2")){
        SaveMenu();
    }
    if(choice == "1"){
        cout << "Enter the name and the extension of your new image:\n";
        cout << "<ImageName.jpg>\n";
        string filename;
        cin >> filename;
        rotatedImage.saveImage(filename);
    }
}
void rotate180() {
    Image img = image();
    Image rotatedImage(img.width, img.height);
    for (int y = 0; y < img.height; y++) {
        for (int x = 0; x < img.width; x++) {
            int newX = img.width - x - 1;  // make the coordinates upside down
            int newY = img.height - y - 1;
            for(int k = 0; k < 3; k++) {
                rotatedImage.setPixel(newX, newY, k, img.getPixel(x, y, k));
            }

        }
    }
    string choice =SaveMenu();
    while(cin.fail() || (choice != "1" && choice != "2")){
        SaveMenu();
    }
    if(choice == "1"){
        cout << "Enter the name and the extension of your new image:\n";
        cout << "<ImageName.jpg>\n";
        string filename;
        cin >> filename;
        rotatedImage.saveImage(filename);
    }

}
void rotate270() {
    Image img = image();
    int newWidth = img.width;
    int newHeight = img.height;
    Image rotatedImage(newWidth, newHeight);
    for (int y = 0; y < img.height; y++) { // to rotate 180 degree
        for (int x = 0; x < img.width; x++) {
            int newX = img.width - x - 1;
            int newY = img.height - y - 1;
            for(int k = 0; k < 3; k++) {
                rotatedImage.setPixel(newX, newY, k, img.getPixel(x, y, k));
            }

        }
    }
    int newWidth2 = rotatedImage.height;
    int newHeight2 = rotatedImage.width;
    Image newimage(newWidth2, newHeight2);
    for (int y = 0; y < rotatedImage.height; y++) { // to rotate 90
        for (int x = 0; x < rotatedImage.width; x++) {// loop on the rotated image to rotate it again
            int newX = y;
            int newY = rotatedImage.width - x - 1;
            for(int k = 0; k < 3; k++) {
                newimage.setPixel(newX, newY, k, rotatedImage.getPixel(x, y, k));
            }
            
        }
    }

    string choice =SaveMenu();
    while(cin.fail() || (choice != "1" && choice != "2")){
        SaveMenu();
    }
    if(choice == "1"){
        cout << "Enter the name and the extension of your new image:\n";
        cout << "<ImageName.jpg>\n";
        string filename;
        cin >> filename;
        newimage.saveImage(filename);
    }
}
void filter6menu(){ // to make the user select the version of the filter
    int choice;
    cout << "Please choose the rotate angle:\n";
    cout << "1. 90\n";
    cout << "2. 180\n";
    cout << "3. 270\n";
    cin >> choice;
    if(cin.fail() || (choice != 1 && choice != 2 && choice != 3)){
        cout << "Please enter a number between 1 and 3\n";
        return filter6menu();
    }
    switch(choice){
        case 1 :
            rotate90();
            break;
        case 2 :
            rotate180();
            break;
        case 3 :
            rotate270();
            break;
        default :
            return filter6menu();             
    }
}

//void blur(){
//    Image img("mario.jpg");
//    int newWidth = img.width;
//    int newHeight = img.height;
//    Image newimage(newWidth, newHeight);
//    for (int y = 0; y < img.height; y++) {
//        for (int x = 0; x < img.width; x++) {
//            int sum = 0;
//            for(int k = 0; k < 3; k++) {
//                sum += img.getPixel(x, y, k);
//            }
//            for(int k = 0; k < 3; k++) {
//                newimage.setPixel(x, y, k, sum/9);
//            }
//        }
//    }
//    // string choice =SaveMenu();
//    // while(cin.fail() || (choice != "1" && choice != "2")){
//    //     SaveMenu();
//    // }
//    img.saveImage("mario3.png");
//}

int main(){
    // rotate180();
// rotate90();
    // rotate270();
    // filter6menu();
    // filter3();
    blur();
    return 0;
}