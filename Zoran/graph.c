// *******************************************
//
// GRAPH3.C - Basic Graphics Support for CLI's
//
// *******************************************

//statically allocated arrays for graphics output
//main historgram display. 10 viewports
char red[640][480][10];
char green[640][480][10];
char blue[640][480][10];

long sx=640; //dimensions of viewport
long sy=480;

//CURRENT COLOR SUPPORT
long cur_red[10];
long cur_green[10];
long cur_blue[10];

//note if using a refreshing browser page for output remember to include cache defeating

// FUNCTION PROTOTYPES

// Limited graphics support
//void writebmp(char *fname); //writes out the graphics arrays to a BMP file
//void bar2(int x, int y, int w, int h, char i);
//void clrscr();

// END OF FUNCTION PROTOTYPES

//Graphics Support Routines

initgraph3()
{
	int a;

	//set all current colors to white
	//for all viewports
	//(this way it will draw right out of the package)
	for (a=0;a<10;a++)
	{
		cur_red[a]=255;
		cur_green[a]=255;
		cur_blue[a]=255;
	}

}

setcolor(int vp, int r, int g, int b)
{
	cur_red[vp]=r; cur_green[vp]=g; cur_blue[vp]=b;
}

clrscr(int vp)
{
	int x,y;

	//clearscreen to white
	for (x=0;x<sx;x++)
		for (y=0;y<sy;y++)
		{
//			red[x][y][vp]=255; //to white
//			green[x][y][vp]=255;
//			blue[x][y][vp]=255;

			red[x][y][vp]=0; //to black
			green[x][y][vp]=0;
			blue[x][y][vp]=0;
		}

}

getpixel(int vp, int x, int y, char *r, char *g, char *b)
{
	if ((x>0)&&(x<sx)&&(y>0)&&(y<sy))
	{
		*r=red[x][y][vp];
		*g=green[x][y][vp];
		*b=blue[x][y][vp];
	}
	else
	{
		*r=0; //returns black on a clip
		*g=0;
		*b=0;
	}
}

putpixel(int vp, int x, int y)
{
	//wrap the putpixel to reduce segmentation faults
	//"clipping"

	if ((x>=0)&&(x<sx)&&(y>=0)&&(y<sy))
	{
		//uses current color
		red[x][y][vp]=cur_red[vp];
		green[x][y][vp]=cur_green[vp];
		blue[x][y][vp]=cur_blue[vp];
	}
}

swap(int *a, int *b)
{
	int tmp; tmp=*a; *a=*b; *b=tmp;
}

bar(int vp, int x1, int y1, int x2, int y2)
{
	int a,b;
	//draws a rectangle in the current color

	if (y2<y1) swap(&y1,&y2);
	if (x2<x1) swap(&x1,&x2);

	for (a=x1;a<=x2;a++)
		for (b=y1;b<=y2;b++)
			putpixel(vp,a,b);
}

bar2(int vp, int x, int y, int w, int h)
{
	//w and h have to be positive
	//draws rectangle in the current color for the viewport
	int a,b;

	for (a=x;a<=(x+w-1);a++)
		for (b=y;b<=(y+h-1);b++)
			putpixel(vp,a,b);
}

line(int vp, int x1, int y1, int x2, int y2)
{
	double m;
	double c=0.0;
	int a;

	if (x2<x1)
	{
		swap(&x1,&x2);
		swap(&y1,&y2);
	}

	//intercept the divide by zero error
	if ((x2-x1)==0)
		m=99999;
	else
		m=((double)(y2-y1))/((double)(x2-x1));

	if (m<1)
	{
		for (a=x1;a<x2;a++)
		{
			c+=m;
			bar2(vp,a,y1+c,2,2);
		}
	}
	else
	{
		if (y2<y1)
		{
			swap(&x1,&x2);
			swap(&y1,&y2);
		}

		for (a=y1;a<y2;a++)
		{
			c+=1/m;
			bar2(vp,x1+c,a,2,2);
		}

	}
}

circle(int vp, int x, int y, int r)
{
	double a;

	//draws a circle in the current color
	for (a=0;a<(2*3.14159);a+=0.001)
		bar2(vp,(int)(cos(a)*r)+x,(int)(sin(a)*r)+y,1,1);
}

