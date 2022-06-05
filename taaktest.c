#include <stdio.h>
#include <stdlib.h>

void smooth(unsigned char * pixels, signed int hoogte, signed int breedte);
void zwartwit(unsigned char * pixels, signed int hoogte, signed int breedte);
void cleanup(unsigned char * pixels, unsigned char * header,int totaalAantalPixels);

int main(int argc, char const *argv[])
{
    // file path
    char filepath[100];
    printf("Filepath : ");
    scanf("%s",filepath);
    sprintf(filepath,"%s.bmp",filepath);
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
   int busy = 0;
   system("cls");
   while (busy == 0)
   {
        char filter;
        printf("s : 3x3 Smooth filter\n\rg : Grayscale\n\rother char : Save file and exit program\n");
        printf("Welke filter will je toepassen : ");
        scanf("%c",&filter);
        scanf("%c",&filter);
        switch (filter)
        {
        case 's' :
            printf("Applying 3x3 smooth filter...\n");
            smooth(pixels,hoogte,breedte);
            system("cls");
            printf("Last filter applied: 3x3 smooth filter\n");
            break;
        case 'g':
            printf("Applying grayscale...\n");
            zwartwit(pixels,hoogte,breedte);
            system("cls");
            printf("Last filter applied: grayscale\n");
            break;
        default:
            printf("Exiting program...\n");
            busy = 1;
            system("cls");
            printf("Saving file and shutting down program\n");
            break;
        }
   }
   cleanup(pixels,header,totaalAantalPixels);

    //-----------------------------------------
}

void smooth(unsigned char * pixels, signed int hoogte, signed int breedte)
{
    for (int y = 1; y < hoogte-1; y++)
    {
        for (int x = 1; x < breedte -1; x++)
        {
            long startloc = (x + (y*breedte));
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
void zwartwit(unsigned char * pixels, signed int hoogte, signed int breedte){

  for (int y = 0; y < hoogte; ++y)
  {
      for (int x = 0; x < breedte; ++x)
      {
        long startloc = (x + (y*breedte));
        startloc *= 3;
        unsigned char gray = pixels[startloc] * 0.3 + pixels[startloc+1] * 0.58 + pixels[startloc+2] * 0.11;
        //printf("test");
        pixels[startloc+2] = gray;
        pixels[startloc+1] = gray;
        pixels[startloc] = gray;
      }
  }
}

void cleanup(unsigned char * pixels, unsigned char * header,int totaalAantalPixels)
{
    char filepath[100];
    printf("File path and file name : ");
    scanf("%s",filepath);
    sprintf(filepath,"%s.bmp",filepath);
    FILE *fpw = fopen(filepath,"wb");
    if (fpw == NULL)
    {
        printf("can't create file");
    }
    fwrite(header,54,1,fpw);
    fwrite(pixels,(totaalAantalPixels)*3,1,fpw);
    fclose(fpw);
    free(pixels);
    printf("INFO: Heap memory Freed = %d (bytes)\n", totaalAantalPixels*3);
}
