#ifndef GDA_H_
#define GDA_H_

#include <stddef.h>
#include <stdarg.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#define __INIT_CAP         8
#define __CAP_MULTI_FACTOR 2

#define da_impl(name, type)                                                             \
    typedef struct _##name {                                                            \
        type* items;                                                                    \
        size_t size;                                                                    \
        size_t cap;                                                                     \
        size_t elem_size;                                                               \
    } name;                                                                             \
    static inline void name##_##da_init(name* da) {                                     \
        da->size = 0;                                                                   \
        da->cap = __INIT_CAP;                                                           \
        da->elem_size = sizeof(*(da->items));                                           \
        da->items = malloc(__INIT_CAP * da->elem_size);                                 \
        assert(da->items != NULL && "Memory allocation error!\n");                      \
    }                                                                                   \
    static inline void name##_##da_append(name* da, type val) {                         \
        if (da->size >= da->cap) {                                                      \
            da->cap *= __CAP_MULTI_FACTOR;                                              \
            da->items = realloc(da->items, da->cap * da->elem_size);                    \
            assert(da->items != NULL && "Memory allocation error!\n");                  \
        }                                                                               \
        memcpy(&da->items[da->size++], &val, da->elem_size);                            \
    }                                                                                   \
    static inline void name##_##da_append_at(name* da, type val, int idx) {             \
        assert(idx >= 0 && idx < da->cap && "Invalid index provided\n");                \
        if (da->size >= da->cap) {                                                      \
            da->cap *= __CAP_MULTI_FACTOR;                                              \
            da->items = realloc(da->items, da->cap * da->elem_size);                    \
            assert(da->items != NULL && "Memory allocation error!\n");                  \
        }                                                                               \
        memcpy(&da->items[idx], &val, da->elem_size);                                   \
        da->size++;                                                                     \
    }                                                                                   \
    static inline void name##_##da_append_many(name* da, int n, ...) {                  \
        va_list va;                                                                     \
        va_start(va, n);                                                                \
        for (int i = 0; i < n; ++i) {                                                   \
            name##_##da_append(da, va_arg(va, type));                                   \
        }                                                                               \
        va_end(va);                                                                     \
    }                                                                                   \
    static inline type name##_##da_pop(name* da) {                                      \
        return da->items[--da->size];                                                   \
    }                                                                                   \
    static inline type name##_##da_get_at(name da, int idx) {                           \
        return da.items[idx];                                                           \
    }                                                                                   \
    static inline int name##_##da_get_val_idx(name da, type val) {                      \
        int idx = -1;                                                                   \
        for (int i = 0; i < da.size; ++i) {                                             \
             if (!memcmp(&val, &da.items[i], da.elem_size)) idx = i;                    \
        }                                                                               \
        return idx;                                                                     \
    }                                                                                   \
    static inline void name##_##da_print(name da, void (*print_func)(name)) {           \
        (*print_func)(da);                                                              \
    }                                                                                   \
    static inline void name##_##da_reverse(name* da) {                                  \
        for (int i = 0, j = da->size-1; j - i > 1; ++i, --j) {                          \
            type temp = da->items[i];                                                   \
            da->items[i] = da->items[j];                                                \
            da->items[j] = temp;                                                        \
        }                                                                               \
    }                                                                                   \
    static inline void name##_##da_left_shift(name* da) {                               \
        assert(da->size > 0 && "Cannot shift an empty array\n");                        \
        memmove(&da->items[0], &da->items[1], (da->size - 1) * da->elem_size);          \
        da->items[da->size-1] = 0;                                                      \
    }                                                                                   \
    static inline void name##_##da_right_shift(name* da) {                              \
        assert(da->size > 0 && "Cannot shift an empty array\n");                        \
        memmove(&da->items[1], &da->items[0], (da->size - 1) * da->elem_size);          \
        da->items[0] = 0;                                                               \
    }                                                                                   \
    static inline void name##_##da_left_shift_by(name* da, int amount) {                \
        assert(da->size > 0 && "Cannot shift an empty array\n");                        \
        if (!amount) return;                                                            \
        memmove(&da->items[0], &da->items[amount], (da->size - amount) * da->elem_size);\
        for (int i = 0; i < amount; ++i) {                                              \
            da->items[da->size - 1 - i] = 0;                                            \
        }                                                                               \
    }                                                                                   \
    static inline void name##_##da_right_shift_by(name* da, int amount) {               \
        assert(da->size > 0 && "Cannot shift an empty array\n");                        \
        if (!amount) return;                                                            \
        memmove(&da->items[amount], &da->items[0], (da->size - amount) * da->elem_size);\
        for (int i = 0; i < amount; ++i) {                                              \
            da->items[i] = 0;                                                           \
        }                                                                               \
    }                                                                                   \
    static inline void name##_##da_free(name da) {                                      \
        free(da.items);                                                                 \
    }                                                                                   \

#endif /* GDA_H_ */
