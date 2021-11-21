#ifndef _IMAGE_H
#define _IMAGE_H

typedef struct image{
         int width;
         int height;
         int  bitsPerPixel;
         int stride;	
         unsigned char *data;
}image_I;

image_I *LFRC_ReadImageFromFile( const char *inputfile);
void LFRC_WriteImageToFile(const char *inputfile,const char *outputfile,image_I* img );
void LFRC_FreeImage(image_I **image);


#endif /* IMAGE_H */