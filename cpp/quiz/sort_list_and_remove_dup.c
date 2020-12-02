#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int nodeValue;
    struct ListNode *next;
};

struct ListNode *makeList(int values[], int size)
{
    int i;
    struct ListNode *head, *node;
    if (size == 0)
        return NULL;
    head = malloc(sizeof(struct ListNode));
    head->nodeValue = values[0];
    node = head;
    for (i = 1; i < size; i++) {
        node->next = malloc(sizeof(struct ListNode));
        node = node->next;
        node->nodeValue = values[i];
    }
    node->next = NULL;
    return head;
}

void destroyList(struct ListNode *head)
{
    struct ListNode *cur, *next;
    cur = head;
    while (cur != NULL) {
        next = cur->next;
        free(cur);
        cur = next;
    }
}

void outputList(const struct ListNode *head)
{
    const struct ListNode *p;
    for (p = head; p != NULL; p = p->next) {
        printf("%3d ", p->nodeValue);
    }
    printf("\n");
}

struct ListNode *sortList(struct ListNode *head)
{
    struct ListNode *prev, *cur, *end;
    if (head == NULL)
        return NULL;
    end = NULL;
    while (head->next != end) {
        cur = head;
        if (cur->nodeValue > cur->next->nodeValue) {
            head = cur->next;
            cur->next = cur->next->next;
            head->next = cur;
        } else {
            cur = cur->next;
        }
        prev = head;
        while (cur->next != end) {
            if (cur->nodeValue > cur->next->nodeValue) {
                prev->next = cur->next;
                cur->next = cur->next->next;
                prev->next->next = cur;
            } else {
                cur = cur->next;
            }
            prev = prev->next;
        }
        end = cur;
    }
    return head;
}

void RemoveDupInSortedList(struct ListNode *head)
{
    struct ListNode *prev, *cur;
    if (head == NULL)
        return;
    for (prev = head, cur = head->next; cur != NULL; cur = prev->next) {
        if (cur->nodeValue == prev->nodeValue) {
            prev->next = cur->next;
            free(cur);
        } else {
            prev = cur;
        }
    }
}

int main()
{
    int a[] = {4, 2, 3, 0, 1, 3, 2, 1, 2, 3, 3, 4, 5};
    struct ListNode *list = makeList(a, sizeof(a) / sizeof(int));
    printf("Before Sorting:\n");
    outputList(list);
    list = sortList(list);
    printf("After Sorting, Before Dedup:\n");
    outputList(list);
    RemoveDupInSortedList(list);
    printf("After Dedup:\n");
    outputList(list);
    destroyList(list);
    getchar();
}
