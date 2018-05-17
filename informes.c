#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utn.h"
#include "abm_aviso.h"
#include "abm_cliente.h"

/**
 * \brief Imprime los clientes con maximos avisos activos, pausados y totales
 * \param clientes array de clientes
 * \param tope es el tope de clientes para recorrer
 * \param opcionInforme toma la opcion del informe activos, pausados o totales
 */


void informe_clientes(tbl_cliente* clientes, int tope, int opcionInforme)
{
    int i;
    int maxActivos=0;
    int maxPausados=0;
    int totalAvisos=0;
    int idClienteMaxActivos=-1;
    int idClienteMaxPausados=-1;
    int idClienteTotalAvisos=-1;


    for(i=0;i<tope;i++)
    {
        if((clientes[i].avisosActivos+clientes[i].avisosPausados)>totalAvisos)
        {
            totalAvisos=clientes[i].avisosActivos+clientes[i].avisosPausados;
            idClienteTotalAvisos=clientes[i].idCliente;
        }
        else if(clientes[i].avisosActivos>maxActivos)
        {
            maxActivos=clientes[i].avisosActivos;
            idClienteMaxActivos=clientes[i].idCliente;
        }
        else if(clientes[i].avisosPausados>maxPausados)
        {
            maxPausados=clientes[i].avisosPausados;
            idClienteMaxPausados=clientes[i].idCliente;
        }

    }
    switch(opcionInforme)
    {
        case 1:
        printf("Cliente con mas avisos activos: %d\n",idClienteMaxActivos);
        break;

        case 2:
        printf("Cliente con mas avisos pausados: %d\n",idClienteMaxPausados);
        break;

        case 3:
        printf("Cliente con mas avisos: %d\n", idClienteTotalAvisos);
        break;
    }
}


/**
 * \brief Imprime los rubros con mas avisos, pausados y totales
 * \param clientes array de clientes
 * \param tope es el tope de clientes para recorrer
 * \param opcionInforme toma la opcion del rubro total, con mas avisos o menos avisos
 */

 void informe_avisos(tbl_aviso* avisos, int tope, int opcionInforme)
{
    int i;
    int j;
    int rubro;
    int avisosPorRubro=0;
    int arrayRubroAvisosActivos[5]={0,0,0,0,0};
    int rubroMasAvisosActivos=0;
    int rubroMenosAvisosActivos=0;
    int rubroMayor;
    int rubroMenor;

    for(i=0;i<5;i++)
    {
        for(j=0;j<tope;j++)
        {
            if(avisos[j].isEmpty==0 && avisos[j].estado==0 && avisos[j].rubro==i+1)
            {
                arrayRubroAvisosActivos[i]+=1;
            }
        }
    }
    for(i=0;i<5;i++)
    {
        if(arrayRubroAvisosActivos[i]>rubroMasAvisosActivos)
        {
            rubroMasAvisosActivos=arrayRubroAvisosActivos[i];
            rubroMayor=i+1;
        }
        else if(arrayRubroAvisosActivos[i]<rubroMenosAvisosActivos)
        {
            rubroMasAvisosActivos=arrayRubroAvisosActivos[i];
            rubroMenor=i+1;
        }
    }

    switch(opcionInforme)
    {
        case 1:
        if(getValidInt("Ingrese un rubro","No valido",&rubro,1,5,3)==0)

            for(i=0;i<tope;i++)
            {
                if(avisos[i].isEmpty==0 && avisos[i].estado==0 && avisos[i].rubro==rubro)
                {
                        avisosPorRubro+=1;
                }
            }
        printf("Cantidad de avisos del rubro %d: %d\n",rubro,avisosPorRubro);
        break;

        case 2:

        printf("Rubro con mas avisos activos: %d\n",rubroMayor);
        break;

        case 3:
        printf("Rubro con menos avisos activos: %d\n",rubroMenor);
        break;
    }
}
