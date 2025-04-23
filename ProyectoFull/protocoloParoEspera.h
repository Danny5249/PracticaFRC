#include <stdio.h>
#include <iostream>
#include "kbhit.h"
#include "linkLayer.h"


#ifndef _PROTOCOLOPAROESPERA_H
#define _PROTOCOLOPAROESPERA_H


void faseEstablecimiento();
unsigned char* tramaDeEstablecimiento(interface *iface, unsigned char mac_dst[], unsigned char type[], char R, int prot, int num);
void faseTransferencia();
void faseLiberacion();
int calculoBCE();


#endif