#include <iostream>
#include <string>

#include <ddjvuapi.h>
#include "external/DjVuImage.h"
#include "external/JB2Image.h"
#include "external/JB2Shape.h"

extern DJVU::DjVuImage* ddjvu_get_DjVuImage(ddjvu_page_t* page);

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " file.djvu\n";
        return 1;
    }

    const char* filename = argv[1];
    ddjvu_context_t* ctx = ddjvu_context_create("labelshapes");
    ddjvu_document_t* doc = ddjvu_document_create_by_filename(ctx, filename, TRUE);

    while (!ddjvu_document_decoding_done(doc)) {
        ddjvu_message_wait(ctx);
    }

    if (!doc || ddjvu_document_get_pagenum(doc) < 1) {
        std::cerr << "Failed to load document or no pages.\n";
        return 1;
    }

    int composite_count = 0;
    int page_count = ddjvu_document_get_pagenum(doc);

    for (int i = 0; i < page_count; ++i) {
        ddjvu_page_t* page = ddjvu_page_create_by_pageno(doc, i);
        if (!page) continue;

        while (!ddjvu_page_decoding_done(page)) {
            ddjvu_message_wait(ctx);
        }

        DJVU::DjVuImage* image = ddjvu_get_DjVuImage(page);
        if (!image) {
            std::cerr << "Failed to access DjVuImage on page " << i << "\n";
            continue;
        }

        image->wait_for_complete_decode();

        GP<DJVU::JB2Image> jimg = image->get_fgjb();
        if (!jimg) continue;

        DJVU::JB2Dict* dict = jimg->get_dict();
        if (!dict) continue;

        for (int j = 0; j < dict->get_shape_count(); ++j) {
            const DJVU::JB2Shape* shape = dict->get_shape(j);
            if (!shape->is_bitmap_shape() && shape->blit_count() > 1) {
                std::cout << "Composite shape on page " << i
                          << ": shape " << j
                          << " (" << shape->blit_count() << " blits)\n";
                ++composite_count;
            }
        }

        ddjvu_page_release(page);
    }

    if (composite_count == 0)
        std::cout << "No composite shapes found.\n";
    else
        std::cout << "Found " << composite_count << " composite shapes.\n";

    ddjvu_document_release(doc);
    ddjvu_context_release(ctx);
    return 0;
}
