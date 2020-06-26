#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "gotoxy.h"
#include <stdbool.h>
#include "time.h"
#include <time.h>


#define DIM_CLI 10000
#define ESC 27
#define AR_CLIENTE "clientes.dat"
#define AR_CONSUMO "consumo.dat"

typedef struct
{
    int  id; /// campo único y autoincremental
    int nroCliente;
    char nombre[30];
    char apellido[30];
    int dni;
    char email[35];
    char domicilio[45];
    int movil;
    int baja; /// 0 si está activo - 1 si está eliminado
} stCliente;

typedef struct
{
    int id;  /// campo único y autoincremental
    int nroConsumo; /// Se agrega este dato para que el cliente no sepa el ID y no intervenga sobre el mismo
    int idCliente;
    int anio;
    int mes; /// 1 a 12
    int dia; /// 1 a … dependiendo del mes
    int datosConsumidos;  /// expresados en mb.
    int baja; /// 0 si está activo - 1 si está eliminado
} stConsumos;

//******** PROTOTIPADO DE ACCESORIOS
void printtest();
void mensaje();
void mensajeDestello(char mensaje [1000]);
void mensajeConsultas();
void mensajeListadoConsumo();
void mensajeModificaciones();
void intro();
void watermark ();

//******** PROTOTIPADO DE ERRORES
void mensajeEmailError (int dato);


//******** PROTITPADO DE VALIDACION
int validaEmail(char email[]);

//******** PRTOTIPADO DE MENU
void menuppal ();
void submenuAltaConsumo ();
void submenuCli ();
void submenuConsu();
void submenuConsultasCli ();
void submenuModificaCli ();
void submenuMuestra();
void submenuMuestraConsumos();
void submenuModificacionConsu();
void submenuMuestraConsumosenMb();
void submenuAltaCliente();

//******** PROTOTIPADO DE FUNCIONES DE CARGAS
stCliente cargaUnCliente();
void cargaClienteArchivo ();
void cargaClienteRandomArchivo ();
stCliente cargoClientesRandom();
void cargaClienteRandomArch(int cantidad);

//******** PROTOTIPADO DE MUESTRA
void muestraUnCliente(stCliente c);/// modificar para gotoxy;
void muestraClienteArchivo();
void muestraClienteArchivoActivo();
void muestraClienteArchivoBaja();
int arch2ArrayClienteArchivoActivo(stCliente a[],int v);
int arch2ArrayClienteArchivoBaja(stCliente a[],int v);
int arch2ArrayClienteArchivo(stCliente a[], int v);
void muestraClientesArreglo(stCliente a[],int v);
int buscaPosMenorId(stCliente a[],int v, int c);
void ordenaSeleccionId(stCliente a[],int v);
int buscaPosMenorNombre(stCliente a[],int v, int c);
void ordenaSeleccionNombre(stCliente a[],int v);

//******** PROTOTIPADO PERSISTENCIA EN ARCHIVO
void guardaClienteArchivo (stCliente c);

//******** PROTOTIPADO FUNCIONES COMPLEMENTARIAS DE ARCHIVO
int buscaUltimoId();  /// BUSCA EL ULTIMO ID CARGADO EN EL ARCHIVO.
int buscaUltimoNroCliente();

//******** PROTOTIPADO FUNCIONES VALIDACION
int validarNumero(char numero[]);
int validaCliente (int nroCli);


//******** PROTOTIPADO FUNCIONES BUSQUEDA
stCliente buscaUnClienteApellidoArchivo(char apellido[]);
stCliente buscaUnClienteNombreArchivo(char nombre[]);
stCliente buscaUnClienteDniArchivo(int dni);
stCliente buscaUnClienteEmailArchivo(char email[]);
stCliente buscaUnClienteDomicilioArchivo(char domicilio[]);
stCliente buscaUnClienteNroClienteArchivo(int nroCli);
stCliente buscaUnClienteMovilArchivo(char movil[]);
stCliente buscaUnClienteIdArchivo(int id);

//******** PROTOTIPADO FUNCIONES DE MODIFICACION
void modificaClienteNroCliente(int id, int nroCli); /// Funcion verificar si la vamos a usar para que solo el Admin pueda administrar este campo..
void modificaClienteNombre(int nroCli,char nombre[]);
void modificaClienteApellido(int nroCli,char apellido[]);
void modificaClienteDni(int nroCli, int dni);
void modificaClienteEmail(int nroCli, char email [ ]);
void modificaClienteDomicilio(int nroCli, char domicilio [ ]);
void modificaClienteMovil(int nroCli, int movil );
void modificaBajaCliente(int baja);

//******** PROTOTIPADO FUNCIONES CARGA CLIENTE ALEATORIO
int randomRango(int min, int max);
int getNroMatricula();
void getNombre(char n[]);
void getApellido(char a[]);
int getDNI();
int getMovil();
void getCalle(char c[]);
void getEmail(char nombre[],char apellido[],char email[]);
void getNomEmail(char ne[]);
stCliente cargoClientesRandom();
int cargaClientesAleatorios( stCliente a[],int v,int dim,int clientesDeseados);
void Array2Archivo(stCliente a[],int v);

//******** PROTOTIPADO FUNCIONES CARGA CONSUMO
stConsumos cargaUnConsumo();
void cargaConsumoArchivo (int idCliente);

//******** PROTOTIPADO FUNCIONES MUESTRA CONSUMO
void muestraUnConusmo(stConsumos consu);
void muestraConsumoArchivo();
void muestraConsumosArreglo(stConsumos a[],int v,int id);


//******** PROTOTIPADO FUNCIONES ARCHIVO A ARREGLO CONSUMO
int arch2ArrayConsumoArchivo(stConsumos a[], int v, int id);
int arch2ArrayConsumoArchivoActivo(stConsumos a[],int v, int id);
int arch2ArrayConsumoArchivoBaja(stConsumos a[],int v, int id);


//******** PROTOTIPADO FUNCIONES ORDENAMIENTO X SELECCION CONSUMO
int buscaPosMenorIdConsumo(stConsumos a[],int v, int c);
void ordenaSeleccionIdConsumo(stConsumos a[],int v);


//******** PROTOTIPADO FUNCIONES VARIAS CONSUMO
stConsumos fecha ();
void guardaConsumoEnArchivo (stConsumos consu);
int buscaUltimoNroConsumo();


//******** PROTOTIPADO FUNCIONES DE MODIFICACION CONSUMOS
void modificaBajaConsumo(int baja);
void modificaFechaCOnsumo(int nroConsumo, int anio, int mes, int dia);
void modificaConsumosMB(int nroConsumo, int nuevoConsumo);


//******** PROTOTIPADO FUNCIONES CONSULTA CONSUMDOS
int archivoaMatrizConsumo (int dia,int mes,stConsumos consu[dia][mes],int cuenta[],int vCuenta);
void muestraTotalConsumos (int dias,int mes,stConsumos consu[dias][mes],int cuenta[],int vCuenta);
void muestraConsumoxMes (int dias,int mes,stConsumos consu[dias][mes],int cuenta[],int vCuenta);
int datosConsumidosTotal (int dia, int mes, stConsumos mConsumos [dia][mes],int vConsumidos,int id);

//******** PROTOTIPADO FUNCIONES DATOS CONSUMIDOS
int arch2ArrayConsumoMes(stConsumos a[], int v, int mes);
int arch2ArrayConsumoDiario(stConsumos a[], int v, int mes,  int dia );
int datosConsumidosMensual(int mes, int id );
int datosConsumidosDiarios(int mes,int dia,int id );

//******** PROTOTIPADO FUNCIONES CONSUMOS RANDOM
int getDatosConsumidos();
stConsumos cargaConsumoRandom(int id);
void cargaConsumoRandomArch(int id,int cantidad);




