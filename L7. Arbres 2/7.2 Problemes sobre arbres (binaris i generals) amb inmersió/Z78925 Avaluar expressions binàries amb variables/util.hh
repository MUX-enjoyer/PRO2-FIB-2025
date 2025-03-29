#ifndef UTILS_HH
#define UTILS_HH

#include <string>
#include <utility>

/**
 * @brief Comprova si un string està format només per dígits
 *
 * Un string buit no és un número. NO es comprova si la longitud
 * de `s` és massa llarga per poder-se convertir a un `int`.
 *
 * @param s String a comprovar
 * @return `true` si és un número, `false` altrament.
 */
bool is_number(std::string s);

/**
 * @brief Comprova si un string està format només per lletres,
 * i per tant és un nom de variable vàlid.
 *
 * Un string buit no és un nom de variable.
 *
 * @param s String a comprovar
 * @return `true` si és un nom de variable, `false` altrament.
 */
bool is_var_name(std::string s);

/**
 * @brief Converteix un string a un enter
 *
 * Per simplicitat, si el string no és un número, retorna 0
 *
 * @param s String a convertir
 * @return `int` El resultat de la conversió. Si la conversió no és possible el programa aborta.
 *
 * @note
 */
int string_to_int(std::string s);

#endif