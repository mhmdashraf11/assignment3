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
