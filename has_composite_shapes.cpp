// Add this as the FIRST line in getjb2dict.cpp and has_composite_shapes.cpp

#include <cstdint>
#include <iostream>
#include <ddjvuapi.h>
#include "external/DjVuImage.h"
#include "external/JB2Image.h"
#include "external/JB2Dict.h"
#include "external/JB2Shape.h"

extern "C" DJVU::DjVuImage* ddjvu_get_DjVuImage(ddjvu_page_t* page);

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <djvu-file>\n";
        return 1;
    }

    const char* filename = argv[1];

    ddjvu_context_t* context = ddjvu_context_create("has_composite_shapes");
    if (!context) {
        std::cerr << "Failed to create ddjvu context\n";
        return 1;
    }

    ddjvu_document_t* doc = ddjvu_document_create_by_filename(context, filename, TRUE);
    if (!doc) {
        std::cerr << "Failed to open document\n";
        return 1;
    }

    while (!ddjvu_document_decoding_done(doc)) {
        ddjvu_message_wait(context);
    }

    int page_count = ddjvu_document_get_pagenum(doc);
    std::cout << "Page count: " << page_count << "\n";

    for (int i = 0; i < page_count; ++i) {
        ddjvu_page_t* page = ddjvu_page_create_by_pageno(doc, i);
        if (!page) continue;

        while (!ddjvu_page_decoding_done(page)) {
            ddjvu_message_wait(context);
        }

        DJVU::DjVuImage* djvu_page = ddjvu_get_DjVuImage(page);
        if (!djvu_page) {
            std::cerr << "Failed to get DjVuImage for page " << i << "\n";
            ddjvu_page_release(page);
            continue;
        }

        DJVU::GP<DJVU::JB2Image> image = djvu_page->get_jb2_image();
        DJVU::JB2Dict* dict = image->get_dict();
        if (!dict) {
            std::cerr << "No JB2Dict found.\n";
            ddjvu_page_release(page);
            continue;
        }

        int composite_count = 0;
        for (int j = 0; j < dict->get_shape_count(); ++j) {
            const DJVU::JB2Shape* shape = dict->get_shape(j);
            if (!shape->is_bitmap_shape() && shape->blit_count() > 1) {
                std::cout << "Page " << i << ": Shape " << j
                          << " is composite (" << shape->blit_count() << " blits)\n";
                composite_count++;
            }
        }

        if (composite_count == 0) {
            std::cout << "Page " << i << ": No composite shapes\n";
        }

        ddjvu_page_release(page);
    }

    ddjvu_document_release(doc);
    ddjvu_context_release(context);

    return 0;
}
