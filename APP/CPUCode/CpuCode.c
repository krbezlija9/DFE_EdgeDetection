#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Maxfiles.h"
#include <MaxSLiCInterface.h>

#include "ppmIO.h"

int check (int width, int height, int32_t *outImage, int32_t *expectedImage)
{
    int i, status = 0, size = width * height;
    for(i = 0; i < size; i++)
    {
        if (abs(outImage[i] - expectedImage[i]) >= 2)
        {
          printf("outImage[%d] != expectedImage[%d] : %d != %d \n", i, i, outImage[i], expectedImage[i]);
        }
    }
    return status;
}

void makeExpected (int width, int height, int32_t *inImage, int32_t *expectedImage)
{
  int i, j, Gx = 0, Gy = 0;
  float g;
  for (i = 0; i < height; i++)
  {
    for (j = 0; j < width; j++)
    {
        if ((i == 0 || i == height - 1)) expectedImage[i * width + j] = 0;
        else
        {
          if (j == 0 || j == width - 1) expectedImage[i * width + j] = 0;
          else
          {
            Gx = -  3 * inImage[(i - 1) * width + (j - 1)] +  3 * inImage[(i - 1) * width + (j + 1)]
                 - 10 * inImage[i * width + (j - 1)]       + 10 * inImage[i * width + (j + 1)]
                 -  3 * inImage[(i + 1) * width + (j - 1)] +  3 * inImage[(i + 1) * width + (j + 1)];

            Gy = +  3 * inImage[(i - 1) * width + (j - 1)] + 10 * inImage[(i - 1) * width + j]
                 +  3 * inImage[(i - 1) * width + (j + 1)] -  3 * inImage[(i + 1) * width + (j - 1)]
                 - 10 * inImage[(i + 1) * width + j]       -  3 * inImage[(i + 1) * width + (j + 1)];

            g = sqrt((float)(Gx * Gx) + (float)(Gy * Gy));
            expectedImage[i * width + j] = (int)sqrt(g);
          }
        }
    }
  }
}

int main(void)
{
	printf("Loading image.\n");
	int32_t *inImage;
	int width = 0, height = 0;
	loadImage("lena.ppm", &inImage, &width, &height, 1);

	int dataSize = width * height * sizeof(int);
	// Allocate buffers for the output image and expected output image
	int32_t *outImage = malloc(dataSize);
	int32_t *expectedImage = malloc(dataSize);

	printf("Running Kernel.\n");
	EdgeDetection(width * height, inImage, outImage);

	printf("Saving image.\n");
	writeImage("lena_Scharr.ppm", outImage, width, height, 1);

  makeExpected(width, height, inImage, expectedImage);

  writeImage("lena_expectedScharr.ppm", expectedImage, width, height, 1);

  // Check if the expected image is the same as the one we got
  int status = check(width, height, outImage, expectedImage);
	if (status)	printf("Test failed.\n");
	else printf("Test passed OK!\n");
  return status;
}
