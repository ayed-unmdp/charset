#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Estructura para administrar conjuntos de caracteres
 * (versión 1)
 */
typedef struct {
    char v[32];
} charset;

/**
 * @brief Crea e inicializa un conjunto de caracteres vacío.
 * 
 * @return puntero al conjunto de caracteres. 
 */
charset *charset_init() {
    charset *result;
    result = malloc(sizeof(charset));

    for (int i = 0; i < 32; i++) {
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
 * @brief calcula máscara e índicie para guaradar un caracter
 * 
 * @param c caracter para calcualr
 * @param index puntero a índicie
 * @param mask puntero a máscara
 * si el carácter ya estaba, lo deja como estaba.
 */
void _charset_hash (unsigned char c, unsigned char *index, unsigned char *mask){
    *index = c / 8;
    char offset = c % 8;
    *mask = 1;
    *mask = *mask << offset;
}

/**
 * @brief agrega un carácter a un conjunto de caracteres
 * 
 * @param cs conjunto de caracteres
 * @param c carácter a agregar
 * si el carácter ya estaba, lo deja como estaba.
 */
void charset_add(charset *cs, unsigned char c) {    
    char i, mask;
    _charset_hash (c, &i, &mask); 
    cs->v[i] = cs->v[i] | mask;
}


/**
 * @brief remueve un caracter de un conjunto de caracteres
 * 
 * @param cs conjunto de caracteres
 * @param c carácter a remover 
 * si el carácter no estaba, no hace nada
 */
void charset_remove(charset *cs, unsigned char c) {
    char i, mask;
    _charset_hash (c, &i, &mask); 
    cs->v[i] = cs->v[i] & (~mask);
}

/**
 * @brief permite consultar si un carácter pertenece a un conjunto. 
 * 
 * @param cs conjunto de caracteres
 * @param c caracter por el cual se consulta
 * @return int 1 = el caracter pertenece al conjunto, 0 si no.
 */
int charset_in(charset *cs, unsigned char c) {
    // devuelve 1 si está o 0 si no está
    char result = 0;
    char i, mask;
    _charset_hash (c, &i, &mask); 
    if ((cs->v[i] & mask) != 0) {
        result = 1;
    }
    return result;
}

/**
 * @brief agrega al conjunto de caracteres 
 * todos los caracteres de un string
 * 
 * @param cs conjunto de caracteres 
 * @param s strinc con los caracteres a agregar
 */
void charset_add_str (charset *cs, unsigned char *s) {    
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
        char c = (char) i;
        charset_add (cs, c);
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

