//Image.h
//
//Class representing an image
//  original by Wagner Correa, 1999
//  turned to C++ by Robert Osada, 2000
//  updated by Stephen J. Guy, 2017

#ifndef IMAGE_INCLUDED
#define IMAGE_INCLUDED

#include <assert.h>
#include <stdio.h>
#include "pixel.h"

#define _USE_MATH_DEFINES
#include <cmath> 


#include "stb_image.h"
#include "stb_image_write.h"

/**
 * constants
 **/

enum {
    IMAGE_CHANNEL_RED,
    IMAGE_CHANNEL_GREEN,
    IMAGE_CHANNEL_BLUE,
    IMAGE_CHANNEL_ALPHA,
    IMAGE_N_CHANNELS
};


/**
 * Image
 **/
class Image
{
public:
    //A union lets us view the data two differen ways
    // either as a collection of pixels (for easy per-pixel processing), and
    // or as just a list of raw bytes (for loading from a file, or cute tricks like quickly setting everything to 0)
    union PixelData{  
       Pixel *pixels;
       uint8_t *raw;
    };
    
    PixelData data;
    //PixelInfo *pixels; //pixel array
    //uint8_t *pixelData;
    int width, height, num_pixels;
    int sampling_method;
    //BMP* bmpImg;

public:
    // Creates a blank image with the given dimensions
    Image (int width, int height);

    // Copy iamage
    Image (const Image& src);

    // Make image from file
    Image(char *fname);

    // Destructor
    ~Image ();

    // Pixel access
    int ValidCoord (int x, int y)  const { return x>=0 && x<width && y>=0 && y<height; }
    Pixel& GetPixel (int x, int y) const { assert(ValidCoord(x,y));  return data.pixels[y*width + x]; }
    void SetPixel (int x, int y, Pixel p) const { assert(ValidCoord(x,y));  data.pixels[y*width + x] = p; }

    // Dimension access
    int Width     () const { return width; }
    int Height    () const { return height; }
    int NumPixels () const { return num_pixels; }

    // Make file from image
    void Write( char *fname );

    void CopyPixels(Image* img);

    // Distance between two points
    double Distance(const double x, const double y, const double x1, const double x2_) const;
};

#endif
