#include <stdio.h>
#include <iostream>
#include "kbhit.h"
#include "linkLayer.h"


#ifndef _PROTOCOLOPAROESPERA_H
#define _PROTOCOLOPAROESPERA_H


void faseEstablecimiento();
void faseTransferenciaBCE();
void faseLiberacion();
unsigned char calculoBCE(unsigned char cad[]);


#endif