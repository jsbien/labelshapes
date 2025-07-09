#ifndef OVERRIDE_STDINT_AND_THREADS_H
#define OVERRIDE_STDINT_AND_THREADS_H

// Fix thread support before DjVuLibre
#ifndef _REENTRANT
#define _REENTRANT
#endif

// Fix standard types before DjVuLibre
#include <cstdint>
typedef uint16_t djvuint16_t;
typedef uint32_t djvuint32_t;

#endif // OVERRIDE_STDINT_AND_THREADS_H
