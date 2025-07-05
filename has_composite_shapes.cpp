#include <iostream>
#include <libdjvu/DjVuDocument.h>
#include <libdjvu/JB2Image.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cerr << "Usage: has_composite_shapes file.djvu\n";
        return 2;
    }

    GURL fileurl = GURL::Filename::UTF8(argv[1]);
    GP<DjVuDocument> doc = DjVuDocument::create_wait(fileurl);

    int composite_count = 0;
    for (int i = 0; i < doc->get_pages_num(); ++i) {
        GP<DjVuPage> page = doc->get_page(i, false);
        page->wait_for_decode();

        GP<JB2Image> image = page->get_jb2image();
        if (!image) continue;

        JB2Dict *dict = image->get_dict();
        if (!dict) continue;

        for (int j = 0; j < dict->get_shape_count(); ++j) {
            const JB2Shape *shape = dict->get_shape(j);
            if (!shape) continue;

            if (!shape->bitmap && shape->blits.size() > 1) {
                std::cout << "Page " << i + 1 << ": Shape " << j << " is composite ("
                          << shape->blits.size() << " blits)\n";
                composite_count++;
            }
        }
    }

    if (composite_count == 0) {
        std::cout << "No composite shapes found.\n";
        return 0;
    } else {
        std::cout << composite_count << " composite shapes found.\n";
        return 1;
    }
}