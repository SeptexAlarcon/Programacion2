//
// Created by ASUS on 21/04/2026.
//

#ifndef LAB04_2023_2_FUNCIONESAUXILIARES_HPP
#define LAB04_2023_2_FUNCIONESAUXILIARES_HPP
#include "Utils.hpp"
void cargaproductos(void *&productos,const char *nombArch);
void aperturaDeArchivo(const char *nombArch,ifstream &arch);
void *leerlineaProducto(ifstream &arch);
void incrementarDatos(int &cantDatos, int &capDatos, void **&auxProducto);
char *leerCadenaExacta(ifstream &arch, char delimitador);
void imprimirProductos(void *productos,const char *nombArch);
void ImpresionDeArchivo(const char *nombArch,ofstream &arch);
void cargarclientes(void *&clientes,const char *nombArch);
void *leerLineaCliente(ifstream &arch);
void cargarPedidos(void *productos,void *clientes,const char *nombArch);
int busquedaDeProducto(void *productos,char *cod);
int busquedaDeCliente(void *clientes,int dni);
void completarDatosClientes(int posProducto,int posCliente,void *productos, void *clientes,int *arrCantClientes,int *arrCapClientes,int cant);
void imprimirReporte(void *clientes,const char *nombArch);
void incrementarDatosClientes(int &cantDatos, int &capDatos, void *&datoCliente);
#endif //LAB04_2023_2_FUNCIONESAUXILIARES_HPP