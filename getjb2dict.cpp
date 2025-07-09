// getjb2dict.cpp
//
// Extracted and adapted from:
//   https://github.com/jsbien/djview4shapes/blob/master/src/qdjvu.cpp
// This file is reused in accordance with the GNU General Public License,
// as published by the Free Software Foundation; either version 2 of the License,
// or (at your option) any later version.

#include <libdjvu/ddjvuapi.h>
#include "external/DjVuImage.h"
#include "external/JB2Image.h"
#include "getjb2dict.h"

DJVU::JB2Dict* get_jb2dict_from_page(ddjvu_page_t* page)
{
    if (!page)
        return nullptr;

    void *internal = ddjvu_page_get_fulldata(page);
    if (!internal)
        return nullptr;

    DJVU::DjVuImage *image = static_cast<DJVU::DjVuImage*>(internal);
    if (!image)
        return nullptr;

    DJVU::GP<DJVU::JB2Image> jb2image = image->get_jb2image();
    if (!jb2image)
        return nullptr;

    return jb2image->get_dict();
}
