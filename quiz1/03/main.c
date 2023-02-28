#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "xor.h"

void simulate() {
    xor_list_t list;
    xor_node_t *p1, *p2;

    XORLIST_INIT(list);
    for (int i = 0; i < 1000; i++) {
        struct test_node *new = malloc(sizeof(struct test_node));
        xornode_init(&new->xornode);
        new->value = i;
        xorlist_add(&list, &new->xornode);
        if (i == 5)
            p1 = &new->xornode;
        if (i == 6)
            p2 = &new->xornode;
    }

    xor_node_t *real_prev, *real_next, *node;
    int i = 0;
    printf("xorlist_for_each test\n");
    xorlist_for_each(node, real_prev, real_next, &list)
    {
        printf("node [%d] %d\n", i++,
               container_of(node, struct test_node, xornode)->value);
    }

    i = 0;
    printf("xorlist_for_from test\n");
    xorlist_for_each_from(node, p1, p2, real_prev, real_next, &list)
    {
        printf("node %d\n",
               container_of(node, struct test_node, xornode)->value);
    }

    i = 0;
    printf("xorlist_for_each_from_prev test\n");
    xorlist_for_each_from_prev(node, p1, p2, real_prev, real_next, &list)
    {
        printf("node [%d] %d\n", i++,
               container_of(node, struct test_node, xornode)->value);
    }

    i = 0;
    printf("xorlist_for_each_prev test\n");
    xorlist_for_each_prev(node, real_prev, real_next, &list)
    {
        printf("node [%d] %d\n", i++,
               container_of(node, struct test_node, xornode)->value);
    }

    printf("xorlist_del test\n");
    xorlist_del(&list, p2, p1, xorlist_delete_call(test_delete));
    i = 0;
    xorlist_for_each(node, real_prev, real_next, &list)
    {
        printf("node [%d] %d\n", i++,
               container_of(node, struct test_node, xornode)->value);
    }

    xorlist_destroy(&list, xorlist_delete_call(test_delete));
}

int main(int argc, char const *argv[])
{
    simulate();

    return 0;
}