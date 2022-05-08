#include "Image.h"

void Image::reduce(Image* source, Image* result, int targetWidth, int targetHeight)
{

    //int copiedColumns = 0;
    //int copiedLines = 0;
    //
    //// Calculate the ration between the target and source image
    //// We'll use this value later to determine how many lines/columns we need to skip before
    //// copying another line/column to the target buffer
    //float horizontalRatio = (float)targetWidth / (float)source->getWidth();
    //float verticalRatio = (float)targetHeight / (float)source->getHeight();
    //
    //// 'current' values = arbitrary number that tells the program when to copy a pixel to the
    //// target image. The program copies a pixel whenever one of these values is at least 1.
    //// We start with both values set to 1 so that we keep the first column and line of the
    //// source image.
    //float horizontalCurrent = 1.0f;
    //float verticalCurrent = 1.0f;
    //
    //// Set the bitmap data so that other programs can read the resulting *.bmp file
    //result->setWidth(targetWidth);
    //result->setHeight(targetHeight);
    //result->recalculateBuffers();
    //
    //// Iterate over all columns of the source image
    //for (int x = 0; x < source->getWidth(); x++)
    //{
    //    // If we reached the target width, abort
    //    if (copiedColumns == targetWidth)
    //        break;
    //
    //    // Copy the current column to the resulting image if the current value is at least 1
    //    if (horizontalCurrent >= 1.0f)
    //    {
    //        // Iterate over each pixel in the current column (from the top of the image to the bottom)
    //        for (int y = 0; y < source->getHeight(); y++)
    //        {
    //            if (copiedLines == targetHeight)
    //                break;
    //
    //            // But make sure to only copy the needed pixels of the current column
    //            if (verticalCurrent >= 1.0f)
    //            {
    //                unsigned char pixel[3];
    //
    //                source->getPixel(x, y, &pixel[0]);
    //                result->setPixel(copiedColumns, copiedLines, pixel[0], pixel[1], pixel[2]);
    //
    //                copiedLines += 1;
    //                verticalCurrent -= 1.0f;
    //            }
    //
    //            verticalCurrent += verticalRatio;
    //        }
    //
    //        copiedLines = 0;
    //        copiedColumns += 1;
    //        horizontalCurrent -= 1.0f;
    //        verticalCurrent = 1.0f;
    //    }
    //
    //    horizontalCurrent += horizontalRatio;
    //}
}
