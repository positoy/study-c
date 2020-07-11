#include <stdio.h>
#include <stdlib.h>
#include <MagickWand/MagickWand.h>

#define QUALITY 90

int main()
{
    MagickWand* m_wand;
    int w,h;

    MagickWandGenesis();
    m_wand = NewMagickWand();

    if(MagickReadImage(m_wand, "./che.jpg") == MagickFalse) {
        fprintf(stderr, "cannot read image file.\n");
        exit(1);
    }

    w = MagickGetImageWidth(m_wand);
    h = MagickGetImageHeight(m_wand);

    MagickResizeImage(m_wand, w/2, h/2, LanczosFilter);
    MagickSetImageCompressionQuality(m_wand, QUALITY);

    if (MagickWriteImage(m_wand, "./che_resize.jpg") == MagickFalse) {
        fprintf(stderr, "failed to write image file.\n");
        exit(1);
    }

    if (m_wand) {
        m_wand = DestroyMagickWand(m_wand);
    }
    MagickWandTerminus();

    return 0;
}