int main()
{
    srand(time(NULL));
    stCliente c,consulta,modifica;
    stConsumos consumo;


    ///****  varibles de los switch *****///
    int opcionPpal=0;
    int opcionCli=0;
    int opcionConsu=0;
    int opcionAlta=0;





    ///***   Varibles usadas en los llamados de las funciones   ***///
    int opcionConsultaCli=0;
    int opcionModificaCli=0;
    int opcionMuestraCli=0;
    gotoxy(20,10);
    printf("Process returned 1 (20x1)   execution time : 0.783 s [ you Compueter is infected ] ");
    Sleep(3500);

    intro();      ///Intro al trabajo
    printtest(); /// MENSAJE DE INICIO
    Sleep(1500); /// el tiempo que demora el mensaje en pantalla
    int nroConsulta;
    int cantidadRandom=0;

    ///*** Variables usadas para las funciones de consultas.
    int  dniConsu;
    char nombreConsu[30];
    char apellidoConsu[30];
    char emailConsu[45];
    char domicilioConsu[45];
    char movilConsu[45];

    ///*** Variables usadas para las funciones de modificacion
    int idModifica;
    int nroModifica,dniModifica;
    char nombreModifica[30];
    char apellidoModifica[30];
    char emailModifica[45];
    char domicilioModifica[45];
    int movilModifica=0;
    int varEmail=0; /// Para tomar lo que retorna la funcion de valida email.

    ///*** Variable usadas para funciones de muestra
    stCliente cliMuestra[DIM_CLI];
    int vCliMuestra=0;

    ///*** Variables de consumidor
    stConsumos muestraConsu[100];
    int vConsu=0;
    int CliDeseados;

    ///***Variable para menu de consumos
    int opcionIngresoCOnsu=1;
    int opcionMuestraConsu=0;
    int opcionSubMenuModifica=0;
    int opcionMuestraConsuenMB=0;

    ///***Variables de consumos
    stConsumos mConsumos[32][13];
    stConsumos aConsumos[13];
    int vMConsu=0;
    int diaConsumido=0;
    int mesConsumido=0;
    int vConsumidos =0;
    int datosMensuales=0;
    int datosDiarios=0;
    int cantConsuAle=0;
    int opcionCargaRandom=0;
    int qwe=121;


    do
    {
        color(7);
        system("cls");
        watermark ();
        menuppal();
        color(9);
        printf("Opcion: ");
        color(7);
        scanf("%d",&opcionPpal);
        system("cls");


        switch(opcionPpal)
        {
        case 1:
            do
            {
                system("cls");
                submenuCli ();
                color(9);
                printf("Opcion: ");
                color(7);
                scanf("%d",&opcionCli);
                system("cls");


                switch(opcionCli)
                {



                case 1:

                    do
                    {
                        system("cls");
                        submenuAltaCliente();
                        color(9);
                        printf("Opcion: ");
                        color(7);
                        scanf("%d",&opcionAlta);
                        system("cls");


                        switch(opcionAlta)
                        {
                        case 1:
                            cargaClienteArchivo();
                            break;

                        case 2:
                            gotoxy(35,3);
                            color(63);
                            printf("Sistema de Alta de Clientes...");
                            color(7);
                            gotoxy(15,5);
                            printf("Ingrese la Cantidad de Clientes Aleatorios a Cargar en el Sistema: ");
                            scanf("%d",&cantidadRandom);
                            cargaClienteRandomArch(cantidadRandom);
                            mensaje();

                            break;
                        }

                    }
                    while(opcionAlta!=0);
                    // system("pause");


                    break;

                case 2:
                    color(63);
                    gotoxy(40,2);
                    printf("Menu Baja Cliente ");
                    color(7);
                    gotoxy(20,4);
                    printf("Ingrese el Nro de Cliente ");
                    scanf("%d",&nroConsulta);
                    modificaBajaCliente(nroConsulta);


                    break;


                case 3:
                    gotoxy(40,2);
                    color(63);
                    printf("Submenu de Modificacion");
                    color(7);
                    gotoxy(10,4);
                    printf("Ingrese el Nro de cliente que desee modificar: ");///usamos id
                    scanf("%d",&idModifica);
                    modifica=buscaUnClienteNroClienteArchivo(idModifica);
                    if(modifica.id!=-1)
                    {
                        do
                        {
                            system("cls");
                            submenuModificaCli();
                            color(9);
                            printf("Opcion: ");
                            color(7);
                            scanf("%d",&opcionModificaCli);
                            system("cls");

                            switch(opcionModificaCli)
                            {
                            case 1:
                                mensajeModificaciones();
                                gotoxy(10,8);
                                printf("El actual Nombre es %s",modifica.nombre);
                                gotoxy(10,9);
                                printf("Ingrese el nuevo Nombre :");
                                fflush(stdin);
                                gets(nombreModifica);
                                modificaClienteNombre(idModifica,nombreModifica);



                                break;

                            case 2:
                                mensajeModificaciones();
                                gotoxy(10,8);
                                printf("El actual Apellido es %s",modifica.apellido);
                                gotoxy(10,9);
                                printf("Ingrese el nuevo Apellido :");
                                fflush(stdin);
                                gets(apellidoModifica);
                                modificaClienteApellido(idModifica,apellidoModifica);



                                break;

                            case 3:
                                mensajeModificaciones();
                                gotoxy(10,8);
                                printf("El actual Dni es %d",modifica.dni);
                                gotoxy(10,9);
                                printf("Ingrese el nuevo Dni :",modifica.dni);
                                scanf("%d",&dniModifica);
                                modificaClienteDni(idModifica,dniModifica);



                                break;

                            case 4:

                                while(varEmail==0) /// Ciclo que lo usamos para que ingrese un email valido al modificar el campo de email.
                                {
                                    mensajeModificaciones();
                                    system("cls");
                                    gotoxy(10,8);
                                    printf("El actual Email es %s",modifica.email);
                                    gotoxy(10,9);
                                    printf("Ingrese el nuevo Email :");
                                    fflush(stdin);
                                    gets(emailModifica);
                                    varEmail= validaEmail(emailModifica);
                                    mensajeEmailError(varEmail);
                                    system("cls");
                                }
                                modificaClienteEmail(idModifica,emailModifica);



                                break;

                            case 5:
                                mensajeModificaciones();
                                gotoxy(10,8);
                                printf("El actual Domicilio es %s",modifica.domicilio);
                                gotoxy(10,9);
                                printf("Ingrese el nuevo Domicilio :");
                                fflush(stdin);
                                gets(domicilioModifica);
                                modificaClienteDomicilio(idModifica,domicilioModifica);



                                break;

                            case 6:
                                mensajeModificaciones();
                                gotoxy(10,8);
                                printf("El actual Movil es %d",modifica.movil);
                                gotoxy(10,9);
                                printf("Ingrese el nuevo Movil :");
                                fflush(stdin);
                                scanf("%d",movilModifica);
                                modificaClienteMovil(idModifica,movilModifica);


                                break;



                            }



                        }
                        while(opcionModificaCli!=0);
                    }
                    else
                    {
                        mensajeDestello("No se encuentra el Nro de Cliente\n");
                    }
                    system("pause");
                    break;


                case 4:
                    do
                    {
                        system("cls");
                        submenuConsultasCli();
                        color(9);
                        printf("Opcion: ");
                        color(7);
                        scanf("%d",&opcionConsultaCli);
                        system("cls");
                        mensajeConsultas();
                        switch(opcionConsultaCli)
                        {
                        case 1:

                            gotoxy(10,9);
                            printf("Ingrese el nro de cliente :");
                            scanf("%d",&nroConsulta);
                            consulta=buscaUnClienteNroClienteArchivo(nroConsulta);
                            if(consulta.id!=-1)
                            {

                                muestraUnCliente(consulta);
                            }
                            else
                            {
                                printf("No se encuentra un cliente con el numero de cliente %d \n",nroConsulta);
                            }
                            system("pause");
                            break;

                        case 2:
                            gotoxy(10,9);
                            printf("Ingrese el nombre de cliente :");
                            fflush(stdin);
                            gets(nombreConsu);
                            consulta=buscaUnClienteNombreArchivo(nombreConsu);
                            if(consulta.id!=-1)
                            {
                                muestraUnCliente(consulta);
                            }
                            else
                            {
                                printf("No se encuentra un cliente con el nombre %s \n",nombreConsu);
                            }
                            system("pause");
                            break;

                        case 3:
                            gotoxy(10,9);
                            printf("Ingrese el apellido de cliente :");
                            fflush(stdin);
                            gets(apellidoConsu);
                            consulta=buscaUnClienteApellidoArchivo(apellidoConsu);
                            if(consulta.id!=-1)
                            {
                                muestraUnCliente(consulta);
                            }
                            else
                            {
                                printf("No se encuentra un cliente con el apellido %s \n",apellidoConsu);
                            }
                            system("pause");
                            break;

                        case 4:
                            gotoxy(10,9);
                            printf("Ingrese el dni de cliente :");
                            scanf("%d",&dniConsu);
                            consulta=buscaUnClienteDniArchivo(dniConsu);
                            if(consulta.id!=-1)
                            {
                                muestraUnCliente(consulta);
                            }
                            else
                            {
                                printf("No se encuentra un cliente con el dni  %d \n",dniConsu);
                            }
                            system("pause");
                            break;

                        case 5:
                            gotoxy(10,9);
                            printf("Ingrese el email de cliente :");
                            fflush(stdin);
                            gets(emailConsu);
                            consulta=buscaUnClienteEmailArchivo(emailConsu);
                            if(consulta.id!=-1)
                            {
                                muestraUnCliente(consulta);
                            }
                            else
                            {
                                printf("No se encuentra un cliente con el email %s \n",emailConsu);
                            }
                            system("pause");
                            break;

                        case 6:
                            gotoxy(10,9);
                            printf("Ingrese el el domicilio de cliente :");
                            fflush(stdin);
                            gets(domicilioConsu);
                            consulta=buscaUnClienteDomicilioArchivo(domicilioConsu);
                            if(consulta.id!=-1)
                            {
                                muestraUnCliente(consulta);
                            }
                            else
                            {
                                printf("No se encuentra un cliente con el domicilio %s \n",domicilioConsu);
                            }
                            system("pause");
                            break;

                        case 7:
                            gotoxy(10,9);
                            printf("Ingrese el movil de cliente :");
                            fflush(stdin);
                            gets(movilConsu);
                            consulta=buscaUnClienteMovilArchivo(movilConsu);
                            if(consulta.id!=-1)
                            {
                                muestraUnCliente(consulta);
                            }
                            else
                            {
                                printf("No se encuentra un cliente con el movil %s \n",movilConsu);
                            }
                            system("pause");
                            break;
                        }



                    }
                    while(opcionConsultaCli!=0);
                    break;


                case 5:
                    do
                    {
                        system("cls");
                        submenuMuestra();
                        color(9);
                        printf("Opcion: ");
                        color(7);
                        scanf("%d",&opcionMuestraCli);
                        system("cls");
                        vCliMuestra=0; /// validos clientes muestra
                        switch(opcionMuestraCli)
                        {
                        case 1:
                            color(63);
                            gotoxy(40,2);
                            printf("Listado de Clientes ");
                            color(7);
                            gotoxy(40,4);
                            vCliMuestra = arch2ArrayClienteArchivo(cliMuestra,vCliMuestra);
                            ordenaSeleccionNombre(cliMuestra,vCliMuestra);
                            muestraClientesArreglo(cliMuestra,vCliMuestra);

                            system("pause");
                            break;

                        case 2:
                            color(63);
                            gotoxy(40,2);
                            printf("Listado de Clientes Activos ");
                            color(7);
                            gotoxy(40,4);
                            vCliMuestra= arch2ArrayClienteArchivoActivo(cliMuestra,vCliMuestra);
                            ordenaSeleccionNombre(cliMuestra,vCliMuestra);
                            muestraClientesArreglo(cliMuestra,vCliMuestra);

                            system("pause");
                            break;

                        case 3:
                            color(63);
                            gotoxy(40,2);
                            printf("Listado de Clientes de Baja ");
                            color(7);
                            gotoxy(40,4);
                            vCliMuestra=arch2ArrayClienteArchivoBaja(cliMuestra,vCliMuestra);
                            if(vCliMuestra==0)
                            {
                                mensajeDestello("Sin clientes Inactivos...");
                            }
                            else
                            {
                                ordenaSeleccionNombre(cliMuestra,vCliMuestra);
                                muestraClientesArreglo(cliMuestra,vCliMuestra);
                                system("pause");
                            }

                            break;


                        }



                    }
                    while(opcionMuestraCli!=0);

                    break;

                }


            }
            while(opcionCli!=0);
            break;

        case 2:
            color(63);
            gotoxy(38,3);
            printf("Sistema de Ingreso a Consumos");
            color(7);

            while(opcionIngresoCOnsu != 0)
            {

                gotoxy(10,6);
                printf("Ingrese el Nro de Cliente: ");
                scanf("%d",&c.nroCliente);
                c=buscaUnClienteNroClienteArchivo(c.nroCliente);
                if(c.baja==1) /// Verificamos que el cliente se encuentre activo para poder realizar consumos o acceder a cualquier tipo de datos relacionados con ellos
                {
                    printf("\nCliente Inactivo, Activelo e ingrese Nuevamente");
                    Sleep(2000);
                    gotoxy(37,6);
                    printf("                                     ");
                    gotoxy(0,8);
                    printf("                                                    ");


                }
                else
                {
                    gotoxy(10,8);
                    mensaje();
                    gotoxy(20,7);
                    muestraUnCliente(c);
                    gotoxy(2,20);
                    printf("[0] Correcto - [1] Incorrecto");
                    gotoxy(2,21);
                    printf("Opcion ");
                    scanf("%d",&opcionIngresoCOnsu);
                    system("cls");
                }

            }
            opcionIngresoCOnsu=1; /// Para que cada vez que salga y vuelva a entra Pida nuevamente el nro de cliente


            do
            {
                system("cls");
                submenuConsu();
                color(9);
                printf("Opcion: ");
                color(7);
                scanf("%d",&opcionConsu);
                system("cls");


                switch(opcionConsu)
                {



                case 1:


                    do
                    {
                        system("cls");
                        gotoxy(35,3);
                        color(63);
                        printf("SISTEMA DE ALTA CONSUMOS");
                        color(7);
                        submenuAltaConsumo();
                        color(9);
                        printf("Opcion: ");
                        color(7);
                        scanf("%d",&opcionCargaRandom);
                        system("cls");
                        switch(opcionCargaRandom)
                        {
                        case 1:
                            cargaConsumoArchivo(c.id);
                            break;

                        case 2:
                            gotoxy(35,3);
                            color(63);
                            printf("Sistema de Carga RANDOM");
                            color(7);
                            gotoxy(30,6);
                            printf("INTRODUZCA CANTIDAD DE DATOS: ");
                            scanf("%d",&cantConsuAle);
                            cargaConsumoRandomArch(c.id,cantConsuAle);
                            mensaje();

                            break;
                        }

                    }
                    while(opcionCargaRandom!=0);


                    break;

                case 2:
                    vConsu=arch2ArrayConsumoArchivoActivo(muestraConsu,vConsu,c.id);
                    muestraConsumosArreglo(muestraConsu,vConsu,c.id);

                    color(63);
                    printf("Ingrese el Nro de Consumo a Eliminar: ");
                    color(7);
                    scanf("%d",&consumo.nroConsumo);
                    system("cls");
                    modificaBajaConsumo(consumo.nroConsumo);
                    break;


                case 3:

                    do
                    {
                        system("cls");
                        submenuModificacionConsu();
                        color(9);
                        printf("Opcion: ");
                        color(7);
                        scanf("%d",&opcionSubMenuModifica);
                        system("cls");
                        switch(opcionSubMenuModifica)
                        {
                        case 1:

                            vConsu=arch2ArrayConsumoArchivoActivo(muestraConsu,vConsu,c.id);
                            muestraConsumosArreglo(muestraConsu,vConsu,c.id);
                            color(63);
                            printf("Ingrese el Nro de Consumo a Modificar la Fecha: ");
                            color(7);
                            scanf("%d",&consumo.nroConsumo);
                            system("cls");
                            color(63);
                            gotoxy(40,2);
                            printf("Sistema de modificacion de Fecha");
                            color(7);
                            modificaFechaCOnsumo(consumo.nroConsumo,consumo.anio,consumo.mes,consumo.dia);
                            break;


                        case 2:
                            vConsu=arch2ArrayConsumoArchivoActivo(muestraConsu,vConsu,c.id);
                            muestraConsumosArreglo(muestraConsu,vConsu,c.id);
                            color(63);
                            printf("Ingrese el Nro de Consumo a Modificar los MB: ");
                            color(7);
                            scanf("%d",&consumo.nroConsumo);
                            printf("\n\nIngrese los nuevos Mb:");
                            scanf("%d",&consumo.datosConsumidos);
                            modificaConsumosMB(consumo.nroConsumo,consumo.datosConsumidos);

                            break;
                        }




                    }
                    while(opcionSubMenuModifica !=0);

                    break;


                case 4:

                    do

                    {
                        system("cls");
                        submenuMuestraConsumosenMb();
                        color(9);
                        printf("Opcion: ");
                        color(7);
                        scanf("%d",&opcionMuestraConsuenMB);
                        system("cls");
                        vConsu=0;
                        switch(opcionMuestraConsuenMB)
                        {
                        case 1:
                            color(63);
                            gotoxy(40,2);
                            printf("Menu Consumos");
                            color(7);
                            vMConsu=archivoaMatrizConsumo(32,13,mConsumos,aConsumos,vMConsu);
                            vConsumidos= datosConsumidosTotal (32,13,mConsumos,vConsumidos,c.id);
                            color(30);
                            gotoxy(30,4);
                            printf("Datos consumidos Durante el Periodo MB = [ %d ]",vConsumidos);
                            color(7);
                            printf("\n\n");
                            break;


                        case 2:
                            color(63);
                            gotoxy(40,2);
                            printf("Menu Consumos");
                            color(7);
                            printf("\nIngrese El Mes para ver los consumos: ");
                            scanf("%d",&mesConsumido);
                            vConsu= arch2ArrayConsumoMes(muestraConsu,vConsu,mesConsumido);
                            datosMensuales=datosConsumidosMensual(mesConsumido,c.id);
                            mensaje();
                            system("cls");
                            gotoxy(30,5);
                            color(8);
                            printf("Datos Conusmidos durante el MES");
                            color(7);
                            printf("\n\n");
                            muestraConsumosArreglo(muestraConsu,vConsu,c.id);
                            color(30);
                            printf("\nEl total de Datos consumidos en el Mes %d son MB = [ %d ]",mesConsumido,datosMensuales);
                            color(7);
                            printf("\n\n");

                            break;

                        case 3:
                            color(63);
                            gotoxy(40,2);
                            printf("Menu Consumos");
                            color(7);
                            printf("\nIngrese El Mes para ver los consumos: ");
                            scanf("%d",&mesConsumido);
                            printf("\nIngrese El Dia para ver los consumos: ");
                            scanf("%d",&diaConsumido);
                            vConsu=  arch2ArrayConsumoDiario(muestraConsu,vConsu,mesConsumido,diaConsumido);
                            datosDiarios=datosConsumidosDiarios(mesConsumido,diaConsumido,c.id);
                            mensaje();
                            system("cls");
                            gotoxy(30,5);
                            color(8);
                            printf("Datos Conusmidos durante el Mes %d y Dia %d",mesConsumido,diaConsumido);
                            color(7);
                            printf("\n\n");
                            muestraConsumosArreglo(muestraConsu,vConsu,c.id);
                            color(30);
                            printf("\nEl total de Datos consumidos en el Dia %d son MB =[ %d ]",diaConsumido,datosDiarios);
                            color(7);
                            printf("\n\n");


                            break;
                        }
                        system("pause");

                    }
                    while(opcionMuestraConsuenMB!=0);




                    break;


                case 5:
                    do
                    {
                        system("cls");
                        submenuMuestraConsumos();
                        color(9);
                        printf("Opcion: ");
                        color(7);
                        scanf("%d",&opcionMuestraConsu);
                        system("cls");
                        vConsu=0; /// validos clientes muestra
                        switch(opcionMuestraConsu)
                        {
                        case 1:

                            vConsu=arch2ArrayConsumoArchivo(muestraConsu,vConsu,c.id);
                            if(vConsu==0)
                            {
                                mensajeDestello("\nNo Hay Registro de datos Consumidos para el Periodo...\n\n\n");
                            }
                            else
                            {
                                system("cls");
                                mensajeListadoConsumo();
                                muestraConsumosArreglo(muestraConsu,vConsu,c.id);
                            }


                            break;

                        case 2:

                            vConsu=arch2ArrayConsumoArchivoActivo(muestraConsu,vConsu,c.id);
                            if(vConsu==0)
                            {
                                mensajeDestello("\nNo Hay Registro de datos Consumidos para el Periodo...\n\n\n");
                            }
                            else
                            {
                                system("cls");
                                mensajeListadoConsumo();
                                muestraConsumosArreglo(muestraConsu,vConsu,c.id);
                            }


                            break;

                        case 3:
                            vConsu=arch2ArrayConsumoArchivoBaja(muestraConsu,vConsu,c.id);
                            if(vConsu==0)
                            {
                                mensajeDestello("\nNo Hay Registro de datos Consumidos para el Periodo...\n\n\n");

                            }
                            else
                            {
                                mensaje();
                                system("cls");
                                mensajeListadoConsumo();
                                muestraConsumosArreglo(muestraConsu,vConsu,c.id);
                            }



                            break;


                        }
                        system("pause");



                    }
                    while(opcionMuestraConsu!=0);


                    break;


                }
            }
            while(opcionConsu!=0);
            break;
        }


    }
    while(opcionPpal!=0);









    printf("Gracias por utilizar el programa pedorro =)");
    return 0;
}


