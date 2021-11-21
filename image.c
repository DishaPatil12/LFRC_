#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "image.h"

image_I* LFRC_ReadImageFromFile( const char *inputfile)
{
struct image image_I;
struct image *img;
img=&image_I;
FILE *fin= fopen(inputfile, "rb");
unsigned char header[54];
fread(header, sizeof(unsigned char), 54, fin);
int width = *(int*)&header[18];
int height = abs(*(int*)&header[22]);
int bpp = abs(*(int*)&header[28]);
int size= width*height*3;
int stride = (width * 3 + 3) & ~3;
int padding = stride - width * 3;

img=malloc(sizeof(image_I));
img->width=width;
img->height=height;
img->bitsPerPixel=bpp;
img->stride=stride;
img->data= (unsigned char*)malloc(size*sizeof(unsigned char));
fclose(fin);
return img;
}

void LFRC_WriteImageToFile(const char *inputfile,const char *outputfile, image_I *img)
{
FILE *fOut=fopen(outputfile,"wb");  
int width = img->width;
int height =img->height;
printf("height =%d\n", height);
printf("height =%d\n", width);
int bitsPerPixel=img->bitsPerPixel;
const int FHS=14;       			//File Header Size
const int IHS =40;     			 //Info Header Size
int bytesPerPixel;
bytesPerPixel =bitsPerPixel/ 8;   
int paddedRwSize = (int)(4 * ceil((float)(width)/4.0f))*bytesPerPixel;
int fileSize = paddedRwSize*height + FHS + IHS;
int bpp = bytesPerPixel*8;  //Bits Per Pixel
int imageSize = (width)*(height)*(bytesPerPixel);
int resolutionX = 11811;
int resolutionY = 11811;

unsigned char file_info[] = {
        0,0,     /// signature
        0,0,0,0, /// image file size in bytes
        0,0,0,0, /// reserved
        0,0,0,0, /// start of pixel array
        0,0,0,0, /// header size
        0,0,0,0, /// image width
        0,0,0,0, /// image height
        0,0,     /// number of color planes
        0,0,     /// bits per pixel
        0,0,0,0, /// compression
        0,0,0,0, /// image size
        0,0,0,0, /// horizontal resolution
        0,0,0,0, /// vertical resolution
        0,0,0,0, /// colors in color table
        0,0,0,0, /// important color count
    };

    file_info[0] = (unsigned char)('B');
    file_info[1] = (unsigned char)('M');
    file_info[2] = (unsigned char)(fileSize);
    file_info[3] = (unsigned char)(fileSize >> 8);
    file_info[4] = (unsigned char)(fileSize >> 16);
    file_info[5] = (unsigned char)(fileSize >> 24);
    file_info[10] = (unsigned char)(FHS+ IHS);

    file_info[14] = (unsigned char)(IHS);
    file_info[18] = (unsigned char)(width);
    file_info[19] = (unsigned char)(width >> 8);
    file_info[20] = (unsigned char)(width >> 16);
    file_info[21] = (unsigned char)(width >> 24);
    file_info[22] = (unsigned char)(height);
    file_info[23] = (unsigned char)(height >> 8);
    file_info[24] = (unsigned char)(height >> 16);
    file_info[25] = (unsigned char)(height >> 24);
    file_info[26] = (unsigned char)(1);
    file_info[28] = (unsigned char)(bpp);
    file_info[29] =(unsigned char)(bpp>>8);
    file_info[34]=(unsigned char)(imageSize);
    file_info[35]=(unsigned char)(imageSize>> 8);
    file_info[36]=(unsigned char)(imageSize>> 16);
    file_info[37]=(unsigned char)(imageSize >> 24);
    file_info[38] =(unsigned char)(resolutionX);
    file_info[39] =(unsigned char)(resolutionX>> 8);
    file_info[40]=(unsigned char)(resolutionX >> 16);
    file_info[41] =(unsigned char)(resolutionX >> 24);
    file_info[42] =(unsigned char)(resolutionY);
    file_info[43] =(unsigned char)(resolutionY >>8);
    file_info[44] =(unsigned char)(resolutionY >>16);
    file_info[45] =(unsigned char)(resolutionY >>24);

fwrite(file_info,  1 , 54, fOut);
int stride = (width * 3 )+(width%4);
int Padding = stride - width * 3;
FILE *fin= fopen(inputfile, "rb");
unsigned char header[54];
fread(header, sizeof(unsigned char), 54, fin);

 unsigned char pixel[3];
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            fread(pixel, 3, 1, fin);                                                			 //reading RGB from the image 
            unsigned char gray = pixel[0] * 0.3 + pixel[1] * 0.58 + pixel[2] * 0.11; 	//converting into greyscale
            memset(pixel, gray, sizeof(pixel));    										                                 		 //update the grey value directly 
            fwrite(&pixel, 3, 1, fOut);                                              			//writting the grey value to the file
        }
    }
fread(pixel, Padding,width*height, fin);                                                        //Reading the whole file 
fwrite(pixel,Padding,width*height,fOut);                                                       //writting the whole file 

             
fclose(fOut);
}


void LFRC_FreeImage(image_I *image)
{
free(image);
}


