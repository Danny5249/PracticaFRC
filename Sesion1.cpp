//============================================================================
// ----------- PRACTICAS DE FUNDAMENTOS DE REDES DE COMUNICACIONES -----------
// ---------------------------- CURSO 2024/25 --------------------------------
// ----------------------------- SESION1.CPP ---------------------------------
//============================================================================


#include <stdio.h>
#include <iostream>
#include "linkLayer.h"




using namespace std;


int main()
{
 interface_t iface;
 pcap_if_t *avail_ifaces=NULL;
 pcap_if_t *pAux = NULL;
 
 int opt = 0;
 int ifaces = 0;
 
 
 printf("\n----------------------------\n");
 printf("------ SESION 1 - FRC ------\n");
 printf("----------------------------\n");
    
 avail_ifaces=GetAvailAdapters();
 
 pAux = avail_ifaces;

 printf("Interfaces disponibles:\n");

 while(pAux->next != nullptr){
    cout<<'['<< ifaces<<']'<< ' ' << pAux->name<<endl;


    ifaces++;
    pAux = pAux->next;
 }
 
 cout<<"Seleccione interfaz: "<<endl;
 cin>> opt;

 pAux = avail_ifaces;
 for(int i=0; i<opt; i++){
    pAux = pAux->next;
 }

 cout<<"Interfaz elegida: "<< pAux->name<<endl;

 setDeviceName(&iface, pAux->name);
 GetMACAdapter(&iface);
 //cout<<"La MAC es: "<<PrintMACAdapter(&iface)<<endl; 

 return 0;
}
