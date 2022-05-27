#include <stdio.h>
#include <stdlib.h>

void MyImageProcessingApp::sharpen()
{
     bitmap1.initFromBMP("test.bmp");  // Reads the Bitmap file
     t = new Bitmap(bitmap1.getHeight(), bitmap1.getWidth()); // Dynamically createas an empty Bitmap
     int sumr;
     int sumg;
     int sumb;
     int sharpen[3][3] = {{0,-1,0}, {-1,5,-1}, {0,-1,0}}; // The sharpen filter
     Pixel color;
     unsigned char r;
     unsigned char g;
     unsigned char b;

     for (int i = 1; i < bitmap1.getHeight() - 1; i++)
     {
          for (int j = 1; j < bitmap1.getWidth() - 1; j++)
          {
    for (int k = 0; k < 3; k++)
    {
          for (int l = 0; l < 3; l++)
          {
               color = bitmap1.getCopyOfPixel(i, j); // gets an individual pixel
               r = color.r;
               g = color.g;
               b = color.b;
               sumr += r * sharpen[k][l];
               sumg += g * sharpen[k][l];
               sumb += b * sharpen[k][l];
         }
    }

    color.r = sumr;
    color.g = sumg;
    color.b = sumb;

    t->setPixel(i, j, color);  // Inserts the pixel
          }
     }
}
