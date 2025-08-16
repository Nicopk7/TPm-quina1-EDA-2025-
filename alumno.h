#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
    char codigo[7];
    char nombreapellido[80];
    char correo[23];
    int nota;
    char condicionFinal[10];
}Alumno;

void inicializarAlumno(Alumno *a){
    strcpy(a->codigo, '\0');
    a->nombreapellido[0] = '\0';
    a->correo[0] = '\0';
    a->nota = 0;
    a->condicionFinal[0] = '\0';
}

void modificarNombreApellido(Alumno *a, const char *nombre){
    strcpy(a->nombreapellido, nombre);
}

void modificarCorreo(Alumno *a, const char *correo){
    strcpy(a->correo, correo);
}

void modificarNota(Alumno *a, int nota){
    a->nota = nota;
}

void modificarCondicionFinal(Alumno *a, const char *condicion){
    strcpy(a->condicionFinal, condicion);
}

