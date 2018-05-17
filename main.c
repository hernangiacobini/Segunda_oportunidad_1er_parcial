#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utn.h"
#include "abm_aviso.h"
#include "abm_cliente.h"
#include "informes.h"

#define TOPE_CLIENTES 100
#define TOPE_AVISOS 1000



int main()
{

    tbl_cliente clientes[TOPE_CLIENTES];
    tbl_aviso avisos[TOPE_AVISOS];

    inicializar_clientes(clientes, TOPE_CLIENTES);
    inicializar_avisos(avisos, TOPE_AVISOS);

    int opcion=0;
    int auxIdCliente;
    int auxIdAviso;
    int confirma=0;
    int posCliente=-1;
    int posAviso=-1;
    int opcionInforme;
    char continuar='s';

    do
    {
        getValidInt("MENU\n---------------\n1-ALTA CLIENTE\n2-MODIFICAR DATOS DEL CLIENTE\n3-BAJA DEL CLIENTE\n"
        "4-PUBLICAR AVISO\n5-PAUSAR AVISO\n6-REANUDAD AVISO\n"
        "7-IMPRIMIR CLIENTES\n8-IMPRIMIR AVISOS\n9-INFORMAR CLIENTES\n10-INFORMAR AVISOS\n11-SALIR\n\n","Opcion invalida"
        ,&opcion,1,11,99);

        confirma=-1;

        switch(opcion)
        {
            system("cls");
        case 1:
            alta_cliente(clientes, TOPE_CLIENTES);
            break;

        case 2:
            if(getValidInt("\nIngrese ID de cliente","No valido",&auxIdCliente,0,TOPE_CLIENTES-1,99)==0)
            {
                if(modifica_cliente(clientes, TOPE_CLIENTES, auxIdCliente)<0)
                {
                    printf("\nEl ID cliente no existe\n");
                }
            }
            break;

        case 3:
            if(getValidInt("\nIngrese ID de cliente","No valido",&auxIdCliente,0,TOPE_CLIENTES-1,99)==0)
            {
                if(buscaCliente(clientes,TOPE_CLIENTES,auxIdCliente)>=0)
                {
                    posCliente=buscaCliente(clientes,TOPE_CLIENTES,auxIdCliente);

                    imprimir_aviso(avisos,TOPE_AVISOS,clientes,TOPE_CLIENTES,auxIdCliente);

                    if(getValidInt("\nDesea eliminar el cliente? 1-Si 2-No","No valido",&confirma,1,2,2)==0)
                    {
                        if(confirma==1)
                        {
                            baja_cliente(clientes, TOPE_CLIENTES, auxIdCliente);
                            baja_aviso(avisos,TOPE_AVISOS,clientes,TOPE_CLIENTES, auxIdCliente);
                        }
                    }
                }
                else
                {
                    printf("\nEl ID cliente no existe\n");
                }
            }

            break;

        case 4:
            if(getValidInt("\nIngrese el ID de cliente","No valido",&auxIdCliente,0,99,99)==0)
            {
                alta_aviso(avisos,TOPE_AVISOS,clientes,TOPE_CLIENTES,auxIdCliente);
            }
            break;

        case 5:
             if(getValidInt("\nIngrese el ID de aviso","No valido",&auxIdAviso,0,99,99)==0)
            {
                system("cls");
                if(buscaAviso(avisos,TOPE_AVISOS,auxIdAviso)>=0)
                {
                    posAviso=buscaAviso(avisos,TOPE_AVISOS,auxIdAviso);
                    auxIdCliente=buscaCliente(clientes,TOPE_CLIENTES,avisos[posAviso].idCliente);
                    posCliente=buscaCliente(clientes,TOPE_CLIENTES,auxIdCliente);
                    imprimir_clientes(clientes,TOPE_CLIENTES,posCliente);
                    if(getValidInt("\nDesea cambiar el estado? 1-Si 2-No","No valido",&confirma,1,2,2)==0)
                    {
                        if(confirma==1)
                        {
                            modifica_aviso(avisos,TOPE_AVISOS, clientes,TOPE_CLIENTES, posAviso,1);
                        }
                    }
                }
                else
                {
                    printf("El ID aviso no existe\n");
                }

            }
            break;

        case 6:
            if(getValidInt("\nIngrese el ID de aviso","No valido",&auxIdAviso,0,99,99)==0)
            {
                system("cls");
                if(buscaAviso(avisos,TOPE_AVISOS,auxIdAviso)>=0)
                {
                    posAviso=buscaAviso(avisos,TOPE_AVISOS,auxIdAviso);
                    auxIdCliente=buscaCliente(clientes,TOPE_CLIENTES,avisos[posAviso].idCliente);
                    posCliente=buscaCliente(clientes,TOPE_CLIENTES,auxIdCliente);
                    imprimir_clientes(clientes,TOPE_CLIENTES,posCliente);
                    if(getValidInt("\nDesea cambiar el estado? 1-Si 2-No","No valido",&confirma,1,2,2)==0)
                    {
                        if(confirma==1)
                        {
                            modifica_aviso(avisos,TOPE_AVISOS, clientes,TOPE_CLIENTES, posAviso,0);
                        }
                    }
                }
                else
                {
                    printf("El ID cliente no existe\n");
                }

            }
            break;

        case 7:
            system("cls");
            imprimir_clientes(clientes,TOPE_CLIENTES,-1);
            break;

        case 8:
            system("cls");
            imprimir_aviso(avisos,TOPE_AVISOS,clientes,TOPE_CLIENTES,-1);
            break;

        case 9:
            system("cls");
            if(getValidInt("Informar clientes:\n\t1-Cliente con mas avisos activos\n\t"
                "2-Cliente con mas avisos pausados\n\t3-Cliente con mas avisos","opcion invalida",&opcionInforme,1,3,999)==0)
            {
                informe_clientes(clientes,TOPE_CLIENTES,opcionInforme);
            }

            break;

        case 10:
            system("cls");
            if(getValidInt("Informar avisos:\n\t1-Cantidad de avisos de un rubro. Se ingresara el numero de rubro y se "
                "imprimira la cantidad de avisos activos de dicho rubro\n\t2-Rubro con mas avisos activos\n\t"
                "3-Rubro con menos avisos activos","opcion invalida",&opcionInforme,1,3,999)==0)
            {
                informe_avisos(avisos,TOPE_AVISOS,opcionInforme);
            }
            break;

        case 11:
            continuar='n';
            break;
        }
    }while(continuar=='s');







    return 0;
}


