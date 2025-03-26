#include <stdio.h>
#include <iostream>
#include "kbhit.h"
#include "linkLayer.h"

#ifndef _FASEDESCUBRIMIENTO_H
#define _FASEDESCUBRIMIENTO_H

void ModoMaestro(int nGrupo, interface_t *iface);
void ModoEsclavo(int nGrupo, interface_t *iface);
void EnviarFichero(interface_t *iface, unsigned char *mac_dst, unsigned char *type);

#endif