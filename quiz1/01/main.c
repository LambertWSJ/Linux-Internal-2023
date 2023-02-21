#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>

#include "list.h"
#include "item.h"

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

    struct item *pivot = list_first_entry(head, struct item, list);
    list_del(&pivot->list);

    struct item *itm = NULL, *is = NULL;
    
    list_for_each_entry_safe (itm, is, head, list) {
        if (cmpint(&itm->i, &pivot->i) < 0) 
            list_move (&itm->list, &list_less);
        else
            list_move_tail (&itm->list, &list_greater);
    }

    list_sort(&list_less);
    list_sort(&list_greater);

    list_add(&pivot->list, head);
    list_splice(&list_less, head);
    list_splice_tail(&list_greater, head);
}

void demo() 
{
    struct list_head *list = item_new();
    uint16_t nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (size_t i = 0; i < 10; i++)
        item_add(nums[i], list);
    item_show(list);
    list_sort(list);
    if(!item_validate(list)) {
        perror("Wrong answer, please check you sort algorithm");
        exit(EXIT_FAILURE);
    }
    item_show(list);
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head)
        return -1;

    int size = 0;
    struct list_head *node;
    list_for_each (node, head) {
        size++;
    }
    return size;
}

void q_shuffle(struct list_head *head) {
    if(list_empty(head))
        return;
    
    srand(time(NULL));
    struct list_head *node;
    struct list_head list, *new_head = &list;
    INIT_LIST_HEAD(new_head);

    for(int size = q_size(head); size; size--) {
        int index = rand() % size;
        int i = 0;
        list_for_each(node, head) {
            if (i == index || node->next == head)
                break;
        }
        list_move_tail(node, new_head);
    }
    
    INIT_LIST_HEAD(head);
    list_splice_tail(new_head, head);
}

int main(int argc, char const *argv[])
{
    // demo();

    struct list_head *list = item_new();
    uint16_t nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11,12,13,14,15};
    size_t size = sizeof(nums) / sizeof(uint16_t);
    for (size_t i = 0; i < size; i++)
        item_add(nums[i], list);

    struct list_head sorted, *tail = list->prev;
    INIT_LIST_HEAD(&sorted);
    q_shuffle(list);
    item_show(list);
    puts("---------------------------");

    return 0;
}
