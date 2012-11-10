
#include "heap.h"
#include <stdbool.h>  /* bool */
#include <stddef.h>	  /* size_t */
#include <stdlib.h>
#include <stdio.h>

struct heap{
	void** datos;
	size_t cant, tam;
	cmp_func_t cmp;
};

void heap_swap (void** vector, size_t a, size_t b){
	void* aux = vector[a];
	vector[a] = vector[b];
	vector[b] = aux;
	return;
}

bool downheap(void** vector, size_t a_bajar, size_t cantidad, cmp_func_t cmp){
	size_t hijo1 = a_bajar*2;
	size_t hijo2 = (a_bajar*2)+1;
	size_t a_subir;
	// Mientras al menos el priemer hijo este dentro del arbol
	while (hijo1 < cantidad) {
		// Si no hay hijo 2
		if (hijo2 == cantidad)
			a_subir = hijo2;

		// SI tengo dos hijos
		// Determino con cual hijo voy a intercambiar, eligiendo el mayor de ellos
		else{
			int hijo_elegido = cmp(vector[hijo1], vector[hijo2]);
			if (hijo_elegido >= 0)
				a_subir = hijo1;
			else
				a_subir = hijo2;
			}
		// Comparo el valor a mover con el hijo elegido
		int r = cmp(vector[a_bajar], vector[a_subir]);
		// Si el padre es mayor o igual que el hijo elegido, no hago nada
		if (r >= 0) return true;
		// Si el padre es menor que el hijo elegido, los intercambio
		else heap_swap (vector, a_subir, a_bajar);
		
		a_bajar = a_subir;
		hijo1 = (a_bajar*2);
		hijo2 = (a_bajar*2) +1;
	}
	return true;
}


/* FunciÃ³n de heapsort genÃ©rica. Esta funciÃ³n ordena mediante heap_sort
 * un arreglo de punteros opacos, para lo cual requiere que se
 * le pase una funciÃ³n de comparaciÃ³n. Modifica el arreglo "in-place".
 * Notar que esta funciÃ³n NO es formalmente parte del TAD Heap.
 */

// por cada nodo aplica downheap. Es O(n)
//~ void heapify(void* datos[]);
	// Ciclo que arranca desde el padre del ultimo nodo (indice del ultimo
	// hijo, padre(hijo) = indice deseado), se le aplica downheap; 
	// despues restando 1 pasa a su hermano y primos
	

// O(nlogn)
//~ void heapsort(void *elementos[], size_t cant, cmp_func_t cmp){
	//~ // Recibo un arreglo cualquiera. Lo primero que tengo que hacer es 
	//~ // heapificarlo, es decir, darle la propiedad del heap.
	//~ heapify(elementos);
	//~ //el primer elemento se intercambia con el ultimo, y se hace el 
	//~ //downheap del primero. O(nlogn)	
	//~ // Ciclo:
		//~ heap_swap(elementos[], 0, cant);
		//~ downheap(elementos, 0);
//~ 
//~ }


/* Crea un heap. Recibe como Ãºnico parÃ¡metro la funciÃ³n de comparaciÃ³n a
 * utilizar. Devuelve un puntero al heap, el cual debe ser destruido con
 * heap_destruir(). 
 */
heap_t* heap_crear(cmp_func_t cmp){
	heap_t* heap = malloc(sizeof(heap_t));
	if (!heap) return NULL;
	heap->datos = NULL;
	heap->cant = 0;
	heap->tam = 0;
	heap->cmp = cmp;
	return heap;
}


/* Elimina el heap, llamando a la funciÃ³n dada para cada elemento del mismo.
 * El puntero a la funciÃ³n puede ser NULL, en cuyo caso no se llamarÃ¡.
 * Post: se llamÃ³ a la funciÃ³n indicada con cada elemento del heap. El heap
 * dejÃ³ de ser vÃ¡lido. */
bool heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
	if (!heap) return false;
	if (destruir_elemento){
		for (int i = 0; i< heap->cant; i++){
			destruir_elemento(heap->datos[i]);
		} 
	if (heap->datos) free(heap->datos);
	free(heap);
	}
	return true;
}

//~ /* Devuelve la cantidad de elementos que hay en el heap. */
size_t heap_cantidad(const heap_t *heap){
	if (!heap) return 0;
	return heap->cant;
}
// Auxiliar para las pruebas: devuelve la variable tamanio
size_t heap_tamanio(const heap_t* heap){
	if (!heap) return 0;
	return heap->tam;
}

/* Devuelve true si la cantidad de elementos que hay en el heap es 0, false en
 * caso contrario. */
bool heap_esta_vacio(const heap_t *heap){
	if (!heap) return false;
	if (heap->cant == 0) return true;
	else return false;
}

// Crea un vector dinamico con espacio para elementos del tipo void*,
// tamanio 50.
// Pre: recibe un heap creado, un elemento void*
// Post: creo un vector dinamico del tipo void**, tamanio 50, al cual apunta
// heap->datos.
bool heap_crear_vector(heap_t* heap, void* elem){
	heap->datos = malloc(50 * sizeof(elem));
	if (!heap->datos){
		free(heap->datos);
		return false;
	}
	// Doy nuevo valor a heap->tam
	heap->tam = heap->tam + 50;
	return true;
}

