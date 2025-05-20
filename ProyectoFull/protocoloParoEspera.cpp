#include "protocoloParoEspera.h"


using namespace std;

void tramaEstablecimiento(interface_t *iface, unsigned char mac_dst[], unsigned char type[], unsigned char prot, unsigned char num){

    unsigned char camposControl[3];
    unsigned char traduccion = 0;
    camposControl[0] = 'R';
    camposControl[1] = prot;
    camposControl[2] = num;

    unsigned char *tramaControl = BuildFrame(iface->MACaddr, mac_dst, type, camposControl);
    traduccion = traduccionTipo(prot);
    cout<<"E"<< "   "<< "R"<< "     "<< traduccion<< "      "<< num <<endl;
    SendFrame(iface, tramaControl, sizeof(camposControl));
    free(tramaControl);
}

void tramaTransferencia(interface *iface, unsigned char mac_dst[], unsigned char type[], unsigned char prot, unsigned char num, unsigned char datos[],int longitud, unsigned char BCE){

    unsigned char camposTrama[5 + longitud]; 
    unsigned char traduccion = 0;

    camposTrama[0] = 'R';
    camposTrama[1] = prot;
    camposTrama[2] = num;
    camposTrama[3] = longitud;
    memcpy(camposTrama + 4, datos, longitud);
    camposTrama[longitud + 4] = BCE;

    unsigned char* tramaDatos = BuildFrame(iface->MACaddr, mac_dst, type, camposTrama);

    
    traduccion = traduccionTipo(prot);
    
    cout<<"E"<< "    "<< "R"<< "     "<< traduccion<< "      "<<num << "        "<< BCE<<endl;
    SendFrame(iface, tramaDatos, sizeof(camposTrama));
    //FreeBuffer();
    free(tramaDatos);

}


void faseEstablecimiento(interface *iface, int opt, unsigned char mac_dst[], unsigned char type[]){
    unsigned char traduccion = 0;
    bool rec = false;
    
    if(opt == 1){
        tramaEstablecimiento(iface, mac_dst, type, 05, 0);
        while(!rec){
            apacket_t tramaEsclava = ReceiveFrame(iface);
            if(tramaEsclava.packet != NULL){
                if(tramaEsclava.packet[15] == 06){
                    rec = true;
                    traduccion = traduccionTipo(tramaEsclava.packet[15]);
                    cout<<"R"<< "    "<< "R"<< "     "<< traduccion<< "      "<< 0 <<endl;
                }
            }
        }
    }

    if(opt == 2){
        while(!rec){
            apacket_t tramaMaestra = ReceiveFrame(iface);
            if(tramaMaestra.packet != NULL){
                if(tramaMaestra.packet[15] == 05){
                    rec = true;
                    traduccion = traduccionTipo(tramaMaestra.packet[15]);
                    cout<<"R"<< "    "<< "R"<< "     "<< traduccion<< "      "<< 0 <<endl;
                    tramaEstablecimiento(iface, mac_dst, type, 06, 0);
                }
            }
        }
        
    }

}