textout(int vp, int x,int y, char s[], int fs)
{
	int cx,cy;
	int c,d;
	char o;

	char font[41][8]={

	{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}, //space
	{0xF8,0xF8,0xF8,0xF8,0xF8,0xF8,0x00,0x00}, //white block - Use for unrecognized chars

	{0x70,0x88,0x88,0xF8,0x88,0x88,0x00,0x00}, //A
	{0xF0,0x88,0xF0,0x88,0x88,0xF0,0x00,0x00}, //B
	{0x70,0x88,0x80,0x80,0x88,0x70,0x00,0x00}, //C
	{0xE0,0x90,0x88,0x88,0x88,0xF0,0x00,0x00}, //D
	{0xF8,0x80,0xE0,0x80,0x80,0xF8,0x00,0x00}, //E

	{0xF8,0x80,0xF0,0x80,0x80,0x80,0x00,0x00}, //F
	{0x78,0x80,0x80,0x98,0x88,0x70,0x00,0x00}, //G
	{0x88,0x88,0x88,0xF8,0x88,0x88,0x00,0x00}, //H
	{0xF8,0x20,0x20,0x20,0x20,0xF8,0x00,0x00}, //I
	{0xF8,0x10,0x10,0x10,0x90,0x60,0x00,0x00}, //J

	{0x90,0x0A,0xC0,0xE0,0x90,0x88,0x00,0x00}, //K
	{0x80,0x80,0x80,0x80,0x80,0xF8,0x00,0x00}, //L
	{0x88,0xD8,0xA8,0x88,0x88,0x88,0x00,0x00}, //M
	{0x88,0xC8,0xC8,0xA8,0x98,0x98,0x00,0x00}, //N
	{0x70,0x88,0x88,0x88,0x88,0x70,0x00,0x00}, //O

	{0xF0,0x88,0x88,0xF0,0x80,0x80,0x00,0x00}, //P
	{0x70,0x88,0x88,0xA8,0x98,0x78,0x00,0x00}, //Q
	{0xF0,0x88,0x88,0xF0,0x90,0x88,0x00,0x00}, //R
	{0x70,0x88,0xE0,0x18,0x88,0x70,0x00,0x00}, //S
	{0xF8,0x20,0x20,0x20,0x20,0x20,0x00,0x00}, //T

	{0x88,0x88,0x88,0x88,0x88,0x70,0x00,0x00}, //U
	{0x88,0x88,0x88,0x88,0x50,0x20,0x00,0x00}, //V
	{0x88,0x88,0xA8,0xA8,0xD8,0x88,0x00,0x00}, //W
	{0x88,0x40,0x20,0x20,0x50,0x80,0x00,0x00}, //X
	{0x88,0x88,0x88,0x50,0x20,0x20,0x00,0x00}, //Y

	{0xF8,0x10,0x20,0x20,0x40,0xF8,0x00,0x00}, //Z


	{0x20,0x60,0xE0,0x20,0x20,0xF8,0x00,0x00}, //1
	{0x70,0x88,0x08,0x30,0x40,0xF8,0x00,0x00}, //2
	{0x70,0x88,0x38,0x38,0x88,0x70,0x00,0x00}, //3
	{0x30,0x50,0x90,0xF8,0x10,0x10,0x00,0x00}, //4
	{0xF8,0x80,0xF0,0x08,0x88,0x70,0x00,0x00}, //5

	{0x38,0x40,0xF0,0x88,0x88,0x70,0x00,0x00}, //6
	{0xF8,0x08,0x10,0x20,0x20,0x20,0x00,0x00}, //7
	{0x70,0x88,0x70,0x88,0x88,0x70,0x00,0x00}, //8
	{0x70,0x88,0x78,0x18,0x20,0x40,0x00,0x00}, //9
	{0x70,0x88,0x98,0xA8,0xC8,0x70,0x00,0x00}, //0

	{0x00,0x20,0x20,0xF8,0x20,0x20,0x00,0x00}, //+
	{0x00,0x00,0x00,0xF8,0x00,0x00,0x00,0x00}, //-
	{0x00,0x00,0x00,0x00,0x30,0x30,0x00,0x00}  //.

	};

	cx=x; cy=y;

	for (c=0;c<strlen((char *)s);c++)
	{

		//map characters to array ordinal (doesn't use ASCII)
		switch(toupper(s[c]))
		{
			case ' ': o=0; break;
			case 'A': o=2; break;
			case 'B': o=3; break;
			case 'C': o=4; break;
			case 'D': o=5; break;
			case 'E': o=6; break;
			case 'F': o=7; break;
			case 'G': o=8; break;
			case 'H': o=9; break;
			case 'I': o=10; break;
			case 'J': o=11; break;
			case 'K': o=12; break;
			case 'L': o=13; break;
			case 'M': o=14; break;
			case 'N': o=15; break;
			case 'O': o=16; break;
			case 'P': o=17; break;
			case 'Q': o=18; break;
			case 'R': o=19; break;
			case 'S': o=20; break;
			case 'T': o=21; break;
			case 'U': o=22; break;
			case 'V': o=23; break;
			case 'W': o=24; break;
			case 'X': o=25; break;
			case 'Y': o=26; break;
			case 'Z': o=27; break;

			case '1': o=28; break;
			case '2': o=29; break;
			case '3': o=30; break;
			case '4': o=31; break;
			case '5': o=32; break;
			case '6': o=33; break;
			case '7': o=34; break;
			case '8': o=35; break;
			case '9': o=36; break;
			case '0': o=37; break;

			case '+': o=38; break;
			case '-': o=39; break;
			case '.': o=40; break;

			default: o=1; break;
		}

		for (d=0;d<8;d++)
		{
			//write text in current color
			if (font[o][d]&0x80) bar2(vp,cx,cy+d*fs,fs,fs);
			if (font[o][d]&0x40) bar2(vp,cx+1*fs,cy+d*fs,fs,fs);
			if (font[o][d]&0x20) bar2(vp,cx+2*fs,cy+d*fs,fs,fs);
			if (font[o][d]&0x10) bar2(vp,cx+3*fs,cy+d*fs,fs,fs);
			if (font[o][d]&0x08) bar2(vp,cx+4*fs,cy+d*fs,fs,fs);
			if (font[o][d]&0x04) bar2(vp,cx+5*fs,cy+d*fs,fs,fs);
			if (font[o][d]&0x02) bar2(vp,cx+6*fs,cy+d*fs,fs,fs);
			if (font[o][d]&0x01) bar2(vp,cx+7*fs,cy+d*fs,fs,fs);
		}

		cx+=8*fs;

	}

}

