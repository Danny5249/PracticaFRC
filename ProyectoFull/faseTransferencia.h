#include <stdio.h>
#include <iostream>
#include <fstream>
#include "kbhit.h"
#include "linkLayer.h"
#include "gestionCaracteres.h"

#ifndef _FASETRANSFERENCIA_H
#define _FASETRANSFERENCIA_H

void TransferenciaMaestra(interface_t *iface, unsigned char *mac_dst, unsigned char *type);
void TransferenciaEsclava(interface_t *iface, unsigned char *mac_dst, unsigned char *type);
void EnviarFichero(interface_t *iface, unsigned char *mac_dst, unsigned char *type);
void faseTransferencia(interface_t *iface, int opt, unsigned char *mac_dst, unsigned char *type);
#endif