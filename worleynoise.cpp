#include <stdio.h>
#include <iostream>
#include <cstdlib> 
#include <cmath> 
#include <time.h> 

// Implements rudimentary Worley noise in a 2D PPM image file
//
// Defines an image height, width, and count of focus pixels
// Focus pixels receive a random x and y position
// Each pixel in the image calculates distance to each focus pixel, and uses as brightness value 
// Values are printed to stdout for conversion into ppm file 
// EX: ./pixelnoise > image.ppm

// Create a struct with pixel x and y coordiates
struct pixel {
    int x; 
    int y;
}; 

int main() {
    // define image dimensions
    int img_width = 256; 
    int img_height = 256; 
    // define number of focus pixels
    int pixel_count = 5;
    // define convenient float maximum
    float RANDF_MAX = float(RAND_MAX);
    // seed rand() function to start randomness 
    srand(time(NULL)); 

    // create array of focus pixels 
    pixel pixels[pixel_count];

    // place focus pixels randomly within image. 
    for (int k = 0; k < pixel_count; k++){
        pixels[k].x = int((rand()/RANDF_MAX)*img_width);
        pixels[k].y = int((rand()/RANDF_MAX)*img_width); 
    }

    // Print initial PPM details
    printf("P3\n"); 
    printf("%d %d\n255\n",img_width,img_height);

    // Define distance comparison holders
    float minDistance = 257;
    float tempDistance = 0.0;
    // Loop over rows and columns of image
    for (int i = 0; i < img_width; i++){
        for (int j = 0; j < img_width; j++){
        // Loop over array of focus pixels
            for (int k = 0; k < pixel_count; k++){
                // get distance from current pixel to focus pixel (distance equation)
                tempDistance = sqrt(pow(pixels[k].x-i,2) + pow(pixels[k].y-j,2));
                // calculate minimum distance to a focus pixel
                minDistance = std::min(minDistance,tempDistance);
            }
            // use minimum distance as red, green, and blue values of pixel in image
            printf("%d %d %d\n",int(minDistance),int(minDistance),int(minDistance));
            // reset minimum distance to a value greater than any possible distance 
            // (distance ranges from 0-1, which is multiplied by img_width, or 256)
            minDistance = 257;
        }
    }
}

