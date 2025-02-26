#include <stdio.h>
#include <iostream>
#include "kbhit.h"
#include "linkLayer.h"


#ifndef _GESTIONCARACTERES_H
#define _GESTIONCARACTERES_H

void enviarCaracter(interface_t *iface, unsigned char c, unsigned char mac_src[], unsigned char mac_dst[], unsigned char tipo[]);

#endif
