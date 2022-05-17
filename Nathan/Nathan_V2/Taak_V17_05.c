#include <stdio.h>
#include <stdlib.h>

void smooth(unsigned char * pixels, signed int hoogte, signed int breedte);
void cleanup(unsigned char * pixels, unsigned char * header,int totaalAantalPixels);

int main(int argc, char const *argv[])
{
    // file path
    char filepath[100];
    printf("Filepath : ");
    scanf("%s",filepath);

    //opening file
    FILE * inputBMP = fopen(filepath, "rb");
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

    //reading header info
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
    printf("INFO: File %s CLOSED\n", filepath);

    //----------------------------------------
    smooth(pixels,hoogte,breedte);
    cleanup(pixels, header ,totaalAantalPixels);
}

void smooth(unsigned char * pixels, signed int hoogte, signed int breedte)
{
    for (int y = 1; y < hoogte-1; y++)
    {
        for (int x = 1; x < breedte -1; x++)
        {
            long startloc = (x + (y*breedte)); // wat als dit over een int (255) gaat
            startloc = startloc *3;
            unsigned char rbuffer = 0;
            unsigned char gbuffer = 0;
            unsigned char bbuffer = 0;
            for (int smoothy = -1; smoothy < 2; smoothy++)
            {

                for (int smoothx = -1; smoothx < 2; smoothx++)
                {
                    long loc = startloc + ((smoothx + (smoothy*breedte))*3); // goed gekeurt rare typecast probleemen
                    float temp1 = (pixels[loc+2]);
                    float temp2 = (pixels[loc+1]);
                    float temp3 = (pixels[loc]);
                    rbuffer = rbuffer + (temp1 / 9);
                    gbuffer = gbuffer + (temp2 / 9);
                    bbuffer = bbuffer + (temp3 / 9);
                }
            }
            pixels[startloc+2] = rbuffer;
            pixels[startloc+1] = gbuffer;
            pixels[startloc] = bbuffer;
        }
    }
}

void cleanup(unsigned char * pixels, unsigned char * header,int totaalAantalPixels)
{
    char filepath[100];
    printf("Filename : ");
    scanf("%s",filepath);
    FILE *fpw = fopen(filepath,"wb");
    if (fpw == NULL)
    {
        printf("can't create file");
    }
    fwrite(header,sizeof (header),1,fpw);
    fwrite(pixels,(totaalAantalPixels)*3,1,fpw);
    fclose(fpw);
    free(pixels);
    printf("INFO: Heap memory Freed = %d (bytes)\n", totaalAantalPixels*3);
}
