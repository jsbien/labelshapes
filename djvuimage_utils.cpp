#include "override_stdint_and_threads.h"
#include "fix_stdint.h"
#include "djvuimage_utils.h"

// This function is based on djview4shapes/src/qdjvu.cpp
// stripped of Qt dependencies. Original authorship:
// Copyright (C) 2002  Léon Bottou
// Licensed under GNU General Public License v2 or later.

DjVuImage *get_djvuimage_from_page(ddjvu_page_t *page)
{
    if (!page)
        return nullptr;

    // Access the opaque pointer set internally by DjVuLibre
    void *internal = ddjvu_page_get_fulldata(page);

    // In DjVuLibre, this is a pointer to DjVuImage
    return static_cast<DjVuImage *>(internal);
}
