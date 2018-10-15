#include "image.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

/**
 * Image
 **/
Image::Image (int width_, int height_){

    assert(width_ > 0);
    assert(height_ > 0);

    width           = width_;
    height          = height_;
    num_pixels      = width * height;
    sampling_method = IMAGE_SAMPLING_POINT;
    
    data.raw = new uint8_t[num_pixels*4];
    int b = 0; //which byte to write to
    for (int j = 0; j < height; j++){
        for (int i = 0; i < width; i++){
            data.raw[b++] = 0;
            data.raw[b++] = 0;
            data.raw[b++] = 0;
            data.raw[b++] = 0;
        }
    }

    assert(data.raw != NULL);
}

Image::Image (const Image& src){
    
    width           = src.width;
    height          = src.height;
    num_pixels      = width * height;
    sampling_method = IMAGE_SAMPLING_POINT;
    
    data.raw = new uint8_t[num_pixels*4];
    
    //memcpy(data.raw, src.data.raw, num_pixels);
    *data.raw = *src.data.raw;
}

Image::Image (char* fname){

    int numComponents; //(e.g., Y, YA, RGB, or RGBA)
    data.raw = stbi_load(fname, &width, &height, &numComponents, 4);
    
    if (data.raw == NULL){
        printf("Error loading image: %s", fname);
        exit(-1);
    }
    

    num_pixels = width * height;
    sampling_method = IMAGE_SAMPLING_POINT;
    
}

Image::~Image (){
    delete data.raw;
    data.raw = NULL;
}

void Image::Write(char* fname){
    
    int lastc = strlen(fname);

    switch (fname[lastc - 1]) {
    case 'g': //jpeg (or jpg) or png
        if (fname[lastc - 2] == 'p' || fname[lastc - 2] == 'e') //jpeg or jpg
            stbi_write_jpg(fname, width, height, 4, data.raw, 95);  //95% jpeg quality
        else //png
            stbi_write_png(fname, width, height, 4, data.raw, width * 4);
        break;
    case 'a': //tga (targa)
        stbi_write_tga(fname, width, height, 4, data.raw);
        break;
    case 'p': //bmp
        stbi_write_bmp(fname, width, height, 4, data.raw);
        break;
    default:
        stbi_write_bmp(fname, width, height, 4, data.raw);
    }
}

void Image::CopyPixels(Image* img) {
    for (int i = 0; i < Width(); i++) {
        for (int j = 0; j < Height(); j++) {
            GetPixel(i, j) = img->GetPixel(i, j);
        }
    }
}

/**
 * Image Sample
 **/
void Image::SetSamplingMethod(int method)
{
    assert((method >= 0) && (method < IMAGE_N_SAMPLING_METHODS));
    sampling_method = method;
}


Pixel Image::Sample (double u, double v) {

    int r = 0;
    int g = 0;
    int b = 0;

    if (u < 0)
        return Pixel(0, 0, 0);
    if (v < 0)
        return Pixel(0, 0, 0);
    if (u > Width() - 1)
        return Pixel(0, 0, 0);
    if (v > Height() - 1)
        return Pixel(0, 0, 0);

    switch (sampling_method) {

        // Closest point
    case IMAGE_SAMPLING_POINT:

        return GetPixel((int)u, (int)v);

        // Bilinear (4 closest)
    case IMAGE_SAMPLING_BILINEAR: {

        double d1 = 1.0 / Distance(u, v, floor(u), floor(v)) < INFINITY ? 1.0 / Distance(u, v, floor(u), floor(v)) : 1.0;
        double d2 = 1.0 / Distance(u, v, floor(u), ceil(v)) < INFINITY ? 1.0 / Distance(u, v, floor(u), ceil(v)) : 1.0;
        double d3 = 1.0 / Distance(u, v, ceil(u), floor(v)) < INFINITY ? 1.0 / Distance(u, v, ceil(u), floor(v)) : 1.0;
        double d4 = 1.0 / Distance(u, v, ceil(u), ceil(v)) < INFINITY ? 1.0 / Distance(u, v, ceil(u), ceil(v)) : 1.0;

        if (ceil(u) < Width() && ceil(v) < Height()) {
            double sum = d1 + d2 + d3 + d4;

            //fprintf(stderr, "sum: %f\n", sum);
            //fprintf(stderr, "d1: %f, d2: %f, d3: %f, d4: %f\n", d1 / sum, d2 / sum, d3 / sum, d4 / sum);
            //fprintf(stderr, "flooru: %f, ceilu: %f, floorv: %f, ceilb: %f\n", floor(u), ceil(u), floor(v), ceil(v));

            Pixel p = 
                GetPixel(floor(u), floor(v)) * (d1 / sum) +
                GetPixel(floor(u), ceil(v)) * (d2 / sum) +
                GetPixel(ceil(u), floor(v)) * (d3 / sum) +
                GetPixel(ceil(u), ceil(v)) * (d4 / sum);

            //fprintf(stderr, "p.r: %f, p.g: %f, p.b: %f\n", p.r, p.g, p.b);
            return p;
        }
        else if (ceil(u) == Width() && ceil(v) != Height()) {
            double sum = d1 + d2;

            return
                GetPixel(floor(u), floor(v)) * (d1 / sum) +
                GetPixel(floor(u), ceil(v)) * (d2 / sum);
        }
        else if (ceil(u) != Width() && ceil(v) == Height()) {
            double sum = d1 + d3;

            return
                GetPixel(floor(u), floor(v)) * (d1 / sum) +
                GetPixel(ceil(u), floor(v)) * (d3 / sum);
        }
        else {
            return GetPixel(floor(u), floor(v));
        }
    }

        // Gaussian
    case IMAGE_SAMPLING_GAUSSIAN: {

        double red = 0;
        double gre = 0;
        double blu = 0;

        double weightTot = 0;

        for (int x = (int)u - 2; x <= (int)u + 2; x++) {
            for (int y = (int)v - 2; y <= (int)v + 2; y++) {

                int r = abs(x);
                if (x >= Width())
                    r = abs(Width() - 1 - abs(x - Width() - 1));

                int c = abs(y);
                if (y >= Height())
                    c = abs(Height() - 1 - abs(y - Height() - 1));

                double weight = (1.0 / (2 * M_PI)) * pow(M_E, -pow(Distance(u, v, r, c), 2) / 2.0);

                red += weight * GetPixel(r, c).r;
                gre += weight * GetPixel(r, c).g;
                blu += weight * GetPixel(r, c).b;

                weightTot += weight;
            }
        }

        return Pixel(
            fmax(0, fmin(255, (int)(red / weightTot))),
            fmax(0, fmin(255, (int)(gre / weightTot))),
            fmax(0, fmin(255, (int)(blu / weightTot))));

    }

        // Shouldn't reach here based on assert in setmethod
    default:
        return Pixel();
    }
}

double Image::Distance(double x, double y, double x1, double y1) {
    return sqrt(pow(x - x1, 2) + pow(y - y1, 2));
}