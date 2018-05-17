#ifndef ABM_AVISO_H_INCLUDED
#define ABM_AVISO_H_INCLUDED
#include "abm_cliente.h"

typedef struct
{
    int idAviso;
    int idCliente;
    int rubro;
    char texto[64];
    int isEmpty;
    int estado; //activo o pausado

}tbl_aviso;

int inicializar_avisos(tbl_aviso* avisos, int tope);
int alta_aviso(tbl_aviso* avisos, int topeA, tbl_cliente* clientes, int topeC, int auxIdCliente);
int modifica_aviso(tbl_aviso* avisos, int topeA, tbl_cliente* clientes, int topeC, int auxIdAviso, int auxEstado);
int baja_aviso(tbl_aviso* avisos, int topeA, tbl_cliente* clientes, int topeC, int auxIdCli);
int buscaAviso(tbl_aviso* avisos, int tope, int idAviso);
int imprimir_aviso(tbl_aviso* avisos, int topeA, tbl_cliente* clientes, int topeC, int auxCli);

int proximoId(void);

#endif // ABM_AVISO_H_INCLUDED
