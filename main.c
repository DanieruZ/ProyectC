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
    char movil[10];   /// se modifico para que se puedan ingresar numeros de telefonos mas largos
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

//******** PROTOTIPADO DE ERRORES
void mensajeEmailError (int dato);


//******** PROTITPADO DE VALIDACION
int validaEmail(char email[]);

//******** PRTOTIPADO DE MENU
void menuppal ();
void submenuCli ();
void submenuConsu();
void submenuConsultasCli ();
void submenuModificaCli ();
void submenuMuestra();
void submenuMuestraConsumos();
void submenuModificacionConsu();

//******** PROTOTIPADO DE FUNCIONES DE CARGAS
stCliente cargaUnCliente();
void cargaClienteArchivo ();

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
void modificaClienteNombre(int id,char nombre[]);
void modificaClienteApellido(int id,char apellido[]);
void modificaClienteDni(int id, int dni);
void modificaClienteEmail(int id, char email [ ]);
void modificaClienteDomicilio(int id, char domicilio [ ]);
void modificaClienteMovil(int id, char movil [ ]);
void modificaBajaCliente(int baja);

//******** PROTOTIPADO FUNCIONES CARGA CLIENTE ALEATORIO
int randomRango(int min, int max);
int getNroMatricula();
void getNombre(char n[]);
void getApellido(char a[]);
int getDNI();
void getMovil(char movil[]);
void getCalle(char c[]);
void getEmail(char nombre[],char apellido[],char email[]);
stCliente cargoClientesRandom();
int cargaClientesAleatorios( stCliente a[],int v,int dim,int clientesDeseados);
void Array2Archivo(stCliente a[],int v);

//******** PROTOTIPADO FUNCIONES CARGA CONSUMO
stConsumos cargaUnConsumo();
void cargaConsumoArchivo (int idCliente);

//******** PROTOTIPADO FUNCIONES MUESTRA CONSUMO
void muestraUnConusmo(stConsumos consu);
void muestraConsumoArchivo();
void muestraConsumosArreglo(stConsumos a[],int v);


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