/************************************************************************//**
*
* \brief funcion que muestra Un mensaje con el logo del programa
*
***************************************************************************/
void printtest()
{

    printf("\t\t                                                ##                             \n");
    printf("\t\t                                                          ###                  \n");
    printf("\t\t ###   ###                 ####  .###                     ##                   \n");
    printf("\t\t ###   ###                 ##### ####                                          \n");
    printf("\t\t ###   ### ###########     # ### ####    #####  ####  ## ###: ###              \n");
    printf("\t\t ###   ###    ####         # #### ###  ###  ###  ###  ##  ##: ###              \n");
    printf("\t\t ###   ###    ####         #  ### ###  ###   ### ###  #   ##: ###              \n");
    printf("\t\t ###   ###     ##          #  ##  ###  ###   ###  ### #   ##: ###              \n");
    printf("\t\t ###   ###     ##          #   #  ###  ###   ###  ####    ##: ###.             \n");
    printf("\t\t ###   ###     ##          #      ###  ###  ###   ####    ##: ######           \n");
    printf("\t\t ###   ###     ###         ##     ###   ######     ###    ##:  ########        \n");
    printf("\t\t  ######        #####                     ##                                   \n");
    color(7);

}


/************************************************************************//**
*
*
* \brief Utilizamos la funcion para mostrar un mensaje del desarrollador
*
*
***************************************************************************/
void watermark ()
{

    color(8);
    gotoxy(80,25);
    printf("POWERED BY UTMOVIL");
    color(7);

}

/************************************************************************//**
*
* \brief funcion que Muestra un mensaje estilo matrix
*
***************************************************************************/
void intro()
{
    {
        color(3);
        system("title UTMOVIL");

        int numeros[21] = {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0,1};
        int i;
        int j=0;

        while(j<100)
        {
            for(i=1; i<=250; i++)
            {
                int numero = numeros [rand() %10];
                printf("%d ", numero);
            }
            printf("\n");
            j++;

        }

        return 0;
    }
}


/************************************************************************//**
*
* \brief funcion que Muestra un mensaje en destello
* \param char
*
***************************************************************************/
void mensajeDestello(char mensaje [1000])
{
    for(int i=0; i<6; i++)
    {
        gotoxy(30,8);
        printf("%s",mensaje);
        Sleep(200);
        if(i%2==0)
        {
            color(30);
        }
        else
        {
            color(7);
        }
    }
}



/************************************************************************//**
*
* \brief funcion que muestra el mensaje en el subMenu de Consultas
*
***************************************************************************/

void mensajeConsultas()
{
    gotoxy(40,6);
    color(63);
    printf("Menu de Consultas");
    color(7);

}


/************************************************************************//**
*
* \brief funcion que muestra el submenu de alta clientes
*
***************************************************************************/

void submenuAltaCliente()
{
    color(3);
    gotoxy(35,3);
    printf(" Alta de Clientes ");
    color(7);
    gotoxy(30,5);
    printf("[1].- Alta Cliente Manual");
    gotoxy(30,6);
    printf("[2].- Alta Cliente Automatica");
    gotoxy(30,8);
    printf("0-Salir");
    gotoxy(45,8);

}


/************************************************************************//**
*
* \brief funcion que muestra el mensaje en el subMenu de modificaciones
*
***************************************************************************/

void mensajeModificaciones()
{
    gotoxy(40,6);
    color(63);
    printf("< Modificaciones en Curso >");
    color(7);

}

/************************************************************************//**
*
* \brief funcion que muestra el mensaje en el subMenu de listado de consumos
*
***************************************************************************/

void mensajeListadoConsumo()
{
    gotoxy(40,5);
    color(63);
    printf("Listado de Consumos \n");
    color(7);

}


/************************************************************************//**
*
* \brief funcion que muestra un mensaje con delay
*
***************************************************************************/

void mensaje()
{
    printf("Cargando Datos");
    for(int i=0; i<10 ; i++)
    {
        printf(".");
        Sleep(300);

    }
}



/************************************************************************//**
*
* \brief funcion que muestra el menu y sus opcones
*
***************************************************************************/

void menuppal ()
{

    color(3);
    gotoxy(35,3);
    printf(" UT MoVil ");
    color(7);
    gotoxy(30,5);
    printf("[1].- Servicios Cliente");
    gotoxy(30,6);
    printf("[2].- Servicios Consumidor");
    gotoxy(30,8);
    printf("0-Salir");
    gotoxy(45,8);

}


/************************************************************************//**
*
* \brief funcion que muestra el submenu de alta consumo
*
***************************************************************************/

void submenuAltaConsumo ()
{


    gotoxy(35,5);
    printf("[1].- Alta Manual");
    gotoxy(35,6);
    printf("[2].- Alta Random");
    gotoxy(35,8);
    printf("0-Salir");
    gotoxy(45,8);

}



/************************************************************************//**
*
* \brief funcion que muestra el Submenu de clientes y sus opcones
*
***************************************************************************/
void submenuCli ()
{
    color(3);
    gotoxy(45,3);
    printf("  Menu Cliente: ");
    color(7);
    gotoxy(40,5);
    printf("[1].- Alta");
    gotoxy(40,6);
    printf("[2].- Baja");
    gotoxy(40,7);
    printf("[3].- Modificacion ");
    gotoxy(40,8);
    printf("[4].- Consulta ");
    gotoxy(40,9);
    printf("[5].- Listado Clientes");
    ///gotoxy(30,10);
    ///printf("[6].- Crea clientes aleatorios");
    gotoxy(40,11);
    printf("0-Salir");
    gotoxy(55,11);
}


/************************************************************************//**
*
* \brief funcion que muestra el Submenu de Consumidor y sus opcones
*
***************************************************************************/
void submenuConsu()
{

    color(3);
    gotoxy(35,3);
    printf("  Menu Consumidor: ");
    color(7);
    gotoxy(30,5);
    printf("[1].- Alta");
    gotoxy(30,6);
    printf("[2].- Baja");
    gotoxy(30,7);
    printf("[3].- Modificacion ");
    gotoxy(30,8);
    printf("[4].- Consulta ");
    gotoxy(30,9);
    printf("[5].- Listado Consumos");
    gotoxy(30,10);
    printf("0-Salir");
    gotoxy(45,10);
}

/**************************************************************
*
* \brief funcion que muestra el Submenu de Consulta del cliente
*
**************************************************************/
void submenuConsultasCli ()
{
    color(3);
    gotoxy(35,3);
    printf("Menu Consultas: ");
    color(7);
    gotoxy(30,5);
    printf("[1].- Nro Cliente");
    gotoxy(30,6);
    printf("[2].- Nombre");
    gotoxy(30,7);
    printf("[3].- Apellido ");
    gotoxy(30,8);
    printf("[4].- Dni ");
    gotoxy(30,9);
    printf("[5].- Email");
    gotoxy(30,10);
    printf("[6].- Domicilio");
    gotoxy(30,11);
    printf("[7].- Nro movil");
    gotoxy(30,12);
    printf("0-Salir");
    gotoxy(45,12);
}


/**************************************************************
*
* \brief funcion que muestra el Submenu de modificacion cliente
*
**************************************************************/
void submenuModificaCli ()
{
    color(63);
    gotoxy(35,3);
    printf("Menu Modificaciones: ");
    color(7);
    gotoxy(30,5);
    printf("[1].- Nombre");
    gotoxy(30,6);
    printf("[2].- Apellido");
    gotoxy(30,7);
    printf("[3].- Dni ");
    gotoxy(30,8);
    printf("[4].- Email ");
    gotoxy(30,9);
    printf("[5].- Domicilio");
    gotoxy(30,10);
    printf("[6].- Nro Movil");
    gotoxy(30,11);
    printf("0-Salir");
    gotoxy(45,11);


}


/**************************************************************
*
* \brief funcion de Submenu de muestras clientes
*
**************************************************************/
void submenuMuestra()
{

    color(3);
    gotoxy(35,3);
    printf("Submenu de Listado");
    color(7);
    gotoxy(30,5);
    printf("[1].- Muestra listado completo");
    gotoxy(30,6);
    printf("[2].- Muestra listado de Clientes de alta");
    gotoxy(30,7);
    printf("[3].- Muestra listado de Clientes de baja");
    gotoxy(30,8);
    printf("0-Salir");
    gotoxy(45,8);
}


