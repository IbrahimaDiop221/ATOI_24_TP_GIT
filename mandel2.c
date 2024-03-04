#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include "ppm.h"

#define TRSH 2.0     // Convergence threshold for the Mandelbrot set.
#define ITER 1024ull // Maximum number of iterations to determine if a point belongs to the Mandelbrot set.
#define SIZEX 1500   // Image X dimension.
#define SIZEY 1500   // Image Y dimension.

/**
 * @struct col
 * @brief Structure representing a color in RGB format
 */
struct col
{
    int r;
    int g;
    int b;
};

/**
 * @brief Computes a color based on a value and a maximum value.
 * @param val The value to map to a color.
 * @param max The maximum value for normalization.
 * @return A struct col representing the color.
 */
struct col getcol(int val, int max)
{
    double q = (double)val / (double)max; // Normalizes the value

    struct col c;

    // Use trigonometric functions for a vivid color palette
    c.r = (sin(q * M_PI * 2) + 1) / 2 * 255;
    c.g = (sin(q * M_PI * 2 + 2.0 / 3.0 * M_PI) + 1) / 2 * 255;
    c.b = (sin(q * M_PI * 2 + 4.0 / 3.0 * M_PI) + 1) / 2 * 255;

    return c;
}

/**
 * @brief Computes the real part corresponding to the x coordinate on the Mandelbrot scale.
 * @param x The x coordinate.
 * @return The real part of the x coordinate on the Mandelbrot scale.
 */
double cx(int x)
{
    static const double qx = 3.0 / (double)SIZEX;
    return -2.0 + x * qx;
}

/**
 * @brief Computes the imaginary part corresponding to the y coordinate on the Mandelbrot scale.
 * @param y The y coordinate.
 * @return The imaginary part of the y coordinate on the Mandelbrot scale.
 */
double cy(int y)
{
    static const double qy = 2.0 / (double)SIZEY;
    return -1.0 + y * qy;
}

int main(int argc, char *argv[])
{
    struct ppm_image im;
    ppm_image_init(&im, SIZEX, SIZEY);

    int i, j;
    int colref = log(ITER);

    for (i = 0; i < SIZEX; ++i)
    {
        for (j = 0; j < SIZEY; ++j)
        {

            unsigned long int iter = 0;

            double complex c = cx(i) + cy(j) * I;
            double complex z = 0;

            while (iter < ITER)
            {
                double mod = cabs(z);

                if (TRSH < mod)
                {
                    break;
                }

                z = z * z + c;

                iter++;
            }

            struct col cc = getcol(iter, colref);
            ppm_image_setpixel(&im, i, j, cc.r, cc.g, cc.b);
        }
    }

    ppm_image_dump(&im, "m.ppm");
    ppm_image_release(&im);

    return 0;
}