int main()
{
    srand(time(NULL));
    stCliente c,consulta,modifica;
    stConsumos consumo;


    ///****  varibles de los switch *****///
    int opcionPpal=0;
    int opcionCli=0;
    int opcionConsu=0;





    ///***   Varibles usadas en los llamados de las funciones   ***///
    int opcionConsultaCli=0;
    int opcionModificaCli=0;
    int opcionMuestraCli=0;

    printtest(); /// MENSAJE DE INICIO
    Sleep(1500); /// el tiempo que demora el mensaje en pantalla
    int nroConsulta;

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
    char movilModifica[45];
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


    do
    {
        color(7);
        system("cls");
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
                    printf("\n Submenu de alta");
                    cargaClienteArchivo();


                    break;

                case 2:
                    printf("\n Menu Baja Cliente ");
                    printf("\n Ingrese el Nro de Cliente ");
                    scanf("%d",&nroConsulta);
                    modificaBajaCliente(nroConsulta);


                    system("pause");


                    break;


                case 3:
                    printf("\n Submenu de Modificacion");
                    gotoxy(30,3);
                    printf("<<<MODIFICACIONES>>>");
                    gotoxy(10,3);
                    printf("Ingrese el ID del cliente que desee modificar: ");///usamos id
                    scanf("%d",&idModifica);
                    modifica=buscaUnClienteIdArchivo(idModifica);
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
                                printf("El actual Nombre es %s.Ingrese el nuevo Nombre :",modifica.nombre);
                                fflush(stdin);
                                gets(nombreModifica);
                                modificaClienteNombre(idModifica,nombreModifica);
                                system("pause");


                                break;

                            case 2:
                                printf("El actual Apellido es %s.Ingrese el nuevo Apellido :",modifica.apellido);
                                fflush(stdin);
                                gets(apellidoModifica);
                                modificaClienteApellido(idModifica,apellidoModifica);
                                system("pause");


                                break;

                            case 3:
                                printf("El actual Dni es %d.Ingrese el nuevo Dni :",modifica.dni);
                                scanf("%d",&dniModifica);
                                modificaClienteDni(idModifica,dniModifica);
                                system("pause");


                                break;

                            case 4:
                                while(varEmail==0) /// Ciclo que lo usamos para que ingrese un email valido al modificar el campo de email.
                                {
                                    system("cls");
                                    printf("El actual Email es %s.Ingrese el nuevo Email :",modifica.email);
                                    fflush(stdin);
                                    gets(emailModifica);
                                    varEmail= validaEmail(emailModifica);
                                    mensajeEmailError(varEmail);
                                    system("pause");
                                    system("cls");
                                }
                                modificaClienteEmail(idModifica,emailModifica);
                                system("pause");


                                break;

                            case 5:
                                printf("El actual Domicilio es %s.Ingrese el nuevo Domicilio :",modifica.domicilio);
                                fflush(stdin);
                                gets(domicilioModifica);
                                modificaClienteDomicilio(idModifica,domicilioModifica);
                                system("pause");


                                break;

                            case 6:
                                printf("El actual Movil es %s.Ingrese el nuevo Movil :",modifica.movil);
                                fflush(stdin);
                                gets(movilModifica);
                                modificaClienteMovil(idModifica,movilModifica);
                                system("pause");


                                break;
                            default:

                                printf("\nOpcion NO Valida...");
                                break;

                            }



                        }
                        while(opcionModificaCli!=0);
                    }
                    else
                    {
                        printf("No se encuentra un cliente con el id %d",idModifica);
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
                        switch(opcionConsultaCli)
                        {
                        case 1:
                            printf("Ingrese el nro de cliente :");
                            scanf("%d",&nroConsulta);
                            consulta=buscaUnClienteNroClienteArchivo(nroConsulta);
                            if(consulta.id!=-1)
                            {
                                muestraUnCliente(consulta);
                            }
                            else
                            {
                                printf("No se encuentra un cliente con el numero de cliente %d ",nroConsulta);
                            }
                            system("pause");
                            break;

                        case 2:

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
                                printf("No se encuentra un cliente con el nombre %s ",nombreConsu);
                            }
                            system("pause");
                            break;

                        case 3:

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
                                printf("No se encuentra un cliente con el apellido %s ",apellidoConsu);
                            }
                            system("pause");
                            break;

                        case 4:

                            printf("Ingrese el dni de cliente :");
                            scanf("%d",&dniConsu);
                            consulta=buscaUnClienteDniArchivo(dniConsu);
                            if(consulta.id!=-1)
                            {
                                muestraUnCliente(consulta);
                            }
                            else
                            {
                                printf("No se encuentra un cliente con el dni  %d ",dniConsu);
                            }
                            system("pause");
                            break;

                        case 5:

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
                                printf("No se encuentra un cliente con el email %s ",emailConsu);
                            }
                            system("pause");
                            break;

                        case 6:

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
                                printf("No se encuentra un cliente con el domicilio %s ",domicilioConsu);
                            }
                            system("pause");
                            break;

                        case 7:

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
                                printf("No se encuentra un cliente con el movil %s ",movilConsu);
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
                            vCliMuestra = arch2ArrayClienteArchivo(cliMuestra,vCliMuestra);
                            ordenaSeleccionNombre(cliMuestra,vCliMuestra);
                            muestraClientesArreglo(cliMuestra,vCliMuestra);

                            system("pause");
                            break;

                        case 2:
                            vCliMuestra= arch2ArrayClienteArchivoActivo(cliMuestra,vCliMuestra);
                            ordenaSeleccionNombre(cliMuestra,vCliMuestra);
                            muestraClientesArreglo(cliMuestra,vCliMuestra);

                            system("pause");
                            break;

                        case 3:
                            vCliMuestra=arch2ArrayClienteArchivoBaja(cliMuestra,vCliMuestra);
                            ordenaSeleccionNombre(cliMuestra,vCliMuestra);
                            muestraClientesArreglo(cliMuestra,vCliMuestra);
                            system("pause");
                            break;


                        }



                    }
                    while(opcionMuestraCli!=0);
                    system("pause");
                    break;
                    /**
                        case 6:
                            vCliMuestra=0;
                            printf("Ingrese la cantidad de clientes que desee crear\n");
                            scanf("%d",&CliDeseados);
                            vCliMuestra=cargaClientesAleatorios(cliMuestra,vCliMuestra,DIM_CLI,CliDeseados);
                            Array2Archivo(cliMuestra,vCliMuestra);
                            break;**/
                }


            }
            while(opcionCli!=0);
            break;

        case 2:
            color(9);
            gotoxy(30,3);
            printf("Sistema de Ingreso a Consumos");
            color(7);

            while(opcionIngresoCOnsu != 0)
            {

                gotoxy(10,6);
                printf("Ingrese el Nro de Cliente: ");
                scanf("%d",&c.nroCliente);
                c=buscaUnClienteNroClienteArchivo(c.nroCliente);
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
                    cargaConsumoArchivo(c.id);

                    break;

                case 2:
                    vConsu=arch2ArrayConsumoArchivoActivo(muestraConsu,vConsu,c.id);
                    muestraConsumosArreglo(muestraConsu,vConsu);
                    printf("Ingrese el Nro de Consumo a Eliminar: ");
                    scanf("%d",&consumo.nroConsumo);
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
                            muestraConsumosArreglo(muestraConsu,vConsu);
                            printf("Ingrese el Nro de Consumo a Modificar la Fecha: ");
                            scanf("%d",&consumo.nroConsumo);
                            printf("\n%d Nro consumo",consumo.nroConsumo);
                            system("pause");
                            modificaFechaCOnsumo(consumo.nroConsumo,consumo.anio,consumo.mes,consumo.dia);
                            break;


                        case 2:
                            vConsu=arch2ArrayConsumoArchivoActivo(muestraConsu,vConsu,c.id);
                            muestraConsumosArreglo(muestraConsu,vConsu);
                            printf("Ingrese el Nro de Consumo a Modificar la Fecha: ");
                            scanf("%d",&consumo.nroConsumo);
                            printf("Ingrese los nuevos Mb");
                            scanf("%d",&consumo.datosConsumidos);
                            modificaConsumosMB(consumo.nroConsumo,consumo.datosConsumidos);

                            break;
                        }




                    }
                    while(opcionSubMenuModifica !=0);

                    break;


                case 4:
                    printf("\n Submenu de Consulta");

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
                            muestraConsumosArreglo(muestraConsu,vConsu);

                            system("pause");
                            break;

                        case 2:
                            vConsu=arch2ArrayConsumoArchivoActivo(muestraConsu,vConsu,c.id);
                            muestraConsumosArreglo(muestraConsu,vConsu);

                            system("pause");
                            break;

                        case 3:
                            vConsu=arch2ArrayConsumoArchivoBaja(muestraConsu,vConsu,c.id);
                            muestraConsumosArreglo(muestraConsu,vConsu);

                            system("pause");
                            break;


                        }



                    }
                    while(opcionMuestraConsu!=0);

                    system("pause");
                    break;


                }
            }
            while(opcionConsu!=0);
            break;
        }
        // system("pause");

    }
    while(opcionPpal!=0);










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
* \brief funcion que muestra el Submenu de clientes y sus opcones
*
***************************************************************************/
void submenuCli ()
{
    color(3);
    gotoxy(35,3);
    printf("  Menu Cliente: ");
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
    printf("[5].- Listado Clientes");
    ///gotoxy(30,10);
    ///printf("[6].- Crea clientes aleatorios");
    gotoxy(30,11);
    printf("0-Salir");
    gotoxy(45,11);
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
    color(3);
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

/************************************************************************//**
*
* \brief funcion que Carga un cliente
* \return Retorna un cliente
*
***************************************************************************/
stCliente cargaUnCliente()
{
    stCliente c;

    do
    {
        gotoxy(3,3);
        printf("Ingrese el nro de Cliente..........: ");
        scanf("%d",&c.nroCliente);


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
        mensajeEmailError(!validaEmail(c.email));
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
        printf("Sistema de Alta de Clientes...");
        c=cargaUnCliente();
        c.id=buscaUltimoId()+1;
        guardaClienteArchivo(c);
        printf("\nUltimo ID %d",c.id);
        system("pause");
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
    printf("\n  --------------------------------------------");
    printf("\n  ID......................: %d", c.id);
    printf("\n  Nro de Cliente..........: %d", c.nroCliente);
    printf("\n  Nombre..................: %s", c.nombre);
    printf("\n  Apellido................: %s", c.apellido);
    printf("\n  DNI.....................: %d", c.dni);
    printf("\n  EMail...................: %s", c.email);
    printf("\n  Calle...................: %s", c.domicilio);
    printf("\n  Nro de Celular..........: %s", c.movil);
    printf("\n  Baja s/n................: %s", (c.baja)?"SI":"NO");
    printf("\n  --------------------------------------------");
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
        gotoxy(3,13);
        printf("Ingresar Un Email Valido..");
    }
}



/************************************************************************//**
*
* \brief funcion que valida un email, fijandose si contiene un @
* \param un string
* \return flag donde 0 si es incorrecto y 1 si es correcto
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
void modificaClienteNombre(int id,char nombre[])
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
void modificaClienteApellido(int id,char apellido[])
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
void modificaClienteDni(int id, int dni)
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
void modificaClienteEmail(int id, char email [ ])
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
void modificaClienteDomicilio(int id, char domicilio [ ])
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
void modificaClienteMovil(int id, char movil [ ])
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

        strcpy(c.movil,movil);
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
            }
            else
            {
                printf("\n****Cliente Inactivo**** \n");
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


int randomRango(int min, int max)
{
    return rand()%(max-min)+min;
}



int getNroMatricula()
{
    return randomRango(1,10000);
}

/*************************************************************//**
*
* \brief Funcion que asigna al string recibido un nombre al azar
* \return void
*
*****************************************************************/
void getNombre(char n[])
{
    char nombres[][30] = {"Ailin","Juan","Jeremias","Daniel","Fernando","Lautaro","Mailen","Jose",
                          "Anastasio","Arturo","Mario","Tamaro","Adolfo","Pedro","Alfredo","Arnaldo",
                          "Mauro","Benicio","Ildefonso","Cuchuflito","Remilgo","Miguel","Reinaldo"
                         };

    strcpy(n,nombres[randomRango(0,sizeof(nombres)/(sizeof(char)*30))]);
}

void getApellido(char a[])
{
    char apellidos[][30] = {"Gomez","Perez","Roca","Latorre","Fernandez","Torquemada", "Marijuan", "Roca", "Mitre", "Rivadavia",
                            "San Martin", "Alvarez", "Comizo", "Borges", "Zama", "Recato", "Olvido", "Gil", "Trapero", "Restinga",
                            "De Antonio", "Ramirez", "Spinetta", "Cortez", "Gonzalez", "Andujar", "San Juan", "Bautista", "Anchorena", "Paso",
                            "Gaboto","Vega","Vargas","Lloret","Linares","Suarez","Sierra","Amenabar","Blanco","White","Black"
                           };

    strcpy(a,apellidos[randomRango(0,sizeof(apellidos)/(sizeof(char)*30))]);
}

int getDNI()
{
    return randomRango(549,1982)* randomRango(549,19801);
}

void getMovil(char movil[])
{
    for(int i=0; i<9; i++)
    {
        movil[i]=randomRango(48,57);
    }
}


void getCalle(char c[])
{
    char calles[][30] = {"San Juan","Funes","Gaboto","San Martin","Colon","Rivadavia", "Alsina", "Roca", "Mitre", "Belgrano",
                         "Paso", "11 de Septiembre", "3 de Febrero", "Balcarce", "Libertad", "Magallanes", "Irala", "Ayolas", "Moreno", "Brown",
                         "Bolivar", "Alberti", "Gascon", "La Rioja", "Catamarca", "Salta", "Jujuy", "XX de Septiembre", "14 de Julio", "Dorrego",
                         "Hernandarias","Don Orione","Juramento","Lanzilota","Estrada","Tierra del Fuego","Mendoza","Chubut","Rio Negro","Misiones","Edison"
                        };

    strcpy(c,calles[randomRango(0,sizeof(calles)/(sizeof(char)*30))]);
}

void getEmail(char nombre[],char apellido[],char email[])
{
    email=strcat(strcat(nombre,64),apellido);
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
    getEmail(c.nombre,c.apellido,c.email);
    getMovil(c.movil);
    return c;
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
    printf("Ingrese el anio del consumo....");
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
                gotoxy(3,8);
                printf("Ingrese el dia del Consumo.....");
                scanf("%d",&consu.dia);
            }
            while(consu.dia<=1 && consu.dia>=30);
            break;

        case  2 :
            if( consu.anio % 4 == 0 && consu.anio % 100 != 0 || consu.anio % 400 == 0 )
            {
                if ( consu.dia >= 1 && consu.dia <= 29 )
                {
                    do
                    {
                        gotoxy(3,9);
                        printf("\nIngrese el dia del Consumo.....");
                        scanf("%d",&consu.dia);
                    }
                    while(consu.dia<=1 && consu.dia>=29);
                }
                else
                {
                    do
                    {
                        printf("\nIngrese el dia del Consumo.....");
                        scanf("%d",&consu.dia);
                    }
                    while(consu.dia<=1 && consu.dia>=28);
                }
            }
        }
    }
    gotoxy(3,10);
    printf("Ingrese sus consumos en MB.............");
    scanf("%d",&consu.datosConsumidos);
    consu.baja=0;
    consu.nroConsumo=buscaUltimoNroConsumo()+1;
    consu.id=buscaUltimoIdConsumo()+1;


    return consu;
}








