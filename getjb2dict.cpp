/*
 * getjb2dict.cpp
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
 * This file implements the function get_jb2dict_from_page(), which retrieves
 * the JB2Dict from a DjVu page using libdjvulibre internals via ddjvuapi.
 * It avoids requiring a full rebuild of DjVuLibre by working with headers
 * already vendored in the external/ directory.
 */

#include "getjb2dict.h"

#include "external/DjVuImage.h"
#include "external/JB2Image.h"
#include "external/JB2Dict.h"

using namespace DJVU;

DJVU::JB2Dict* get_jb2dict_from_page(ddjvu_page_t *page) {
    if (!page) return nullptr;

    DjVuImage *image = ddjvu_get_DjVuImage(page);
    if (!image) return nullptr;

    GP<JB2Image> jb2image = image->get_jb2image();
    if (!jb2image) return nullptr;

    return jb2image->get_dict();
}
