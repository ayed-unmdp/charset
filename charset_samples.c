#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "charset_lib3.c"

/**
 * Contar la cantidad de vocales de una frase. 
 * (versión 1)
 */
int cuantas_vocales_1(char s[]) {
    int result = 0;
    for (int i = 0; i < strlen(s); i++) {
        char c = toupper(s[i]);
        if ((c == 'A') || (c == 'E') || (c == 'I') || (c == 'O') ||
            (c == 'U')) {
            result++;
        }
    }
    return result;
}

/**
 * Contar la cantidad de vocales de una frase. 
 * (versión 2)
 */
int cuantas_vocales_2(char s[]) {
    int result = 0;
    int size = strlen(s);
    char *vocales = "AaEeIiOoUu";
    for (int i = 0; i < size; i++) {
        char *v = vocales;
        while ((*v != '\0') && (*v != s[i])) {
            v++;
        }
        if ((*v != '\0')) {
            result++;
        }
    }
    return result;
}

/**
 * Contar la cantidad de vocales de una frase. 
 * (Generalizado)
 */
int cuantas_vocales_2_2(char s[], char *vocales) {
    int result = 0;
    int size = strlen(s);
    for (int i = 0; i < size; i++) {
        char *v = vocales;
        while ((*v != '\0') && (*v != s[i])) {
            v++;
        }
        if ((*v != '\0')) {
            result++;
        }
    }
    return result;
}

/**
 * Contar grupo de caracteres (*c) de una frase (*s). 
 */
int count_char_1 (char s[], char *c) {
    int result = 0;
    int size = strlen(s);
    for (int i = 0; i < size; i++) {
        char *v = c;
        while ((*v != '\0') && (*v != s[i])) {
            v++;
        }
        if ((*v != '\0')) {
            result++;
        }
    }
    return result;
}

/**
 * Contar la cantidad de vocales de una frase. 
 * (versión 3)
 */
int cuantas_vocales_3 (char s[]) {
    return count_char_1 (s, "AaEeIiOoUu");
}

/**
 * Contar conjunto de caracteres (*cs) de una frase (*s). 
 */
int count_char_2 (char *s, charset *cs) {
    int result = 0;
    while (*s != '\0') {
        result += charset_in(cs, *s);
        s++;
    }
    return result;
}

/**
 * Contar la cantidad de vocales de una frase. 
 * (versión 4)
 */
int cuantas_vocales_4(char s[]) {
    static charset *vocales;
    if (vocales == NULL) {
        vocales = charset_init();
        charset_add_str(vocales, "AaEeIiOoUu");
    }
    return count_char_2 (s, vocales);
}

/**
 * Validar que una cadena de caracteres, que representa un nombre de usuario,
 * solo conenga caraceres permitidos a..z, A..Z, 0..9, '_' y '-'
 * devuelve 0 = flase o 1 = true
 */
int username_validate(char *username) {
    int result = 1;

    // inicialización del conjunto de caracteres válidos
    charset *cs = charset_init();
    charset_add_range(cs, 'a', 'z');
    charset_add_range(cs, 'A', 'Z');
    charset_add_range(cs, '0', '9');
    charset_add_str(cs, "_-");

    // recorre el string
    while ((*username != '\0') && (result != 0)) {
        if (!(charset_in(cs, *username))) {
            result = 0;
        }
        username++;
    }

    charset_free(cs);  // elimina el grupo de caracteres

    return result;
}

void test1() {
    charset *cs = charset_init();
    charset_add(cs, ',');
    charset_add(cs, ';');
    charset_add(cs, '!');
    charset_add(cs, '$');
    charset_add(cs, '.');

    char s[] = "asd,f.!";

    int r = count_char_2 (s, cs);

    printf("Cantidad = %d\n", r);
}

void test_sample1() {
    char *username = "juan_1234-J";
    if (username_validate(username)) {
        printf("Nombre de usuario '%s' válido\n", username);
    } else {
        printf("Nombre de usuario '%s' NO VALIDO\n", username);
    }
}

void test_sample_vocales_1() {
    char frase[] = "¿Cuantas vocales hay en esta frase?";
    printf("cantidad de vocales (v1): %d\n En: '%s' \n",
           cuantas_vocales_1(frase), frase);
}

void test_sample_vocales_2() {
    char frase[] = "¿Cuantas vocales hay en esta frase?";
    printf("cantidad de vocales (v2): %d\n En: '%s' \n",
           cuantas_vocales_2(frase), frase);

    printf("cantidad de vocales (v2): %d\n En: '%s' \n",
           cuantas_vocales_2_2(frase, "AaEeIiOoUu"), frase);
}

void test_sample_vocales_3() {
    char frase[] = "¿Cuantas vocales hay en esta frase?";
    printf("cantidad de vocales (v3): %d\n En: '%s' \n",
           cuantas_vocales_3(frase), frase);

    char frase2[] = "Y esta otra frase ¿Cuantas vocales tiene?";
    printf("cantidad de vocales (v3): %d\n En: '%s' \n",
           cuantas_vocales_3(frase2), frase2);
}

void test_sample_vocales_4() {
    char frase[] = "Hola";
    printf("cantidad de vocales (v3): %d\n En: '%s' \n",
           cuantas_vocales_4(frase), frase);

    char frase2[] = "Hola MUNDO!";
    printf("cantidad de vocales (v3): %d\n En: '%s' \n",
           cuantas_vocales_4(frase2), frase2);
}

void main() { test_sample_vocales_4(); }