stConsumos fechaRandom ()
{
    stConsumos consu;
    consu.anio=2020; // año de consumos...
    consu.mes=randomRango(1,12);

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
* \brief funcion que muestra un consumo
* \param Estrucutura consumo
*
***************************************************************************/
void muestraUnConusmo(stConsumos consu) /// modificar para gotoxy
{
    printf("\n  -----------------------------------------------------------------");
    printf("\n  ID CLIENTE..............: %d", consu.idCliente);
    printf("\n  ID CONSUMO..............: %d", consu.id);
    printf("\n  Nro CONSUMO.............: %d", consu.nroConsumo);
    printf("\n  Anio....................: %d", consu.anio);
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
        printf("Sistema de Alta de Clientes...");
        consu=cargaUnConsumo();
        consu.idCliente=idCliente;
        consu.nroConsumo=buscaUltimoNroConsumo()+1;
        consu.id=buscaUltimoIdConsumo()+1;
        guardaConsumoEnArchivo(consu);
        printf("\nId consumo %d",consu.nroConsumo);
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

            muestraUnConusmo(consu);

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
void muestraConsumosArreglo(stConsumos a[],int v)
{
    int i=0;
    while(i<v)
    {
        muestraUnConusmo(a[i]);
        i++;
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
                    muestraUnConusmo(c);
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
    }
}
