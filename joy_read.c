#include "joy_read.h"

/*
mapa[4][0] es un flag
mapa[4][0] = 0 -> en el juego
mapa[4][0] = 1 -> en el menu
mapa[4][0] = 2 -> menu principal
*/

void joy_movement(int mapa[][COL])
{
    joyinfo_t coord = {0, 0, J_NOPRESS};
    int npos = 0;
    dcoord_t coords = {15, 0};
    mapa[5][0] = 0; // flag para seleccion en el menu
    // JUEGO
    while (1)
    {
        if (mapa[4][0] == 0) // JUEGO
        {
            coord = joy_read();
            if (coord.sw = J_PRESS) // dispara el player
            {
                gamer_fire(mapa);
            }
            if (coord.x > THRESHOLD) // movimiento a la derecha
            {
                npos++;
            }
            if (coord.x < -THRESHOLD) // movimiento a la izquierda
            {
                npos--;
            }

            if (coord.y <= THRESHOLD)
            { // si la coordenada en y no se movio hacia la seleccion del menu
                mapa[4][0] = 0;
            }
            else
            { // sino, cambia al menu
                mapa[4][0] = 1;
            }
            gamer_movement(mapa, npos); // genera el movimiento del player
        }
        if (mapa[4][0] == 1) // MENU
        {
            if (coord.x > THRESHOLD && coord.sw == J_NOPRESS)
            {
                mapa[5][0] = 1; // TITILA EL PLAY
            }
            else if (coord.x > THRESHOLD && coord.sw == J_PRESS)
            {
                mapa[4][0] = 2; // CAMBIA A MENU PRINCIPAL
            }
            if (coord.x < -THRESHOLD && coord.sw == J_NOPRESS)
            {
                mapa[5][0] = 0; // TITLA EL SALIR
            }
            else if (coord.x < -THRESHOLD && coord.sw == J_PRESS)
            {
                mapa[4][0] = 0; // VUELVE AL JUEGO
            }
        }
        if (mapa[4][0] == 2) // MENU PRINCIPAL
        {
            menu_principal_vis();
        }
    }
}

/*joy_init();										   // inicializa el joystick
    disp_init();									   // inicializa el display
    disp_clear();									   // limpia todo el display
    dcoord_t pos = {DISP_MAX_X >> 1, DISP_MAX_Y >> 1}; // pos es la posiciÃ³n actual, empieza en el centro de la matriz
    dcoord_t npos = pos;							   // npos es la prÃ³xima posiciÃ³n
    joyinfo_t coord = {0, 0, J_NOPRESS};			   // coordenadas medidas del joystick
    do
    {
        printf("Joystick: (%4d,%4d)", coord.x, coord.y); // Imprime las coordenadas del joystick
        printf(" | ");
        printf("Display: (%2d,%2d)\n", npos.x, npos.y); // Imprime la posiciÃ³n del LED encendio

        disp_update();		// Actualiza el display con el contenido del buffer
        coord = joy_read(); // Guarda las coordenadas medidas

        // Establece la prÃ³xima posiciÃ³n segÃºn las coordenadas medidas
        if (coord.x > THRESHOLD && npos.x < DISP_MAX_X)
        {
            npos.x++;
        }
        if (coord.x < -THRESHOLD && npos.x > DISP_MIN)
        {
            npos.x--;
        }
        if (coord.y > THRESHOLD && npos.y > DISP_MIN)
        {
            npos.y--;
        }
        if (coord.y < -THRESHOLD && npos.y < DISP_MAX_Y)
        {
            npos.y++;
        }

        disp_write(pos, D_OFF); // apaga la posiciÃ³n vieja en el buffer
        disp_write(npos, D_ON); // enciende la posiciÃ³n nueva en el buffer
        pos = npos;				// actualiza la posiciÃ³n actual

    } while (coord.sw == J_NOPRESS); // termina si se presiona el switch

    // Borro el display al salir
    disp_clear();
    disp_update();
*/