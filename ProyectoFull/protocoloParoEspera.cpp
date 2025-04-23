#include "protocoloParoEspera.h"


using namespace std;


void faseEstablecimiento(){

}

void faseTransferenciaBCE(){

}

void faseLiberacion(){

}

unsigned char calculoBCE(char cad[]){
    unsigned char bce = cad[0];
    for(int i = 1; i < sizeof(cad); i++){
        bce = bce ^ cad[i];
    }

    if (bce == 0 || bce == 0xFF){
        return 1;
    } else {
        return bce;
    }
}