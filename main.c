#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
///ESTRUCTURAS:
typedef struct{
    char nombre[20];
    int edad;
}stPersona;

typedef struct{
    stPersona persona;
    struct nodoDoble *anterior;
    struct nodoDoble *siguiente;
}nodoDoble;
///PROTOTIPADO FUNCIONES ARCHIVOS:
stPersona crearUnaPersonaArchi();
void cargarPesonasArchi(char nombreArchi[], stPersona persona);
void mostrarArchi(char nombreArchi[]);
void mostrarUnaPersona(stPersona persona);
///PROTOTIPADO FUNCIONES:
nodoDoble *inicLista();
nodoDoble *crearNodo(stPersona persona);
nodoDoble *insertarEnOrdenPorEdad(nodoDoble *lista, nodoDoble *nodoInsertar);
nodoDoble *agregarAlPrincipio(nodoDoble *lista, nodoDoble *nodoInsertar);
nodoDoble *agregarAlFinal(nodoDoble *lista, nodoDoble *nodoInsertar);
nodoDoble *PasarDeArchivoAListasDobles(char nombreArchi[], nodoDoble *lista);
void mostrarListaRecursiva(nodoDoble *lista);
void mostrarUnNodoEspecifico(nodoDoble *lista);
nodoDoble *eliminarPrimerNodoDeLaLista(nodoDoble *lista);
nodoDoble *eliminarUltimoNodoDeLaLista(nodoDoble *lista);
nodoDoble *eliminarUnNodoPorEdad(nodoDoble *lista, int edad);
nodoDoble *buscarUnNodoPorValor(nodoDoble *lista, char nombre[20]);
nodoDoble *buscarUltimoNodoRecursion(nodoDoble *lista);
int determinarSiUnaListaEsCapicuaRecursion(nodoDoble *lista, nodoDoble *inicio, nodoDoble *fin);
int recorrerUnaListaYDeterminarCuantosNodosTiene(nodoDoble *lista);
nodoDoble *eliminarNodoMitadLista(nodoDoble *lista);

nodoDoble* elimina_nodo_mitad_lista (nodoDoble* lista);

nodoDoble *practicandoInsertarEnOrdenPorEdad(nodoDoble *lista, nodoDoble *nodoInsertar);



