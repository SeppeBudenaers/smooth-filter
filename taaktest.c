#include <stdio.h>
#include <stdlib.h>

#define BMPINPUT "test_bmp.bmp"


int main(int argc, char const *argv[])
{
    FILE * inputBMP = fopen(BMPINPUT, "rb");
    unsigned char header[54] = {0};
    signed int hoogte = 0;
    signed int breedte = 0;
    unsigned char * pixels = NULL;
    int totaalAantalPixels = 0;


    if(inputBMP == NULL)
    {
        printf("%s\n", "ERROR: can't open the file");
        return -1;
    }

    fread(header, 1, 54, inputBMP);

    breedte = header[21] << 24 | header[20] << 16 | header[19] << 8 | header[18]; 
    printf("De breedte van mijn afbeelding is = %d\n", breedte);
    hoogte = header[25] << 24 | header[24] << 16 | header[23] << 8 | header[22]; 
    printf("De hoogte van mijn afbeelding is = %d\n", hoogte);

    totaalAantalPixels = breedte * hoogte;
    pixels = (unsigned char *) malloc(totaalAantalPixels*3);
    if(pixels == NULL)
    {
        printf("ERROR: memory allocation Failed\n");
        return -2;
    }

    fread(pixels, 1, totaalAantalPixels*3, inputBMP);
    printf("INFO: Heap memory allocated = %d (bytes)\n", totaalAantalPixels*3);

    
    fclose(inputBMP);
    printf("INFO: File %s CLOSED\n", BMPINPUT);

    //----------------------------------------
    for (int y = 1; y < hoogte-1; y++)
    {
        for (int x = 1; x < hoogte -1; x++)
        {
            int startloc = (x + (y*breedte))*3 ;
            float rbuffer = 0;
            float gbuffer = 0;
            float bbuffer = 0;
            for (int smoothy = -1; smoothy < 2; smoothy++)
            {
               
                for (int smoothx = -1; smoothx < 2; smoothx++)
                {
                    int loc = startloc + ((smoothx + (smoothy*breedte))*3); // goed gekeurt rare typecast probleemen
                    float temp1 = (pixels[loc+2]);
                    float temp2 = (pixels[loc+1]);
                    float temp3 = (pixels[loc]);
                    rbuffer = rbuffer + (temp1 / 9);
                    gbuffer = gbuffer + (temp2 / 9);
                    bbuffer = bbuffer + (temp3 / 9);
                }
            }
            float rs = pixels[startloc+2];
            float gs = pixels[startloc+1];
            float bs = pixels[startloc];
            printf("pixels : %i, r: %f g : %f b : %f\n",startloc,rs,gs,bs);
            pixels[startloc+2] = rbuffer;
            pixels[startloc+1] = gbuffer;
            pixels[startloc] = bbuffer;
        }  
    }
    printf("output:\n");
    for (int y = 1; y < hoogte-1; y++)
    {
        for (int x = 1; x < hoogte -1; x++)
        {
            int cord = (x + (y*breedte))*3 ;
            float r = pixels[cord+2];
            float g = pixels[cord+1];
            float b = pixels[cord];
            printf("pixels : %i, r: %f g : %f b : %f\n",cord,r,g,b);
        }  
    } 
    //----------------------------------------
    free(pixels);
    printf("INFO: Heap memory Freed = %d (bytes)\n", totaalAantalPixels*3);
    return 0;
}
