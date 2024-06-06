/**
 * @file main.c
 * @author Jose Luis Cruz (jlcruz@ipn.mx)
 * @brief 
 * @version 0.1
 * @date 2024-05-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "miniwin.h"
#include <stdlib.h>
#include <time.h>
#define GRAVEDAD 1
#define VELOCIDADH 5
#define REBOTE -30

int main()
{
    MWImage pato1, pato2, fondo;
    int t;
    bool fs = false;
    float x = 100, y = 100;
    //Agregar patos
    int cx1 = 100, cy1 = 100, salto1 = 0, direccion1 = 1, vertical1 = 0;
    int cx2 = 200, cy2 = 50, salto2 = 0, direccion2 = 1, vertical2 = 0;
    
    int puntos = 0;
    char puntos_str[10];

    pato1 = creaImagenBMP("pat.bmp");
    pato2 = creaImagenBMP("pat.bmp");
    fondo = creaImagenBMP("fondo.bmp");

    titulo("Duck Hunt");
    ventana(800, 600);

    srand(time(NULL));

    t = tecla();

    while (t != ESCAPE)
    {
        vertical1 += GRAVEDAD;
        cy1 += vertical1;
        cx1 += direccion1 * VELOCIDADH;

        vertical2 += GRAVEDAD;
        cy2 += vertical2;
        cx2 += direccion2 * VELOCIDADH;

        if (cx1 <= 0 || cx1 + 50 >= vancho()) {
            direccion1 *= -1;
        }
        if (cx2 <= 0 || cx2 + 50 >= vancho()) {
            direccion2 *= -1;
        }

        if (cy1 + 50 >= valto()) {
            cy1 = valto() - 50;
            vertical1 = REBOTE;
        }
        if (cy2 + 50 >= valto()) {
            cy2 = valto() - 50;
            vertical2 = REBOTE;
        }

        borra();
        t = teclaDown();

        if (t == RETURN) {
            fs = !fs;
            fullscreen(fs);
        }

        raton(&x, &y);

        fondo.pos_x = 0;
        fondo.pos_y = 0;
        fondo.ancho = vancho();
        fondo.alto = valto();
        muestraImagen(&fondo);

        color(BLANCO);
        linea(x - 10, y, x + 10, y);
        linea(x, y - 10, x, y + 10);

        sprintf(puntos_str, "%d", puntos);
        texto(10, valto() - 40, "Puntos: ");
        texto(150, valto() - 40, puntos_str);

        color(ROJO);
        texto(5, 5, "Presione ESC para salir.");

        //Posicion patos
        pato1.pos_x = cx1;
        pato1.pos_y = cy1;
        pato1.ancho = 50;
        pato1.alto = 50;
        muestraImagen(&pato1);

        pato2.pos_x = cx2;
        pato2.pos_y = cy2;
        pato2.ancho = 50;
        pato2.alto = 50;
        muestraImagen(&pato2);

        refresca();

        if (raton_boton_izq()) {
            if ((x >= cx1 && x <= cx1 + 50 && y >= cy1 && y <= cy1 + 50) ||
                (x >= cx2 && x <= cx2 + 50 && y >= cy2 && y <= cy2 + 50) ) {
                puntos++;
                if (x >= cx1 && x <= cx1 + 50 && y >= cy1 && y <= cy1 + 50) {
                    cx1 = rand() % (vancho() - 50);
                    cy1 = rand() % (valto() - 50);
                    vertical1 = 0;
                }
                if (x >= cx2 && x <= cx2 + 50 && y >= cy2 && y <= cy2 + 50) {
                    cx2 = rand() % (vancho() - 50);
                    cy2 = rand() % (valto() - 50);
                    vertical2 = 0;
                }
            }
        }

        Sleep(50);
    }

    cierra();

    return 0;
}