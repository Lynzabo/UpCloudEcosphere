#ifndef TREEGLOBAL
#define TREEGLOBAL


#if defined(TREEGLOBAL)
#  define GLOBAL_EXPORT Q_DECL_EXPORT
#else
#  define GLOBAL_EXPORT Q_DECL_IMPORT
#endif
#endif // TREEGLOBAL

