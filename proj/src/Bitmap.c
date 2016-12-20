#include "Bitmap.h"

#include "stdio.h"
#include "graphics.h"
//#include "Utilities.h"

Bitmap* loadBitmap(const char* filename) {
    // allocating necessary size
    Bitmap* bmp = (Bitmap*) malloc(sizeof(Bitmap));

    // open filename in read binary mode
    FILE *filePtr;
    filePtr = fopen(filename, "rb");
    if (filePtr == NULL)
        return NULL;

    // read the bitmap file header
    BitmapFileHeader bitmapFileHeader;
    fread(&bitmapFileHeader, 2, 1, filePtr);

    // verify that this is a bmp file by check bitmap id
    if (bitmapFileHeader.type != 0x4D42) {
        fclose(filePtr);
        return NULL;
    }

    int rd;
    do {
        if ((rd = fread(&bitmapFileHeader.size, 4, 1, filePtr)) != 1)
            break;
        if ((rd = fread(&bitmapFileHeader.reserved, 4, 1, filePtr)) != 1)
            break;
        if ((rd = fread(&bitmapFileHeader.offset, 4, 1, filePtr)) != 1)
            break;
    } while (0);

    if (rd = !1) {
        fprintf(stderr, "Error reading file\n");
        exit(-1);
    }

    // read the bitmap info header
    BitmapInfoHeader bitmapInfoHeader;
    fread(&bitmapInfoHeader, sizeof(BitmapInfoHeader), 1, filePtr);

    // move file pointer to the begining of bitmap data
    fseek(filePtr, bitmapFileHeader.offset, SEEK_SET);

    // allocate enough memory for the bitmap image data
    unsigned char* bitmapImage = (unsigned char*) malloc(
            bitmapInfoHeader.imageSize);

    // verify memory allocation
    if (!bitmapImage) {
        free(bitmapImage);
        fclose(filePtr);
        return NULL;
    }

    // read in the bitmap image data
    fread(bitmapImage, bitmapInfoHeader.imageSize, 1, filePtr);

    // make sure bitmap image data was read
    if (bitmapImage == NULL) {
        fclose(filePtr);
        return NULL;
    }

    // close file and return bitmap image data
    fclose(filePtr);

    bmp->bitmapData = bitmapImage;
    bmp->bitmapInfoHeader = bitmapInfoHeader;

    return bmp;
}

void drawBitmap(char* db, Bitmap* bmp, int x, int y, Alignment alignment) {
    if (bmp == NULL)
        return;

    int width = bmp->bitmapInfoHeader.width;
    int drawWidth = width;
    int height = bmp->bitmapInfoHeader.height;

    if (alignment == ALIGN_CENTER)
        x -= width / 2;
    else if (alignment == ALIGN_RIGHT)
        x -= width;

    if (x + width < 0 || x > H_RES || y + height < 0
            || y > V_RES)
        return;

    int xCorrection = 0;
    if (x < 0) {
        xCorrection = -x;
        drawWidth -= xCorrection;
        x = 0;

        if (drawWidth > H_RES)
            drawWidth = H_RES;
    } else if (x + drawWidth >= H_RES) {
        drawWidth = H_RES - x;
    }

    char* bufferStartPos;
    char* imgStartPos;

    int i;
    for (i = 0; i < height; i++) {
        int pos = y + height - 1 - i;

        if (pos < 0 || pos >= V_RES)
            continue;

        bufferStartPos = db;
        bufferStartPos += x * 2 + pos * H_RES * 2;

        //printf("%x \n", bufferStartPos);
        imgStartPos = bmp->bitmapData + xCorrection * 2 + i * width * 2;

        int j;
		for (j = 0; j < drawWidth; j++)
		{
			if (imgStartPos[j*2] != 0x17 && imgStartPos[j*2+1] != 0xfffffff8)
			{

				bufferStartPos[j*2] = imgStartPos[j*2];
				bufferStartPos[j*2+1] = imgStartPos[j*2+1];
			}
			//printf("VALOR 1: %x\n", imgStartPos[j*2]);
			//printf("VALOR 2: %x\n", imgStartPos[j*2+1]);
		}

        //memcpy(bufferStartPos, imgStartPos, drawWidth * 2);

    }
}

void drawbackground(char* db, Bitmap* bmp, int x, int y, Alignment alignment)
{
	  if (bmp == NULL)
	        return;

	    int width = bmp->bitmapInfoHeader.width;
	    int drawWidth = width;
	    int height = bmp->bitmapInfoHeader.height;

	    if (alignment == ALIGN_CENTER)
	        x -= width / 2;
	    else if (alignment == ALIGN_RIGHT)
	        x -= width;

	    if (x + width < 0 || x > H_RES || y + height < 0
	            || y > V_RES)
	        return;

	    int xCorrection = 0;
	    if (x < 0) {
	        xCorrection = -x;
	        drawWidth -= xCorrection;
	        x = 0;

	        if (drawWidth > H_RES)
	            drawWidth = H_RES;
	    } else if (x + drawWidth >= H_RES) {
	        drawWidth = H_RES - x;
	    }

	    char* bufferStartPos;
	    char* imgStartPos;

	    int i;
	    for (i = 0; i < height; i++) {
	        int pos = y + height - 1 - i;

	        if (pos < 0 || pos >= V_RES)
	            continue;

	        bufferStartPos = db;
	        bufferStartPos += x * 2 + pos * H_RES * 2;

	        imgStartPos = bmp->bitmapData + xCorrection * 2 + i * width * 2;

	        memcpy(bufferStartPos, imgStartPos, drawWidth * 2);

	    }
}

void deleteBitmap(Bitmap* bmp) {
    if (bmp == NULL)
        return;

    free(bmp->bitmapData);
    free(bmp);
}
