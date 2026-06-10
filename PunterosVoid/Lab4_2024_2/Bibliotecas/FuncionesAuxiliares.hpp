//
// Created by ASUS on 23/04/2026.
//

#ifndef LAB4_2024_2_FUNCIONESAUXILIARES_HPP
#define LAB4_2024_2_FUNCIONESAUXILIARES_HPP
#include "Utils.hpp"
void aperturaDeArchivos(const char *nombArch,ifstream &arch);
void cargarInventario(const char *nombArch,void *&inventario);
void *lecturaDeUnInventario(ifstream &arch);
char *leerCadenaExacta(ifstream &arch,char delimitador);
void incrementoDatos(int &cantDatos,int &capDatos, void **&auxInventario);
void probarCargaInventario(const char *nombArch,void *inventario);
void imprimirDeArchivos(const char *nombArch,ofstream &arch);
void *lecturaDeUnMenu(ifstream &arch);
void pruebaCargarMenu(const char *nombArch,void *menu);
void cargarMenu(const char *nombArch, void *&menu);
void actualizarMenu(const char *nombArch,void *inventario,void *menu);
int posMenu(void *menu,char *codBebida);
int posInventario(void *inventario,char *codInventario);
void rellenarDatos(void *inventario,void *menu,int *arrCant,int *arrCap,int posBebida,int posCodInventario,double cant,char *medicion);
void incrementoDatosInsumos(int &cant,int &cap,void *&menu);
void reporteMenu(const char *nombArch,void *menu);
#endif //LAB4_2024_2_FUNCIONESAUXILIARES_HPP