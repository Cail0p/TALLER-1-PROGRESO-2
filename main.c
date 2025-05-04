// INTEGRANTES DEL GRUPO CAMILO GUZMAN-NICOLAS NOBOA
// FECHA DE TRABAJO 4/5/25



#include <stdio.h>          // Libreria estandar para E / S (printf, scanf, etc.)
#include "funciones.h"      // Cabecera propia con constantes y prototipos

int main(void)              // Funcion principal; no recibe argumentos
{
    
    // 1. DECLARACION DE ARREGLOS Y VARIABLES GLOBALES DEL MAIN
    char   nombres[MAX_PROD][NAME_LEN];   // Matriz de cadenas: nombres[i] guarda
                                          // el nombre del producto i‑esimo
    double precios[MAX_PROD];             // Arreglo paralelo con los precios
    int    nProd = 0;                     // Cantidad real de productos cargados

    
    // 2. CARGA INICIAL DE DATOS DEL INVENTARIO
    nProd = ingresarProductos(nombres, precios); // Llama a la funcion que pide
                                                 // nombres y precios al usuario

    // 3. VARIABLES PARA EL MENU INTERACTIVO
    int  opcion;                  // Guarda la opcion elegida por el usuario
    int  pos;                     // Indice devuelto por las funciones de busqueda
    char buscado[NAME_LEN];       // Buffer temporal para el nombre a buscar

    // 4. BUCLE PRINCIPAL DEL MENU
    do {
        //Imprime el menu cada vuelta 
        printf("\n===== MENU DE INVENTARIO =====\n");
        printf("1. Precio total\n");
        printf("2. Producto mas caro\n");
        printf("3. Producto mas barato\n");
        printf("4. Precio promedio\n");
        printf("5. Buscar producto\n");
        printf("0. Salir\n");
        printf("Seleccione opcion: ");

        scanf("%d", &opcion);     // Lee la opcion elegida
        limpiarBuffer();          // Elimina el '\n' que queda en stdin

        //Ejecuta la accion segun la opcion
        switch (opcion) {

            case 1:   // Calcular y mostrar el total del inventario
                printf("Total del inventario: %.2f\n",
                       calcularTotal(precios, nProd));
                break;

            case 2:   // Mostrar el producto mas caro
                pos = indiceMaximo(precios, nProd);        // Indice del maximo
                printf("Mas caro -> %s (%.2f)\n",
                       nombres[pos], precios[pos]);
                break;

            case 3:   // Mostrar el producto mas barato
                pos = indiceMinimo(precios, nProd);        // Indice del minimo
                printf("Mas barato -> %s (%.2f)\n",
                       nombres[pos], precios[pos]);
                break;

            case 4:   // Calcular y mostrar el precio promedio
                printf("Precio promedio: %.2f\n",
                       calcularPromedio(precios, nProd));
                break;

            case 5:   // Buscar un producto por su nombre
                printf("Nombre a buscar: ");
                fgets(buscado, NAME_LEN, stdin);   // Lee el nombre con espacios
                quitarSalto(buscado);              // Elimina el '\n' final

                pos = buscarProducto(nombres, nProd, buscado); // Busca coincidencia
                if (pos >= 0)                                   // Si lo encontro
                    printf("%s cuesta %.2f\n",
                           nombres[pos], precios[pos]);
                else                                            // Si NO lo encontro
                    printf("No existe '%s' en el inventario.\n", buscado);
                break;

            case 0:   // Salir del programa
                puts("Hasta luego!");
                break;

            default:  // Cualquier entrada no valida
                puts("Opcion invalida.");
        }
    } while (opcion != 0);   // Repite hasta que el usuario elija 0 (Salir)

    return 0;                // Retorna 0 -> fin correcto del programa
}
