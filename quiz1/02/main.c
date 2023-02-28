#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "list.h"
#include "item.h"

#define MAX_DEPTH 512

int cmpint(const uint16_t *a, const uint16_t *b) {
    return *a - *b;
}

static void list_sort_nr(struct list_head *head)
{
    if (list_empty(head) || list_is_singular(head))
        return;

    struct list_head stack[MAX_DEPTH];
    for (int i = 0; i < MAX_DEPTH; i++)
        INIT_LIST_HEAD(&stack[i]);
    int top = -1;
    list_splice_init(head, &stack[++top]);

    struct list_head partition;
    INIT_LIST_HEAD(&partition);

    while (top >= 0) {
        INIT_LIST_HEAD(&partition);
        list_splice_init(&stack[top--], &partition);
        if (!list_empty(&partition) && !list_is_singular(&partition)) {
            struct list_head list_less, list_greater;
            INIT_LIST_HEAD(&list_less);
            INIT_LIST_HEAD(&list_greater);
            struct item *pivot =
                list_first_entry(&partition, struct item, list);
            list_del(&pivot->list);
            INIT_LIST_HEAD(&pivot->list);

            struct item *itm = NULL, *is = NULL;
            list_for_each_entry_safe (itm, is, &partition, list) {
                list_del(&itm->list);
                if (cmpint(&itm->i, &pivot->i) < 0)
                    list_move(&itm->list, &list_less);
                else
                    list_move(&itm->list, &list_greater);
            }
            #if 0
            list_move_tail (&pivot->list, &list_less);
            if (!list_empty(&list_greater))
                list_splice_tail(&list_greater, &stack[++top]);
            if (!list_empty(&list_less))
                list_splice_tail(&list_less, &stack[++top]);
            #else
            list_move_tail (&pivot->list, &list_less);
            if (!list_empty(&list_less))
                list_splice_tail(&list_less, &stack[++top]);
            if (!list_empty(&list_greater))
                list_splice_tail(&list_greater, &stack[++top]);
            #endif
        } else {
            top++;
            list_splice_tail(&partition, &stack[top]);
            while (top >= 0 && list_is_singular(&stack[top])) {
                struct item *tmp =
                    list_first_entry(&stack[top], struct item, list);
                list_del(&tmp->list);
                INIT_LIST_HEAD(&stack[top--]);
                list_add_tail(&tmp->list, head);
            }
        }
    }
}


void list_quicksort(struct list_head *head) {
    if (list_empty(head) || list_is_singular(head))
        return;

    struct list_head stack[MAX_DEPTH];
    for (int i = 0; i < MAX_DEPTH; i++)
        INIT_LIST_HEAD(&stack[i]);
    int top = -1;
    list_splice_init(head, &stack[++top]);


    while (top >= 0) {
        LIST_HEAD(partition);   
        list_splice_init(&stack[top--], &partition);
        if (!list_empty(&partition) && !list_is_singular(&partition)) {
            LIST_HEAD(list_less);
            LIST_HEAD(list_greater);
            struct item *pivot =
                list_first_entry(&partition, struct item, list);
            list_del(&pivot->list);

            struct item *itm = NULL, *is = NULL;
            list_for_each_entry_safe (itm, is, &partition, list) {
                list_del(&itm->list);
                if (cmpint(&itm->i, &pivot->i) < 0)
                    list_move(&itm->list, &list_less);
                else
                    list_move(&itm->list, &list_greater);
            }

            list_move_tail (&pivot->list, &list_less);
            if (!list_empty(&list_greater))
                list_splice_tail(&list_greater, &stack[++top]);
            if (!list_empty(&list_less))
                list_splice_tail(&list_less, &stack[++top]);
        } else {
            list_splice_tail(&partition, &stack[++top]);
            while (top >= 0 && list_is_singular(&stack[top])) {
                struct item *tmp =
                    list_first_entry(&stack[top], struct item, list);
                list_del(&tmp->list);
                INIT_LIST_HEAD(&stack[top--]);
                list_add_tail(&tmp->list, head);
            }
        }
    }
}

int main(int argc, char const *argv[])
{

    struct list_head *list = item_new();
    uint16_t nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,12,13,14,15};
    size_t size = sizeof(nums) / sizeof(uint16_t);
    for (size_t i = 0; i < size; i++)
        item_add(nums[i], list);
    puts("init");
    item_show(list);
    puts("sort list via quicksort");
    // list_quicksort(list);
    list_sort_nr(list);
    puts("show");
    item_show(list);
    return 0;
}
