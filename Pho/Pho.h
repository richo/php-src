#ifndef PHP_PHO_H
#define PHP_PHO_H
#ifdef PHO

#ifdef ZTS
#error "You cannot even imagine the bads that will happen if you build this with ZTE"
#else

// Sub out the ZTE API
/* #define TSRMLS_FETCH() void ***vm; */
/* #define TSRMLS_FETCH_FROM_CTX(ctx) void ***vm */
/* #define TSRMLS_SET_CTX(ctx) */

/* #define TSRMLS_D void ***vm */
/* #define TSRMLS_DC , TSRMLS_D */
/* #define TSRMLS_C vm */
/* #define TSRMLS_CC , TSRMLS_C */

/* ================= */
#define THREAD_HASH_OF(thr,ts)  (unsigned long)thr%(unsigned long)ts
typedef int ts_rsrc_id;

/* /1* Define THREAD_T and MUTEX_T *1/ */

#define THREAD_T int
#define MUTEX_T int*

/* /1* fetches the requested resource for the current thread *1/ */
/* TSRM_API void *ts_resource_ex(ts_rsrc_id id, THREAD_T *th_id); */
/* #define ts_resource(id)			ts_resource_ex(id, NULL) */

typedef void (*ts_allocate_ctor)(void *, void ***);
typedef void (*ts_allocate_dtor)(void *, void ***);
/* TSRM_API ts_rsrc_id ts_allocate_id(ts_rsrc_id *rsrc_id, size_t size, ts_allocate_ctor ctor, ts_allocate_dtor dtor); */

/* TSRM_API THREAD_T tsrm_thread_id(void); */
/* TSRM_API MUTEX_T tsrm_mutex_alloc(void); */
/* TSRM_API void tsrm_mutex_free(MUTEX_T mutexp); */
/* TSRM_API int tsrm_mutex_lock(MUTEX_T mutexp); */
/* TSRM_API int tsrm_mutex_unlock(MUTEX_T mutexp); */

/* typedef void (*tsrm_thread_begin_func_t)(THREAD_T thread_id, void ***vm); */
/* typedef void (*tsrm_thread_end_func_t)(THREAD_T thread_id, void ***vm); */

/* TSRM_API int tsrm_error(int level, const char *format, ...); */
/* TSRM_API void tsrm_error_set(int level, char *debug_filename); */

/* #define TSRMLS_FETCH()			void ***vm = (void ***) ts_resource_ex(0, NULL) */
/* #define TSRMLS_FETCH_FROM_CTX(ctx)	void ***vm = (void ***) ctx */
/* #define TSRMLS_SET_CTX(ctx)		ctx = (void ***) vm */
/* #define TSRMG(id, type, element)	(((type) (*((void ***) vm))[TSRM_UNSHUFFLE_RSRC_ID(id)])->element) */
/* #define TSRMLS_D	void ***vm */
/* #define TSRMLS_DC	, TSRMLS_D */
/* #define TSRMLS_C	vm */
/* #define TSRMLS_CC	, TSRMLS_C */

/* ================= */

/* startup/shutdown */
TSRM_API int tsrm_startup(int expected_threads, int expected_resources, int debug_level, char *debug_filename);
TSRM_API void tsrm_shutdown(void);

/* allocates a new thread-safe-resource id */
TSRM_API ts_rsrc_id ts_allocate_id(ts_rsrc_id *rsrc_id, size_t size, ts_allocate_ctor ctor, ts_allocate_dtor dtor);

/* fetches the requested resource for the current thread */
TSRM_API void *ts_resource_ex(ts_rsrc_id id, THREAD_T *th_id);
#define ts_resource(id)			ts_resource_ex(id, NULL)

/* frees all resources allocated for the current thread */
TSRM_API void ts_free_thread(void);

/* frees all resources allocated for all threads except current */
void ts_free_worker_threads(void);

/* deallocates all occurrences of a given id */
TSRM_API void ts_free_id(ts_rsrc_id id);


/* Debug support */
#define TSRM_ERROR_LEVEL_ERROR	1
#define TSRM_ERROR_LEVEL_CORE	2
#define TSRM_ERROR_LEVEL_INFO	3

typedef void (*tsrm_thread_begin_func_t)(THREAD_T thread_id, void ***vm);
typedef void (*tsrm_thread_end_func_t)(THREAD_T thread_id, void ***vm);


TSRM_API int tsrm_error(int level, const char *format, ...);
TSRM_API void tsrm_error_set(int level, char *debug_filename);

/* utility functions */
TSRM_API THREAD_T tsrm_thread_id(void);
TSRM_API MUTEX_T tsrm_mutex_alloc(void);
TSRM_API void tsrm_mutex_free(MUTEX_T mutexp);
TSRM_API int tsrm_mutex_lock(MUTEX_T mutexp);
TSRM_API int tsrm_mutex_unlock(MUTEX_T mutexp);
#ifdef HAVE_SIGPROCMASK
TSRM_API int tsrm_sigmask(int how, const sigset_t *set, sigset_t *oldset);
#endif

TSRM_API void *tsrm_set_new_thread_begin_handler(tsrm_thread_begin_func_t new_thread_begin_handler);
TSRM_API void *tsrm_set_new_thread_end_handler(tsrm_thread_end_func_t new_thread_end_handler);

/* these 3 APIs should only be used by people that fully understand the threading model
 * used by PHP/Zend and the selected SAPI. */
TSRM_API void *tsrm_new_interpreter_context(void);
TSRM_API void *tsrm_set_interpreter_context(void *new_ctx);
TSRM_API void tsrm_free_interpreter_context(void *context);

#define TSRM_SHUFFLE_RSRC_ID(rsrc_id)		((rsrc_id)+1)
#define TSRM_UNSHUFFLE_RSRC_ID(rsrc_id)		((rsrc_id)-1)

#define TSRMLS_FETCH()			void ***vm = (void ***) ts_resource_ex(0, NULL)
#define TSRMLS_FETCH_FROM_CTX(ctx)	void ***vm = (void ***) ctx
#define TSRMLS_SET_CTX(ctx)		ctx = (void ***) vm
#define TSRMG(id, type, element)	(((type) (*((void ***) vm))[TSRM_UNSHUFFLE_RSRC_ID(id)])->element)
#define TSRMLS_D	void ***vm
#define TSRMLS_DC	, TSRMLS_D
#define TSRMLS_C	vm
#define TSRMLS_CC	, TSRMLS_C

#define ZTS
#endif // ZTS
#endif // PHO
#endif // PHP_PHO_H
