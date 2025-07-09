#ifndef DJVUIMAGE_UTILS_H
#define DJVUIMAGE_UTILS_H

#include <cstdint>  // ensures uint16_t and uint32_t are known before DjVu headers

#include <libdjvu/ddjvuapi.h>
#include "external/DjVuImage.h"

DjVuImage *get_djvuimage_from_page(ddjvu_page_t *page);

#endif // DJVUIMAGE_UTILS_H
