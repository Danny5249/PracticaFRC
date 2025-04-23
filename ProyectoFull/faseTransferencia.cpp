#include "faseTransferencia.h"
using namespace std;


void EnviarFichero(interface_t *iface, unsigned char *mac_dst, unsigned char *type){
    ifstream f;
    unsigned char trama_envio[254];
    char cad[255];
    bool fin_trama = false;

    f.open("envio.txt");

    if(f.is_open()){
        while(!f.eof()){                        //Mientras el flujo esté abierto, iremos mandando tramas.
            f.read(cad, 254);
            cad[f.gcount()] = '\0';             //Indicamos el final de una trama.

            for(int i = 0; !fin_trama; i++){
                if(cad[i] == '\0'){
                    fin_trama = true;
                } else{
                    trama_envio[i] = cad[i];  
                }
            }
            fin_trama = false;
            unsigned char *trama = BuildFrame(iface->MACaddr, mac_dst, type, trama_envio); //Construimos la trama
            SendFrame(iface, trama, f.gcount()); //Enviamos la trama. Repetimos hasta que se llegue al final del fichero.
            free(trama);
        }
       
    }
    f.close();

    
}

void faseTransferencia(interface_t *iface, int opt, unsigned char *mac_dst, unsigned char *type){
    if(opt == 1){
        TransferenciaMaestra(iface, mac_dst, type);
    } else if(opt == 2){
        TransferenciaEsclava(iface, mac_dst, type);
    }
}
void TransferenciaMaestra(interface_t *iface, unsigned char *mac_dst, unsigned char *type){
    
    bool esc = false;
    char tecla;
    char caracter;
    cout << "Selección de modo" << endl
    << "\t[F1] Envío de caracteres interactivo" << endl
    << "\t[F2] Envío de un fichero" << endl
    << "\t[ESC] Salir " << endl;
   
    while(!esc){
        if(kbhit()){
            tecla = getch();
            if(tecla == 27 && kbhit()){
                tecla = getch();
                if(tecla == 'O'){
                    if(kbhit()){
                        tecla = getch();
                        switch (tecla)
                        {
                        case 'P':
                        cout << "" << endl;
                        cout<<"Envío de caracteres interactivo. Pulse caracteres a enviar."<<endl;
                        cout<<"Pulse [ESC] para volver."<<endl;

                        while(caracter != 27){
                            RecibirCaracter(iface);
                            if(kbhit()){
                                caracter = getch();
                                if(caracter != 27){
                                    enviarCaracter(iface, caracter, iface->MACaddr, mac_dst, type);
                                }
                            }   
                        }
                        
                        caracter = 0;

                        cout << "" << endl
                            << "Selección de modo" << endl
                            << "\t[F1] Envío de caracteres interactivo" << endl
                            << "\t[F2] Envío de un fichero" << endl
                            << "\t[ESC] Salir " << endl;

                        break;
                        
                        case 'Q':
                        cout<<"Envio de fichero. Se enviará el fichero de prueba."<<endl;
                        EnviarFichero(iface, mac_dst, type);
                        cout<<"Pulse [ESC] para volver"<<endl;

                        while(caracter != 27){
                            if(kbhit()){
                                caracter = getch();
                            }
                        }

                        caracter = 0;

                        cout << "" << endl
                            << "Selección de modo" << endl
                            << "\t[F1] Envío de caracteres interactivo" << endl
                            << "\t[F2] Envío de un fichero" << endl
                            << "\t[ESC] Salir " << endl;

                        break;
                        
                        default:
                            break;
                        }
                    }
                }
            } else if(tecla == 27){
                esc = true;
            } 
            
        }
    }
}

void TransferenciaEsclava(interface_t *iface, unsigned char *mac_dst, unsigned char *type){
    bool esc = false;
    char tecla;
    char caracter;

    cout << "Selección de modo" << endl
    << "\t[F1] Envío de caracteres interactivo" << endl
    << "\t[ESC] Salir " << endl;

    while(!esc){
        RecibirCaracter(iface);
        if(kbhit()){
            tecla = getch();
            if(tecla == 27 && kbhit()){
                tecla = getch();
                if (tecla == 'O'){
                    if(kbhit()){
                        tecla = getch();
                        switch (tecla)
                        {
                        case 'P':
                        cout << "" << endl;
                        cout<<"Envío de caracteres interactivo. Pulse caracteres a enviar."<<endl;
                        cout<<"Pulse [ESC] para volver."<<endl;
                        
                        while(caracter != 27){
                            RecibirCaracter(iface);
                            if(kbhit()){
                                caracter = getch();
                                if(caracter !=27){
                                enviarCaracter(iface, caracter, iface->MACaddr, mac_dst, type);
                                }
                            } 
                        }

                        caracter = 0;

                        cout << "" << endl
                            << "Selección de modo" << endl
                            << "\t[F1] Envío de caracteres interactivo" << endl
                            << "\t[ESC] Salir " << endl;
                           
                            break;
                       
                        
                        default:
                            break;
                        }
                    }
                }
            } else if(tecla == 27){
                esc = true;
            } 
            
        }
    }
    

}