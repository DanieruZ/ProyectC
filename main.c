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


//******** PROTOTIPADO DE FUNCIONES DE CARGAS
stCliente cargaUnCliente();
void cargaClienteArchivo ();

//******** PROTOTIPADO DE MUESTRA
void muestraUnCliente(stCliente c);/// modificar para gotoxy;
void muestraClienteArchivo();

//******** PROTOTIPADO PERSISTENCIA EN ARCHIVO
void guardaClienteArchivo (stCliente c);

//******** PROTOTIPADO FUNCIONES COMPLEMENTARIAS DE ARCHIVO
int buscaUltimoId();  /// BUSCA EL ULTIMO ID CARGADO EN EL ARCHIVO.

//******** PROTOTIPADO FUNCIONES VALIDACION
int validarNumero(char numero[]);



void muestraClienteArchivoActivo();
void muestraClienteArchivoBaja();
stCliente buscaUnClienteApellidoArchivo(char apellido[]);
stCliente buscaUnClienteNombreArchivo(char nombre[]);
stCliente buscaUnClienteDniArchivo(int dni);
stCliente buscaUnClienteEmailArchivo(char email[]);
stCliente buscaUnClienteDomicilioArchivo(char domicilio[]);
stCliente buscaUnClienteNroClienteArchivo(int nroCli);
stCliente buscaUnClienteMovilArchivo(char movil[]);
stCliente modificaNroCliente(stCliente a,int numero);
stCliente modificaNombreCliente(stCliente a,char nombre[]);
stCliente modificaApellidoCliente(stCliente a,char apellido[]);
stCliente modificaDniCliente(stCliente a,int dni);
stCliente modificaEmailCliente(stCliente a,char email[]);///validar previamente el email
stCliente modificaMovilCliente(stCliente a,char movil[]);
stCliente modificaBajaCliente(stCliente a,int baja);






int main()
{
    stCliente c,consulta;

    int opcionPpal=0;
    int opcionCli=0;
    int opcionConsu=0;
    int opcionConsultaCli=0;
    printtest();
    Sleep(1500);
    int nroConsulta;

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
                    printf("\n Submenu de Baja");

                    break;


                case 3:
                    printf("\n Submenu de Modificacion");

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
                         printf("Ingrese el nro de cliente");
                         scanf("%d",&nroConsulta);
                         consulta=buscaUnClienteNroClienteArchivo(nroConsulta);
                         if(consulta.id!=-1){
                            muestraUnCliente(consulta);
                         }
                         else{
                            printf("El numero de cliente %d no se encontro",nroConsulta);
                         }
                         system("pause");
                            break;

                        case 2:

                            break;

                        case 3:

                            break;

                        case 4:

                            break;

                        case 5:

                            break;

                        case 6:

                            break;

                        case 7:

                            break;
                        }



                    }
                    while(opcionConsultaCli!=0);

                    break;


                case 5:
                    printf("\n Submenu de Listado");
                    muestraClienteArchivo();
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

