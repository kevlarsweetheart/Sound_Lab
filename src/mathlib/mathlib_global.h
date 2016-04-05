#ifndef MATHLIB_GLOBAL_H
#define MATHLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MATHLIB_LIBRARY)
#  define MATHLIBSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MATHLIBSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MATHLIB_GLOBAL_H
