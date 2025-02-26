//============================================================================
// ----------- PRACTICAS DE FUNDAMENTOS DE REDES DE COMUNICACIONES -----------
// ---------------------------- CURSO 2024/25 --------------------------------
// ----------------------------- SESION1.CPP ---------------------------------
//============================================================================
// Daniel Barrantes Pulido y Pedro Fernández Germán, Lab 8

#include <stdio.h>
#include <iostream>
#include "linkLayer.h"
#include "gestionCaracteres.h"




using namespace std;


int main()
{

 unsigned char mac_src[6]={0x00, 0x00, 0x00, 0x00,0x00, 0x00};
 unsigned char mac_dst[6]={0x00, 0x01, 0x02, 0x03,0x04, 0x05};
 unsigned char type[2]={0x30,0x00};
 char car;
 interface_t iface;
 pcap_if_t *avail_ifaces=NULL;
 pcap_if_t *pAux = NULL;
 
 int opt = 0;
 int ifaces = 0;
 unsigned char tecla = 0;
 
 
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
//
 setDeviceName(&iface, pAux->name);
 GetMACAdapter(&iface);
 //
 cout<<"La MAC es: "<<endl; 
 //Se muestra la dirección MAC, pasandola de hexadecimal a binario
   for(int b = 0; b<6; b++){
         printf("%02x:", iface.MACaddr[b]);
    }
   printf("%02X", iface.MACaddr[6]);
   printf("\n");
 //
 
 while(tecla != 27){
   if(kbhit()){

      //cout<<"El caracter enviado es " <<endl;
      tecla = getch();
      enviarCaracter(&iface, tecla, mac_src, mac_dst, type);
   } else{
   }
 }
 return 0;
}
 //PrintMACAdapter(&iface); 
//Pasar mac de hexadecimal a binario    



 