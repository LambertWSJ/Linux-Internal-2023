#include "item.h"
#include <stdio.h>
#include <stdlib.h>


void item_add(uint16_t val, struct list_head *head) 
{
    struct item *new_item = malloc(sizeof(struct item));
    new_item->i = val;
    list_add(&new_item->list, head);
}

void item_add_tail(uint16_t val, struct list_head *head) 
{
    struct item *new_item = malloc(sizeof(struct item));
    new_item->i = val;
    list_add_tail(&new_item->list, head);
}

struct list_head* item_new() 
{
    struct list_head *head = malloc(sizeof(struct list_head));
    if(head)
        INIT_LIST_HEAD(head);
    return head;
}

void item_show(struct list_head *head) {
    struct item *node;
    list_for_each_entry(node, head, list) {
        printf("%d ", node->i);
    }
    puts("");
}

void item_reverse(struct list_head *head) {
    struct list_head *node, *safe;
    list_for_each_safe(node, safe, head) {
        list_move(node, head);
    }
}

bool item_validate(struct list_head *head) 
{
    struct item *cur = NULL, *next = NULL;
    list_for_each_entry_safe(cur, next, head, list) {
        if(cur->i > next->i)
            return false;
    }
    return true;
}