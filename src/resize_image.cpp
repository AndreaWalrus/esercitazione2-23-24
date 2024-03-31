#include <cmath>
#include "image.h"

using namespace std;

// HW1 #1
// float x,y: inexact coordinates
// int c: channel
// returns the nearest neighbor to pixel (x,y,c)
float Image::pixel_nearest(float x, float y, int c) const
  {
  return clamped_pixel(round(x),round(y),c);
  }

// HW1 #1
// float x,y: inexact coordinates
// int c: channel
// returns the bilinearly interpolated pixel (x,y,c)
float Image::pixel_bilinear(float x, float y, int c) const
  {
  int x_l = floor(x);
  int y_l = floor(y);
  int x_h = ceil(x);
  int y_h = ceil(y);
  float V1 = clamped_pixel(x_l,y_l,c);
  float V2 = clamped_pixel(x_h,y_l,c);
  float V3 = clamped_pixel(x_l,y_h,c);
  float V4 = clamped_pixel(x_h,y_h,c);
  return (V1*(x_h-x)*(y_h-y))+(V2*(x-x_l)*(y_h-y))+(V3*(x_h-x)*(y-y_l))+(V4*(x-x_l)*(y-y_l));
  }

// HW1 #1
// int w,h: size of new image
// const Image& im: input image
// return new Image of size (w,h,im.c)
Image nearest_resize(const Image& im, int w, int h)
  {
  Image ret(w,h,im.c);

  for(int c=0; c<ret.c; c++){
    for(int j=0; j<h; j++){
      for(int i=0; i<w; i++){
        float x_interpolated = -0.5+((i+0.5)/w)*im.w;
        float y_interpolated = -0.5+((j+0.5)/h)*im.h;
        float val = im.pixel_nearest(x_interpolated,y_interpolated,c);
        ret.set_pixel(i,j,c,val);
      }
    }
  }

  return ret;
  }


// HW1 #1
// int w,h: size of new image
// const Image& im: input image
// return new Image of size (w,h,im.c)
Image bilinear_resize(const Image& im, int w, int h)
  {
  Image ret(w,h,im.c);

  for(int c=0; c<ret.c; c++){
    for(int j=0; j<h; j++){
      for(int i=0; i<w; i++){
        float x_interpolated = -0.5+((i+0.5)/w)*im.w;
        float y_interpolated = -0.5+((j+0.5)/h)*im.h;
        float val = im.pixel_bilinear(x_interpolated,y_interpolated,c);
        ret.set_pixel(i,j,c,val);
      }
    }
  }

  return ret;
  }


