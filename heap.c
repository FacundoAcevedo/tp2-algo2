#ifndef _HEAP_H
#define _HEAP_H

#include <vector_dinamico.c>
#include <stdbool.h>  /* bool */
#include <stddef.h>	  /* size_t */

/* Prototipo de funciÃ³n de comparaciÃ³n que se le pasa como parÃ¡metro a las
 * diversas funciones del heap.
 * Debe recibir dos punteros del tipo de dato utilizado en el heap, y
 * debe devolver:
 *   menor a 0  si  a < b
 *       0      si  a == b
 *   mayor a 0  si  a > b
 */
typedef int (*cmp_func_t) (const void *a, const void *b);


/* FunciÃ³n de heapsort genÃ©rica. Esta funciÃ³n ordena mediante heap_sort
 * un arreglo de punteros opacos, para lo cual requiere que se
 * le pase una funciÃ³n de comparaciÃ³n. Modifica el arreglo "in-place".
 * Notar que esta funciÃ³n NO es formalmente parte del TAD Heap.
 */
void heapsort(void *elementos[], size_t cant, cmp_func_t cmp);

/*
 * ImplementaciÃ³n de un TAD cola de prioridad, usando un max-heap.
 *
 * Notar que al ser un max-heap el elemento mas grande serÃ¡ el de mejor
 * prioridad. Si se desea un min-heap, alcanza con invertir la funciÃ³n de
 * comparaciÃ³n.
 */

/* Tipo utilizado para el heap. */
struct heap_t {
	void** datos;
	size_t cant, tam;
	cmp_func_t cmp;
};

/* Crea un heap. Recibe como Ãºnico parÃ¡metro la funciÃ³n de comparaciÃ³n a
 * utilizar. Devuelve un puntero al heap, el cual debe ser destruido con
 * heap_destruir(). 
 */
heap_t *heap_crear(cmp_func_t cmp){
	heap_t* heap = malloc(sizeof(heap_t));
	if (!heap) return NULL;
	heap->datos = NULL;
	heap->cant = 0;
	heap->tam = 0;
	heap->cmp = cmp;
	return arbol;
}


/* Elimina el heap, llamando a la funciÃ³n dada para cada elemento del mismo.
 * El puntero a la funciÃ³n puede ser NULL, en cuyo caso no se llamarÃ¡.
 * Post: se llamÃ³ a la funciÃ³n indicada con cada elemento del heap. El heap
 * dejÃ³ de ser vÃ¡lido. */
bool heap_destruir(heap_t *heap, void destruir_elemento(void *e)){
	if (!heap) return false;
	if (destruir_elemento){
		for (int i = 0; i< heap->cant; i++){
			destruir_elemento(heap->datos[i];
		} 
	if (heap->datos) free(heap->datos);
	free(heap);
	}
}

/* Devuelve la cantidad de elementos que hay en el heap. */
size_t heap_cantidad(const heap_t *heap){
	if (!heap) return 0;
	return heap->cant;
}

/* Devuelve true si la cantidad de elementos que hay en el heap es 0, false en
 * caso contrario. */
bool heap_esta_vacio(const heap_t *heap){
	if (!heap) return false;
	if (heap->cant == 0) return true;
	else return false;
}

/* Agrega un elemento al heap. El elemento no puede ser NULL.
 * Devuelve true si fue una operaciÃ³n exitosa, o false en caso de error. 
 * Pre: el heap fue creado.
 * Post: se agregÃ³ un nuevo elemento al heap.
 */

// Crea un vector dinamico con espacio para elementos del tipo void*,
// tamanio 50.
// Pre: recibe un heap creado, un elemento void*
// Post: creo un vector dinamico del tipo void**, tamanio 50, al cual apunta
// heap->datos.
bool heap_crear_vector(heap_t* heap, void* elem){
	heap->datos = malloc(50 * sizeof(void*));
	if (!heap->datos){
		free(heap->datos);
		return false;
	}
	// Doy nuevo valor a heap->tam
	heap->tam = heap->tam + 50;
	return true;
}

// Agrega 50 espacios tipo void* al vector heap->datos.
bool heap_agrandar_vector(heap_t* heap, void* elem){
	void** datos_nuevo = realloc(heap->datos, (heap->tam + 50)* sizeof(void*));
	if (!datos_nuevo) return false;
	heap->datos = datos_nuevo; 
	// Doy nuevo valor a heap->tam
	heap->tam = heap->tam + 50;
	return true;
}

bool heap_swap (void** vector, size_t a, size_t b){
}

bool upheap(void** vector, size_t cantidad, cmp_func_t cmp){
	// Si cantidad == 0, o sea si el elemento ya se encuentra en primer
	// lugar del arreglo, no cambio nada y devuelvo true
	if (cantidad == 0) return true;
	
	size_t actual = cantidad -1:
	size_t padre = (actual -1)/2;
	while ( padre >= 0 ) {
		int r = cmp(vector[actual], vector[padre]);
		if (r <= 0) return true;
		else swap (vector, actual, padre);
		actual = padre;
		padre = (actual -1)/2;
	return true;
	}
}

bool heap_encolar(heap_t *heap, void *elem){
	if (!heap) return false;
	// Si heap->datos es un vector no inicializado, debo crear el vector
	if (!heap->datos) heap_crear_vector(heap, elem);
	// Si la cantidad de elementos ya es igual al tamanio, debo redimensionar
	if (heap->cant == heap->tam) heap_agrandar_vector(heap, elem);

	heap->datos[heap->cant] = elem;
	upheap(heap->datos, heap->cant, heap->cmp);
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
	void* dato_a_borrar = heap->datos[heap->cant -1];
	heap->cant --;
	swap (heap-cant -1, 0);
	if 
	
}

#endif // _HEAP_H

