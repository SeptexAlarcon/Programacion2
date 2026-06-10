//
// Created by ASUS on 21/04/2026.
//
#include "Utils.hpp"
#include "FuncionesAuxiliares.hpp"
#define INCREMENTO 5

void cargaproductos(void *&productos,const char *nombArch) {
    ifstream arch;
    aperturaDeArchivo(nombArch,arch);
    void **auxProducto=nullptr,*producto;
    int cantDatos=0,capDatos=0;
    while (true) {
        producto=leerlineaProducto(arch);
        if (arch.eof()) break;
        if (cantDatos==capDatos) incrementarDatos(cantDatos, capDatos, auxProducto) ;
        auxProducto[cantDatos-1]=producto;
        cantDatos++;
    }
    productos=auxProducto;
}
void *leerlineaProducto(ifstream &arch){
//BIT-434,Campana Extractora modelo Glass,375.09,S
    void **arrProducto=nullptr;
    char *arrcodigo,c,auxtipo,*arrnombre,*cp;
    double auxprecio,*p;
    arrcodigo=leerCadenaExacta(arch, ',');
    if (arch.eof()) return nullptr;
    arrnombre=leerCadenaExacta(arch, ',');
    arch>>auxprecio>>c>>auxtipo;
    arch.get();
    p=new double;
    *p=auxprecio;
    cp=new char;
    *cp=auxtipo;
    arrProducto=new void *[4];
    arrProducto[codigo]=arrcodigo;
    arrProducto[descripcion]=arrnombre;
    arrProducto[precio]=p;
    arrProducto[tipo]=cp;
    return arrProducto;
}
char *leerCadenaExacta(ifstream &arch, char delimitador) {
    char *exacta,buffer[200];
    arch.getline(buffer,200,delimitador);
    exacta=new char[strlen(buffer)+1];
    strcpy(exacta,buffer);
    return exacta;
}
void incrementarDatos(int &cantDatos, int &capDatos, void **&auxProducto) {
        capDatos+=INCREMENTO;
    void **antProduc;
    if (auxProducto==nullptr) {
        auxProducto=new void *[capDatos]{};
        cantDatos=1;
    }else {
        antProduc=new void *[capDatos]{};
        for (int i=0;i<cantDatos;i++) {
            antProduc[i]=auxProducto[i];
        }
        delete [] auxProducto;
        auxProducto=antProduc;
    }
}
void imprimirProductos(void *productos,const char *nombArch) {
    ofstream arch;
    ImpresionDeArchivo(nombArch,arch);
    void **arrProducto=(void **)productos;
    for (int i=0;arrProducto[i];i++) {
        void **prod=(void **)arrProducto[i];
        arch<<(char *)prod[codigo]<<endl;
        arch<<(char *)prod[descripcion]<<endl;
        arch<<*(double *)prod[precio]<<endl;
        arch<<*(char *)prod[tipo]<<endl;
        for (int j=0;j<25;j++) arch.put('-');
        arch<<endl;
    }
}
void aperturaDeArchivo(const char *nombArch,ifstream &arch) {
    arch.open(nombArch);
    if (not arch.is_open()) {
        cout << "Error opening file " << nombArch << endl;
        exit(1);
    }
}
void ImpresionDeArchivo(const char *nombArch,ofstream &arch) {
    arch.open(nombArch);
    if (not arch.is_open()) {
        cout << "Error opening file " << nombArch << endl;
        exit(1);
    }
}

