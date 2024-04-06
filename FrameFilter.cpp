#include "Image_Class.h"
using namespace std;
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
void MainMenu(Image& img){
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
            MainMenu(img);
    }
}
int main() {
    Image img("luffy.jpg");
    MainMenu(img);
    img.saveImage("new1.jpg");
    return 0;
}
