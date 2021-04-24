#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct Producto 
{
    int ProductoID; //Numerado en ciclo iterativo
    int Cantidad; // entre 1 y 10
    char *TipoProducto; // Algún valor del arreglo TiposProductos
    float PrecioUnitario; // entre 10 - 100
}Producto;

typedef struct Cliente 
{
    int ClienteID; // Numerado en el ciclo iterativo
    char *NombreCliente; // Ingresado por usuario
    int CantidadProductosAPedir; // (alteatorio entre 1 y 5)
    Producto *Productos; //El tamaño de este arreglo depende de la variable        
    // “CantidadProductosAPedir”
}cliente;

char *TiposProductos[]={"Galletas","Snack","Cigarrillos","Caramelos","Bebidas"};

//***********FUNCIONES*************//
Producto *crearProductos(int cant_prod){
    Producto *vec_prod;
    int aleatorio;

    for (int i = 0; i < cant_prod; i++)
    {
        (vec_prod + i)->ProductoID = i+1;
        (vec_prod + i)->Cantidad = rand() % 11;
        (vec_prod + i)->PrecioUnitario = (float)(rand() % 91) / 10;
        aleatorio=rand()% (sizeof(TiposProductos)/sizeof(char));
        strcpy((vec_prod + i)->TipoProducto,TiposProductos[aleatorio]);
    }
    return vec_prod;
}

void cargarClientes(cliente *vecClientes,int cantidadClientes){

    for (int i = 0; i < cantidadClientes; i++)
    {
        (vecClientes + i)->ClienteID = i + 1;
        (vecClientes + i)->NombreCliente = (char*)malloc(sizeof(char)*10);//como NombreCliente es un vector tengo que ahorrar memoria
        printf("ingrese el nombre del cliente:\n");
        gets((vecClientes + i)->NombreCliente);
        (vecClientes + i)->CantidadProductosAPedir= rand() % 6;
        (vecClientes + i)->Productos = crearProductos((vecClientes + i)->CantidadProductosAPedir);  
    }
}

int mostrarProductos(Producto *Listaprod){
    printf("ID del producto: %d\n",Listaprod->ProductoID);
    printf("Tipo de producto: %s\n",Listaprod->TipoProducto);
    printf("Precio por unidad: %.2f",Listaprod->PrecioUnitario);
    printf("Cantidad: %d",Listaprod->Cantidad);

    return (Listaprod->PrecioUnitario * Listaprod->Cantidad);
}

void Mostrar(cliente *vec_clientes,int cant_clientes){
    int total_a_pagar=0;
    for (int i = 0; i < cant_clientes; i++)
    {
        printf("\t*****Datos el cliente n° %d *****\n\n\n",i+1);
        printf("ID del cliente:%d\n",(vec_clientes +i)->ClienteID);
        printf("Nombre: %s\n",(vec_clientes +i)->NombreCliente);
        printf("cantidad de productos a pedir: %d\n",(vec_clientes + i)->CantidadProductosAPedir);
        printf("\nDatos del producto: \n");
        for (int j = 0; j < (vec_clientes + i)->CantidadProductosAPedir; j++)
        {
            total_a_pagar += mostrarProductos((vec_clientes +i)->Productos+ j);
        }
        printf("EL total a pagar es: %d", total_a_pagar);   
    }   
}



//***********MAIN*******************//
int main(){
    int cant_clientes;
    cliente *vec_clientes;//creo un puntero de tipo cliente

    do
    {
        printf("Ingrese la cantidad de clientes:");
        scanf("%d",&cant_clientes);
    } while (cant_clientes>5);//seguirá en el bucle hasta que la cantidad de clientes sea mayor a 5

    vec_clientes = (cliente *)malloc(sizeof(cliente)*cant_clientes);//reservo memoria de la lista completa
    /*
    como Lista_cliente es un puntero, éste contiene la direccion de memoria de 
    el primer elemento de mi arreglo de estructuras y usaré esta direccion para moverme en el arreglo
    */
    cargarClientes(vec_clientes,cant_clientes);//envío el puntero

    Mostrar(vec_clientes,cant_clientes);

    system("pause");
    return 0;
}