void cargarclientes(void *&clientes, const char *nombArch) {
    ifstream arch;
    aperturaDeArchivo(nombArch,arch);
    void **arrClientes=nullptr,*buffCliente;
    int cantCliente=0,capCliente=0;
    while (true) {
        buffCliente=leerLineaCliente(arch);
        if (arch.eof()) break;
        if (cantCliente==capCliente) incrementarDatos(cantCliente,capCliente, arrClientes);
        arrClientes[cantCliente-1]=buffCliente;
        cantCliente++;
    }
    clientes=arrClientes;
}
void *leerLineaCliente(ifstream &arch) {
    //79464412,PORTUGAL RAFFO ALEXANDER,3902394,10000
    void **buffer=nullptr;
    char c,*nombre;
    int *dni=new int,*credito=new int,telefono;
    arch>>*dni>>c;
    if (arch.eof()) return nullptr;
    nombre=leerCadenaExacta(arch,',');
    arch>>telefono>>c>>*credito;
    buffer=new void*[4];
    buffer[DNI]=dni;
    buffer[NOMBRE]=nombre;
    buffer[LISTPEDIDOS]=nullptr;
    buffer[LINEACREDITO]=credito;
    return buffer;
}
void cargarPedidos(void *productos, void *clientes, const char *nombArch) {
    ifstream arch;
    aperturaDeArchivo(nombArch,arch);
    // JXD-139,50375303,6
    // CRU-009,50375303,5
    int dni,cant,posProducto,posCliente,arrCantClientes[300]{},arrCapClientes[300]{};
    char *cod,c;
    while (true) {
        cod=leerCadenaExacta(arch,',');
        if (arch.eof()) break;
        arch>>dni>>c>>cant;
        arch.get();
        posProducto=busquedaDeProducto(productos,cod);
        posCliente=busquedaDeCliente(clientes,dni);
        if (posCliente!=-1 and posProducto!=-1) {
            completarDatosClientes(posProducto,posCliente,productos,clientes,arrCantClientes,arrCapClientes,cant);
        }
    }
}
void completarDatosClientes(int posProducto,int posCliente,void *productos, void *clientes,int *arrCantClientes,int *arrCapClientes,int cant) {
    void **arrCliente=(void**)clientes;
    void **datoCliente=(void **)arrCliente[posCliente];
    if (datoCliente[LISTPEDIDOS]==nullptr) {
        incrementarDatosClientes(arrCantClientes[posCliente],arrCapClientes[posCliente],datoCliente[LISTPEDIDOS]);
    }else if (arrCantClientes[posCliente]==arrCapClientes[posCliente]) {
        incrementarDatosClientes(arrCantClientes[posCliente],arrCapClientes[posCliente],datoCliente[LISTPEDIDOS]);
    }
    void **orden=(void**)datoCliente[LISTPEDIDOS];
    orden[arrCantClientes[posCliente]-1]=new void *[3];
    void **ordenDeProductos=(void **)orden[arrCantClientes[posCliente]-1];
    void **arrProducto=(void **) productos;
    void **producto=(void **) arrProducto[posProducto];
    char *cod=(char *) producto[codigo];
    int *cantidad=new int;
    *cantidad=cant;
    double monto=*(double *) producto[precio];
    int total=(int) monto*cant;
    int *montoTotal=new int;
    *montoTotal=total;
    ordenDeProductos[COD]=cod;
    ordenDeProductos[CANTIDAD]=cantidad;
    ordenDeProductos[TOTAL]=montoTotal;
    arrCantClientes[posCliente]++;
}
void imprimirReporte(void *clientes,const char *nombArch) {
    ofstream arch;
    ImpresionDeArchivo(nombArch,arch);
    void **arrCliente=(void **)clientes;
    for (int i=0;arrCliente[i];i++) {
        void **datoCliente=(void **)arrCliente[i];
        arch<<*(int *)datoCliente[DNI]<<"     "<<(char *)datoCliente[NOMBRE]<<"    "<<*(int *)datoCliente[LINEACREDITO]<<endl;
        if (datoCliente[LISTPEDIDOS]!=nullptr) {
            arch<<"LISTA DE PEDIDOS: "<<endl;
            void **lista=(void **)datoCliente[LISTPEDIDOS];
            for (int j=0;lista[j];j++) {
                void **orden=(void **)lista[j];
                arch<<(char *)orden[COD]<<"   "<<*(int *)orden[CANTIDAD]<<"    "<<*(int *)orden[TOTAL]<<endl;
            }
        }
    }
}
void incrementarDatosClientes(int &cantDatos, int &capDatos, void *&datoCliente) {
    capDatos+=INCREMENTO;
    void **antProduc;
    if (datoCliente==nullptr) {
        void **arrCliente=(void**)datoCliente;
        arrCliente=new void *[capDatos]{};
        cantDatos=1;
        datoCliente=arrCliente;
    }else {
        antProduc=new void *[capDatos]{};
        void **auxCliente=(void **)datoCliente;
        for (int i=0;i<cantDatos;i++) {
            antProduc[i]=auxCliente[i];
        }
        delete [] auxCliente;
        datoCliente=antProduc;
    }
}
int busquedaDeProducto(void *productos,char *cod) {
    void **arrProducto=(void **)productos;
    for (int i=0;arrProducto[i];i++) {
        void **prod=(void **)arrProducto[i];
        char *auxCod;
        auxCod=(char *)prod[codigo];
        if (strcmp(auxCod,cod)==0) {
            return i;
        }
    }
    return -1;
}
int busquedaDeCliente(void *clientes,int dni) {
    void **arrCliente=(void **)clientes;
    for (int i=0;arrCliente[i];i++) {
        void **cliente=(void **)arrCliente[i];
        int dniCliente=*(int*)cliente[DNI];
        if (dniCliente==dni) {
            return i;
        }
    }
    return -1;
}

