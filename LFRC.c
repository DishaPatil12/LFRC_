/*RGB_TO_GRAYSCALE*/
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include "image.h"
int main()
{
const char inputfile[]="org.bmp";
const char outputfile[]="converted.bmp";
image_I *img= LFRC_ReadImageFromFile(inputfile);
LFRC_WriteImageToFile(inputfile,outputfile, img);
LFRC_FreeImage(&img);
return 0;
}