/**************************************************************
*
* \brief funcion de Submenu de modifica consumos
*
**************************************************************/
void submenuModificacionConsu()
{

    color(3);
    gotoxy(35,3);
    printf("Submenu de Modificacion");
    color(7);
    gotoxy(30,5);
    printf("[1].- Modificar Fecha");
    gotoxy(30,6);
    printf("[2].- Modificar Consumos MB");
    gotoxy(30,7);
    printf(" 0-Volver");
    gotoxy(45,8);
}


/**************************************************************
*
* \brief funcion de Submenu de muestras consumos
*
**************************************************************/
void submenuMuestraConsumos()
{

    color(3);
    gotoxy(35,3);
    printf("Submenu de Listado");
    color(7);
    gotoxy(30,5);
    printf("[1].- Muestra listado completo");
    gotoxy(30,6);
    printf("[2].- Muestra listado de Consumos de alta");
    gotoxy(30,7);
    printf("[3].- Muestra listado de Consumos de baja");
    gotoxy(30,8);
    printf("0-Salir");
    gotoxy(45,8);
}


/**************************************************************
*
* \brief funcion de Submenu de muestras consumos en MB
*
**************************************************************/
void submenuMuestraConsumosenMb()
{

    color(3);
    gotoxy(35,3);
    printf("Submenu de Listado");
    color(7);
    gotoxy(30,5);
    printf("[1].- Muestra Total de consumos");
    gotoxy(30,6);
    printf("[2].- Muestra Consumos por Mes");
    gotoxy(30,7);
    printf("[3].- Muestra Consumos por Dia");
    gotoxy(30,8);
    printf("0-Salir");
    gotoxy(45,9);
}

/************************************************************************//**
*
* \brief funcion que Carga un cliente
* \return Retorna un cliente
*
***************************************************************************/
stCliente cargaUnCliente()
{
    stCliente c;
    int validaCli=1;

    do
    {
        while(validaCli==1)
        {
            gotoxy(3,3);
            printf("Ingrese el nro de Cliente..........: ");
            scanf("%d",&c.nroCliente);
            validaCli=validaCliente(c.nroCliente);
            if(validaCli==1)
            {
                gotoxy(39,3);
                printf("        ");
                gotoxy(3,5);
                printf("Ingrese un nro de cliente valido");
            }

        }
    }
    while(c.nroCliente<0 || c.nroCliente>9999999);
    gotoxy(3,5);
    printf("Ingrese el Nombre..................: ");
    fflush(stdin);
    gets(c.nombre);
    gotoxy(3,7);
    printf("Ingrese el Apellido................: ");
    fflush(stdin);
    gets(c.apellido);
    gotoxy(3,9);
    printf("Ingrese el DNI.....................: ");
    scanf(" %d", &c.dni);

    do
    {
        gotoxy(3,11);
        printf("Ingrese el EMail...................: ");
        fflush(stdin);
        gets(c.email);
        mensajeEmailError(validaEmail(c.email));
        //printf("\nMENSAJE ERROR %d",(validaEmail(c.email)));
    }
    while(!validaEmail(c.email));

    gotoxy(3,13);
    printf("Ingrese el Domicilio...............: ");
    fflush(stdin);
    gets(c.domicilio);
    gotoxy(3,15);
    printf("Ingrese el Numero de celular.......: ");
    scanf("%s",&c.movil);
    c.baja=0;
    return c;
}


/************************************************************************//**
*
* \brief funcion que persiste el dato cargador en un archivo.
*
***************************************************************************/
void guardaClienteArchivo (stCliente c)
{
    FILE *pArchCliente = fopen(AR_CLIENTE,"ab");
    if(pArchCliente)
    {
        fwrite(&c,sizeof(stCliente),1,pArchCliente);
        fclose(pArchCliente);
    }
}


/************************************************************************//**
*
* \brief funcion que Carga uno o mas clientes y los guarda en el Archivo
*
***************************************************************************/
void cargaClienteArchivo ()
{
    stCliente c;
    char opcion =0;
    while(opcion!=27)
    {
        system("cls");
        color(63);
        gotoxy(40,2);
        printf("Sistema de Alta de Clientes...");
        color(7);
        c=cargaUnCliente();
        c.id=buscaUltimoId()+1;
        guardaClienteArchivo(c);
        printf("ESC para salir ");
        opcion=getch();
    }
}


