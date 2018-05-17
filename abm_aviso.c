#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "abm_aviso.h"
#include "abm_cliente.h"

#define TOPE_CLIENTES 100
#define TOPE_AVISOS 1000

/**
 * \brief Solicita un string
 * \param requestMessage Es el mensaje a ser mostrado para solicitar el dato
 * \param errorMessage Es el mensaje a ser mostrado en caso de error de tipo
 * \param errorMessageLenght Es el mensaje a ser mostrado en caso de error de longitud
 * \param input Array donde se cargará el texto ingresado
 * \param maxLenght int Longitud maxima del texto ingresado
 * \param attemps indica la cantidad de reintentos ante un error
 * \return 0 si consiguio el String -1 si no
 *
 */
int alta_aviso(tbl_aviso* avisos, int topeA, tbl_cliente* clientes, int topeC, int auxIdCliente)
{
    int i;
    int auxID;
    int auxRubro;
    char auxtexto[64];
    int retorno=-1;
    int posCliente=-1;

    if(buscaCliente(clientes,topeC,auxIdCliente)>=0)
    {
        posCliente=buscaCliente(clientes,topeC,auxIdCliente);
        for(i=0;i<topeA;i++)
        {
            if(avisos[i].isEmpty==1)
            {
                if(getValidInt("\nEscriba el rubro (1 a 5):\n","No valido",&auxRubro,1,5,99)==0)
                {
                    avisos[i].rubro=auxRubro;
                    if(getValidString("\nEscriba el texto del aviso:\n","No valido","Debe ingresar un maximo de 64 caracteres",auxtexto,64,3)==0)
                    {
                        strcpy(avisos[i].texto,auxtexto);
                        auxID=proximoId();
                        avisos[i].idAviso=auxID;
                        avisos[i].idCliente=auxIdCliente;
                        avisos[i].isEmpty=0;
                        avisos[i].estado=0;
                        clientes[posCliente].avisosActivos+=1;
                        printf("ID aviso %d generado\n\n",auxID);
                        retorno= 0;
                        break;
                    }
                }
            }
        }
    }
    else
    {
        printf("El cliente no esta registrado\n");
    }
    return retorno;
}

int modifica_aviso(tbl_aviso* avisos, int topeA, tbl_cliente* clientes, int topeC, int auxIdAviso, int auxEstado)
{
    int i;
    int retorno=-1;
    int posCliente;

    for(i=0;i<topeA;i++)
    {
         if(auxIdAviso==avisos[i].idAviso && avisos[i].isEmpty==0)
        {
            posCliente=buscaCliente(clientes,topeC,avisos[i].idCliente);
            if(avisos[i].estado==0 && auxEstado==1)
            {
                avisos[i].estado=1;
                clientes[posCliente].avisosActivos-=1;
                clientes[posCliente].avisosPausados+=1;
            }
            else if(avisos[i].estado==1 && auxEstado==0)
            {
                avisos[i].estado=0;
                clientes[posCliente].avisosActivos+=1;
                clientes[posCliente].avisosPausados-=1;
            }
            retorno=0;
            break;
        }

    }

    return retorno;
}


int proximoId(void)
{
    static int id=-1;

    id++;
    return id;
}

int inicializar_avisos(tbl_aviso* avisos, int tope)
{
    int retorno = -1;
    int i;
    if(tope > 0 && avisos != NULL)
    {
        retorno = 0;
        for(i=0;i<tope;i++)
        {
            avisos[i].isEmpty=1;
            avisos[i].estado=-1;
        }
    }
    return retorno;
}

int buscaAviso(tbl_aviso* avisos, int tope, int idAviso)
{
    int i;
    int retorno=-1;

    for(i=0;i<tope;i++)
    {
        if(avisos[i].idAviso==idAviso)
        {
            retorno=i;
            break;
        }
    }
    return retorno;
}

int imprimir_aviso(tbl_aviso* avisos, int topeA, tbl_cliente* clientes, int topeC, int auxCli)
{
    int i;
    int posCliente=-1;
    char auxEstado[7];

    for(i=0;i<topeA;i++)
    {
        if(avisos[i].isEmpty==0)
        {
            if(avisos[i].idCliente==auxCli)
            {
                if(avisos[i].estado==0)
                {
                    strcpy(auxEstado,"Activa");
                }else if(avisos[i].estado==1)
                {
                    strcpy(auxEstado,"Pausada");
                }
                printf("ID aviso [%d] \nRubro: %d \nTexto: %s \nEstado: %s\n-----------------------------\n",
                avisos[i].idAviso,avisos[i].rubro,avisos[i].texto, auxEstado);
            }
            else
            {
                if(auxCli==-1 && avisos[i].estado==0)
                {
                    posCliente=buscaCliente(clientes,topeC,avisos[i].idCliente);
                    printf("ID aviso [%d] \nRubro: %d \nTexto: %s \nCUIT: %.0f \nEstado: %d\n-----------------------------\n",
                    avisos[i].idAviso,avisos[i].rubro,avisos[i].texto,clientes[posCliente].CUIT, avisos[i].estado);
                }
            }
        }
    }
    return 0;
}


int baja_aviso(tbl_aviso* avisos, int topeA, tbl_cliente* clientes, int topeC, int auxIdCli)
{
    int i;
    int retorno=-1;
    int avisosActivos=0;
    int avisosPausados=0;
    int posCliente=-1;

    for(i=0;i<topeA;i++)
    {
        if((avisos[i].isEmpty==0) && avisos[i].idCliente==auxIdCli)
        {
            posCliente=buscaCliente(clientes,topeC,avisos[i].idCliente);

            if(avisos[i].estado==0)
            {
                avisosActivos+=1;
            }
            else if(avisos[i].estado==1)
            {
                avisosPausados+=1;
            }
            avisos[i].isEmpty=1;
            retorno=0;

        }
    }
    clientes[posCliente].avisosActivos-=avisosActivos;
    clientes[posCliente].avisosPausados-=avisosPausados;

    return retorno;
}
