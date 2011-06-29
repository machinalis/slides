#include <glib.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

using namespace std;

GHashTable *usuarios = NULL;

void cargar_usuarios(const char *archivo) {
	ifstream f(archivo);
	string usuario, clave;

	usuarios = g_hash_table_new_full(
		g_str_hash,
		g_str_equal,
		g_free,
		g_free);

	while (f >> usuario >> clave) {
		g_hash_table_insert(usuarios, g_strdup(usuario.c_str()), g_strdup(clave.c_str()));
	}
}

gint main(gint argc, gchar **argv) {
	cargar_usuarios("usuarios.txt");
	while (TRUE) {
		string nombre;
		string clave;
		gchar *clave_real = NULL;

		/* Preguntar al usuario */
		cout << "Usuario: " << flush;
		cin >> nombre;
		if (nombre == "q") break; /* Salir si no ponen nada */
		cout << "Clave: " << flush;
		cin >> clave;

//		/* Sacar el \n final */
//		nombre[strlen(nombre)-1] = clave[strlen(clave)-1] = '\0';

		/* Validar */
		clave_real = (gchar *)g_hash_table_lookup(usuarios, nombre.c_str());
		if (g_strcmp0(clave.c_str(), clave_real) == 0) {
			cout << "Usuario " << nombre << " aceptado!" << endl;
		} else {
			cout << "Usuario(" << nombre << ")/clave(" << clave <<"); inexistente o no coinciden!" << endl;
		}
	}
	g_hash_table_destroy(usuarios);
	return 0;
}