int main(){
    char nombreArchi[] = {"personas.txt"};
    stPersona persona;
    char nombre[20];
    //cargarPesonasArchi(nombreArchi,persona);
    printf("\nMostrando Archivo\n");
    mostrarArchi(nombreArchi);
    nodoDoble *lista = inicLista();
    lista = PasarDeArchivoAListasDobles(nombreArchi,lista);
    printf("\nMOSTRANDO LISTA\n");
    mostrarListaRecursiva(lista);
//    printf("Ingrese el nombre: ");
//    fflush(stdin);
//    gets(nombre);
//    nodoDoble *aux;
//    aux = buscarUnNodoPorValor(lista,nombre);
//    printf("\nDEBUGGG IMPRIMIENDO DIREC MEMORIA ---> %p\n", aux);
//    mostrarUnNodoEspecifico(aux);
//    lista = eliminarPrimerNodoDeLaLista(lista);
//    printf("\nMOSTRANDO LISTA CON PRIMER ELEMENTO ELIMINADO\n");
//    mostrarListaRecursiva(lista);
///PUNTO 1 DE LA GUIA ES HACER LA FUNCION DE ELIMINAR UN NODO ESPECIFICO:
//    int dato;
//    printf("Ingrese la edad del registro a borrar: ");
//    fflush(stdin);
//    scanf("%i", &dato);
//    lista = eliminarUnNodoPorEdad(lista, dato);
//    if(lista != NULL){
//        printf("\nMOSTRANDO LISTA CON EL ELEMENTO ELIMINADO.\n");
//        mostrarListaRecursiva(lista);
//    }else printf("\nNo encontramos un registro con esa edad.\n");
///PUNTO 2 DETERMINAR SI UNA LISTA ES CAPICUA
    nodoDoble *inicio = lista;
    nodoDoble *fin = buscarUltimoNodoRecursion(lista);
    int resultado = determinarSiUnaListaEsCapicuaRecursion(lista, inicio, fin);
    if(resultado == 0)printf("\nLa lista no es capicua.\n");
    else printf("\nLa lista es capicua.\n");
///PUNTO 3:
    lista = elimina_nodo_mitad_lista(lista);
//    int cantidadDeNodos = recorrerUnaListaYDeterminarCuantosNodosTiene(lista);
//    printf("\nCantidad de nodos de la lista: %i \n", cantidadDeNodos );
//    lista = eliminarNodoMitadLista(lista);
    printf("\nMOSTRANDO LA LISTA CON EL NODO DE LA MITAD ELIMINADO: \n");
    mostrarListaRecursiva(lista);
}
///FUNCIONES BASICAS LISTAS DOBLES:
///inicializar listas dobles:
nodoDoble *inicLista(){
    return NULL;
}
///Crear nodo
nodoDoble *crearNodo(stPersona persona){
    nodoDoble *aux = (nodoDoble *)malloc(sizeof(nodoDoble));
    aux->persona = persona;
    aux->anterior = NULL;
    aux->siguiente = NULL;
    return aux;
}
///Agregar al principio:
nodoDoble *agregarAlPrincipio(nodoDoble *lista, nodoDoble *nodoInsertar){
    if(lista == NULL) nodoInsertar->siguiente = lista; ///Si la lista no tiene elementos
    else{///Si la lista tiene mas elementos
        nodoInsertar->siguiente = lista;
        lista->anterior = nodoInsertar;
    }
    return nodoInsertar;///Retornamos el nuevo inicio de la lista
}
///Agregar nodo al final:
nodoDoble *agregarAlFinal(nodoDoble *lista, nodoDoble *nodoInsertar){
    nodoDoble *aux = lista;
    if(lista == NULL) lista = nodoInsertar;
    else{
        while(aux->siguiente != NULL){///NOS DA LA POSICION DEL ULTIMO NODO
            aux = aux->siguiente;
        }
        ///INSERTAMOS EL ULTIMO NODO (NUEVO)
        nodoInsertar->anterior = aux;
        aux->siguiente = nodoInsertar;
    }
    return lista;
}
///Insertar nodo por edad:
nodoDoble *insertarEnOrdenPorEdad(nodoDoble *lista, nodoDoble *nodoNuevo){

    if(lista == NULL) {
        lista = agregarAlPrincipio(lista, nodoNuevo);
    }else{
        if(nodoNuevo->persona.edad < lista->persona.edad){
        lista = agregarAlPrincipio(lista,nodoNuevo);
    }else{
        nodoDoble *anteDeAux = lista;
        nodoDoble *aux = lista->siguiente;
        while(aux != NULL &&(nodoNuevo->persona.edad > aux->persona.edad)){
            anteDeAux = aux;
            aux = aux->siguiente;
        }
            if(aux != NULL){
                anteDeAux->siguiente = nodoNuevo;
                nodoNuevo->anterior = anteDeAux;
                aux->anterior = nodoNuevo;
                nodoNuevo->siguiente = aux;
            }
        }
    }
    return lista;
}

///Mostrar lista de manera recursiva:
void mostrarListaRecursiva(nodoDoble *lista){
    if(lista == NULL) printf("");
    else{
        printf("\n----------------------------------------------------->\n");
        printf("Nombre: %s\n", lista->persona.nombre);
        printf("Edad: %i", lista->persona.edad);
        printf("\n----------------------------------------------------->\n");
        mostrarListaRecursiva(lista->siguiente);
    }
}
///Mostrar un nodo:
void mostrarUnNodoEspecifico(nodoDoble *lista){
    if(lista != NULL){
        printf("\n...................................\n");
        printf("Nombre: %s\n", lista->persona.nombre);
        printf("Edad: %i", lista->persona.edad);
        printf("\n...................................\n");
    }else printf("\nNo encontramos ese registro. Intente con otro Nombre\n");

}
///Eliminar primer nodo de  la lista:
nodoDoble *eliminarPrimerNodoDeLaLista(nodoDoble *lista){
    if(lista == NULL) printf("\nLa lista esta vacia, no hay nada que eliminar.\n");
    else{
        nodoDoble *aux = lista;
        lista = lista->siguiente;
        lista->anterior = NULL;
        aux = NULL;
        free(aux);
    }
    return lista;
}
///Eliminar el ultimo nodo de la lista:
nodoDoble *eliminarUltimoNodoDeLaLista(nodoDoble *lista){
    nodoDoble *aux;
    nodoDoble *anteDeAux;
    if(lista == NULL) return NULL;
    if(lista ->siguiente == NULL){///Quiere decir q solo tiene un nodo
        free(lista);
    }else{///Quiere decir que tiene mas elementos
        aux = lista;
        anteDeAux = NULL;
        while(aux->siguiente != NULL){
            anteDeAux = aux;
            aux = aux->siguiente;
        }///Nos va posicionar en el ultimo nodo
        aux->anterior = NULL;
        anteDeAux->siguiente = NULL; ///ANTE DE AUX ESTA UNA POSICION ANTES Q EL
        free(aux);///Tuve que utilizar anteDeAux para poder eliminar el ultimo nodo por completo.
    }
    return lista;
}
///Eliminar un nodo especifico:
nodoDoble *eliminarUnNodoPorEdad(nodoDoble *lista, int edad){
    nodoDoble *aux;
    nodoDoble *anteDeAux;
    if(lista == NULL) printf("\nLa lista esta vacia no hay nada que eliminar.\n");
    else{
        if(lista->persona.edad == edad){///Caso de que sea el primer elemento
            lista = eliminarPrimerNodoDeLaLista(lista);
        }else{
            anteDeAux = lista;
            aux = lista->siguiente;
            while(aux->siguiente != NULL && (aux->persona.edad != edad)){
                anteDeAux = aux;
                aux = aux->siguiente;
            }
            if(aux != NULL && aux->persona.edad == edad){
                anteDeAux->siguiente = aux->siguiente;
                aux->siguiente = anteDeAux->siguiente;
                free(aux);
                aux = NULL;
            }else return NULL;
        }
    }
    return lista;
}

