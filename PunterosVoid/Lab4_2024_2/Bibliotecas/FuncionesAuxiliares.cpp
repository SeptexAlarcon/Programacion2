//
// Created by ASUS on 23/04/2026.
//
#include "Utils.hpp"
#include "FuncionesAuxiliares.hpp"
char *leerCadenaExacta(ifstream &arch,char delimitador) {
    char *cadena,buffer[500];
    arch.getline(buffer,500,delimitador);
    cadena=new char[strlen(buffer)+1];
    strcpy(cadena,buffer);
    return cadena;
}
void aperturaDeArchivos(const char *nombArch,ifstream &arch) {
    arch.open(nombArch);
    if (not arch.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }
}
void imprimirDeArchivos(const char *nombArch,ofstream &arch) {
    arch.open(nombArch);
    if (not arch.is_open()) {
        cout << "Error al abrir el archivo" << endl;
        exit(1);
    }
}
void incrementoDatos(int &cantDatos,int &capDatos, void **&auxInventario) {
    capDatos+=INCREMENTO;
    void **aux;
    if (auxInventario==nullptr) {
        auxInventario=new void *[capDatos]{};
        cantDatos=1;
    }else {
        aux=new void *[capDatos]{};
        for (int i=0;i<cantDatos;i++) {
            aux[i]=auxInventario[i];
        }
        delete []auxInventario;
        auxInventario=aux;
    }
}
void cargarInventario(const char *nombArch,void *&inventario) {
    ifstream arch;
    aperturaDeArchivos(nombArch,arch);
    void **auInventario=nullptr,*unicoInventario;
    int cantDatos=0,capDatos=0;
    while (true) {
        unicoInventario=lecturaDeUnInventario(arch);
        if (arch.eof()) break;
        if (cantDatos==capDatos) incrementoDatos(cantDatos,capDatos, auInventario);
        auInventario[cantDatos-1]=unicoInventario;
        cantDatos++;
    }
    inventario=auInventario;
}
void *lecturaDeUnInventario(ifstream &arch) {
    // I001,Café Arábica,50,kg
    void **buffer=nullptr;
    char *codigo,*nombreLugar,*unidadMedida,c;
    double cantidad,*unidad,*requerido;
    codigo=leerCadenaExacta(arch,',');
    if (arch.eof()) return nullptr;
    nombreLugar=leerCadenaExacta(arch,',');
    arch>>cantidad>>c;
    unidadMedida=leerCadenaExacta(arch,'\n');
    buffer=new void *[5];
    unidad=new double;
    requerido=new double;
    *requerido=0.0;
    *unidad=cantidad;
    buffer[CODIGOINSUMO]=codigo;
    buffer[NOMBREINSUMO]=nombreLugar;
    buffer[CANTIDAD_DIS]=unidad;
    buffer[CANTIDAD_REQ]=requerido;
    buffer[UNIDAD]=unidadMedida;
    return buffer;
}
void probarCargaInventario(const char *nombArch,void *inventario) {
    ofstream arch;
    imprimirDeArchivos(nombArch,arch);
    void **arrInventario=(void **)inventario;
    for (int i=0;arrInventario[i];i++) {
        void **unInventario=(void **)arrInventario[i];
        arch<<(char *)unInventario[CODIGOINSUMO]<<"  "<<(char *)unInventario[NOMBREINSUMO]<<"    "
        <<*(double *)unInventario[CANTIDAD_DIS]<<"   "<<*(double *)unInventario[CANTIDAD_REQ]<<" "<<(char *)unInventario[UNIDAD]<<endl;
    }
}
void cargarMenu(const char *nombArch, void *&menu) {
    ifstream arch;
    aperturaDeArchivos(nombArch,arch);
    void **auxMenu=nullptr,*unMenu;
    int cantDatos=0,capDatos=0;
    while (true) {
        unMenu=lecturaDeUnMenu(arch);
        if (arch.eof()) break;
        if (cantDatos==capDatos) incrementoDatos(cantDatos,capDatos, auxMenu);
        auxMenu[cantDatos-1]=unMenu;
        cantDatos++;
    }
    menu=auxMenu;
}
void *lecturaDeUnMenu(ifstream &arch) {
    void **arrMenu=nullptr;
    char *codigo,*nombre,*descripcion,*caracter,c;
    double *precio;
    int *cantidad;
    bool *disp;
    precio=new double;
    cantidad=new int;
    codigo=leerCadenaExacta(arch,',');
    if (arch.eof()) return nullptr;
    nombre=leerCadenaExacta(arch,',');
    descripcion=leerCadenaExacta(arch,',');
    caracter=leerCadenaExacta(arch,',');
    arch>>*precio>>c>>*cantidad;
    disp=new bool;
    *disp=true;
    arrMenu=new void *[8];
    arrMenu[CODIGOBEBIDA]=codigo;
    arrMenu[NOMBREBEBIDA]=nombre;
    arrMenu[DESCRIPCION]=descripcion;
    arrMenu[TIPOBEBIDA]=caracter;
    arrMenu[DISPONIBLE]=disp;
    arrMenu[PRECIO]=precio;
    arrMenu[CANTVENTAS]=cantidad;
    arrMenu[LISTINSUMOS]=nullptr;
    return arrMenu;
}
void pruebaCargarMenu(const char *nombArch,void *menu) {
    ofstream arch;
    imprimirDeArchivos(nombArch,arch);
    void **arrMenu=(void **)menu;
    for (int i=0;arrMenu[i];i++) {
        void **unMenu=(void **)arrMenu[i];
        arch<<(char *)unMenu[CODIGOBEBIDA]<<"  "<<(char *)unMenu[NOMBREBEBIDA]<<"    "<<(char *)unMenu[DESCRIPCION]
        <<"  "<<(char *)unMenu[TIPOBEBIDA]<<"  "<<*(bool *)unMenu[DISPONIBLE]<<"   "<<*(double *)unMenu[PRECIO]<<"   "<<*(int *)unMenu[CANTVENTAS]<<endl;
    }
}
void actualizarMenu(const char *nombArch,void *inventario,void *menu) {
    ifstream arch;
    aperturaDeArchivos(nombArch,arch);
    int arrCant[200]{},arrCap[200]{};
    char *codBebida,*codInventario,*medicion,c;
    int posBebida,posCodInventario;
    double cant;
    //B001,I001,10,g
    while (true) {
        codBebida=leerCadenaExacta(arch,',');
        if (arch.eof()) break;
        codInventario=leerCadenaExacta(arch,',');
        arch>>cant>>c;
        medicion=leerCadenaExacta(arch,'\n');
        posBebida=posMenu(menu,codBebida);
        posCodInventario=posInventario(inventario,codInventario);
        if (posBebida!=-1 and posCodInventario!=-1) {
            rellenarDatos(inventario,menu,arrCant,arrCap,posBebida,posCodInventario,cant,medicion);
        }
    }
}
void rellenarDatos(void *inventario,void *menu,int *arrCant,int *arrCap,int posBebida,int posCodInventario,double cant,char *medicion) {
    void **arrMenu=(void **)menu,**arrInventario=(void **)inventario;
    void **unMenu=(void **)arrMenu[posBebida];
    if (unMenu[LISTINSUMOS]==nullptr) {
        incrementoDatosInsumos(arrCant[posBebida],arrCap[posBebida], unMenu[LISTINSUMOS]);
    }else if (arrCant[posBebida]==arrCap[posBebida]){
        incrementoDatosInsumos(arrCant[posBebida],arrCap[posBebida], unMenu[LISTINSUMOS]);
    }
    void **arrInsumo=(void **)unMenu[LISTINSUMOS];
    arrInsumo[arrCant[posBebida]-1]=new void *[3]{};
    void **insumo=(void **)arrInsumo[arrCant[posBebida]-1];
    double *cantidad,*cantReq;
    cantidad=new double,cantReq=new double;
    *cantidad=cant;
    insumo[INVENTARIO]=arrInventario[posCodInventario];
    insumo[CANTIDAD]=cantidad;
    insumo[MEDIDA]=medicion;
    arrCant[posBebida]++;
    void **revisarInventario=(void **)insumo[INVENTARIO];
    int cantVendido=*(int*)unMenu[CANTVENTAS];
    *cantReq=cant*1000*cantVendido;
    revisarInventario[CANTIDAD_REQ]=cantReq;
    if (cant>*(double *)unMenu[CANTIDAD_DIS]) {
        *(bool *)unMenu[DISPONIBLE]=false;
        *(double *)unMenu[CANTIDAD_DIS]=-cant;
    }
}
void reporteMenu(const char *nombArch,void *menu) {
    ofstream arch;
    imprimirDeArchivos(nombArch,arch);
    void **arrMenu=(void **)menu;
    arch<<"==============================Menu del dia===================================="<<endl;
    for (int i=0;arrMenu[i];i++) {
        void **unMenu=(void **)arrMenu[i];
        if (strcmp((char *)unMenu[TIPOBEBIDA],"C")==0) arch<<"Cafe: ";
        else if (strcmp((char *)unMenu[TIPOBEBIDA],"T")==0) arch<<"Te: ";
        else if (strcmp((char *)unMenu[TIPOBEBIDA],"I")==0) arch<<"Infusion: ";
        else arch<<"Chocolate: ";
        arch<<(char *)unMenu[NOMBREBEBIDA]<<endl;
        arch<<(char *)unMenu[DESCRIPCION]<<endl;
        arch<<"Precio: S/ "<<*(double *)unMenu[PRECIO]<<endl;
        arch<<"Disponible: ";
        if (*(bool *)unMenu[DISPONIBLE]) arch<<"Si"<<endl;
        else arch<<"No"<<endl;
        arch<<"--------------------------------------------------------------------------"<<endl;
    }
}
void incrementoDatosInsumos(int &cant,int &cap,void *&menu) {
    cap+=INCREMENTO;
    void **auxiliar;
    if (menu==nullptr) {
        void **arreglo;
        arreglo=new void *[cap]{};
        cant=1;
        menu=arreglo;
        delete [] arreglo;
    }else {
        void **arreglo=(void **)menu;
        auxiliar=new void *[cap]{};
        for (int i=0;i<cant;i++) {
            auxiliar[i]=arreglo[i];
        }
        menu=auxiliar;
        delete [] arreglo;
    }
}
int posMenu(void *menu,char *codBebida) {
    void **arrMenu=(void **)menu;
    for (int i=0;arrMenu[i];i++) {
        void **unMenu=(void **)arrMenu[i];
        char *codigo=(char *)unMenu[CODIGOBEBIDA];
        if (strcmp(codigo,codBebida)==0) {
            return i;
        }
    }
    return -1;
}
int posInventario(void *inventario,char *codInventario) {
    void **arrInventario=(void **)inventario;
    for (int i=0;arrInventario[i];i++) {
        void **unInventario=(void **)arrInventario[i];
        char *codigo=(char *)unInventario[CODIGOINSUMO];
        if (strcmp(codigo,codInventario)==0) {
            return i;
        }
    }
    return -1;
}