/************************************************************************//**
*
* \brief funcion que muestra un cliente
* \param Estrucutura cliente
*
***************************************************************************/
void muestraUnCliente(stCliente c) /// modificar para gotoxy
{
    printf("\n  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223,223);
    printf("\n  ID......................: %d", c.id);
    printf("\n  Nro de Cliente..........: %d", c.nroCliente);
    printf("\n  Nombre..................: %s", c.nombre);
    printf("\n  Apellido................: %s", c.apellido);
    printf("\n  DNI.....................: %d", c.dni);
    printf("\n  EMail...................: %s", c.email);
    printf("\n  Calle...................: %s", c.domicilio);
    printf("\n  Nro de Celular..........: %d", c.movil);
    printf("\n  Baja s/n................: %s", (c.baja)?"SI":"NO");
    printf("\n  %c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c",219,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220,220);
    printf("\n");
}

void muestraClientesArreglo(stCliente a[],int v)
{
    int i=0;
    while(i<v)
    {
        muestraUnCliente(a[i]);
        i++;
    }
}

/************************************************************************//**
*
* \brief funcion que muestra un cliente del archivo
*
***************************************************************************/
void muestraClienteArchivo()
{
    stCliente c;
    FILE *pArchCliente = fopen(AR_CLIENTE,"rb");
    if(pArchCliente)
    {
        while(fread(&c,sizeof(stCliente),1,pArchCliente)>0)
        {
            muestraUnCliente(c);
        }
        printf("\n");
        fclose(pArchCliente);
    }
}

/************************************************************************//**
*
* \brief funcion que pasa todos los clientes de un archivo a un arreglo
*
***************************************************************************/
int arch2ArrayClienteArchivo(stCliente a[], int v)
{
    stCliente c;
    FILE *pArchCliente = fopen(AR_CLIENTE,"rb");
    if(pArchCliente)
    {
        while(fread(&c,sizeof(stCliente),1,pArchCliente)>0)
        {
            a[v]=c;
            v++;
        }
        fclose(pArchCliente);
    }
    return v;
}

/************************************************************************//**
*
* \brief funcion que muestra un error si el email es incorrecto
* \param un entero que es devuelto de la funcion de validar email
*
***************************************************************************/
void mensajeEmailError (int dato)
{
    stCliente c;

    if(validaEmail(c.email)== dato)
    {
        gotoxy(40,11);
        printf("                 ");
        gotoxy(3,13);
        printf("Ingrese un Email Valido");
    }
}



/************************************************************************//**
*
* \brief funcion que valida un email, fijandose si contiene un @
* \param un string
* \return flag 0 si es incorrecto y 1 si es correcto
*
***************************************************************************/
int validaEmail(char email[])
{
    int v=strlen(email);
    int i=0;
    int flag=0;
    while(i<v && flag == 0)
    {
        if(email[i]==64)  /// =='@'
        {
            flag=1;
        }
        i++;
    }
    return flag;
}


/************************************************************************//**
*
* \brief funcion que muestra busca el ultimo Id ingresado en el Archivo
* \return devuelve el ultimo ID del archivo
*
***************************************************************************/
int buscaUltimoId()
{
    stCliente c;
    int id=-1;
    FILE *pArchCliente = fopen(AR_CLIENTE,"rb");
    if(pArchCliente)
    {
        fseek(pArchCliente, sizeof(stCliente)*(-1),SEEK_END);
        if(fread(&c,sizeof(stCliente),1,pArchCliente) > 0)
        {
            id=c.id;
        }
        fclose(pArchCliente);
    }
    return id;
}

/************************************************************************//**
*
* \brief funcion que muestra busca el ultimo Nro de Clietne ingresado en el Archivo
* \return devuelve el ultimo ID del archivo
*
***************************************************************************/
int buscaUltimoNroCliente()
{
    stCliente c;
    int NroCliente=-1;
    FILE *pArchCliente = fopen(AR_CLIENTE,"rb");
    if(pArchCliente)
    {
        fseek(pArchCliente, sizeof(stCliente)*(-1),SEEK_END);
        if(fread(&c,sizeof(stCliente),1,pArchCliente) > 0)
        {
            NroCliente=c.nroCliente;
        }
        fclose(pArchCliente);
    }
    return NroCliente;
}

/************************************************************************//**
*
* \brief funcion que muestra Los clientes activos del archivo
*
***************************************************************************/
void muestraClienteArchivoActivo()
{
    stCliente c;
    FILE *pArchCliente = fopen(AR_CLIENTE,"rb");
    if(pArchCliente)
    {
        while(fread(&c,sizeof(stCliente),1,pArchCliente)>0)
        {
            if(c.baja==0)
            {
                muestraUnCliente(c);
            }
        }
        printf("\n");
        fclose(pArchCliente);
    }
}


/************************************************************************//**
*
* \brief funcion que muestra Los clientes Inactivos del archivo
*
***************************************************************************/
void muestraClienteArchivoBaja()
{
    stCliente c;
    FILE *pArchCliente = fopen(AR_CLIENTE,"rb");
    if(pArchCliente)
    {
        while(fread(&c,sizeof(stCliente),1,pArchCliente)>0)
        {
            if(c.baja==1)
            {
                muestraUnCliente(c);
            }
        }
        printf("\n");
        fclose(pArchCliente);
    }
}

/************************************************************************//**
*
* \brief funcion que pasa los clientes activos a un arreglo
*\param Arreglo de clientes
*\param validos
*\return validos
*
***************************************************************************/
int arch2ArrayClienteArchivoActivo(stCliente a[],int v)
{
    stCliente c;
    FILE *pArchCliente = fopen(AR_CLIENTE,"rb");
    if(pArchCliente)
    {
        while(fread(&c,sizeof(stCliente),1,pArchCliente)>0)
        {
            if(c.baja==0)
            {
                a[v]=c;
                v++;
            }
        }
        fclose(pArchCliente);
    }
    return v;
}


/************************************************************************//**
*
* \brief funcion que pasa los clientes de baja a un arreglo
*\param Arreglo de clientes
*\param validos
*\return validos
*
***************************************************************************/
int arch2ArrayClienteArchivoBaja(stCliente a[],int v)
{
    stCliente c;
    FILE *pArchCliente = fopen(AR_CLIENTE,"rb");
    if(pArchCliente)
    {
        while(fread(&c,sizeof(stCliente),1,pArchCliente)>0)
        {
            if(c.baja==1)
            {
                a[v]=c;
                v++;
            }
        }
        fclose(pArchCliente);
    }
    return v;
}




/************************************************************************//**
*
* \brief funcion que busca un cliente en el archivo por apellido
* \param apellido (char)
* \return cliente Si lo encuentra devuelve el Id correspondiente, si no el Id=-1
*
***************************************************************************/
stCliente buscaUnClienteApellidoArchivo(char apellido[])
{
    stCliente c;
    int flag=0;
    FILE *pArchCliente = fopen(AR_CLIENTE,"rb");
    if(pArchCliente)
    {
        while( flag == 0 && fread(&c, sizeof(stCliente), 1, pArchCliente) > 0)
        {
            if(strcmp(c.apellido, apellido) == 0)
            {
                flag=1;
            }
        }
        fclose(pArchCliente);
    }
    if(flag==0)
    {
        c.id=-1;
    }

    return c;
}


/************************************************************************//**
*
* \brief funcion que busca un cliente en el archivo por Nombre
* \param Nombre (char)
* \return cliente Si lo encuentra devuelve el Id correspondiente, si no el Id=-1
*
***************************************************************************/
stCliente buscaUnClienteNombreArchivo(char nombre[])
{
    stCliente c;
    int flag=0;
    FILE *pArchCliente = fopen(AR_CLIENTE,"rb");
    if(pArchCliente)
    {
        while( flag == 0 && fread(&c, sizeof(stCliente), 1, pArchCliente) > 0)
        {
            if(strcmp(c.nombre, nombre) == 0)
            {
                flag=1;
            }
        }
        fclose(pArchCliente);
    }
    if(flag==0)
    {
        c.id=-1;
    }

    return c;
}


/************************************************************************//**
*
* \brief funcion que busca un cliente en el archivo por Dni
* \param dni(int)
* \return cliente Si lo encuentra devuelve el Id correspondiente, si no el Id=-1
*
***************************************************************************/
stCliente buscaUnClienteDniArchivo(int dni)
{
    stCliente c;
    int flag=0;
    FILE *pArchCliente = fopen(AR_CLIENTE,"rb");
    if(pArchCliente)
    {
        while( flag == 0 && fread(&c, sizeof(stCliente), 1, pArchCliente) > 0)
        {
            if(c.dni==dni)
            {
                flag=1;
            }
        }
        fclose(pArchCliente);
    }
    if(flag==0)
    {
        c.id=-1;
    }

    return c;
}
/************************************************************************//**
*
* \brief funcion que valida un cliente por el nrodeCliente
* \param nroCliente(int)
* \return cliente Si lo encuentra devuelve Flag 1 y si no 0
*
***************************************************************************/
int validaCliente (int nroCli)
{
    stCliente c;
    int flag=0;
    FILE *pArchCliente = fopen(AR_CLIENTE,"rb");
    if(pArchCliente)
    {
        while( flag == 0 && fread(&c, sizeof(stCliente), 1, pArchCliente) > 0)
        {
            if(c.nroCliente==nroCli)
            {
                flag=1;
            }
        }
        fclose(pArchCliente);
    }


    return flag;
}


/************************************************************************//**
*
* \brief funcion que busca un cliente en el archivo por NroCliente
* \param nroCliente(int)
* \return cliente Si lo encuentra devuelve el Id correspondiente, si no el Id=-1
*
***************************************************************************/
stCliente buscaUnClienteNroClienteArchivo(int nroCli)
{
    stCliente c;
    int flag=0;
    FILE *pArchCliente = fopen(AR_CLIENTE,"rb");
    if(pArchCliente)
    {
        while( flag == 0 && fread(&c, sizeof(stCliente), 1, pArchCliente) > 0)
        {
            if(c.nroCliente==nroCli)
            {
                flag=1;
            }
        }
        fclose(pArchCliente);
    }
    if(flag==0)
    {
        c.id=-1;
    }

    return c;
}


/************************************************************************//**
*
* \brief funcion que busca un cliente en el archivo por Email
* \param Email(char)
* \return cliente Si lo encuentra devuelve el Id correspondiente, si no el Id=-1
*
***************************************************************************/
stCliente buscaUnClienteEmailArchivo(char email[])
{
    stCliente c;
    int flag=0;
    FILE *pArchCliente = fopen(AR_CLIENTE,"rb");
    if(pArchCliente)
    {
        while( flag == 0 && fread(&c, sizeof(stCliente), 1, pArchCliente) > 0)
        {
            if(strcmp(c.email,email) == 0)
            {
                flag=1;
            }
        }
        fclose(pArchCliente);
    }
    if(flag==0)
    {
        c.id=-1;
    }

    return c;
}


/************************************************************************//**
*
* \brief funcion que busca un cliente en el archivo por Domicilio
* \param Domicilio(char)
* \return cliente Si lo encuentra devuelve el Id correspondiente, si no el Id=-1
*
***************************************************************************/
stCliente buscaUnClienteDomicilioArchivo(char domicilio[])
{
    stCliente c;
    int flag=0;
    FILE *pArchCliente = fopen(AR_CLIENTE,"rb");
    if(pArchCliente)
    {
        while( flag == 0 && fread(&c, sizeof(stCliente), 1, pArchCliente) > 0)
        {
            if(strcmp(c.domicilio,domicilio) == 0)
            {
                flag=1;
            }
        }
        fclose(pArchCliente);
    }
    if(flag==0)
    {
        c.id=-1;
    }

    return c;
}


/************************************************************************//**
*
* \brief funcion que busca un cliente en el archivo por Movil
* \param Movil(char)
* \return cliente Si lo encuentra devuelve el Id correspondiente, si no el Id=-1
*
***************************************************************************/
stCliente buscaUnClienteMovilArchivo(char movil[])
{
    stCliente c;
    int flag=0;
    FILE *pArchCliente = fopen(AR_CLIENTE,"rb");
    if(pArchCliente)
    {
        while( flag == 0 && fread(&c, sizeof(stCliente), 1, pArchCliente) > 0)
        {
            if(strcmp(c.movil,movil) == 0)
            {
                flag=1;
            }
        }
        fclose(pArchCliente);
    }
    if(flag==0)
    {
        c.id=-1;
    }

    return c;
}


/************************************************************************//**
*
* \brief funcion que busca un cliente en el archivo por Id
* \param Id(int)
* \return cliente Si lo encuentra devuelve el Id correspondiente, si no el Id=-1
*
***************************************************************************/
stCliente buscaUnClienteIdArchivo(int id)
{
    stCliente c;
    int flag=0;
    FILE *pArchCliente = fopen(AR_CLIENTE,"rb");
    if(pArchCliente)
    {
        while( flag == 0 && fread(&c, sizeof(stCliente), 1, pArchCliente) > 0)
        {
            if(c.id==id)
            {
                flag=1;
            }
        }
        fclose(pArchCliente);
    }
    if(flag==0)
    {
        c.id=-1;
    }

    return c;
}


/************************************************************************//********
*
* \brief funcion que modificar el campo de nro Cliente de un cliente y lo guarda en el archivo
* \param id(int)
* \param nroCliente(int)
*
**********************************************************************************/
void modificaClienteNroCliente(int id, int nroCli)
{
    stCliente c;
    FILE *pArchCliente=fopen(AR_CLIENTE,"r+b");
    int flag =-1;
    int i=0;

    if(pArchCliente)
    {
        while(flag==-1 && fread(&c,sizeof(stCliente),1,pArchCliente)>0)
        {
            if(c.id==id)
            {
                flag=i;
            }
            i++;
        }

        c.nroCliente=nroCli;
        fseek(pArchCliente,sizeof(stCliente)*(i-1),SEEK_SET);
        if(fwrite(&c,sizeof(stCliente),1,pArchCliente)==1)
        {
            printf("El Cliente se actualizo Correctamente!!\n");
            muestraUnCliente(c);
            system("pause");
            fclose(pArchCliente);
        }
    }

}


/************************************************************************//********
*
* \brief funcion que modificar el campo de nombre de un cliente y lo guarda en el archivo
* \param id(int)
* \param nombre(char)
*
**********************************************************************************/
void modificaClienteNombre(int nroCli,char nombre[])
{
    stCliente c;
    FILE *pArchCliente=fopen(AR_CLIENTE,"r+b");
    int flag =-1;
    int i=0;

    if(pArchCliente)
    {
        while(flag==-1 && fread(&c,sizeof(stCliente),1,pArchCliente)>0)
        {
            if(c.nroCliente==nroCli)
            {
                flag=i;
            }
            i++;
        }

        strcpy(c.nombre,nombre);
        fseek(pArchCliente,sizeof(stCliente)*(i-1),SEEK_SET);

        if(fwrite(&c,sizeof(stCliente),1,pArchCliente)==1)
        {
            printf("El Cliente se actualizo Correctamente!!\n");
            muestraUnCliente(c);
            system("pause");
            fclose(pArchCliente);
        }
    }

}


/************************************************************************//********
*
* \brief funcion que modificar el campo de apellido de un cliente y lo guarda en el archivo
* \param id(int)
* \param apellido(char)
*
**********************************************************************************/
void modificaClienteApellido(int nroCli,char apellido[])
{
    stCliente c;
    FILE *pArchCliente=fopen(AR_CLIENTE,"r+b");
    int flag =-1;
    int i=0;

    if(pArchCliente)
    {
        while(flag==-1 && fread(&c,sizeof(stCliente),1,pArchCliente)>0)
        {
            if(c.nroCliente==nroCli)
            {
                flag=i;
            }
            i++;
        }

        strcpy(c.apellido,apellido);
        fseek(pArchCliente,sizeof(stCliente)*(i-1),SEEK_SET);
        if(fwrite(&c,sizeof(stCliente),1,pArchCliente)==1)
        {
            printf("El Cliente se actualizo Correctamente!!\n");
            muestraUnCliente(c);
            system("pause");
            fclose(pArchCliente);
        }
    }

}


/************************************************************************//********
*
* \brief funcion que modificar el campo de dni de un cliente y lo guarda en el archivo
* \param id(int)
* \param dni(int)
*
**********************************************************************************/
void modificaClienteDni(int nroCli, int dni)
{
    stCliente c;
    FILE *pArchCliente=fopen(AR_CLIENTE,"r+b");
    int flag =-1;
    int i=0;

    if(pArchCliente)
    {
        while(flag==-1 && fread(&c,sizeof(stCliente),1,pArchCliente)>0)
        {
            if(c.nroCliente==nroCli)
            {
                flag=i;
            }
            i++;
        }

        c.dni=dni;
        fseek(pArchCliente,sizeof(stCliente)*(i-1),SEEK_SET);
        if(fwrite(&c,sizeof(stCliente),1,pArchCliente)==1)
        {
            printf("El Cliente se actualizo Correctamente!!\n");
            muestraUnCliente(c);
            system("pause");
            fclose(pArchCliente);
        }
    }

}


/************************************************************************//********
*
* \brief funcion que modificar el campo de email de un cliente y lo guarda en el archivo
* \param id(int)
* \param email(char)
*
**********************************************************************************/
void modificaClienteEmail(int nroCli, char email [ ])
{
    stCliente c;
    FILE *pArchCliente=fopen(AR_CLIENTE,"r+b");
    int flag =-1;
    int i=0;


    if(pArchCliente)
    {
        while(flag==-1 && fread(&c,sizeof(stCliente),1,pArchCliente)>0)
        {
            if(c.nroCliente==nroCli)
            {
                flag=i;
            }
            i++;
        }


        strcpy(c.email,email);
        fseek(pArchCliente,sizeof(stCliente)*(i-1),SEEK_SET);
        if(fwrite(&c,sizeof(stCliente),1,pArchCliente)==1)
        {
            printf("El Cliente se actualizo Correctamente!!\n");
            muestraUnCliente(c);
            system("pause");
            fclose(pArchCliente);
        }
    }

}


/************************************************************************//********
*
* \brief funcion que modificar el campo de domicilio de un cliente y lo guarda en el archivo
* \param id(int)
* \param domicilio(char)
*
**********************************************************************************/
void modificaClienteDomicilio(int nroCli, char domicilio [ ])
{
    stCliente c;
    FILE *pArchCliente=fopen(AR_CLIENTE,"r+b");
    int flag =-1;
    int i=0;

    if(pArchCliente)
    {
        while(flag==-1 && fread(&c,sizeof(stCliente),1,pArchCliente)>0)
        {
            if(c.nroCliente==nroCli)
            {
                flag=i;
            }
            i++;
        }

        strcpy(c.domicilio,domicilio);
        fseek(pArchCliente,sizeof(stCliente)*(i-1),SEEK_SET);
        if(fwrite(&c,sizeof(stCliente),1,pArchCliente)==1)
        {
            printf("El Cliente se actualizo Correctamente!!\n");
            muestraUnCliente(c);
            system("pause");
            fclose(pArchCliente);
        }
    }

}


/************************************************************************//********
*
* \brief funcion que modificar el campo de movil de un cliente y lo guarda en el archivo
* \param id(int)
* \param movil (char)
*
**********************************************************************************/
void modificaClienteMovil(int nroCli, int movil )
{
    stCliente c;
    FILE *pArchCliente=fopen(AR_CLIENTE,"r+b");
    int flag =-1;
    int i=0;

    if(pArchCliente)
    {
        while(flag==-1 && fread(&c,sizeof(stCliente),1,pArchCliente)>0)
        {
            if(c.nroCliente==nroCli)
            {
                flag=i;
            }
            i++;
        }

        c.movil=movil;
        fseek(pArchCliente,sizeof(stCliente)*(i-1),SEEK_SET);
        if(fwrite(&c,sizeof(stCliente),1,pArchCliente)==1)
        {
            printf("El Cliente se actualizo Correctamente!!\n");
            muestraUnCliente(c);
            system("pause");
            fclose(pArchCliente);
        }
    }
}


/************************************************************************//********
*
* \brief funcion que modificar el campo de baja de un cliente 0 activo / 1 inactivo y lo guarda en el archivo
* \param baja(int) seria el id
*
**********************************************************************************/
void modificaBajaCliente(int baja)
{
    stCliente c;
    FILE *pArchCliente=fopen(AR_CLIENTE,"r+b");
    int pasaje=0;
    int flag =-1;
    int i=0;
    if(pArchCliente!=NULL)
    {
        while(flag==-1 && fread(&c,sizeof(stCliente),1,pArchCliente)>0)
        {


            if(c.nroCliente==baja)
            {
                flag=i;
            }
            i++;
        }
        if(flag!=-1)
        {
            printf("\nEl Nro de Cliente %d",baja);
            if(c.baja==0)
            {
                printf("\n****Cliente Activo**** \n");
                muestraUnCliente(c);
            }
            else
            {
                printf("\n****Cliente Inactivo**** \n");
                muestraUnCliente(c);
            }
            printf("\nPresione [1] para Desactivar y [0] Para activar: ");
            scanf("%d", &pasaje);

            if(pasaje==1)
            {
                c.baja=1;
                fseek(pArchCliente,sizeof(stCliente)*(i-1),SEEK_SET);
                if(fwrite(&c,sizeof(stCliente),1,pArchCliente)==1)
                {

                    printf("El Cliente se actualizo Correctamente!!\n");
                    muestraUnCliente(c);
                    system("pause");
                    fclose(pArchCliente);
                }
            }
            else
            {
                c.baja=0;
                fseek(pArchCliente,sizeof(stCliente)*(i-1),SEEK_SET);
                if(fwrite(&c,sizeof(stCliente),1,pArchCliente)==1)
                {

                    printf("El Cliente se actualizo Correctamente!!\n");
                    muestraUnCliente(c);
                    system("pause");
                    fclose(pArchCliente);
                }
            }
        }
        else
        {
            printf("No se encuentra Nro de Cliente \n");
        }

    }
    else
    {
        exit(1);
    }

}


/************************************************************************//**
*
* \brief funcion que busca la menor posicion del menor id
* \param Arreglo de cliente
* \param validos
* \param posicion
* \return posicion del menor id
*
***************************************************************************/
int buscaPosMenorId(stCliente a[],int v, int c)
{
    int i=c;
    int posMenor=i;
    i++;
    while(i<v)
    {
        if(a[i].id<a[posMenor].id)
        {
            posMenor=i;
        }
        i++;
    }
    return posMenor;
}


/************************************************************************//**
*
* \brief funcion que ordena por seleccion los Id de los clientes
* \param Arreglo de clientes
* \param validos
*
***************************************************************************/
void ordenaSeleccionId(stCliente a[],int v)
{
    int poMenor=0;
    int i=0;
    stCliente aux;

    while(i<v-1)
    {
        poMenor=buscaPosMenorId(a,v,i);
        aux=a[poMenor];
        a[poMenor]=a[i];
        a[i]=aux;
        i++;
    }
}


/************************************************************************//**
*
* \brief funcion que busca la posicion del nombre menor en el arreglo
* \param Arreglo de clientes
* \param validos
* \param posicion
* \return posicion del nombre menor
*
***************************************************************************/
int buscaPosMenorNombre(stCliente a[],int v, int c)
{
    int i=c;
    int posMenor=i;
    i++;
    while(i<v)
    {
        if(strcmp(a[i].nombre,a[posMenor].nombre)<0)
        {
            posMenor=i;
        }
        i++;
    }
    return posMenor;
}


/************************************************************************//**
*
* \brief funcion que ordena por seleccion los nombres
* \param Arreglo de clientes
* \param validos
*
***************************************************************************/
void ordenaSeleccionNombre(stCliente a[],int v)
{
    int poMenor=0;
    int i=0;
    stCliente aux;

    while(i<v-1)
    {
        poMenor=buscaPosMenorNombre(a,v,i);
        aux=a[poMenor];
        a[poMenor]=a[i];
        a[i]=aux;
        i++;
    }
}

/**
----------------------------------------------------------------
carga cliente aleatorio
----------------------------------------------------------------
*/


/*************************************************************//**
*
* \brief Funcion que genera un numero al azar, entre un minimo y maximo
* \return void
*
*****************************************************************/
int randomRango(int min, int max)
{
    return rand()%(max-min)+min;
}



/*************************************************************//**
*
* \brief Funcion que asigna al string recibido un nombre al azar
* \return void
*
*****************************************************************/
void getNomEmail(char ne[])
{
    char nombresem[][30] = {"alconNegro","Aniceto","Glafida","Aproniano","","Austiquiliano","pikachu","Canuto",
                            "Liduvina","Cilta","Merenciana","Crescenciano","Meuris","Ercilio","Ninfodora","Espidiforo",
                            "Sovietic","Evasilio","Sindulfo","casaRoja","peakyBlinder","daredevil","ricardoFort","tornado","bocaSubcampeon","profeaprobanos","lapromocionamo",
                            "asusRog","ibm","apple","zeus"
                           };

    strcpy(ne,strcat(nombresem[randomRango(1,sizeof(nombresem)/(sizeof(char)*30))],"@hotmail.com"));

}



/*************************************************************//**
*
* \brief Funcion que asigna al string recibido un nombre al azar
* \return void
*
*****************************************************************/
void getNombre(char n[])
{
    char nombres[][150] = {"Ailin","Juan","Jeremias","Daniel","Fernando","Lautaro","Mailen","Jose",
                           "Anastasio","Arturo","Mario","Tamaro","Adolfo","Pedro","Alfredo","Arnaldo",
                           "Mauro","Benicio","Ildefonso","Cuchuflito","Remilgo","Miguel","Reinaldo","Aaron",
                           "Abdon", "Abel", "Abelardo", "Abrahan", "Absalon", "Acacio", "Adalberto", "Adan",
                           "Adela", "Adelaida", "Adolfo", "Adon", "Adrian", "Agustin", "Aitor", "Alba", "Albert",
                           "Alberto", "Albina", "Alejandra", "Alejandro", "Alejo", "Alfonso", "Alfredo", "Alicia",
                           "Alipio", "Almudena", "Alonso", "Alvaro", "Amadeo", "Amaro", "Ambrosio", "Amelia", "Amparo",
                           "Ana", "Ananias", "Anastasia", "Anatolio", "Andrea", "Andres", "Angel", "Angela", "Angeles",
                           "Aniano", "Anna", "Anselmo", "Antero", "Antonia", "Antonio", "Aquiles", "Araceli", "Aranzazu",
                           "Arcadio", "Aresio", "Ariadna", "Aristides", "Arnaldo", "Artemio", "Arturo", "Ascension", "Asuncion",
                           "Atanasio", "Augusto", "Aurea", "Aurelia", "Aureliano", "Aurelio", "Aurora", "Baldomero", "Balduino",
                           "Baltasar", "Barbara", "Bartolome", "Basileo", "Beatriz", "Begonia", "Belen", "Beltran", "Benedicto",
                           "Benigno", "Benito", "Benjamin", "Bernabe", "Bernarda", "Bernardo", "Blanca", "Blas", "Bonifacio",
                           "Borja", "Bruno", "Calixto", "Camilo", "Candida", "Carina", "Carlos", "Carmelo", "Carmen", "Carolina",
                           "Casiano", "Casimiro", "Casio", "Catalina", "Cayetano", "Cayo", "Cecilia", "Ceferino", "Celia", "Celina",
                           "Celso", "Cesar", "Cesareo", "Cipriano", "Cirilo", "Cirino", "Ciro", "Clara", "Claudia", "Claudio",
                           "Cleofas", "Clotilde", "Colombo", "Columba", "Columbano", "Concepción", "Conrado", "Constancio",
                          };

    strcpy(n,nombres[randomRango(0,sizeof(nombres)/(sizeof(char)*150))]);
}

void getApellido(char a[])
{
    char apellidos[][100] = {"Gomez","Perez","Roca","Latorre","Fernandez","Torquemada", "Marijuan", "Roca", "Mitre", "Rivadavia",
                             "San Martin", "Alvarez", "Comizo", "Borges", "Zama", "Recato", "Olvido", "Gil", "Trapero", "Restinga",
                             "De Antonio", "Ramirez", "Spinetta", "Cortez", "Gonzalez", "Andujar", "San Juan", "Bautista", "Anchorena", "Paso",
                             "Gaboto","Vega","Vargas","Lloret","Linares","Suarez","Sierra","Amenabar","Blanco","White","Black","Aguilar", "Alonso",
                             "Alvarez", "Arias", "Benítez", "Blanco", "Blesa", "Bravo", "Caballero", "Cabrera", "Calvo", "Cambil", "Campos", "Can",
                             "Carmona", "Carrasco", "Castillo", "Castro", "Crespo", "Cruz", "Da Silva", "Delgado",
                             "Duran", "Esteban", "Fernandez", "Ferrer", "Flores", "Fuentes", "Gallardo", "Gallego", "Gimenez","Hidalgo", "Ibañez", "Iglesias", "Jimenez",
                             "Leon", "Lopez", "Lorenzo", "Lozano","Perez", "Prieto", "Ramos", "Rey", "Reyes", "Roca",  "Roman", "Saez", "Sanz",  "Suarez", "Torres", "Vargas", "Vazquez", "Vega", "Velasco",
                             "Vicente", "Vidal", "Zarategui","romano","griego","persa"
                            };

    strcpy(a,apellidos[randomRango(0,sizeof(apellidos)/(sizeof(char)*100))]);

}

int getDNI()
{
    return randomRango(549,1982)* randomRango(549,19801);
}

int getMovil()
{

    return randomRango(4800000,5700000);

}


void getCalle(char c[])
{

    char calles[][30] = {"San Juan ","Funes","Gaboto","San Martin","Colon","Rivadavia", "Alsina", "Roca", "Mitre", "Belgrano",
                         "Paso", "11 de Septiembre", "3 de Febrero", "Balcarce", "Libertad", "Magallanes", "Irala", "Ayolas", "Moreno", "Brown",
                         "Bolivar", "Alberti", "Gascon", "La Rioja", "Catamarca", "Salta", "Jujuy", "XX de Septiembre", "14 de Julio", "Dorrego",
                         "Hernandarias","Don Orione","Juramento","Lanzilota","Estrada","Tierra del Fuego","Mendoza","Chubut","Rio Negro","Misiones","Edison",
                         "Alberti", "Moreno", "Cordoba", "Belgrano", "Colon", "Rivadavia",  "Gascon", "Falucho", "Bolivar", "Buenos Aires", "Santa Fe",
                         "Independencia", "Corrientes", "San Martin", "Guemes", "Santiago del Estero", "Alvarado", "San Luis", "Catamarca", "Rawson",
                         "Jujuy", "Entre Rios", "Juan B. Justo", "La Rioja", "Garay", "San Juan", "Luro", "Salta", "12 de Octubre", "Las Heras", "25 de Mayo",
                         "Sarmiento", "Mitre", "Tucuman", "Arenales", "9 de Julio", "Olavarria", "Lamadrid", "Castelli", "Dorrego", "Constitucion", "Brown",
                         "Madrid", "Magallanes", "San Lorenzo", "Avellaneda", "Roca", "Alsina", "Libertad", "3 de Febrero", "20 de Septiembre", "Balcarce",
                         "11 de Septiembre", "Matheu", "14 de Julio", "Puan", "Alvear", "Ituzaingo", "Rodriguez Pena", "Alem", "Chaco", "Funes", "Santa Cruz",
                         "Ayacucho", "Chacabuco", "Almirante Brown", "Misiones", "Av. Colon", "Cerrito"
                        };

    strcpy(c,calles[randomRango(0,sizeof(calles)/(sizeof(char)*30))]);

}


stCliente cargoClientesRandom()
{
    stCliente c;
    c.baja=0;
    c.id=buscaUltimoId()+1;
    c.nroCliente=buscaUltimoNroCliente()+1;
    getApellido(c.apellido);
    getNombre(c.nombre);
    c.dni=getDNI();
    getCalle(c.domicilio);
    getNomEmail(c.email);
    c.movil=getMovil();
    return c;
}

/************************************************************************//**
*
* \brief funcion que Carga uno o mas clientes Random y los guarda en el Archivo
*
***************************************************************************/
void cargaClienteRandomArchivo ()
{
    stCliente c;
    char opcion =0;
    while(opcion!=27 )
    {
        system("cls");
        gotoxy(40,2);
        color(63);
        printf("Sistema de Alta de Clientes...");
        color(7);
        c=cargoClientesRandom();
        c.id=buscaUltimoId()+1;
        guardaClienteArchivo(c);
        gotoxy(30,4);
        printf("Enter Para Agregar un Cliente");
        gotoxy(30,5);
        printf("ESC para salir ");
        opcion=getch();

    }
}

/************************************************************************//**
*
* \brief funcion que carga el cliente random al archivo
* \param int cantidad  de datos a cargar
*
***************************************************************************/
void cargaClienteRandomArch(int cantidad)
{
    stCliente c;
    int i=0;

    while(i<cantidad)
    {
        c = cargoClientesRandom();
        guardaClienteArchivo(c);
        i++;
    }
}

int cargaClientesAleatorios( stCliente a[],int v,int dim,int clientesDeseados)
{

    while(v<dim&&v<clientesDeseados)
    {
        a[v]=cargoClientesRandom();
        v++;
    }
    return v;
}


/************************************************************************//**
*
* \brief funcion que pasa los datos del arreglo al archivo
* \param Arreglo de cliente
* \param validos
*
***************************************************************************/
void Array2Archivo(stCliente a[],int v)
{
    int i=0;
    FILE * pArch=fopen(AR_CLIENTE,"ab");
    if(pArch)
    {
        while(i<v)
        {
            fwrite(&a[i],sizeof(stCliente),1,pArch);
            i++;
        }
        fclose(pArch);
    }
}


/************************************************************************//**
*
* \brief funcion que muestra busca el ultimo Id ingresado en el Archivo de consumos
* \return devuelve el ultimo ID del archivo
*
***************************************************************************/
int buscaUltimoIdConsumo()
{
    stConsumos c;
    int id=-1;
    FILE *pArchConsumo = fopen(AR_CONSUMO,"rb");
    if(pArchConsumo)
    {
        fseek(pArchConsumo, sizeof(stConsumos)*(-1),SEEK_END);
        if(fread(&c,sizeof(stConsumos),1,pArchConsumo) > 0)
        {
            id=c.id;
        }
        fclose(pArchConsumo);
    }
    return id;
}


/************************************************************************//**
*
* \brief funcion que muestra busca el ultimo nro de consumo ingresado en el Archivo de consumos
* \return devuelve el ultimo ID del archivo
*
***************************************************************************/
int buscaUltimoNroConsumo()
{
    stConsumos c;
    int id=-1;
    FILE *pArchConsumo = fopen(AR_CONSUMO,"rb");
    if(pArchConsumo)
    {
        fseek(pArchConsumo, sizeof(stConsumos)*(-1),SEEK_END);
        if(fread(&c,sizeof(stConsumos),1,pArchConsumo) > 0)
        {
            id=c.nroConsumo;
        }
        fclose(pArchConsumo);
    }
    return id;
}



/************************************************************************//**
*
* \brief funcion que Carga un cliente
* \return Retorna un cliente
*
***************************************************************************/
stConsumos cargaUnConsumo()
{
    stConsumos consu;

    gotoxy(3,5);
    printf("Ingrese el a%co del consumo....",164);
    scanf("%d",&consu.anio);

    do
    {
        gotoxy(3,6);
        printf("Ingrese el mes del consumo.....");
        scanf("%d",&consu.mes);
    }
    while(consu.mes<1 || consu.mes>12);
    if ( consu.mes >= 1 && consu.mes <= 12 )
    {
        switch ( consu.mes )
        {
        case  1 :
        case  3 :
        case  5 :
        case  7 :
        case  8 :
        case 10 :
        case 12 :
            do
            {
                gotoxy(3,7);
                printf("Ingrese el dia del Consumo.....");
                scanf("%d",&consu.dia);
            }
            while(consu.dia<=1 && consu.dia>=31);
            break;

        case  4 :
        case  6 :
        case  9 :
        case 11 :
            do
            {
                gotoxy(3,7);
                printf("Ingrese el dia del Consumo.....");
                scanf("%d",&consu.dia);
            }
            while(consu.dia<=1 && consu.dia>=30);
            break;

        case  2 :
            if( consu.anio % 4 == 0 && consu.anio % 100 != 0 || consu.anio % 400 == 0 )
            {
                do
                {
                    gotoxy(34,7);
                    printf("    ");
                    gotoxy(3,7);
                    printf("Ingrese el dia del Consumo.....");
                    scanf("%d",&consu.dia);
                }
                while(consu.dia<1 || consu.dia>=30);
            }


            else
            {
                do
                {
                    gotoxy(3,7);
                    printf("Ingrese el dia del Consumo.....");
                    scanf("%d",&consu.dia);
                }
                while(consu.dia<1 || consu.dia>=29);
            }

        }
    }
    gotoxy(3,8);
    printf("Ingrese sus consumos en MB.....");
    scanf("%d",&consu.datosConsumidos);
    consu.baja=0;
    consu.nroConsumo=buscaUltimoNroConsumo()+1;
    consu.id=buscaUltimoIdConsumo()+1;


    return consu;
}


/************************************************************************//**
*
* \brief funcion que carga una fecha random
* \param Estrucutura consumo
*
***************************************************************************/
stConsumos fechaRandom ()
{
    stConsumos consu;
    consu.anio=2020; // año de consumos...
    consu.mes=randomRango(1,13);

    if ( consu.mes >= 1 && consu.mes <= 12 )
    {
        switch ( consu.mes )
        {
        case  1 :
        case  3 :
        case  5 :
        case  7 :
        case  8 :
        case 10 :
        case 12 :
            consu.dia= randomRango(1,31);
            break;

        case  4 :
        case  6 :
        case  9 :
        case 11 :
            consu.dia=randomRango(1,30);
            break;

        case  2 :
            if( consu.anio % 4 == 0 && consu.anio % 100 != 0 || consu.anio % 400 == 0 )
            {
                if ( consu.dia >= 1 && consu.dia <= 29 )
                {
                    consu.dia=randomRango(1,29);
                }
                else
                {
                    consu.dia=randomRango(1,28);
                }
            }
        }
    }
    return consu;
}
/************************************************************************//**
*
* \brief funcion que genera un consumo random
* \param int consumo
*
***************************************************************************/
int getDatosConsumidos()
{
    return randomRango(1,10000);
}


/************************************************************************//**
*
* \brief funcion que carga el consumo random a un cliente en particular
* \param int Id del cliente
* \return Estructura consumo
*
***************************************************************************/
stConsumos cargaConsumoRandom(int id)
{
    stConsumos c;

    c = fechaRandom();
    c.id=buscaUltimoIdConsumo()+1;
    c.baja=0;
    c.idCliente = id;
    c.nroConsumo = buscaUltimoNroConsumo()+1;
    c.datosConsumidos = getDatosConsumidos();

    return c;
}


/************************************************************************//**
*
* \brief funcion que carga el consumo al archivo
* \param int id del cliente
* \param int cantidad  de datos a cargar
*
***************************************************************************/
void cargaConsumoRandomArch(int id,int cantidad)
{
    stConsumos c;
    int i=0;

    while(i<cantidad)
    {
        c = cargaConsumoRandom(id);
        guardaConsumoEnArchivo(c);
        i++;
    }
}

/************************************************************************//**
*
* \brief funcion que muestra un consumo
* \param Estrucutura consumo
*
***************************************************************************/
void muestraUnConusmo(stConsumos consu) /// modificar para gotoxy
{

    printf("-----------------------------------------------------------------");
    printf("\n  ID CLIENTE..............: %d", consu.idCliente);
    printf("\n  ID CONSUMO..............: %d", consu.id);
    printf("\n  Nro CONSUMO.............: %d", consu.nroConsumo);
    printf("\n  A%co....................: %d",164, consu.anio);
    printf("\n  Mes.....................: %d", consu.mes);
    printf("\n  Dia.....................: %d", consu.dia);
    printf("\n  Datos Consumidos........: %d", consu.datosConsumidos);
    printf("\n  Baja s/n................: %s", (consu.baja)?"SI":"NO");
    printf("\n  -----------------------------------------------------------------");
    printf("\n");
}


/************************************************************************//**
*
* \brief funcion que persiste el dato cargador en un archivo.
*
***************************************************************************/
void guardaConsumoEnArchivo (stConsumos consu)
{
    FILE *pArchConsumo = fopen(AR_CONSUMO,"ab");
    if(pArchConsumo)
    {
        fwrite(&consu,sizeof(stConsumos),1,pArchConsumo);
        fclose(pArchConsumo);
    }
}


/************************************************************************//**
*
* \brief funcion que Carga uno o mas consumos y los guarda en el Archivo
* \param id del cliente
*
***************************************************************************/
void cargaConsumoArchivo (int idCliente)
{
    stConsumos consu;
    char opcion =0;
    while(opcion!=27)
    {
        system("cls");
        color(63);
        gotoxy(30,4);
        printf("Sistema de Alta de Clientes...");
        color(7);
        consu=cargaUnConsumo();
        consu.idCliente=idCliente;
        consu.nroConsumo=buscaUltimoNroConsumo()+1;
        consu.id=buscaUltimoIdConsumo()+1;
        guardaConsumoEnArchivo(consu);
        // printf("\nId consumo %d",consu.nroConsumo); se podria printear y mostrar el id del consumo cargado...
        system("pause");
        muestraUnConusmo(consu);
        printf("ESC para salir ");
        opcion=getch();
    }
}


/************************************************************************//**
*
* \brief funcion que muestra todos los consumos del archivo
*
***************************************************************************/
void muestraConsumoArchivo()
{
    stConsumos consu;
    FILE *pArchConsumo = fopen(AR_CONSUMO,"rb");
    if(pArchConsumo)
    {
        while(fread(&consu,sizeof(stConsumos),1,pArchConsumo)>0)
        {
            if(consu.baja==1)
            {
                color(5);
                muestraUnConusmo(consu);
                color(7);
            }
            else
            {
                muestraUnConusmo(consu);
            }



        }
        printf("\n");
        fclose(pArchConsumo);
    }
}


/************************************************************************//**
*
* \brief funcion que pasa los consumos del archivo a un arreglo
* \param Arreglo de consumos
* \param validos
* \param id
* \return validos cargados del archivo al arreglo
*
***************************************************************************/

int arch2ArrayConsumoArchivo(stConsumos a[], int v, int id)
{
    stConsumos c;
    FILE *pArchConsumo = fopen(AR_CONSUMO,"rb");
    if(pArchConsumo)
    {
        while(fread(&c,sizeof(stConsumos),1,pArchConsumo)>0)
        {
            if(c.idCliente==id)
            {
                a[v]=c;
                v++;
            }

        }
        fclose(pArchConsumo);
    }
    return v;
}


/************************************************************************//**
*
* \brief funcion que busca la posicion del menor consumo
* \param Arreglo de consumos
* \param validos
* \param posicion
* \return posicion del menor consumo
*
***************************************************************************/
int buscaPosMenorIdConsumo(stConsumos a[],int v, int c)
{
    int i=c;
    int posMenor=i;
    i++;
    while(i<v)
    {
        if(a[i].id<a[posMenor].id)
        {
            posMenor=i;
        }
        i++;
    }
    return posMenor;
}


/************************************************************************//**
*
* \brief funcion que ordena por seleccion el arreglo de consumos
* \param Arreglo de consumos
* \param validos
*
***************************************************************************/
void ordenaSeleccionIdConsumo(stConsumos a[],int v)
{
    int poMenor=0;
    int i=0;
    stConsumos aux;

    while(i<v-1)
    {
        poMenor=buscaPosMenorId(a,v,i);
        aux=a[poMenor];
        a[poMenor]=a[i];
        a[i]=aux;
        i++;
    }
}


/************************************************************************//**
*
* \brief funcion que pasa los consumos que estan activos del archivo a un arreglo
* \param Arreglo de consumos
* \param validos
* \param id
* \return validos cargados del archivo al arreglo
*
***************************************************************************/
int arch2ArrayConsumoArchivoActivo(stConsumos a[],int v, int id)
{
    stConsumos c;
    FILE *pArchConsumo = fopen(AR_CONSUMO,"rb");
    if(pArchConsumo)
    {
        while(fread(&c,sizeof(stConsumos),1,pArchConsumo)>0)
        {

            if(c.baja==0&&c.idCliente==id)
            {
                a[v]=c;
                v++;
            }
        }
        fclose(pArchConsumo);
    }
    return v;
}


/************************************************************************//**
*
* \brief funcion que pasa los consumos con id dados de baja de un cliente del archivo a un arreglo
* \param Arreglo de consumos
* \param validos
* \param id
* \return validos cargados del archivo al arreglo
*
***************************************************************************/
int arch2ArrayConsumoArchivoBaja(stConsumos a[],int v,int id)
{
    stConsumos c;
    FILE *pArchConsumo = fopen(AR_CONSUMO,"rb");
    if(pArchConsumo)
    {
        while(fread(&c,sizeof(stConsumos),1,pArchConsumo)>0)
        {
            if(c.baja==1&&c.idCliente==id)
            {
                a[v]=c;
                v++;
            }
        }
        fclose(pArchConsumo);
    }
    return v;
}


/************************************************************************//**
*
* \brief funcion que recorre el arreglo y llama a la funcion que muestra un consumo
* \param Arreglo de consumos
* \param validos
*
***************************************************************************/
void muestraConsumosArreglo(stConsumos a[],int v,int id)
{
    stConsumos c;
    int i=0;
    while(i<v )
    {

        if(a[i].idCliente == id)
        {


            if( a[i].baja  )
            {
                color(4);
                muestraUnConusmo(a[i]);
                color(7);

            }
            else
            {

                muestraUnConusmo(a[i]);

            }

        }
        i++;
        if(i%5 ==0) /// Para que muestre de a 5 datos
        {
            system("pause");
        }




    }
}


/************************************************************************//********
*
* \brief funcion que modificar el campo de baja de un consumo 0 activo / 1 inactivo y lo guarda en el archivo
* \param baja(int) seria el id
*
**********************************************************************************/
void modificaBajaConsumo(int baja)
{
    stConsumos c;
    FILE *pArchConsumo=fopen(AR_CONSUMO,"r+b");
    int pasaje=0;
    int flag =-1;
    int i=0;
    if(pArchConsumo!=NULL)
    {
        while(flag==-1 && fread(&c,sizeof(stConsumos),1,pArchConsumo)>0)
        {


            if(c.nroConsumo==baja)
            {
                flag=i;
            }
            i++;
        }
        if(flag!=-1)
        {
            printf("\nEl Nro de Consumo %d",baja);
            if(c.baja==0)
            {
                printf("\n****Consumo Activo**** \n");
            }
            else
            {
                printf("\n****Consumo Inactivo**** \n");
            }
            printf("\nPresione [1] para Desactivar y [0] Para activar: ");
            scanf("%d", &pasaje);

            if(pasaje==1)
            {
                c.baja=1;
                fseek(pArchConsumo,sizeof(stConsumos)*(i-1),SEEK_SET);
                if(fwrite(&c,sizeof(stConsumos),1,pArchConsumo)==1)
                {
                    printf("El Consumo se actualizo Correctamente!!\n");
                    color(4);
                    muestraUnConusmo(c);
                    color(7);
                    system("pause");
                    fclose(pArchConsumo);
                }
            }
            else
            {
                c.baja=0;
                fseek(pArchConsumo,sizeof(stConsumos)*(i-1),SEEK_SET);
                if(fwrite(&c,sizeof(stConsumos),1,pArchConsumo)==1)
                {
                    printf("El Consumo se actualizo Correctamente!!\n");
                    muestraUnConusmo(c);
                    system("pause");
                    fclose(pArchConsumo);
                }
            }
        }
        else
        {
            printf("No se encuentra Nro de Cliente \n");
        }

    }
    else
    {
        exit(1);
    }

}


/************************************************************************//********
*
* \brief funcion que modificar la fecha de consumo
* \param nro de consumo
* \param anio
* \param mes
* \param dia
*
**********************************************************************************/
void modificaFechaCOnsumo(int nroConsumo, int anio, int mes, int dia)
{
    stConsumos consu;
    int flag=-1;
    int i=0;

    FILE *pArchConsumos = fopen(AR_CONSUMO,"r+b");
    if(pArchConsumos)
    {
        while(flag==-1 && fread(&consu,sizeof(stConsumos),1,pArchConsumos)>0)
        {
            if(consu.nroConsumo==nroConsumo)
            {
                flag=i;
            }
            i++;
        }


        if(flag!=-1)
        {

            printf("\nIngrese el anio del consumo....");
            scanf("%d",&anio);

            do
            {
                printf("\nIngrese el mes del consumo.....");
                scanf("%d",&mes);

            }
            while(mes<1 || mes>12);
            if ( mes >= 1 && mes <= 12 )
            {
                switch ( mes )
                {
                case  1 :
                case  3 :
                case  5 :
                case  7 :
                case  8 :
                case 10 :
                case 12 :
                    do
                    {
                        printf("\nIngrese el dia del Consumo.....");
                        scanf("%d",&dia);
                    }
                    while(dia<=1 && dia>=31);
                    break;

                case  4 :
                case  6 :
                case  9 :
                case 11 :
                    do
                    {
                        printf("\nIngrese el dia del Consumo.....");
                        scanf("%d",&dia);
                    }
                    while(dia<=1 && dia>=30);
                    break;

                case  2 :
                    if( anio % 4 == 0 && anio % 100 != 0 || anio % 400 == 0 )
                    {
                        if ( dia >= 1 && dia <= 29 )
                        {
                            do
                            {
                                printf("\nIngrese el dia del Consumo.....");
                                scanf("%d",&dia);
                            }
                            while(dia<=1 && dia>=29);
                        }
                        else
                        {
                            do
                            {
                                printf("\nIngrese el dia del Consumo.....");
                                scanf("%d",&dia);
                            }
                            while(dia<=1 && dia>=28);


                        }
                    }
                }
            }
            consu.anio=anio;
            consu.mes=mes;
            consu.dia=dia;
            fseek(pArchConsumos,sizeof(stConsumos)*(i-1),SEEK_SET);
            if(fwrite(&consu,sizeof(stConsumos),1,pArchConsumos)==1)
            {
                printf("El Cliente se actualizo Correctamente!!\n");
                muestraUnConusmo(consu);
                system("pause");
                fclose(pArchConsumos);
            }
        }/// fin if flag !=1
        else
        {
            printf("Consumo No Registrado...");
            system("pause");
        }
        fclose(pArchConsumos);
    }
}


/************************************************************************//********
*
* \brief funcion que modificar el consumo en mb
* \param nro de consumo
* \param consumo nuevo
*
**********************************************************************************/
void modificaConsumosMB(int nroConsumo, int nuevoConsumo)
{
    stConsumos c;
    FILE *pArchConsumo=fopen(AR_CONSUMO,"r+b");
    int flag =-1;
    int i=0;

    if(pArchConsumo)
    {
        while(flag==-1 && fread(&c,sizeof(stConsumos),1,pArchConsumo)>0)
        {
            if(c.nroConsumo==nroConsumo)
            {
                flag=i;
            }
            i++;
        }

        c.datosConsumidos=nuevoConsumo;
        fseek(pArchConsumo,sizeof(stConsumos)*(i-1),SEEK_SET);
        if(fwrite(&c,sizeof(stConsumos),1,pArchConsumo)==1)
        {
            printf("El Cliente se actualizo Correctamente!!\n");
            muestraUnConusmo(c);
            system("pause");
            fclose(pArchConsumo);
        }
        fclose(pArchConsumo);
    }
}


/************************************************************************//********
*
* \brief funcion que pasa los consumos a una matriz de estructura
* \param dia
* \param mes
* \param estructura Consumo
* \param validos consumos
* \param arreglo cuenta los meses que levan datos
* \param validos
* \return validos
*
**********************************************************************************/
int archivoaMatrizConsumo (int dia,int mes,stConsumos consu[dia][mes],int cuenta[],int vCuenta)
{
    stConsumos c;

    FILE * pArch = fopen(AR_CONSUMO,"rb");

    if(pArch)
    {
        while(fread(&c,sizeof(stConsumos),1,pArch)>0)
        {

            for(int mes=1; mes<13; mes++)
            {
                for(int dias=1; dias<32; dias++)
                {
                    if(c.dia==dias&&c.mes==mes)
                    {

                        consu[dias][mes]=c;
                        cuenta[vCuenta]++;


                    }
                }
                vCuenta++;
            }
        }
        fclose(pArch);
    }
    return vCuenta;
}


/************************************************************************//********
*
* \brief funcion que cuenta el total de datos consumidos hasta la fecha
* \param dia
* \param mes
* \param estructura Consumo
* \param validos consumos
* \return total de datos consumidos
*
**********************************************************************************/
int datosConsumidosTotal (int dia, int mes, stConsumos mConsumos [dia][mes],int vConsumidos,int id)
{
    stConsumos c;
    FILE *pArch =fopen(AR_CONSUMO,"rb");
    int consumoTotal = 0;
    if(pArch)
    {
        while(fread(&c,sizeof(stConsumos),1,pArch)>0)
        {



            for(int mes=1; mes<13; mes++)
            {
                for(int dias=1; dias<32; dias++)
                {
                    if(c.idCliente == id && c.dia==dias&&c.mes==mes  )
                    {

                        mConsumos[dias][mes]=c;
                        consumoTotal+=mConsumos[dias][mes].datosConsumidos;

                    }
                }

            }

        }
        fclose(pArch);
    }
    return consumoTotal;
}


/************************************************************************//********
*
* \brief funcion que muestra todos los consumos de un cliente
* \param dia
* \param mes
* \param estructura Consumo
* \param arreglo cuenta los meses que llevan datos
* \param validos
*
**********************************************************************************/
void muestraTotalConsumos (int dias,int mes,stConsumos consu[dias][mes],int cuenta[],int vCuenta)
{

    for(int i=1; i<13; i++)
    {

        for(int j=1; j<31; j++)
        {
            if(consu[j][i].dia==j&&consu[j][i].mes==i)
            {
                printf("Mes %d /",i);
                muestraUnConusmo(consu[j][i]);
            }
        }
    }
}


/************************************************************************//********
*
* \brief funcion que muestra los consumos x mes de un cliente
* \param dia
* \param mes
* \param matriz de consumos
* \param arreglo cuenta los meses que llevan datos
* \param validos
*
**********************************************************************************/
void muestraConsumoxMes (int dias,int mes,stConsumos consu[dias][mes],int cuenta[],int vCuenta)
{

    for(int j=1; j<31; j++)
    {
        if(consu[j][mes].dia==j && consu[j][mes].mes==mes)
        {
            printf("Mes %d /",mes);
            muestraUnConusmo(consu[j][mes]);
        }
    }
}

/************************************************************************//**
*
* \brief funcion que pasa los consumos de un mes en particular del archivo a un arreglo
* \param Arreglo de consumos
* \param validos
* \param int dato ( mes )
* \return validos cargados del archivo al arreglo
*
***************************************************************************/

int arch2ArrayConsumoMes(stConsumos a[], int v, int mes)
{
    stConsumos c;
    FILE *pArchConsumo = fopen(AR_CONSUMO,"rb");
    if(pArchConsumo)
    {
        while(fread(&c,sizeof(stConsumos),1,pArchConsumo)>0)
        {

            if(c.mes == mes )
            {

                a[v]=c;
                v++;
            }

        }
        fclose(pArchConsumo);
    }
    return v;
}

/************************************************************************//**
*
* \brief funcion que pasa los consumos de un mes y dia en particular del archivo a un arreglo
* \param Arreglo de consumos
* \param validos
* \param int dato ( mes )
* \param int dato ( dia )
* \return validos cargados del archivo al arreglo
*
***************************************************************************/

int arch2ArrayConsumoDiario(stConsumos a[], int v, int mes, int dia )
{
    stConsumos c;
    FILE *pArchConsumo = fopen(AR_CONSUMO,"rb");
    if(pArchConsumo)
    {
        while(fread(&c,sizeof(stConsumos),1,pArchConsumo)>0)
        {

            if(c.mes == mes && c.dia == dia)
            {

                a[v]=c;
                v++;
            }

        }
        fclose(pArchConsumo);
    }
    return v;
}

/************************************************************************//**
*
* \brief funcion que recorre el archivo y cuenta los datos consumidos en un determinado mes
* \param dato entero ( mes )
* \return datos consumidos
*
***************************************************************************/

int datosConsumidosMensual(int mes, int id )
{
    stConsumos c;
    int datosMensual=0;
    FILE *pArchConsumo = fopen(AR_CONSUMO,"rb");
    if(pArchConsumo)
    {
        while(fread(&c,sizeof(stConsumos),1,pArchConsumo)>0)
        {

            if(c.idCliente == id && c.mes == mes && c.baja == 0 )
            {
                datosMensual=datosMensual+c.datosConsumidos;
            }

        }
        fclose(pArchConsumo);
    }
    return datosMensual;
}


/************************************************************************//**
*
* \brief funcion que recorre el archivo y cuenta los datos consumidos en un determinado dia
* \param int dato ( mes )
* \param int dato ( dia )
* \return datos consumidos
*
***************************************************************************/

int datosConsumidosDiarios(int mes,int dia,int id )
{
    stConsumos c;
    int datosDiarios=0;
    FILE *pArchConsumo = fopen(AR_CONSUMO,"rb");
    if(pArchConsumo)
    {

        while(fread(&c,sizeof(stConsumos),1,pArchConsumo)>0)
        {

            if( c.mes == mes && c.dia == dia && c.baja == 0 && c.idCliente == id  )
            {
                datosDiarios=datosDiarios+c.datosConsumidos;
            }

        }
        fclose(pArchConsumo);
    }
    return datosDiarios;
}





