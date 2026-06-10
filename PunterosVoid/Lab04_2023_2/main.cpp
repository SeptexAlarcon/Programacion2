#include "Bibliotecas/Utils.hpp"

int main() {
    void *productos,*clientes;
    cargaproductos(productos,"ArchivosDeDatos/Productos2.csv");
    imprimirProductos(productos,"ArchivosDeReporte/PruebaProductos.txt");
    cargarclientes(clientes,"ArchivosDeDatos/Clientes2.csv");
    cargarPedidos(productos,clientes,"ArchivosDeDatos/Pedidos2.csv");
    imprimirReporte(clientes,"ArchivosDeReporte/PruebaClientes.txt");
    return 0;
}