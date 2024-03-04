#include <stdio.h>
#include <stdlib.h>
#include <complex.h>
#include <math.h>
#include "ppm.h"

#define TRSH 2.0     // Seuil de convergence pour l'ensemble de Mandelbrot.
#define ITER 1024ull // Nombre maximal d'itérations pour déterminer si un point appartient à l'ensemble de Mandelbrot.
#define SIZEX 1500   // Dimension X de l'image.
#define SIZEY 1500   // Dimension Y de l'image.

/**
 * @struct col
 * @brief Structure représentant une couleur au format RGB
 */
struct col
{
    int r;
    int g;
    int b;
};

/**
 * @brief Calcule une couleur en fonction d'une valeur et d'une valeur maximale.
 * @param val La valeur à mapper sur une couleur.
 * @param max La valeur maximale pour la normalisation.
 * @return Une structure col représentant la couleur.
 */
struct col getcol(int val, int max)
{
    double q = (double)val / (double)max; // Normalise la valeur

    struct col c = {0, 0, 0};

    // Mappe la valeur normalisée sur une plage de couleurs
    if (q < 0.25)
    {
        c.r = (q * 4.0) * 255.0;
        c.b = 255;
    }
    else if (q < 0.5)
    {
        c.b = 255;
        c.g = 255;
        c.r = (q - 0.25) * 4.0 * 255.0;
    }
    else if (q < 0.75)
    {
        c.b = 255;
        c.r = 255;
        c.g = 255.0 - (q - 0.5) * 4.0 * 255.0;
    }
    else
    {
        c.b = 255 - (q - 0.75) * 4.0 * 255.0;
        c.g = 0;
        c.r = 255;
    }

    return c;
}

/**
 * @brief Calcule la partie réelle correspondant à la coordonnée x sur l'échelle de Mandelbrot.
 * @param x La coordonnée x.
 * @return La partie réelle de la coordonnée x sur l'échelle de Mandelbrot.
 */
double cx(int x)
{
    static const double qx = 3.0 / (double)SIZEX;
    return -2.0 + x * qx;
}

/**
 * @brief Calcule la partie imaginaire correspondant à la coordonnée y sur l'échelle de Mandelbrot.
 * @param y La coordonnée y.
 * @return La partie imaginaire de la coordonnée y sur l'échelle de Mandelbrot.
 */
double cy(int y)
{
    static const double qy = 2.0 / (double)SIZEY;
    return -1.0 + y * qy;
}

int main(int argc, char *argv[])
{
    double trsh = TRSH;
    if (argc != 2)
    {
        printf("Utilisation du seuil par défaut : %f\n", trsh);
    }
    else
    {
        trsh = atof(argv[1]); // Seuil de convergence pour l'ensemble de Mandelbrot.
        printf("Utilisation du seuil : %f\n", trsh);
    }

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

                if (trsh < mod)
                {
                    break;
                }

                z = z * z + c;

                iter++;
            }

            struct col cc = getcol(log(iter), colref);
            ppm_image_setpixel(&im, i, j, cc.r, cc.g, cc.b);
        }
    }

    ppm_image_dump(&im, "m.ppm");
    ppm_image_release(&im);

    return 0;
}