/**
*
* \brief funcion que muestra el Submenu de Consulta del cliente
*
*/
void submenuConsultasCli ()
{
    color(3);
    gotoxy(35,3);
    printf("  Menu Consultas: ");
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
{    stCliente c;
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
* \brief funcion que muestra un cliente
* \param Estrucutura cliente
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
    if(!validaEmail(c.email)== dato)
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





void muestraClienteArchivoActivo()
{
    stCliente c;
    FILE *pArchCliente = fopen(arCliente,"rb");
    if(pArchCliente)
    {
        while(fread(&c,sizeof(stCliente),1,pArchCliente)>0)
        {if(c.baja==0){
            muestraUnCliente(c);}
        }
        printf("\n");
        fclose(pArchCliente);
    }
}

void muestraClienteArchivoBaja()
{
    stCliente c;
    FILE *pArchCliente = fopen(arCliente,"rb");
    if(pArchCliente)
    {
        while(fread(&c,sizeof(stCliente),1,pArchCliente)>0)
        {if(c.baja==1){
            muestraUnCliente(c);}
        }
        printf("\n");
        fclose(pArchCliente);
    }
}


stCliente buscaUnClienteApellidoArchivo(char apellido[]){
    stCliente c;
    int flag=0;
    FILE *pArchCliente = fopen(arCliente,"rb");
    if(pArchCliente){
        while( flag == 0 && fread(&c, sizeof(stCliente), 1, pArchCliente) > 0){
            if(strcmp(c.apellido, apellido) == 0){
                flag=1;
            }
        }
        fclose(pArchCliente);
    }
    if(flag==0){
        c.id=-1;
    }

    return c;
}

stCliente buscaUnClienteNombreArchivo(char nombre[]){
    stCliente c;
    int flag=0;
    FILE *pArchCliente = fopen(arCliente,"rb");
    if(pArchCliente){
        while( flag == 0 && fread(&c, sizeof(stCliente), 1, pArchCliente) > 0){
            if(strcmp(c.nombre, nombre) == 0){
                flag=1;
            }
        }
        fclose(pArchCliente);
    }
    if(flag==0){
        c.id=-1;
    }

    return c;
}

stCliente buscaUnClienteDniArchivo(int dni){
    stCliente c;
    int flag=0;
    FILE *pArchCliente = fopen(arCliente,"rb");
    if(pArchCliente){
        while( flag == 0 && fread(&c, sizeof(stCliente), 1, pArchCliente) > 0){
            if(c.dni==dni){
                flag=1;
            }
        }
        fclose(pArchCliente);
    }
    if(flag==0){
        c.id=-1;
    }

    return c;
}

stCliente buscaUnClienteNroClienteArchivo(int nroCli){
    stCliente c;
    int flag=0;
    FILE *pArchCliente = fopen(arCliente,"rb");
    if(pArchCliente){
        while( flag == 0 && fread(&c, sizeof(stCliente), 1, pArchCliente) > 0){
            if(c.nroCliente==nroCli){
                flag=1;
            }
        }
        fclose(pArchCliente);
    }
    if(flag==0){
        c.id=-1;
    }

    return c;
}

stCliente buscaUnClienteEmailArchivo(char email[]){
    stCliente c;
    int flag=0;
    FILE *pArchCliente = fopen(arCliente,"rb");
    if(pArchCliente){
        while( flag == 0 && fread(&c, sizeof(stCliente), 1, pArchCliente) > 0){
            if(strcmp(c.email,email) == 0){
                flag=1;
            }
        }
        fclose(pArchCliente);
    }
    if(flag==0){
        c.id=-1;
    }

    return c;
}

stCliente buscaUnClienteDomicilioArchivo(char domicilio[]){
    stCliente c;
    int flag=0;
    FILE *pArchCliente = fopen(arCliente,"rb");
    if(pArchCliente){
        while( flag == 0 && fread(&c, sizeof(stCliente), 1, pArchCliente) > 0){
            if(strcmp(c.domicilio,domicilio) == 0){
                flag=1;
            }
        }
        fclose(pArchCliente);
    }
    if(flag==0){
        c.id=-1;
    }

    return c;
}

stCliente buscaUnClienteMovilArchivo(char movil[]){
    stCliente c;
    int flag=0;
    FILE *pArchCliente = fopen(arCliente,"rb");
    if(pArchCliente){
        while( flag == 0 && fread(&c, sizeof(stCliente), 1, pArchCliente) > 0){
            if(strcmp(c.movil,movil) == 0){
                flag=1;
            }
        }
        fclose(pArchCliente);
    }
    if(flag==0){
        c.id=-1;
    }

    return c;
}



/***
------------------------------------------------------------------------------
MODIFICAR CLIENTE
------------------------------------------------------------------------------
***/


///REVISAR

stCliente modificaNroCliente(stCliente a,int numero){
stCliente c=a;
c.nroCliente=numero;
return c;
}

stCliente modificaNombreCliente(stCliente a,char nombre[]){
stCliente c=a;
strcpy(c.nombre,nombre);
return c;
}

stCliente modificaApellidoCliente(stCliente a,char apellido[]){
stCliente c=a;
strcpy(c.apellido,apellido);
return c;
}

stCliente modificaDniCliente(stCliente a,int dni){
stCliente c=a;
c.dni=dni;
return c;
}

stCliente modificaEmailCliente(stCliente a,char email[]){///validar previamente el email
stCliente c=a;
strcpy(c.email,email);
return c;
}

stCliente modificaMovilCliente(stCliente a,char movil[]){
stCliente c=a;
strcpy(c.movil,movil);
return c;
}

stCliente modificaBajaCliente(stCliente a,int baja){
stCliente c=a;
c.baja=baja;
return c;
}
