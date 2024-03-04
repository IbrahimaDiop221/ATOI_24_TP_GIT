```c
/**
 * @file ppm.h
 * @brief Bibliothèque pour la génération de fichiers d'images PPM.
 */

#ifndef PPM_H
#define PPM_H

/**
 * @struct ppm_pixel
 * @brief Structure représentant un pixel unique dans une image PPM.
 */
struct ppm_pixel {
  unsigned char r; /**< Valeur du canal rouge */
  unsigned char g; /**< Valeur du canal vert */
  unsigned char b; /**< Valeur du canal bleu */
};

/**
 * @brief Définit les valeurs RGB d'un pixel.
 * @param px Pointeur vers le pixel à définir.
 * @param r Valeur du canal rouge.
 * @param g Valeur du canal vert.
 * @param b Valeur du canal bleu.
 */
static inline void ppm_setpixel(struct ppm_pixel *px, unsigned char r,
                                unsigned char g, unsigned char b) {
  px->r = r;
  px->g = g;
  px->b = b;
}

/**
 * @struct ppm_image
 * @brief Structure représentant une image PPM.
 */
struct ppm_image {
  unsigned int width; /**< Largeur de l'image */
  unsigned int height; /**< Hauteur de l'image */
  struct ppm_pixel *px; /**< Données des pixels */
};

/**
 * @brief Initialise une image PPM avec une largeur et une hauteur spécifiées.
 * @param im Pointeur vers la structure ppm_image à initialiser.
 * @param w Largeur de l'image.
 * @param h Hauteur de l'image.
 * @return 0 en cas de succès, -1 en cas d'échec.
 */
int ppm_image_init(struct ppm_image *im, int w, int h);

/**
 * @brief Libère la mémoire allouée pour une image PPM.
 * @param im Pointeur vers la structure ppm_image à libérer.
 * @return 0 en cas de succès, -1 en cas d'échec.
 */
int ppm_image_release(struct ppm_image *im);

/**
 * @brief Définit les valeurs RGB d'un pixel dans une image PPM.
 * @param im Pointeur vers la structure ppm_image.
 * @param x Coordonnée X du pixel.
 * @param y Coordonnée Y du pixel.
 * @param r Valeur du canal rouge.
 * @param g Valeur du canal vert.
 * @param b Valeur du canal bleu.
 */
static inline void ppm_image_setpixel(struct ppm_image *im, int x, int y,
                                      unsigned char r, unsigned char g,
                                      unsigned char b) {
  struct ppm_pixel *px = im->px + im->width * y + x;
  ppm_setpixel(px, r, g, b);
}

/**
 * @brief Écrit le contenu d'une image PPM dans un fichier.
 * @param im Pointeur vers la structure ppm_image.
 * @param path Chemin vers le fichier où l'image sera écrite.
 * @return 0 en cas de succès, -1 en cas d'échec.
 */
int ppm_image_dump(struct ppm_image *im, char *path);

#endif /* PPM_H */
```