void faseTransferenciaBCE(interface *iface, int opt, unsigned char mac_dst[], unsigned char type[]){

    unsigned char traduccion = 0;
    int longitud = 0;
    if(opt == 1){
        ifstream f;
        unsigned char datos[254];
        char cad[255];
        bool finTrama = false;
        bool finTransmision = false;
        bool hayError = false;
        f.open("EProtoc.txt");
        char tecla;
        unsigned char num = 0;
        bool tramaCorrecta = false;

        while(!finTransmision){
            if(f.is_open()){
                while(!f.eof()){
                    if(kbhit()){
                        tecla = getch();
                        if(tecla == 27 && kbhit()){
                            tecla = getch();
                            if(tecla == 'O' && kbhit())
                            tecla = getch();
                            if(tecla == 'S'){
                                hayError = true;
                            }
                        }
                    }
                    f.read(cad, 254);
                    cad[f.gcount()] = '\0';
                   // longitud = f.gcount() - 1;
                    

                    for(int i = 0; !finTrama; i++){
                        if(cad[i] == '\0'){
                            finTrama = true;
                        } else{
                            datos[i] = cad[i];
                        }
                    }
                    finTrama = false;
                    unsigned char BCE = calculoBCE(datos);
                    unsigned char correcto = datos[0];
                    if(hayError){
                        datos[0] = 'ç';                          
                     }
                    tramaTransferencia(iface, mac_dst, type, 02, num, datos, f.gcount(), BCE);

                    while(!tramaCorrecta){
                        apacket_t respuestaEsclava = ReceiveFrame(iface);
                        if(respuestaEsclava.packet != NULL){
                            if(respuestaEsclava.packet[15] == 06){
                                num = !num;
                                tramaCorrecta = true;
                                traduccion = traduccionTipo(respuestaEsclava.packet[15]);
                                cout<<"R"<< "    "<< "R"<< "     "<< traduccion<< "      "<< num <<endl;
                            }
                            else if(respuestaEsclava.packet[15] == 21){
                                traduccion = traduccionTipo(respuestaEsclava.packet[15]);
                                cout<<"R"<< "    "<< "R"<< "     "<< traduccion<< "      "<< num <<endl;
                                datos[0] = correcto;
                                tramaTransferencia(iface, mac_dst, type, 02, num, datos, longitud, BCE);
                            }
                        }
                    }
                    tramaCorrecta = false;

                }
            }
            f.close();
            finTransmision = true;
        }
        tramaEstablecimiento(iface, mac_dst, type, 04, 0);
        bool aceptaFin = false;
        while(!aceptaFin){
            apacket_t respuesta = ReceiveFrame(iface);
            if(respuesta.packet != NULL){
                if(respuesta.packet[15] == 06){
                    traduccion = traduccionTipo(respuesta.packet[15]);
                    cout<<"E"<< "    "<< "R"<< "     "<< traduccion<< "      "<<num <<endl;
                    aceptaFin = true;
                }
            }
        }
       

    }

    else if(opt == 2){
        bool finEsclava = false;
        while(!finEsclava){
            apacket_t tramaMaestra = ReceiveFrame(iface);
            if(tramaMaestra.packet != NULL){
                if(tramaMaestra.packet[15] == 02){ //Comprueba si el paquete recibido es de datos

                    unsigned char datosRecibidos[tramaMaestra.packet[17]]; //Variable que guardará el valor de los datos recibidios

                    for(int i = 18, z = 0; i < tramaMaestra.packet[17];i++ , z++){ //Copiamos a la variable
                        datosRecibidos[z] = tramaMaestra.packet[i];     //NO ESTÁ RECIBIENDO LOS DATOS BIEN
                    }
                    unsigned char BCEReceive = calculoBCE(datosRecibidos); //Calculamos el BCE con los datos recibidos
                    traduccion = traduccionTipo(tramaMaestra.packet[15]);

                    cout<<"R"<< "     "<< "R"<< "     "<< traduccion<< "      "<< tramaMaestra.packet[16] << "        "<< tramaMaestra.packet[18 + tramaMaestra.packet[17]] << "     "<< BCEReceive <<endl;

                    if(BCEReceive != tramaMaestra.packet[tramaMaestra.packet[17] + 18]){
                        tramaEstablecimiento(iface, mac_dst, type, 21, tramaMaestra.packet[16]); //Si el BCE calculado es erroneo, mandamos una trama de fallo
                    } else if(BCEReceive == tramaMaestra.packet[tramaMaestra.packet[17] + 18]){
                        tramaEstablecimiento(iface,mac_dst, type, 06, tramaMaestra.packet[16]); //Si el BCE calculado es correcto, mandamos una trama de confirmacion.
                    }
                } else if(tramaMaestra.packet[15] == 04){
                    finEsclava = true;
                    traduccion = traduccionTipo(tramaMaestra.packet[15]);

                    cout<<"R"<< "      "<< "R"<< "     "<< traduccion << "      "<< 0 <<endl;
                }
            }
        }

        tramaEstablecimiento(iface, mac_dst, type, 06, 0);

    }


}


unsigned char calculoBCE(unsigned char cad[]){
    unsigned char bce = cad[0];

    for(int i = 1; i < sizeof(cad); i++){
        bce = bce ^ cad[i];
    }

    if (bce == 0 || bce == 255){
        bce = 1;
    }
    return bce;
}

unsigned char traduccionTipo(unsigned char num){
    unsigned char traduccion = 0;
    switch  (num){
        case 5:
            traduccion = 'ENQ';
            break;
        case 4:
            traduccion = 'EOT';
            break;
        case 6:
            traduccion = 'ACK';
            break;
        case 21:
            traduccion = 'NACK';
            break;
        case 2:
            traduccion = 'STX';
            break;
        
        default:
            break;
    }

    return traduccion;
}