#include <stdio.h>

#include "cliente.h"
#include "hash.h"

struct cliente {
	int x, y;
};

// Crea el hash clientes_db. db for database, BITCH
hash_t* clientes_db(hash_destruir_dato_t cliente_destruir){
	return hash_crear(cliente_destruir);
}

/* Interna */
// Crea un cliente
cliente_t* cliente_crear(int x, int y) {
	cliente_t* cliente = malloc (sizeof (cliente_t));
	if (!cliente) return NULL;
	cliente->x = x;
	cliente->y = y;
	return cliente;
}

// Recibe const char* telefono, int x e int y.
// Crea dato tipo cliente_t* con x e y, luego llama a hash_guardar con el
// cliente creado y el telefono como clave.
bool cliente_guardar(hash_t* clientes_db, const char* telefono, int x, int y){
	cliente_t* cliente = cliente_crear(x, y);
	bool guardar = hash_guardar(clientes_db, telefono, cliente);
	if (!guardar) return false;
	return true;
}

// Llama a hash_obtener con la clave telefono, devuelve x e y
cliente_t* cliente_obtener(hash_t* clientes_db, const char* telefono){
	cliente_t* cliente = hash_obtener(clientes_db, telefono);
	if (!cliente) return NULL;
	return cliente;
}

// Llama a hash_borrar, se destruye el cliente
bool cliente_borrar(hash_t* clientes_db, const char* telefono){
	bool borrar = hash_borrar(clientes_db, telefono);
	if (!borrar) return false;
	return true;
}

// Destruye dato tipo cliente_t*
void cliente_destruir(cliente_t* cliente){
	if (!cliente) return;
	free (cliente);
	return;
}
	
