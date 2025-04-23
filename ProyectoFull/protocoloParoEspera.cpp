#include "protocoloParoEspera.h"


using namespace std;

unsigned char* tramaDeEstablecimiento(interface *iface, unsigned char mac_dst[], unsigned char type[], int prot, int num){

    unsigned char camposControl[3];
    camposControl[0] = 'R';
    camposControl[1] = prot;
    camposControl[2] = num;

    unsigned char *tramaControl = BuildFrame(iface->MACaddr, mac_dst, type, camposControl);
    return tramaControl;

}

void faseDescubrimiento(){

}

void faseTransferencia(){

}

void faseLiberacion(){

}

int calculoBCE(){
    
}