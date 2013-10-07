#ifndef PHP_PHO_H
#define PHP_PHO_H
#ifdef PHO

#ifdef ZTS
#error "You cannot even imagine the bads that will happen if you build this with ZTE"
#else

// Sub out the ZTE API
#define TSRMLS_FETCH() void ***vm;
#define TSRMLS_FETCH_FROM_CTX(ctx) void ***vm
#define TSRMLS_SET_CTX(ctx)

#define TSRMLS_D void ***vm
#define TSRMLS_DC , TSRMLS_D
#define TSRMLS_C vm
#define TSRMLS_CC , TSRMLS_C

#endif // ZTS
#endif // PHO
#endif // PHP_PHO_H
