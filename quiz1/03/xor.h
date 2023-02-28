#pragma once

#include <stdint.h>
#include <assert.h>

typedef struct _xorlist_node {
    struct _xorlist_node *cmp;
} xor_node_t;

typedef struct _xor_list_struct {
    xor_node_t head, tail;
    uint32_t count;
} xor_list_t;

struct test_node {
    int value;
    xor_node_t xornode;
};

#define container_of(ptr, type, member)                            \
    __extension__({                                                \
        const __typeof__(((type *) 0)->member) *__pmember = (ptr); \
        (type *) ((char *) __pmember - offsetof(type, member));    \
    })

#define xorlist_for_each(node, rp, rn, list)                        \
    for (rp = &(list)->head, node = rp->cmp; node != &(list)->tail; \
         rn = address_of(rp, node->cmp), rp = node, node = rn)

#define xorlist_for_each_prev(node, rp, rn, list)                   \
    for (rp = &(list)->tail, node = rp->cmp; node != &(list)->head; \
         rn = address_of(rp, node->cmp), rp = node, node = rn)

#define xorlist_for_each_from(node, pos1, pos2, rp, rn, list) \
    for (rp = pos2, node = pos1; node != &(list)->tail;       \
         rn = address_of(rp, node->cmp), rp = node, node = rn)

#define xorlist_for_each_from_prev(node, pos1, pos2, rp, rn, list) \
    for (rp = pos1, node = pos2; node != &(list)->head;            \
         rn = address_of(rp, node->cmp), rp = node, node = rn)

/* Note that when the delete function success is must return 0. */
#define xorlist_delete_prototype(name, node) \
    int _xorlist_delete_##name(xor_node_t *node)

#define xorlist_delete_call(name) _xorlist_delete_##name

#define XORNODE_INIT(n) \
    do {                \
        (n).cmp = NULL; \
    } while (0)

#define XORLIST_INIT(h)           \
    do {                          \
        (h).head.cmp = &(h).tail; \
        (h).tail.cmp = &(h).head; \
        (h).count = 0;            \
    } while (0)

int xorlist_add(xor_list_t *list, xor_node_t *n);

int xorlist_del(xor_list_t *list,
                xor_node_t *n,
                xor_node_t *target,
                int (*delete_func)(xor_node_t *));

int xorlist_destroy(xor_list_t *list, int (*delete_func)(xor_node_t *));

xorlist_delete_prototype(test_delete, _node);