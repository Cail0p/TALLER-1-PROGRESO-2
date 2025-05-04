// -----------------------------------------------------------------------------
// inventario_funciones.c
// -----------------------------------------------------------------------------
// Archivo unico que mezcla lo que antes era inventario_funciones.h y
// inventario_funciones.c.  Contiene:
//
//   1.  Constantes globales                   (MAX_PROD, NAME_LEN)
//   2.  Prototipos de las funciones publicas  (seccion “INTERFAZ”)
//   3.  Implementaciones de utilidades internas (limpiarBuffer, quitarSalto)
//   4.  Implementaciones de las funciones de negocio
//
// Se incluye directamente en main o se compila aparte.

// 1.  CONSTANTES GLOBALES  
#ifndef INVENTARIO_FUNCIONES_GUARD   // Evita multiples inclusiones
#define INVENTARIO_FUNCIONES_GUARD

#define MAX_PROD 10    // Capacidad maxima de productos
#define NAME_LEN 30    // Longitud maxima para cada nombre

// 2.  PROTOTIPOS — INTERFAZ PUBLICA  
void  limpiarBuffer(void);                                   // Descarta '\n'
void  quitarSalto(char s[]);                                 // Elimina '\n'
int   ingresarProductos(char nombres[][NAME_LEN],
                         double precios[]);                  // Carga inicial
double calcularTotal   (const double p[], int n);            // Suma precios
double calcularPromedio(const double p[], int n);            // Promedio
int   indiceMaximo     (const double p[], int n);            // Pos. maximo
int   indiceMinimo     (const double p[], int n);            // Pos. minimo
int   buscarProducto   (char nombres[][NAME_LEN], int n,
                        const char buscado[]);               // Busca por nombre

#endif  // INVENTARIO_FUNCIONES_GUARD

// 3.  IMPLEMENTACIONES — INCLUDES NECESARIOS  
#include <stdio.h>    // printf, scanf, fgets, getchar
#include <string.h>   // strlen, strcmp


// 3A.  UTILIDADES INTERNAS  

// limpiarBuffer: descarta restos del buffer de entrada (ej. '\n')
void limpiarBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF); // Consume hasta fin de linea
}

// quitarSalto: reemplaza el '\n' final de una cadena por '\0'
void quitarSalto(char s[])
{
    size_t len = strlen(s);          // Obtiene longitud de la cadena
    if (len && s[len - 1] == '\n')   // Si hay salto de linea al final
        s[len - 1] = '\0';           // Lo reemplaza por terminador nulo
}

// 4.  FUNCIONES PRINCIPALES DE INVENTARIO  
// ingresarProductos: solicita al usuario cantidad y datos de cada producto.
// Devuelve la cantidad almacenada (n).
int ingresarProductos(char nombres[][NAME_LEN], double precios[])
{
    int n;                                           // Cantidad a registrar
    do {
        printf("Cuantos productos registrara (1-%d)? ", MAX_PROD);
        scanf("%d", &n);                             // Lee la cantidad
        limpiarBuffer();                             // Descarta '\n'
    } while (n < 1 || n > MAX_PROD);                 // Valida rango

    for (int i = 0; i < n; ++i) {                    // Repite por producto
        printf("\nProducto #%d\n", i + 1);

        printf("Nombre: ");
        fgets(nombres[i], NAME_LEN, stdin);          // Lee nombre (con espacios)
        quitarSalto(nombres[i]);                     // Elimina salto final

        printf("Precio: ");
        scanf("%lf", &precios[i]);                   // Lee precio double
        limpiarBuffer();                             // Descarta '\n'
    }
    return n;                                        // Retorna cantidad cargada
}

// calcularTotal: suma todos los precios y devuelve el total
double calcularTotal(const double p[], int n)
{
    double total = 0.0;
    for (int i = 0; i < n; ++i)      // Recorre arreglo de precios
        total += p[i];
    return total;
}

// calcularPromedio: promedio = total / n (proteccion si n==0)
double calcularPromedio(const double p[], int n)
{
    return (n > 0) ? calcularTotal(p, n) / n : 0.0;
}

// indiceMaximo: devuelve la posicion del precio mas alto
int indiceMaximo(const double p[], int n)
{
    int idx = 0;                                  // Supone maximo en pos 0
    for (int i = 1; i < n; ++i)                   // Compara con resto
        if (p[i] > p[idx]) idx = i;               // Actualiza si encuentra mayor
    return idx;
}

// indiceMinimo: devuelve la posicion del precio mas bajo
int indiceMinimo(const double p[], int n)
{
    int idx = 0;                                  // Supone minimo en pos 0
    for (int i = 1; i < n; ++i)                   // Recorre resto
        if (p[i] < p[idx]) idx = i;               // Actualiza si encuentra menor
    return idx;
}

// buscarProducto: devuelve indice donde se encuentra 'buscado' o -1 si no esta
int buscarProducto(char nombres[][NAME_LEN], int n, const char buscado[])
{
    for (int i = 0; i < n; ++i)                   // Recorre nombres
        if (strcmp(nombres[i], buscado) == 0)     // Compara cadenas
            return i;                             // Encontrado: devuelve indice
    return -1;                                    // No encontrado
}

