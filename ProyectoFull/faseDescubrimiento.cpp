#include "faseDescubrimiento.h"

using namespace std;

void ModoMaestro(int nGrupo, interface_t *iface, unsigned char *mac_dst){
    unsigned char mac_src[6];
    unsigned char mac_broadcast [6]={0xFF, 0xFF, 0xFF, 0xFF,0xFF, 0xFF};
    int grupoI = 48 + nGrupo;
    unsigned char grupoH = static_cast<unsigned char>(grupoI);
    unsigned char type[2]={grupoH,0x01};
    unsigned char *tramaDescubrimiento;
    bool EsclavoEncontrado = false;
    
    
    for(int i = 0; i < 6 ; i++){
        mac_src[i] = iface->MACaddr[i];
    }

    tramaDescubrimiento = BuildHeader(mac_src, mac_broadcast, type);
    SendFrame(iface, tramaDescubrimiento, 0);
    cout << "Esperando respuesta de esclavo..." << endl;

    while(!EsclavoEncontrado){
        apacket_t tramaEsclava = ReceiveFrame(iface);
        if(tramaEsclava.packet != NULL){
            if(tramaEsclava.packet[12] == type[0]){
                if(tramaEsclava.packet[13] == 2){
                    EsclavoEncontrado = true;
                    for (int i =0;i<6;i++){
                        mac_dst[i] = tramaEsclava.packet[i+6];
                    }

                    cout << "Estacion esclava encontrada. La MAC es: ";
                    for(int b = 0; b<6; b++){
                        printf("%02x:", mac_dst[b]);
                    }
                    printf("%02X", mac_dst[6]);
                    printf("\n");

                
                }
            }
        }
    }
}


void ModoEsclavo(int nGrupo, interface_t *iface){
    unsigned char  mac_dst[6];
    bool MaestroEncontrado = false;
    bool mismoG = false;
    int grupoI = 48 + nGrupo;
    unsigned char grupoH = static_cast<unsigned char>(grupoI);
    unsigned char type[2]={grupoH,0x02};
    cout << "Buscando estación maestra..." << endl;

    while(!MaestroEncontrado){
        apacket_t tramaMaestra = ReceiveFrame(iface);
        if(tramaMaestra.packet != NULL){
            if(tramaMaestra.packet[12] == type[0]){
                if(tramaMaestra.packet[13] == 1){
                    MaestroEncontrado = true;
                    for (int i =0;i<6;i++){
                        mac_dst[i] = tramaMaestra.packet[i+6];
                    }
            
                    cout << "Estacion maestra encontrada. La MAC es: " ;
                    for(int b = 0; b<6; b++){
                        printf("%02x:", mac_dst[b]);
                    }
                    printf("%02X", mac_dst[6]);
                    printf("\n");
                    unsigned char *tramaDescubrimiento = BuildHeader(iface->MACaddr, mac_dst, type);
                    SendFrame(iface, tramaDescubrimiento, 0);

                    cout << "Selección de modo" << endl
                    << "\t[F1] Envío de caracteres interactivo" << endl
                    << "\t[ESC] Salir " << endl;
                }
            }   
        }
    }
}


int faseDescubrimiento(int n_grupo, char opt, interface_t *iface, unsigned char *mac_dest){
    if(opt == 1){
        ModoMaestro(n_grupo, iface, mac_dest);
        return 1;
    }

    if(opt == 2){
        ModoEsclavo(n_grupo, iface);
        return 1;
    }
    return 0;
}




/*
modoMaestro(){
type=[48+nºgrupo, 0x01]
buildframe(macBroadcast, macOrigen, type)
sendframe()
while(!Recibido){}
trama = receiveFrame()
SI TRAMA[12] == type[0] && TRAMA[13] ==0x02{
sacarMac()
}
}



modoEsclavo(){
type=[48+nºgrupo, 0x02]
while(!Recibamos){
trama = receiveFRame()
SI TRAMA[12] == type[0] && trama[13] == 0x01 {
sacarMacOrigen()
}
}
buildFrame()
sendFrame()
}
*/