// Redimensiona un vector dinamico con espacio para elementos del tipo void*,
// agregando 50 lugares.
// Pre: recibe un heap creado, un elemento void*. heap->datos contiene
// exactamente multiplo de 50 elementos.
// Post: el vector dinamico del tipo void** del heap, contiene espacio para 50 elementos
// mas.
bool heap_agrandar(heap_t* heap, void* elem){
	// Creo un nuevo vector con 50 espacios mas que heap->datos del tamanio del elemento pasado
	void** nuevo_datos = malloc((heap->tam + 50)*sizeof(elem));
	if (!nuevo_datos){
		free(nuevo_datos);
		return false;
	}
	// Copio los elementos de heap->datos en el nuevo vector
	int i =0;
	while (i<50){
		nuevo_datos[i] = heap->datos[i];
		i++;
	}
	// Libero el viejo vector heap->datos
	free(heap->datos);
	// Apunto heap->datos al nuevo vector
	heap->datos = nuevo_datos;
	// Doy nuevo valor a heap->tam
	heap->tam = heap->tam + 50;
	return true;
}
// Redimensiona un vector dinamico con espacio para elementos del tipo void*,
// quitando 50 lugares.
// Pre: recibe un heap creado. Heap->datos contiene exactamente multiplo 
// de 50 elementos y heap->cant - heap->tam = 50.
// Post: el vector dinamico del tipo void** del heap, contiene espacio 
// para 50 elementos menos.
bool heap_achicar(heap_t* heap){
	int i = 50;
	// Libero los ultimos 50 espacios en heap->datos
	while (i>= 0){
		free (heap->datos[heap->tam - i]);
		i--;
	}
	// Doy nuevo valor a heap->tam
	heap->tam = heap->tam - 50;
	return true;
}

//Pre: el vector qu eme pasan tiene más de un solo elemento, porque sino
// No tiene sentido moverlo
bool upheap(void** vector, size_t a_mover, cmp_func_t cmp){
	//~ printf("Entre a upheap porque cantidad: %zu\n", cantidad);
	int actual = a_mover;
	//~ printf("actual: %zu, apunta a %d \n",actual, vector[actual]);
	
	int padre;
	if (actual <= 2) padre = 0;
	else padre = (actual -1)/2;
	//~ printf("actual-1 / 2: %zu, apunta a %d\n", padre, vector[padre]);
	while ( padre >= 0 ) {
		int r = cmp(vector[actual], vector[padre]);
		
		if (r <= 0) {
			//~ printf(" r <= 0 ==> Actual: '%d', Padre: '%d'\n", vector[actual], vector[padre]);
			return true;
		}
		else{
		//~ printf("r > 0 ==> Actual: '%d', Padre: '%d'\n", vector[actual], vector[padre]);
		heap_swap (vector, actual, padre);
		//~ printf("Luego de swap: Actual: '%d', Padre: '%d'\n", vector[actual], vector[padre]);
		actual = padre;
		padre = (actual -1)/2;
		}
		//~ puts("\n");
	}
	return true;
	
}

//~ void printeo(heap_t* heap){
	//~ size_t i = 0;
	//~ while (i<heap->cant){
		//~ printf("i: %zu = %zu //",i,  heap->datos[i]);
		//~ i++;
	//~ }
	//~ return;
//~ }
/* Agrega un elemento al heap. El elemento no puede ser NULL.
 * Devuelve true si fue una operaciÃ³n exitosa, o false en caso de error. 
 * Pre: el heap fue creado.
 * Post: se agregÃ³ un nuevo elemento al heap.
 */
bool heap_encolar(heap_t* heap, void* elem){
	 if (!elem) return false;
	 if (heap->tam == 0) heap_crear_vector(heap, elem);
	 if (heap->cant == heap->tam) heap_agrandar(heap, elem);
	 heap->datos[heap->cant] = elem;
	 // Lo ubico en su lugar por prioridad si no es el unico elemento que hay
	 if (heap->cant >0) upheap(heap->datos, heap->cant, heap->cmp);
	 heap->cant ++;
	 return true;
	 }

/* Devuelve el elemento con mÃ¡xima prioridad. Si el heap esta vacÃ­o, devuelve
 * NULL. 
 * Pre: el heap fue creado.
 */
void *heap_ver_max(const heap_t *heap){
	if (!heap) return NULL;
	if (heap_esta_vacio(heap)) return NULL;
	return heap->datos[0];
}

/* Elimina el elemento con mÃ¡xima prioridad, y lo devuelve.
 * Si el heap esta vacÃ­o, devuelve NULL.
 * Pre: el heap fue creado.
 * Post: el elemento desencolado ya no se encuentra en el heap. 
 */
void *heap_desencolar(heap_t *heap){
	if (!heap) return NULL;
	if (heap_esta_vacio(heap)) return NULL;
	void* dato_a_borrar = heap->datos[0];
	heap_swap (heap->datos, heap->cant -1, 0);
	downheap(heap->datos, 0, heap->cant, heap->cmp);
	if ((heap->cant + 50)== heap->tam) heap_achicar(heap);
	heap->cant --;
	return dato_a_borrar;
}
//~ 
