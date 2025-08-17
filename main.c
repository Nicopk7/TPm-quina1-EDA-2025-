
#include <stdio.h>
#include <stdlib.h>
#define separador printf("____________________________________________________________________________________________ \n")
#define borrador system("cls")
#define MAXALUMNOS 130

typedef struct{
    char codigo[8];
    char nombreapellido[80];
    char correo[23];
    int nota;
    char condicionFinal[10];
}Alumno;

Alumno LSO[MAXALUMNOS];

//PROTOTIPOS
void localizar(char codigo[], int *exito, int *posicion, int contador);
int alta(Alumno a, int *contador);
int baja(char codigo[], int *contador);
Alumno evocar(char codigo[], int contador);
int modificarAlumno(Alumno a, int contador);
int memorizacionprevia(int *contador);
void mostrarLSO(int contador);

int main()
{
    int menu=0, contadorAlumnos=0, cantidad=0, archivo=0;
    Alumno nuevo;
    char codigoaux[7];

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
                    else{
                        printf("Ingrese el codigo del alumno: ");
                        scanf("%s", nuevo.codigo);

                        printf("Ingrese el nombre y apellido: ");
                        scanf(" %[^\n]", nuevo.nombreapellido);

                        printf("Ingrese el correo: ");
                        scanf("%s", nuevo.correo);

                        printf("Ingrese la condicion final (ej: Promociona, regular, libre, ausente): ");
                        scanf(" %[^\n]", nuevo.condicionFinal);

                        printf("Ingrese la nota: ");
                        scanf("%d", &nuevo.nota);
                        int resultadoAlta = alta(nuevo, &contadorAlumnos);
                        if(resultadoAlta == 1){
                            printf("Se ha cargado el alumno correctamente\n");
                            printf("Ahora hay %d alumnos cargados\n", contadorAlumnos);
                        }
                        else{
                            printf("No se pudo cargar el alumno\n\n");
                        }
                        }
                    break;

            case 2: if(contadorAlumnos == 0){
                        printf("No hay alumnos registrados \n");
                    }
                    else{
                        printf("Ingrese el codigo del alumno que desea eliminar: ");
                        scanf("%s", nuevo.codigo);
                        int resultadoBaja = baja(nuevo.codigo, &contadorAlumnos);
                        if(resultadoBaja == 1) printf("Se elimino el alumno con exito\n");
                        else printf("No se pudo eliminar el alumno\n");
                    }
                    break;

            case 3: if(contadorAlumnos == 0){
                        printf("No hay alumnos registrados \n");
                    }
                    else{
                        printf("Ingrese el codigo del alumno que desea modificar: ");
                        scanf("%s", nuevo.codigo);
                        printf("Ingrese el nombre y apellido: ");
                        scanf(" %[^\n]", nuevo.nombreapellido);
                        printf("Ingrese el correo: ");
                        scanf("%s", nuevo.correo);
                        printf("Ingrese la condicion final (ej: Promociona, regular, libre, ausente): ");
                        scanf(" %[^\n]", nuevo.condicionFinal);
                        printf("Ingrese la nota: ");
                        scanf("%d", &nuevo.nota);

                        int resultadoModificar = modificarAlumno(nuevo, contadorAlumnos);
                        if (resultadoModificar == 1) printf("Se modifico al alumno con exito\n");
                        else printf("No se pudo modificar al alumno (Verifique si se encuentra registrado)");
                    }
                    break;

            case 4: if(contadorAlumnos == 0){
                        printf("No hay alumnos registrados \n");
                    }
                    else{
                        printf("Ingrese el codigo del alumno que desea buscar: ");
                        scanf("%s", codigoaux);
                        nuevo = evocar(codigoaux, contadorAlumnos);
                        if(strcmp(nuevo.codigo, "-1") == 0){
                            printf("No se encontro el alumno\n");
                        }
                        else{
                            printf("\n--- Datos del Alumno ---\n");
                            printf("Codigo: %s\n", nuevo.codigo);
                            printf("Nombre: %s\n", nuevo.nombreapellido);
                            printf("Correo: %s\n", nuevo.correo);
                            printf("Condicion final: %s\n", nuevo.condicionFinal);
                            printf("Nota: %d\n", nuevo.nota);
                            printf("------------------------\n");
                        }
                    }

                    break;

            case 5:  archivo = memorizacionprevia(&contadorAlumnos);
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


int alta(Alumno a, int *contador) {
    int exito = 0, posicion = 0, j = 0;
    localizar(a.codigo, &exito, &posicion, *contador);
    if (exito == 1) {
        return 0; // ya existe, alta NO exitosa
    }
    if (*contador >= MAXALUMNOS) {
        return 2; // lista llena, no se puede insertar
    }
    for (j = *contador; j > posicion; j--) {
        LSO[j] = LSO[j - 1];
    }
    LSO[posicion] = a;
    (*contador)++;

    return 1; // alta exitosa
}


int baja(char codigo[], int *contador) {
    int exito = 0, posicion = 0;
    localizar(codigo, &exito, &posicion, *contador);
    if (exito == 0) {
        return 0; // NO encontrado
    }
    // comparar todos los campos
    Alumno b = LSO[posicion];
    if (strcmp(LSO[posicion].codigo, b.codigo) != 0 ||
        strcmp(LSO[posicion].nombreapellido, b.nombreapellido) != 0 ||
        strcmp(LSO[posicion].correo, b.correo) != 0 ||
        LSO[posicion].nota != b.nota ||
        strcmp(LSO[posicion].condicionFinal, b.condicionFinal) != 0) {
        return 0; // los datos no coinciden
    }
    for (int j = posicion; j < *contador - 1; j++) {
        LSO[j] = LSO[j + 1];
    }
    (*contador)--;
    return 1; // baja exitosa
}


Alumno evocar(char codigo[], int contador) {
    int exito = 0, posicion = 0;
    Alumno aux;
    localizar(codigo, &exito, &posicion, contador);
    if (exito == 1) { // encontrado
        return LSO[posicion];
    } else {
        strcpy(aux.codigo, "-1");
        strcpy(aux.nombreapellido, "");
        strcpy(aux.correo, "");
        strcpy(aux.condicionFinal, "");
        aux.nota = 0;
        return aux;
    }
}

int modificarAlumno(Alumno a, int contador){
    int exito = 0, posicion = 0;
    localizar(a.codigo, &exito, &posicion, contador);
    if(exito == 1){
        LSO[posicion] = a;
        strcpy(LSO[posicion].codigo, a.codigo);
        return 1;
    }
    else return 0;
}


int memorizacionprevia(int *contador) {
    FILE *fp = fopen("Alumnos.txt", "r");
    Alumno aux;
    char buffer[100];  // buffer temporal para leer líneas

    if (fp == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 0; // error al abrir archivo
    }

    while (!feof(fp) && *contador < MAXALUMNOS) {

        if (fgets(buffer, sizeof(buffer), fp) == NULL) break;
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(aux.codigo, buffer, 8);
        aux.codigo[7] = '\0';


        if (fgets(buffer, sizeof(buffer), fp) == NULL) break;
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(aux.nombreapellido, buffer, 80);
        aux.nombreapellido[79] = '\0';


        if (fgets(buffer, sizeof(buffer), fp) == NULL) break;
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(aux.correo, buffer, 23);
        aux.correo[22] = '\0';


        if (fgets(buffer, sizeof(buffer), fp) == NULL) break;
        aux.nota = atoi(buffer);


        if (fgets(buffer, sizeof(buffer), fp) == NULL) break;
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(aux.condicionFinal, buffer, 10);
        aux.condicionFinal[9] = '\0';


        if (!alta(aux, contador)) {
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


