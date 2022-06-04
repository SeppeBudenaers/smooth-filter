#include <stdio.h>
#include <stdlib.h>

void sharping(unsigned char * pixels, signed int hoogte, signed int breedte){

  int sharpen[3][3] = {{0,-1,0}, {-1,5,-1}, {0,-1,0}};

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
                  temp1 = temp1 * sharpen[smoothy][smoothx];
                  temp2 = temp2 * sharpen[smoothy][smoothx];
                  temp3 = temp3 * sharpen[smoothy][smoothx];
                  rbuffer = temp1;
                  gbuffer = temp2;
                  bbuffer = temp3;
              }
          }
          pixels[startloc+2] = rbuffer;
          pixels[startloc+1] = gbuffer;
          pixels[startloc] = bbuffer;
      }
  }
}
