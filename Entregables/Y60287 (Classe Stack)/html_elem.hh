#ifndef HTML_ELEM_HH
#define HTML_ELEM_HH

#include <string>
/**
 * @brief Determina si un string és un tag d'HTML (ja sigui d'obrir o tancar)
 * 
 * @b Exemples:
 * ```
 * is_tag("<html>") => true
 * is_tag("</span>") => true
 * is_tag("hello") => false
 * ```
 * 
 * @param s un string.
 * @returns `true` si `s` és un tag d'HTML, `false` altrament.
 */
bool is_tag(std::string s);

/**
 * @brief Determina si un string és un tag d'HTML de tancar.
 * 
 * @b Exemples:
 * ```
 * is_close_tag("<html>") => false
 * is_close_tag("</span>") => true
 * ```
 * 
 * @param s un string.
 * @returns `true` si `s` és un tag d'HTML de tancar, `false` altrament.
 */
bool is_close_tag(std::string s);

/**
 * @brief Extreu el nom d'un tag d'HTML.
 *
 * @b Exemples:
 * ```
 * tag_name("<html>") => "html"
 * tag_name("</span>") => "span"
 * ```
 *
 * @param s string que conté un tag d'HTML (obrir o tancar).
 * @pre s és un tag d'HTML vàlid.
 *
 */
std::string tag_name(std::string s);

#endif