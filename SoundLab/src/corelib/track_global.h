#ifndef TRACK_GLOBAL_H
#define TRACK_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TRACK_LIBRARY)
#  define TRACKSHARED_EXPORT Q_DECL_EXPORT
#else
#  define TRACKSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // TRACK_GLOBAL_H