///Buscar un nodo:
nodoDoble *buscarUnNodoPorValor(nodoDoble *lista, char nombre[20]){
    nodoDoble *aux = lista;
    if(lista == NULL){
        printf("\nLa lista esta vacia. No hay registros que buscar.\n");
        return lista;
    }
    if(strcmp(aux->persona.nombre,nombre) == 0){
        ///Quiere decir que el primer nodo de la lista coincide con el dato.
        printf("\nEl Nombre --> %s es el primer registro.\n", nombre);
        return aux;
    }else{///Si el primero no coincide la recorremos
        while(aux != NULL){
            if(strcmp(aux->persona.nombre,nombre) == 0){
                printf("\nEl Nombre --> %s se encuentra en los registros.\n", nombre);
                return aux;
            }
            aux = aux->siguiente;
        }
        if(aux == NULL){
            printf("\nEl nombre %s no se encuentra en los registros.\n", nombre);
            ///Quiere decir que se recorrio por completo y no encontro el nodo a buscar
        }
    }
    return  aux;
}
///CARGARLE DATOS AL ARCHIVO;
void cargarPesonasArchi(char nombreArchi[], stPersona persona){
    FILE *punteroArchi = fopen(nombreArchi,"a");
    char eleccion = 's';
    if(punteroArchi != NULL){
        while(eleccion == 's'){
            persona = crearUnaPersonaArchi();
            fwrite(&persona,sizeof(stPersona),1,punteroArchi);
            printf("\nPulsa 's' si desea continuar: ");
            fflush(stdin);
            scanf("%c", &eleccion);
        }
        fclose(punteroArchi);
    }
}
stPersona crearUnaPersonaArchi(){
    stPersona persona;
    printf("Nombre: ");
    fflush(stdin);
    gets(persona.nombre);
    printf("Edad: ");
    fflush(stdin);
    scanf("%i", &persona.edad);
    return persona;
}
void mostrarArchi(char nombreArchi[]){
    stPersona persona;
    FILE *punteroArchi = fopen(nombreArchi,"r");
    if(punteroArchi != NULL){
        while(!feof(punteroArchi)){
            fread(&persona,sizeof(stPersona),1,punteroArchi);
            if(!feof(punteroArchi)){
                mostrarUnaPersona(persona);
            }
        }
        fclose(punteroArchi);
    }
}
void mostrarUnaPersona(stPersona persona){
    printf("\n------------------------------------------------->\n");
    printf("Nombre: %s\n", persona.nombre);
    printf("Edad: %i", persona.edad);
    printf("\n------------------------------------------------->\n");
}
///PASAR DE UN ARCHIVO A LISTAS DOBLES:
nodoDoble *PasarDeArchivoAListasDobles(char nombreArchi[], nodoDoble *lista){
    FILE *punteroArchi = fopen(nombreArchi,"r");
    stPersona persona;
    if(punteroArchi != NULL){
        while(!feof(punteroArchi)){
            fread(&persona,sizeof(stPersona),1,punteroArchi);
            nodoDoble *nodoNuevo = crearNodo(persona);
            if(!feof(punteroArchi)){
                lista = practicandoInsertarEnOrdenPorEdad(lista,nodoNuevo);
            }
        }
        fclose(punteroArchi);
    }
    return lista;
}
///PRACTICANDO DE NUEVO EL DE INSERTAR EN ORDEN:

