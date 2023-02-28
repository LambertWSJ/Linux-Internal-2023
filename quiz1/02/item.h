
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "list.h"
#include <stdbool.h>
#include <stdint.h>

struct item {                         
    uint16_t i;
    struct list_head list;
};

void item_add(uint16_t val, struct list_head *head);
void item_add_tail(uint16_t val, struct list_head *head);
struct list_head* item_new();
void item_show(struct list_head *head);
bool item_validate(struct list_head *head);
void item_reverse(struct list_head *head);

#ifdef __cplusplus
}
#endif