#include "Image_Class.h"
using namespace std;
void RedFrame(Image& img){
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
void GreenFrame(Image& img){
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
void BlueFrame(Image &img){
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
void FrameFilter(Image& img){
    cout << "Choose the frame color\n";
    cout << "1. Red\n2. Green\n3. Blue\n";
    string choice;
    cin >> choice;
    if(choice == "1"){
        RedFrame(img);
    }
    else if(choice == "2"){
        GreenFrame(img);
    }
    else if(choice == "3"){
        BlueFrame(img);
    }
    else{
        cout << "Invalid input. try again.\n";
        FrameFilter(img);
    }
}
int main() {

    return 0;
}
