#include <stdio.h>
#include <iostream>
#include "kbhit.h"
#include "linkLayer.h"
#include <string>

#ifndef _FASEDESCUBRIMIENTO_H
#define _FASEDESCUBRIMIENTO_H

void ModoMaestro(int nGrupo, interface_t *iface,unsigned char *mac_dst);
void ModoEsclavo(int nGrupo, interface_t *iface);
int faseDescubrimiento(int nGrupo, char opt, interface_t *iface, unsigned char *mac_dst);


#endif