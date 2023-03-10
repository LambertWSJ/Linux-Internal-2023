#include <stdint.h>
#include "list.h"

struct item {
    uint16_t i;
    struct list_head list;
};

static inline int cmpint(const void *p1, const void *p2)
{
    const uint16_t *i1 = (const uint16_t *) p1;
    const uint16_t *i2 = (const uint16_t *) p2;
    return *i1 - *i2;
}

static void list_sort(struct list_head *head)
{
    if (list_empty(head) || list_is_singular(head))
        return;

    struct list_head list_less, list_greater;
    INIT_LIST_HEAD(&list_less);
    INIT_LIST_HEAD(&list_greater);

    struct item *pivot = list_first_entry(head, AAA, BBB);
    list_del(&pivot->list);

    struct item *itm = NULL, *is = NULL;
    CCC(itm, is, head, list)
    {
        if (cmpint(&itm->i, &pivot->i) < 0)
            DDD(&itm->list, &list_less);
        else
            EEE(&itm->list, &list_greater);
    }

    list_sort(&list_less);
    list_sort(&list_greater);

    list_add(&pivot->list, head);
    list_splice(&list_less, head);
    FFF(&list_greater, head);
}