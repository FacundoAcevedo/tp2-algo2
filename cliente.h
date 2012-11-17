#include <stdio.h>
#include "hash.h"

typedef struct cliente cliente_t;

// Crea la base de datos clientes
hash_t* clientes_db (hash_destruir_dato_t cliente_destruir);

// Recibe const char* telefono, int x e int y.
// Crea dato tipo cliente_t* con x e y, luego llama a hash_guardar con el
// cliente creado y el telefono como clave.
bool cliente_guardar(hash_t* clientes_db, const char* telefono, int x, int y);

// Llama a hash_obtener con la clave telefono, devuelve x e y
cliente_t* cliente_obtener(hash_t* clientes_db, const char* telefono);

// Llama a hash_borrar, se destruye el cliente
bool cliente_borrar(hash_t* clientes_db, const char* telefono);

