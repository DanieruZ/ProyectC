#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "gotoxy.h"
#include <stdbool.h>


#define DIM_CLI 10000
#define ESC 27
#define arCliente "clientes.dat"
#define arConsumo "consumo.dat"

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
    int idCliente;
    int anio;
    int mes; /// 1 a 12
    int dia; /// 1 a … dependiendo del mes
    int datosConsumidos;  /// expresados en mb.
    int baja; /// 0 si está activo - 1 si está eliminado
} stConsumos;

//******** PROTOTIPADO DE ACCESORIOS
void printtest();

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

//******** PROTOTIPADO DE FUNCIONES DE CARGAS
stCliente cargaUnCliente();
void cargaClienteArchivo ();

//******** PROTOTIPADO DE MUESTRA
void muestraUnCliente(stCliente c);/// modificar para gotoxy;
void muestraClienteArchivo();
void muestraClienteArchivoActivo();
void muestraClienteArchivoBaja();

//******** PROTOTIPADO PERSISTENCIA EN ARCHIVO
void guardaClienteArchivo (stCliente c);

//******** PROTOTIPADO FUNCIONES COMPLEMENTARIAS DE ARCHIVO
int buscaUltimoId();  /// BUSCA EL ULTIMO ID CARGADO EN EL ARCHIVO.

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









int main()
{
    stCliente c,consulta,modifica;


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
                        switch(opcionMuestraCli)
                        {
                        case 1:
                            muestraClienteArchivo();
                            system("pause");
                            break;

                        case 2:
                            muestraClienteArchivoActivo();
                            system("pause");
                            break;

                        case 3:
                            muestraClienteArchivoBaja();
                            system("pause");
                            break;


                        }



                    }
                    while(opcionMuestraCli!=0);
                    system("pause");
                    break;


                }


            }
            while(opcionCli!=0);
            break;

        case 2:
            do
            {
                system("cls");
                submenuCli ();
                color(9);
                printf("Opcion: ");
                color(7);
                scanf("%d",&opcionConsu);
                system("cls");


                switch(opcionConsu)
                {



                case 1:
                    printf("\n Submenu de alta");
                    break;

                case 2:
                    printf("\n Submenu de Baja");
                    break;


                case 3:
                    printf("\n Submenu de Modificacion");

                    break;


                case 4:
                    printf("\n Submenu de Consulta");

                    break;


                case 5:
                    printf("\n Submenu de Listado");
                    break;


                }
            }
            while(opcionConsu!=0);
            break;
        }
        system("pause");

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
    gotoxy(30,10);
    printf("0-Salir");
    gotoxy(45,10);
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

void submenuMuestra()
{

    color(3);
    gotoxy(35,3);
    printf("Submenu de Listado");
    color(7);
    gotoxy(30,5);
    printf("[1].- Muestra listado completo");
    gotoxy(30,6);
    printf("[2].- Muestra listado de clientes de alta");
    gotoxy(30,7);
    printf("[3].- Muestra listado de clientes de baja");
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
    FILE *pArchCliente = fopen(arCliente,"ab");
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
    printf("\n  -----------------------------------------------------------------");
    printf("\n  ID......................: %d", c.id);
    printf("\n  Nro de Cliente..........: %d", c.nroCliente);
    printf("\n  Nombre..................: %s", c.nombre);
    printf("\n  Apellido................: %s", c.apellido);
    printf("\n  DNI.....................: %d", c.dni);
    printf("\n  EMail...................: %s", c.email);
    printf("\n  Calle...................: %s", c.domicilio);
    printf("\n  Nro de Celular..........: %s", c.movil);
    printf("\n  Baja s/n................: %s", (c.baja)?"SI":"NO");

}



/************************************************************************//**
*
* \brief funcion que muestra un cliente del archivo
*
***************************************************************************/
void muestraClienteArchivo()
{
    stCliente c;
    FILE *pArchCliente = fopen(arCliente,"rb");
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
    FILE *pArchCliente = fopen(arCliente,"rb");
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
* \brief funcion que muestra Los clientes activos del archivo
*
***************************************************************************/
void muestraClienteArchivoActivo()
{
    stCliente c;
    FILE *pArchCliente = fopen(arCliente,"rb");
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
    FILE *pArchCliente = fopen(arCliente,"rb");
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
* \brief funcion que busca un cliente en el archivo por apellido
* \param apellido (char)
* \return cliente Si lo encuentra devuelve el Id correspondiente, si no el Id=-1
*
***************************************************************************/
stCliente buscaUnClienteApellidoArchivo(char apellido[])
{
    stCliente c;
    int flag=0;
    FILE *pArchCliente = fopen(arCliente,"rb");
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
    FILE *pArchCliente = fopen(arCliente,"rb");
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
    FILE *pArchCliente = fopen(arCliente,"rb");
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
    FILE *pArchCliente = fopen(arCliente,"rb");
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
    FILE *pArchCliente = fopen(arCliente,"rb");
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
    FILE *pArchCliente = fopen(arCliente,"rb");
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
    FILE *pArchCliente = fopen(arCliente,"rb");
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
    FILE *pArchCliente = fopen(arCliente,"rb");
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
    FILE *pArchCliente=fopen(arCliente,"r+b");
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
    FILE *pArchCliente=fopen(arCliente,"r+b");
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
    FILE *pArchCliente=fopen(arCliente,"r+b");
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
    FILE *pArchCliente=fopen(arCliente,"r+b");
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
    FILE *pArchCliente=fopen(arCliente,"r+b");
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
    FILE *pArchCliente=fopen(arCliente,"r+b");
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
    FILE *pArchCliente=fopen(arCliente,"r+b");
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
    FILE *pArchCliente=fopen(arCliente,"r+b");
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



