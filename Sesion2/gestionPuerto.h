#include <stdio.h>
#include <iostream>
#include "linkLayer.h"


#ifndef _GESTIONPUERTO_H
#define _GESTIONPUERTO_H

using namespace std;

void EnviarCaracter(interface iface, unsigned char c, unsigned char mac_src[6], unsigned char mac_dst[6], unsigned char type[2]);

#endif
