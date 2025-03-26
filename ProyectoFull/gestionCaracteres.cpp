#include "gestionCaracteres.h"


using namespace std;


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

char RecibirCaracter(interface *iface){
    apacket_t tRecibida;
    tRecibida = ReceiveFrame(iface);
    //cout<<tRecibida.packet[14]<<endl;
    unsigned char datosTrama[255];
    if(tRecibida.packet != nullptr && tRecibida.packet[14] > 0){
        int i = 14;
        int z = 0;
        
        while(tRecibida.header.len > i){
            datosTrama[z] = tRecibida.packet[i];
            i++;
            z++;
        }
        cout<< datosTrama <<endl;
        cout<< "Número de carácteres recibidos:" << tRecibida.header.len - 14 << endl;
        
    }
    else{
        return 0;
    }
    
    return 0;
}



