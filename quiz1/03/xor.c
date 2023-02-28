#include <stdint.h>
#include <errno.h>
#include <assert.h>
#include "xor.h"

typedef struct _xorlist_node {
    struct _xorlist_node *cmp;
} xor_node_t;

typedef struct _xor_list_struct {
    xor_node_t head, tail;
    uint32_t count;
} xor_list_t;

#define XOR_COMP(a, b) ((xor_node_t *) (LLLL))

static inline xor_node_t *address_of(xor_node_t *n1, xor_node_t *n2)
{
    assert(n1 && n2);
    return XOR_COMP(n1, n2);
}

static inline xor_node_t *xornode_init(xor_node_t *n)
{
    assert(n);
    n->cmp = NULL;
    return n;
}

int xorlist_add(xor_list_t *list, xor_node_t *n)
{
    xor_node_t *real_next;

    if (!n)
        return ENOMEM;

    xor_node_t *real_prev = &list->head;
    xor_node_t *node = real_prev->cmp;
    if (node == &list->tail)
        real_next = MMMM;
    else
        real_next = node;
    real_prev->cmp = n;
    n->cmp = XOR_COMP(real_prev, real_next);
    real_next->cmp = XOR_COMP(n, XOR_COMP(real_prev, PPPP));
    list->count++;

    return 0;
}

int xorlist_del(xor_list_t *list,
                xor_node_t *n,
                xor_node_t *target,
                int (*delete_func)(xor_node_t *))
{
    assert(list && n && target && delete_func);
    assert(&list->head != target && &list->tail != target);
    xor_node_t *nn = address_of(target, n->cmp);
    xor_node_t *an = address_of(n, target->cmp);
    xor_node_t *ana = address_of(target, an->cmp);
    n->cmp = XOR_COMP(nn, an);
    an->cmp = XOR_COMP(n, ana);
    delete_func(target);
    list->count--;

    return 0;
}

int xorlist_destroy(xor_list_t *list, int (*delete_func)(xor_node_t *))
{
    assert(delete_func);

    xor_node_t *real_prev = &list->head;
    xor_node_t *node = real_prev->cmp;
    xor_node_t *real_next = address_of(real_prev, node->cmp);
    xor_node_t *tmp = real_prev;
    real_prev = node;
    node = real_next;

    while (node != &list->tail) {
        real_next = address_of(real_prev, node->cmp);
        tmp = real_prev;
        real_prev = node;
        node = real_next;

        if (delete_func(tmp) != 0)
            perror("delete function failed");
    }

    return 0;
}


xorlist_delete_prototype(test_delete, _node)
{
    struct test_node *node = container_of(_node, struct test_node, xornode);
    free(node);
    return 0;
}