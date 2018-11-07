#include <cstdlib>
#include <cmath>

#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
using namespace cs225;

// sets up the output image
PNG* setupOutput(unsigned w, unsigned h) {
    PNG* image = new PNG(w, h);
    return image;
}

// Returns my favorite color
HSLAPixel* myFavoriteColor(double saturation) {
  //second bug: my fave pixel should be created on heap if we only use pointer pointing to it
  //so that it would not be over-wrrited.
    HSLAPixel *pixel = new HSLAPixel(225, saturation, 0.5);
    return pixel;
}

void sketchify(std::string inputFile, std::string outputFile) {
    // Load in.png
    //first bug: NULL(x0000) is not reachable for user
    //allocate a memory in heap;
    PNG* original = new PNG;
    cout << "Reached line 23" << endl;
    original->readFromFile(inputFile);
    unsigned int width = original->width();
    cout << width << endl ;
    unsigned int height = original->height();
    cout << height <<endl;
    cout << "Reached line 27" << endl;
    // Create out.png
    //third bug: we need to initialize the pointer output to the setup output
    PNG* output =  setupOutput(width, height);

    // Load our favorite color to color the outline
    HSLAPixel* myPixel = myFavoriteColor(0.5);

    // Go over the whole image, and if a pixel differs from that to its upper
    // left, color it my favorite color in the output

    //bug four possibly? : the conditions only could take one at a time or use &&
    for (unsigned y = 1;  y < height; y++) {
        cout << "start inner for" << endl;
        for (unsigned x = 1; x < width; x++) {
            // Calculate the pixel difference
            HSLAPixel & prev = original->getPixel(x - 1, y - 1);
            HSLAPixel & curr = original->getPixel(x, y);
            double diff = std::fabs(curr.h - prev.h);
            // If the pixel is an edge pixel,
            // color the output pixel with my favorite color
            HSLAPixel * currOutPixel = &(output->getPixel(x, y));
            if (diff > 20) {
              //bug five, the most hidden one: if we change pixel by pointer, which means if we do shallow copy,
              //we just not pointing to the output's pixels anymore
              //so that we never could be able to change the pixels for real
              //thus we need deep copy
                    *currOutPixel = *myPixel;
            }

        }

    }

    // Save the output file
    output->writeToFile(outputFile);

    // Clean up memory
    delete myPixel;
    delete output;
    delete original;
}
