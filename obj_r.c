
// INCLUDES
#include "obj_r.h"

// PROTOTYPES
static void led_flick(dcoord_t coor_shield);

// guardan las coordenadas del led de abajo a la izquierda
dcoord_t shield1 = {1, 4}, shield2 = {5, 4}, shield3 = {9, 4}, shield4 = {13, 4};

/***********************************  GAMER   ***********************************/

void gamer_vis(dcoord_t ubi){
    int i;
    dcoord_t ubi_inicial = ubi;
    for( i = ubi.x ; i < ubi.x + 3 ; i++){
        ubi.x = i;
        if( i == ubi_inicial.x + 1)
        {
            disp_write(ubi, D_ON);
            ubi.y ++;
            disp_write(ubi, D_ON);
            ubi.y --;
        }
        else{
            disp_write(ubi, D_ON);
        }
        
    }
    disp_update();
}

void gamer_shot(void)

/***********************************  ALIENS   ***********************************/
void aliens_vis(dcoord_t coor_inicial){
    int i, j;
    dcoord_t coor = coor_inicial;
    for(j = coor_inicial.y; j < coor_inicial.y + 4; j++)
    {
        if((j%2) == 0)
        {
            for(i = coor_inicial.x; i < coor_inicial.x + 13; i++)
            {
                disp_write(coor, D_ON);
                ++coor.x;
                disp_write(coor, D_OFF);

            }
        } else{
            for(i = coor_inicial.x + 1; i < coor_inicial.x + 14; i++)
            {
                disp_write(coor, D_ON);
                ++coor.x;
                disp_write(coor, D_OFF);

            }
        }
        
    }
    disp_update();

}


/*******************************  THE FINAL BOSS  *********************************/

void final_boss_vis(dcoord_t ubi){
    int i;
    dcoord_t ubi_inicial = ubi;
    for( i = ubi.x ; i < ubi.x + 3 ; i++){
        ubi.x = i;
        if( i == ubi_inicial.x + 1)
        {
            disp_write(ubi, D_ON);
            ubi.y --;
            disp_write(ubi, D_ON);
            ubi.y ++;
        }
        else{
            disp_write(ubi, D_ON);
        }
        
    }
    disp_update();
}

/***********************************  LIVES   ***********************************/

void lives_vis(int cant)
{
    //coordenadas de la visualizacion de las vidas
    dcoord_t first_life = {1, 0}, second_life = {2, 0}, third_life = {3, 0};
    switch (cant)
    {
    case 0: //CASO 0 VIDAS: BORRA LA ULTIMA VIDA (FALTA LLAMAR FUNCION DE GAME OVER)
        disp_write(first_life, D_OFF);
        break;
    case 1: //CASO 1 VIDAS: BORRA LA SEGUNDA VIDA
        disp_write(second_life, D_OFF);
        disp_update();
        break;
    case 2:
        disp_write(third_life, D_OFF);
        disp_update();
        break;
    default:
        disp_write(third_life, D_ON);
        disp_write(second_life, D_ON);
        disp_write(first_life, D_ON);
        disp_update();
        break;
    }
}

/***********************************  SHIELDS  ***********************************/

void shields_vis(dcoord_t coor)
{
    disp_write(coor, D_ON); // prendo led de abajo a la izq
    coor.y++;
    disp_write(coor, D_ON); // prendo led de arriba a la izq
    coor.x++;
    disp_write(coor, D_ON); // prendo led de arriba a la der
    coor.y--;
    disp_write(coor, D_ON); // prendo led de abajo a la der
    disp_update();
}

void shields_life(int life_of_shield, dcoord_t coor_of_shield)
{
    // primera colision -> parpadea el led
    // segunda colision -> se apaga (2 vidas por cada led)
    if (life_of_shield == 1)
    { 
       led_flick(coor_of_shield);
    }
    else{
        disp_write(coor_of_shield, D_OFF);
        disp_update();
    }
    
}

/***********************************  GAME OVER  ***********************************/

void game_over(void){
    int i, j;
    disp_clear();
    dcoord_t coor;
    //BOORO TODO
    for( i = 0 ; i < 16 ; i++ ){
        coor.x = i;
        for( j = 0 ; j < 16 ; j++ ){
            coor.y = j;
            disp_write(coor, D_OFF);
        }
    }
    disp_update();

    //CARITA TRISTE
    //ojo izq
    for( i = 9 ; i <= 11 ; i++ ){
        coor.y = i;
        for( j = 5 ; j <= 6 ; j++ ){
            coor.x = j;
            disp_write(coor, D_ON);
        }
    }
    //ojo der
    for( i = 9 ; i <= 11 ; i++ ){
        coor.y = i;
        for( j = 9 ; j <= 10 ; j++ ){
            coor.x = j;
            disp_write(coor, D_ON);
        }
    }
    //boca
    for ( i = 4; i <= 6 ; i++)
    {
        coor.x = i;
        for ( j = 3; j <= 5; j++)
        {
            coor.y = j;
            disp_write(coor, D_ON);
        }
        
    }
    for( i = 7 ; i <= 8 ; i++ ){
        coor.x = i;
        disp_write(coor, D_ON);
    }
    
    for ( i = 9; i <= 11 ; i++)
    {
        coor.x = i;
        for ( j = 5; j >= 3; j--)
        {
            coor.y = j;
            disp_write(coor, D_ON);
        }
        
    }
    disp_update();

}

/***********************************  AUX -> ARCHIVO NUEVO  ***********************************/

// FUNCION LED_FLICK
// Hace titilar al LED de la coordenada indicada (el grado indica que tan rapido titila)
static void led_flick(dcoord_t coor_)
{

    int i;
    int tiempo_espera = DELAY / 100;
    
    for(i = 0; i < MAX_ITERATIONS; i++)
    {
        //se enciende el led
        disp_write(coor_, D_ON);
        disp_update();

        // tiempo que esta apagado 
        usleep(tiempo_espera);

        // apaga el LED en la posición especificada
        disp_write(coor_, D_OFF);
        disp_update();

    }

}