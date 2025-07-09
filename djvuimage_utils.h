#ifndef DJVUIMAGE_UTILS_H
#define DJVUIMAGE_UTILS_H

#include <libdjvu/ddjvuapi.h>
#include "external/DjVuImage.h"

DjVuImage *get_djvuimage_from_page(ddjvu_page_t *page);

#endif // DJVUIMAGE_UTILS_H
