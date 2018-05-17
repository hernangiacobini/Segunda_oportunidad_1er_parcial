#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "abm_aviso.h"
#include "abm_cliente.h"

#define TOPE_CLIENTES 100
#define TOPE_AVISOS 1000

/**
 * \brief Realiza el alta del cliente
 * \param clientes array de estructura tbl_cliente
 * \param tope maximo de clientes
 * \return 0 si consiguio el String -1 si no
 *
 */

int alta_cliente(tbl_cliente* clientes, int tope)
{
    int i;
    int auxID;
    char auxNombre[15];
    char auxApellido[20];
    float auxCuit;
    int retorno=-1;

    for(i=0;i<tope;i++)
    {
        if(clientes[i].isEmpty==1)
        {
            retorno=-2;
            if(getValidString("\nEscriba su nombre:\n","No valido","Debe ingresar un maximo de 15 caracteres",auxNombre,15,3)==0)
            {
                strcpy(clientes[i].nombre_cli,auxNombre);
                retorno=-3;
                if(getValidString("\nEscriba su apellido:\n","No valido","Debe ingresar un maximo de 20 caracteres",auxApellido,20,3)==0)
                {
                    strcpy(clientes[i].apellido_cli,auxApellido);
                    retorno=-4;
                    if(getValidFloat("\nEscriba su CUIT (sin guiones):\n","No valido",&auxCuit,1,99999999999,3)==0)
                    {
                        clientes[i].CUIT=auxCuit;

                        auxID=proximoIdCliente();
                        clientes[i].idCliente=auxID;
                        clientes[i].isEmpty=0;
                        clientes[i].avisosActivos=0;
                        clientes[i].avisosPausados=0;
                        retorno=0;
                        break;
                    }
                }
            }

        }
    }
    switch(retorno)
    {
    case 0:
        printf("ID generado: %d\n\n",auxID);
        break;
    case -1:
        printf("Todas las posiciones estan ocupadas");
        break;
    case -2:
        printf("Nombre no valido");
        break;
    case -3:
        printf("Apellido no valido");
        break;
    case -4:
        printf("CUIT no valido");
        break;
    }
    return retorno;
}

/**
 * \brief Modifica los datos del cliente
 * \param clientes array de estructura tbl_cliente
 * \param tope maximo de clientes
 * \return 0 si consiguio el String -1 si no
 *
 */
int modifica_cliente(tbl_cliente* clientes, int tope, int auxIdCli)
{
    int i;
    char auxNombre[15];
    char auxApellido[20];
    float auxCuit;
    int retorno=-1;

    for(i=0;i<tope;i++)
    {
        if(auxIdCli==clientes[i].idCliente && clientes[i].isEmpty==0)
        {
            if(getValidString("\nEscriba su nombre:\n","No valido","Debe ingresar un maximo de 15 caracteres",auxNombre,15,3)==0)
            {
                strcpy(clientes[i].nombre_cli,auxNombre);
                if(getValidString("\nEscriba su apellido:\n","No valido","Debe ingresar un maximo de 20 caracteres",auxApellido,20,3)==0)
                {
                    strcpy(clientes[i].apellido_cli,auxApellido);
                    if(getValidFloat("\nEscriba su CUIT (sin guiones):\n","No valido",&auxCuit,1,99999999999,3)==0)
                    {
                        clientes[i].CUIT=auxCuit;
                    }
                }
            }
            retorno=0;
            break;
        }
    }

    return retorno;
}

int baja_cliente(tbl_cliente* clientes, int tope, int auxIdCli)
{
    int i;
    int retorno=-1;

    for(i=0;i<tope;i++)
    {
        if((clientes[i].isEmpty==0) && clientes[i].idCliente==auxIdCli)
        {
            clientes[i].isEmpty=1;
            retorno=0;
        }
    }
    return retorno;
}

int proximoIdCliente(void)
{
    static int id=-1;

    id++;
    return id;
}


int inicializar_clientes(tbl_cliente* clientes, int tope)
{
    int retorno = -1;
    int i;
    if(tope > 0 && clientes != NULL)
    {
        retorno = 0;
        for(i=0;i<tope;i++)
        {
            clientes[i].isEmpty=1;
            clientes[i].avisosActivos=0;
            clientes[i].avisosPausados=0;
        }
    }
    return retorno;
}


int buscaCliente(tbl_cliente* clientes, int tope, int idCliente)
{
    int i;
    int retorno=-1;

    for(i=0;i<tope;i++)
    {
        if(clientes[i].idCliente==idCliente)
        {
            retorno=i;
            break;
        }
    }
    return retorno;
}


int imprimir_clientes(tbl_cliente* clientes, int tope, int auxCli)
{
    int i;

    for(i=0;i<tope;i++)
    {
        if(clientes[i].isEmpty==0)
        {
            if(auxCli==-1)
            {
                printf("ID cliente [%d] \nNombre: %s \nApellido: %s \nCUIT: %.0f\nAvisos activos: %d\n-----------------------------\n",
                clientes[i].idCliente,clientes[i].nombre_cli,clientes[i].apellido_cli,clientes[i].CUIT,clientes[i].avisosActivos);

            }
            else
            {
                printf("ID cliente [%d] \nNombre: %s \nApellido: %s \nCUIT: %.0f\n-----------------------------",
                clientes[auxCli].idCliente,clientes[auxCli].nombre_cli,clientes[auxCli].apellido_cli,clientes[auxCli].CUIT);
                break;
            }

        }
    }

    return 0;
}