writebmp(char *fname, int vp)
{

	FILE *fptr;
	long fs,is,a,b; //filesize, image size, counters
	int yr;
	char s[255];
	char n,o,p; //color save values

	//save the current color and restore at the end of the function
	//usually this is the last call to a viewport, but sometimes not.
	n=cur_red[vp]; o=cur_green[vp]; p=cur_blue[vp];


	//minimalist graphics support for CLI's
	char bmp_hdr[54]={	0x42,0x4D,0x46,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x36,0x00, 0x00,0x00,
				0x28,0x00,0x00,0x00, 0x02,0x00,0x00,0x00, 0x02,0x00,0x00,0x00, 0x01,0x00,
				0x18,0x00,0x00,0x00, 0x00,0x00,0x10,0x00, 0x00,0x00,0x13,0x00, 0x00,0x00,
				0x13,0x0B,0x00,0x00, 0x00,0x00,0x00,0x00, 0x00,0x00,0x00,0x00};

	fs=54+(sx*sy*3); //filesize is the dimentions of the array multiplied by 3 bytes (R,G and B bytes)
	is=(sx*sy*3);

	//put RED registration square in top-left hand corner at (20,20), height =20, width=20
	//for (a=0;a<20;a++)
	//	for (b=0;b<20;b++)
	//		red[a+20][b+20][vp]=255;

	setcolor(vp,255,255,255);
	//textout(vp,20,20,"Reg",1);

	//Stanford Systems copyright notice
       	yr=2016;
	//sprintf(s,"%d (c) Copyright Stanford Systems",yr);
	//textout(vp,sx/2-(8*strlen(s))/2,sy-10,s,1);

	memcpy((void *)&bmp_hdr[2],(void *)&fs,4);
	memcpy((void *)&bmp_hdr[18],(void *)&sx,4);
	memcpy((void *)&bmp_hdr[22],(void *)&sy,4);
	memcpy((void *)&bmp_hdr[34],(void *)&is,4);

	if ((fptr=fopen(fname,"wb"))!=NULL)
	{
		fwrite(bmp_hdr,54,1,fptr);

		for (b=sy;b>0;b--)
			for (a=0;a<sx;a++)
			{
				fwrite(&blue[a][b][vp],1,1,fptr);
				fwrite(&green[a][b][vp],1,1,fptr);
				fwrite(&red[a][b][vp],1,1,fptr);
			}
	}
	else
	{
		printf("failed to open BMP file.\n");
		return -1; //error code indicating file could not be opened
	}

	fclose(fptr);

	//restore any viewport vars we changed here
	cur_red[vp]=n; cur_green[vp]=o; cur_blue[vp]=o;

	return 1;
}
