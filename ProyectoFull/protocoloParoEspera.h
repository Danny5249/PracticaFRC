#include <stdio.h>
#include <iostream>
#include <fstream>
#include "kbhit.h"
#include "linkLayer.h"


#ifndef _PROTOCOLOPAROESPERA_H
#define _PROTOCOLOPAROESPERA_H


void faseEstablecimiento(interface *iface, int opt, unsigned char mac_dst[], unsigned char type[]);

void faseTransferenciaBCE(interface *iface, int opt, unsigned char mac_dst[], unsigned char type[]);

void tramaEstablecimiento(interface_t *iface, unsigned char mac_dst[], unsigned char type[], unsigned char prot, unsigned char num);

void tramaTransferencia(interface *iface, unsigned char mac_dst[], unsigned char type[], unsigned char prot, unsigned char num, unsigned char datos[], int longitud, unsigned char BCE);

unsigned char calculoBCE(unsigned char cad[]);

unsigned char traduccionTipo(unsigned char prot);


#endif