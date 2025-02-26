#include "gestionCaracteres.h"


void enviarCaracter(interface_t *iface, unsigned char c, unsigned char mac_src[], unsigned char mac_dst[], unsigned char protocol[]){

    
    //Reservar Memoria de Datos
    unsigned char *trama;
    unsigned char *caracter = (unsigned char *) malloc(sizeof(c));
    

    //Almacenar Datos
    caracter[0] = c;
    //Construir trama
    trama = BuildFrame(mac_src, mac_dst, protocol, caracter);

    //Envio de datos
    SendFrame(iface, trama, sizeof(c));

    //Liberar Memoria
    free(trama);
    free(caracter);

}

