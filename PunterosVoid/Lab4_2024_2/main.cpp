#include <iostream>
#include "Bibliotecas/FuncionesAuxiliares.hpp"
#include "Bibliotecas/Utils.hpp"
int main() {
    void *inventario,*menu;
    cargarInventario("ArchivosDeDatos/inventario.csv",inventario);
    probarCargaInventario("ArchivosDeReporte/prueba_inventario.txt",inventario);
    cargarMenu("ArchivosDeDatos/menu.csv", menu);
    pruebaCargarMenu("ArchivosDeReporte/Menu_Inicial.txt",menu);
    actualizarMenu("ArchivosDeDatos/insumos-bebidas.csv",inventario,menu);
    reporteMenu("ArchivosDeReporte/ReporteFinal.txt",menu);
    return 0;
}