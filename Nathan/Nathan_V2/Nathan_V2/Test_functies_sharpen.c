void sharpenImage(Image& input, Image& output)
{
  for x = 1 ... width
  for y = 1 ... height
  {
    output[x,y] = 5*input[x,y] - input[x+1,y] - input[x-1,y]
                           - input[x,y+1] - input[x,y-1];
  }
}

------------------------------------------------------------------------------------------------------------------------------

void sharpen()
{
     int sharpen[3][3] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
     bitmap2.initFromBMP("test.bmp");     // Reads the bitmap file

     for(int i=0; i < bitmap2.getHeight(); i++)
         for(int j=0; j < bitmap2.getWidth(); j++)
              for (int k = 0; k < 3; k++)
                  for (int l = 0; l < 3; l++)
                  {
                       Pixel p = bitmap2.getCopyOfPixel(i,j); // Gets the pixel from the specific position.
                       p.r = p.r * sharpen[k][l];   // Color red
                       p.g = p.g * sharpen[k][l];  // Color green
                       p.b = p.b * sharpen[k][l];  // Color blue
                       bitmap2.setPixel(i,j,p);      // Inserts the pixel at the right place.
                  }
}

------------------------------------------------------------------------------------------------------------------------------

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
