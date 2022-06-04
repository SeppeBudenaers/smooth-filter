#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

#define BMPINPUT "test_bmp.bmp"
// function that randomly generates numbers
void fillArray(int a[10][20], int m, int n)
{
  int random;
  int i,j;
      for (i=0;i<m;i++)
      {
          for (j=0;j<n;j++)
          {
                           random=rand()%100;
                           a[i][j]=random;
                           }
                           }
  }
  // function that prints the first matrix of random numbers
  void printarray (int a[10][20], int m, int n)
 {
 int i,j;
for (i=0;i<m;i++)
{
    for (j=0;j<n;j++)
        {
                     printf("%4d", a[i][j]);
                     }
                     printf("\n");
                     }
  }
  // function that finds the mean for any number and its 4 nieghbors
  void smooth (int a[10][20], int m, int n)
 {

 int i,j;
 for (i=1;i<m;i++)
{
    for (j=1;j<n;j++)
    {
        a[i][j]=a[i][j]=(a[i-1][j]+a[i][j-1]+a[i+1][j]+a[i][j+1])/4;
        printf("%4d",a[i][j]);
        }
        printf("\n");
 }
 }
 int main()
{

int a[10][20];
 int m,n;
 srand(time(NULL));
 //User input
 printf("please enter number of columns and rows");
 scanf("%d %d", &m,&n);
 fillArray(a,m,n);
 printarray (a,m,n);
 printf("The smoothed image is\n");
 smooth(a,m,n);
 getch();
return 0;
}
