#include "prototypes.h"

Variables var;
Affichage aff;

void drawGame()
{
    int i = 0, j = 0, k = 0, x = 0, y = 0, posX = 0, posY = 0;

    // Map
    for(y = 0; y < Y; y++)
    {
        for(x = 0; x < X; x++)
        {
            if(x == 0) {
                posX = 0;
            }

            k = var.tilemap[y][x];

            switch(k)
            {
                case MUR:
                    drawImage(aff.img[IMG_MUR], posX, posY);
                    break;

                case SOL:
                    drawImage(aff.img[IMG_SOL], posX, posY);
                    break;

                case DEPART:
                    drawImage(aff.img[IMG_SOL], posX, posY);
                    break;

                case ARRIVEE:
                    drawImage(aff.img[IMG_SOL], posX, posY);
                    break;
            }

            posX += 32;
        }
        posY += 32;
    }

    // Bot
    drawImage(aff.img[IMG_BOT], var.pos[POS_BOT_X], var.pos[POS_BOT_Y]);

}

void drawReussite()
{
    drawImage(aff.img[IMG_EXIT], 0, 0);
}

void drawError()
{
    int i = 0, x = 0, y = 0;
    x = 55;

    for(i = 0; i < 15; i++)
    {
        drawImage(aff.img[IMG_BOT], x, y);
        x += 32;
        y += 32;
    }
    y = 0;
    for(i = 0; i < 15; i++)
    {
        drawImage(aff.img[IMG_BOT], x, y);
        x -= 32;
        y += 32;
    }
}
