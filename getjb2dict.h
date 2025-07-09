/*
 * getjb2dict.h
 *
 * Extracted from djview4shapes (https://github.com/jsbien/djview4shapes)
 * which is a fork of DjView4 project based on DjVuLibre.
 * Copyright for the fork: Michał Rudolf, Grzegorz Chimosz.
 *
 * Maintainer of the extract: Janusz S. Bień (jsbien@uw.edu.pl)
 *
 * License: GNU General Public License v2 or later
 * See: https://www.gnu.org/licenses/old-licenses/gpl-2.0.html
 *
 * This header declares the function get_jb2dict_from_page() for retrieving
 * the JB2Dict object from a decoded DjVu page using libdjvulibre internals.
 */

#ifndef GETJB2DICT_H
#define GETJB2DICT_H

#include <ddjvuapi.h>

// Forward declare JB2Dict
namespace DJVU {
  class JB2Dict;
}

DJVU::JB2Dict* get_jb2dict_from_page(ddjvu_page_t *page);

#endif