nodoDoble *practicandoInsertarEnOrdenPorEdad(nodoDoble *lista, nodoDoble *nodoInsertar){
    nodoDoble *anteAux;
    nodoDoble *aux;
    if(lista == NULL){///La lista no tiene elementos se lo agregamos al principio
        lista = agregarAlPrincipio(lista,nodoInsertar);
    }else{
        if(nodoInsertar->persona.edad < lista->persona.edad){///Caso q el primer elemento sea mayor q el de insertar
            lista = agregarAlPrincipio(lista,nodoInsertar);
        }else{///Caso en que tenemos que recorrer para ubicarlo en su posicion adecuada.
            anteAux = lista;
            aux = lista->siguiente;
            while(aux != NULL && nodoInsertar->persona.edad > aux->persona.edad){
                anteAux = aux;
                aux = aux->siguiente;
            }///El while frena cuando encuentra la posicion.
            if(aux != NULL){ ///Verificamos si es distinto de null porque si esta en null no le vamos a poder guardar nada.
                    anteAux->siguiente = nodoInsertar;
                    aux->anterior = nodoInsertar;
                    nodoInsertar->siguiente = aux;
                    nodoInsertar->anterior = anteAux;
            }
        }
    }
    return lista;
}
///Buscar ultimo nodo:
nodoDoble *buscarUltimoNodoRecursion(nodoDoble *lista){
    nodoDoble *aux = lista;
    if(aux->siguiente == NULL) printf("");
    else{
       aux = buscarUltimoNodoRecursion(aux->siguiente);
    }
    return aux;
}
///PUNTO 2 DE LA GUIA. DETERMINAR SI UNA LISTA ES CAPICUA DE MANERA RECURSIVA:
int determinarSiUnaListaEsCapicuaRecursion(nodoDoble *lista, nodoDoble *inicio, nodoDoble *fin){
    int flag = 0;
    if(inicio > fin) printf("");
    else{
        if(inicio->persona.edad == fin->persona.edad){
            flag = 1;
        }
        determinarSiUnaListaEsCapicuaRecursion(lista,inicio->siguiente,fin->anterior);
    }
    return flag;
}

///PUINTO 3:
///recorrer una lista y retornar la cantidad de nodos que tiene:
int recorrerUnaListaYDeterminarCuantosNodosTiene(nodoDoble *lista){
    nodoDoble *aux = lista;
    int contador = 0;
    while(aux != NULL){
        aux = aux->siguiente;
        contador++;
    }
    return contador;
}
nodoDoble *eliminarNodoMitadLista(nodoDoble *lista){
    int contador = 0;
    int totalNodos = recorrerUnaListaYDeterminarCuantosNodosTiene(lista);
    nodoDoble *aux = lista;
    nodoDoble *anteDeAux = lista;
    while(aux != NULL && contador != 2){
        anteDeAux = aux;
        aux = aux->siguiente;
        contador++;
    }///CUANDO TENEMOS LA POSICION PARA ELIMINAR EL NODO:
    if(aux != NULL){
        anteDeAux->siguiente = aux->siguiente;
        aux->siguiente = anteDeAux->siguiente;
        free(aux);
        aux = NULL;
    }
    return lista;
}





nodoDoble* elimina_nodo_mitad_lista (nodoDoble* lista)
{

    int totalNodos = 0;
    if (lista)
        {
        nodoDoble* aBorrar = inicLista();
        nodoDoble* ante = lista;
        nodoDoble* siguiente = lista->siguiente;

        totalNodos = recorrerUnaListaYDeterminarCuantosNodosTiene(lista);

        if (totalNodos % 2 == 0)
            {
            int i = 2;

            while ((siguiente) && (i < (totalNodos / 2) + 1))
                {
                ante = siguiente;
                siguiente = siguiente->siguiente;

                i++;
                }
            }
        else
            {
            int i = 2;

            while ((siguiente) && (i <= (totalNodos / 2)))
                {
                ante = siguiente;
                siguiente = siguiente->siguiente;
                i++;
                }
            }

        aBorrar = siguiente;
        siguiente = siguiente->siguiente;

        ante->siguiente = siguiente;

        free(aBorrar);
        }

    return lista;
}
