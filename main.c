
#include <stdio.h>
#include <stdlib.h>
#define separador printf("____________________________________________________________________________________________ \n")
#define borrador system("cls")
#define MAXALUMNOS 130

typedef struct{
    char codigo[7];
    char nombreapellido[80];
    char correo[23];
    int nota;
    char condicionFinal[10];
}Alumno;

Alumno LSO[MAXALUMNOS];

int main()
{
    int menu=0, contadorAlumnos=0, cantidad=0, archivo=0;
    Alumno a;

    //MENU
    do{
        separador;
        printf("\n\tMENU ALUMNOS\n\n");
        printf ("1. Ingresar alumno\n");
        printf("2. Eliminar un alumno registrado\n");
        printf ("3. Modificar datos de un alumno\n");
        printf("4. Consultar informacion de un alumno\n");
        printf("5. Memorizacion previa\n");
        printf("6. Mostrar estructura\n");
        printf ("7. Salir\n");
        separador;
        printf("\nIngrese una opcion: ");
        scanf("%i",&menu);
        borrador;
        fflush(stdin);
        switch(menu){
            case 1: if(contadorAlumnos==MAXALUMNOS){
                        printf("No se pueden cargar más alumnos (lista llena).\n");
                    }
                    else{printf("Ingrese cuantos alumnos quiere ingresar\n");
                         scanf("%d",&cantidad);
                         for(int i = 0; i < cantidad; i++) //altaAlumno(&contador, LSO)
                        printf("Ahora hay %d alumnos cargados.\n", contadorAlumnos);
                        }
                    break;

            case 2: if(contadorAlumnos == 0){
                        printf("No hay alumnos registrados \n");
                    }
                    //else borrar_prestador(&l, &contador);
                    break;

            case 3: if(contadorAlumnos == 0){
                        printf("No hay alumnos registrados \n");
                    }
                    //else modificar_prestador(&l, &contador);
                    break;

            case 4: if(contadorAlumnos == 0){
                        printf("No hay alumnos registrados \n");
                    }
                    //else mostrar_prestador(l);
                    break;

            case 5:  //archivo= memorizacionprevia(LSO,&contadorAlumnos);
                      if (archivo==0){printf("No se pudo cargar el archivo \n");}
                                else {printf("Se cargo el archivo con exito \n");}
                    break;

            case 6: if(contadorAlumnos == 0){
                        printf("No hay alumnos registrados \n");
                    }
                    else mostrarLSO(contadorAlumnos);
                    break;

            case 7: printf("Cerrando programa...\n");
        }
    }while(menu != 7);

    return 0;
}

void localizar(char codigo[], int *exito, int *posicion, int contador) {
    int i = 0;
    *exito = 0;
    while (i < contador && strcmp(LSO[i].codigo, codigo) < 0){
        i++;
    }

    if (i < contador && strcmp(LSO[i].codigo, codigo) == 0) {
        *exito = 1;
        *posicion = i;
    } else {
        *posicion = i;
    }
}


int alta(Alumno a, int *exito, int *posicion, int *contador) {
    localizar(a.codigo, exito, posicion, *contador);
    if (*exito == 1) {
        return 0; // ya existe, alta NO exitosa
    }
    if (*contador >= MAXALUMNOS) {
        return 2; // lista llena, no se puede insertar
    }
    for (int j = *contador; j > *posicion; j--) {
        LSO[j] = LSO[j - 1];
    }
    LSO[*posicion] = a;
    (*contador)++;

    return 1; // alta exitosa
}


int baja(Alumno a, int *exito, int *posicion, int *contador) {
    localizar(a.codigo, exito, posicion, *contador);
    if (*exito == 0) {
        return 0; // NO encontrado
    }
    // comparar todos los campos
    Alumno b = LSO[*posicion];
    if (strcmp(a.codigo, b.codigo) != 0 ||
        strcmp(a.nombreapellido, b.nombreapellido) != 0 ||
        strcmp(a.correo, b.correo) != 0 ||
        a.nota != b.nota ||
        strcmp(a.condicionFinal, b.condicionFinal) != 0) {
        return 0; // los datos no coinciden
    }
    for (int j = *posicion; j < *contador - 1; j++) {
        LSO[j] = LSO[j + 1];
    }
    (*contador)--;
    return 1; // baja exitosa
}


Alumno evocar(char codigo[], int *exito, int *posicion, int contador) {
    Alumno aux;
    localizar(codigo, exito, posicion, contador);
    if (*exito == 1) { // encontrado
        return LSO[*posicion]; // más simple: devolver el alumno directamente
    } else {
        strcpy(aux.codigo, "");
        strcpy(aux.nombreapellido, "");
        strcpy(aux.correo, "");
        strcpy(aux.condicionFinal, "");
        aux.nota = 0;
        return aux;
    }
}


int memorizacionprevia(int *contador) {
    FILE *fp = fopen("Alumnos.txt", "r");
    Alumno aux;
    if (fp == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 0; // error al abrir archivo
    }
    while (!feof(fp) && *contador < MAXALUMNOS) {
        // Leer los campos en el orden en que aparecen en el archivo
        if (fscanf(fp, "%7s", aux.codigo) != 1) break;
        fscanf(fp, " %[^\n]", aux.nombreapellido);
        fscanf(fp, " %[^\n]", aux.correo);
        fscanf(fp, "%d", &aux.nota);
        fscanf(fp, " %[^\n]", aux.condicionFinal);
        int exito, pos;
        if (!alta(aux, &exito, &pos, contador, MAXALUMNOS)) {
            printf("No se pudo cargar el alumno con código %s (duplicado o lista llena)\n", aux.codigo);
        }
    }
    fclose(fp);
    if (*contador == MAXALUMNOS) {
        return 3; // lista llena
    }
    return 1; // carga exitosa
}


void mostrarLSO(int contador){
    int mostrados = 0;
    for(int i = 0; i < contador; i++){
        separador;
        printf("\nAlumno #%d\n", mostrados + 1);
        printf("Codigo: %s\n", LSO[i].codigo);
        printf("Nombre completo: %s\n", LSO[i].nombreapellido);
        printf("Nota: %d\n", LSO[i].nota);
        printf("Correo: %s\n", LSO[i].correo);
        printf("Condicion final: %s\n", LSO[i].condicionFinal);
        separador;
        mostrados++;
        if (mostrados % 3 == 0) {
            printf("\nPresione cualquier tecla para continuar...\n");
            system("pause");
            borrador;
        }
    }
    if (mostrados % 3 != 0) {
        system("pause");
    }
}


