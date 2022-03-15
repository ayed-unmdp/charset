#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 256

/**
 * @brief Estructura para administrar conjuntos de caracteres
 * (versión 2)
 */
typedef struct {
    char v[MAX_CHARS];    
} charset;

typedef charset* pcharset;


/**
 * @brief Crea e inicializa un conjunto de caracteres vacío.
 * 
 * @return puntero al conjunto de caracteres. 
 */
charset* charset_init(){
    charset* result;
    result = (charset*)malloc(sizeof(charset));

    for (int i = 0; i < 256; i++){
        result->v[i] = 0;
    }

    return result;
}

/**
 * @brief Destruye y libera la memoria de un conjunto de caracteres
 * 
 * @param cs conjunto de caracteres a liberar. 
 */
void charset_free(charset *cs) {
    free(cs);
}

/**
 * @brief agrega un carácter a un conjunto de caracteres
 * 
 * @param cs conjunto de caracteres
 * @param c carácter a agregar
 * si el carácter ya estaba, lo deja como estaba.
 */
void charset_add(charset *cs, unsigned char c){
    cs->v[c] = 1;
}

/**
 * @brief remueve un caracter de un conjunto de caracteres
 * 
 * @param cs conjunto de caracteres
 * @param c carácter a remover 
 * si el carácter no estaba, no hace nada
 */
void charset_remove(charset *cs, unsigned char c){
    cs->v[c] = 0;
}

/**
 * @brief permite consultar si un carácter pertenece a un conjunto. 
 * 
 * @param cs conjunto de caracteres
 * @param c caracter por el cual se consulta
 * @return int 1 = el caracter pertenece al conjunto, 0 si no.
 */
int charset_in(charset *cs, unsigned char c){
    // devuelve 255 si está o 0 si no está
    return cs->v[c];
}

/**
 * @brief agrega al conjunto de caracteres 
 * todos los caracteres de un string
 * 
 * @param cs conjunto de caracteres 
 * @param s strinc con los caracteres a agregar
 */
void charset_add_str (charset *cs, char *s) {    
    if (s == NULL) return;
    while (*s != '\0'){
        charset_add (cs, *s);
        s++;
    }
}

/**
 * @brief agrega al conjunto de caracteres 
 * todos los caracteres en un rango ASCII
 * 
 * @param cs con junto de caracteres 
 * @param from carácter inicial
 * @param to carácter final
 */
void charset_add_range (charset *cs,unsigned char from, unsigned char to) {    
    for (unsigned char i = from; i <= to; i++){
        charset_add (cs, i);
    }
}

void charset_print(charset *cs) {
    for (int i = 0; i < 256; i++) {
        if (charset_in(cs, (char)i)) {
            printf(" %c", (char)i);
        }
    }
    printf("\n");
}

void test_charset_v2 () {
    charset *cs = charset_init();

    charset_add(cs, 'a');
    charset_add(cs, 'b');
    charset_add(cs, 'c');
    charset_add(cs, 'd');


    printf ("Conentendio luego de la carga: ");
    charset_print(cs);

    charset_remove(cs, 'a');

    printf ("Contenido luego de quitar 'a': ");
    charset_print(cs);

}

