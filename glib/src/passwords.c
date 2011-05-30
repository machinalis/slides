#include <glib.h>
#include <stdio.h>
#include <string.h>

GHashTable *usuarios = NULL;

void cargar_usuarios(gchar *archivo) {
	FILE *f = fopen(archivo, "r");
	gchar usuario[50], clave[50]; 
	/* Esto es susceptible a buffer overflow. Solo para simplificar el ejemplo */
	
	usuarios = g_hash_table_new_full(
		g_str_hash,
		g_str_equal,
		g_free,
		g_free);
	
	g_warn_if_fail(f!= NULL); /* No habra usuarios disponibles*/

	while (fscanf(f, "%s %s", usuario, clave) == 2) {
		g_hash_table_insert(usuarios, g_strdup(usuario), g_strdup(clave));
	}
	fclose(f);
}

gint main(gint argc, gchar **argv) {
	cargar_usuarios("usuarios.txt");
	while (TRUE) {
		gchar nombre[50];
		gchar clave[50];
		gchar *clave_real = NULL;

		/* Preguntar al usuario */
		g_print("Usuario: ");
		fgets(nombre, G_N_ELEMENTS(nombre), stdin);
		if (strlen(nombre) == 1) break; /* Salir si no ponen nada */
		g_print("Clave: ");
		fgets(clave, G_N_ELEMENTS(clave), stdin);

		/* Sacar el \n final */
		nombre[strlen(nombre)-1] = clave[strlen(clave)-1] = '\0';

		/* Validar */
		clave_real = g_hash_table_lookup(usuarios, nombre);
		if (g_strcmp0(clave, clave_real) == 0) {
			g_print("Usuario %s aceptado!\n", nombre);
		} else {
			g_print("Usuario(%s)/clave(%s); inexistente o no coinciden!\n", nombre, clave);
		}
	}
	g_hash_table_destroy(usuarios);
	return 0;
}

