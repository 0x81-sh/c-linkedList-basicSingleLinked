#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    struct Node* next;
    int data;
} TNode, *PNode;

PNode createNode(int value, PNode next);
void printList(PNode list);
void insertFront(PNode *list, int value);
void insertEnd(PNode *list, int value);
void insertMiddle(PNode *list, int index, int value);
PNode findFirstNode(PNode *list, int value);
void deleteNodeAfter(PNode *list, PNode node);
void deleteNode(PNode *list, PNode node);
void deleteNodeWithIndex(PNode *list, int index);
void deleteValue(PNode *list, int value);
PNode getNode(PNode *list, int index);
void deleteList(PNode *list);

void __testMessage(char *, char *);
void __doubleNL();

void testFront();
void testMiddle();
void testEnd();
void testCreation();
void testEndOnEmpty();
void testFindFirstNode();
void testDeleteNodeAfter();
void testDeleteNode();
void testDeleteNodeWithIndex();
void testDeleteValue();
void testGetNode();
void testDeleteList();

int main() {
    testCreation();
    testFront();
    testMiddle();
    testEnd();
    testEndOnEmpty();
    testFindFirstNode();
    testDeleteNodeAfter();
    testDeleteNode();
    testDeleteNodeWithIndex();
    testDeleteValue();
    testGetNode();
    testDeleteList();

    printf("All tests complete.\n");
    return 0;
}

//------ tests

void testCreation () {
    __testMessage("Creation", "1");

    PNode list = createNode(1, NULL);
    printList(list);

    __doubleNL();
}

void testFront () {
    __testMessage("Front insert", "2, 1");

    PNode list = createNode(1, NULL);
    insertFront(&list, 2);
    printList(list);

    __doubleNL();
}

void testEnd () {
    __testMessage("End insert", "1, 2, 3");

    PNode list = createNode(1, createNode(2, NULL));
    insertEnd(&list, 3);
    printList(list);

    __doubleNL();
}

void testMiddle () {
    __testMessage("Middle insert", "1, 3, 2");

    PNode list = createNode(1, createNode(2, NULL));
    insertMiddle(&list, 0, 3);
    printList(list);

    __doubleNL();
}

void testEndOnEmpty () {
    __testMessage("End insert on empty list", "1");

    PNode list = NULL;
    insertEnd(&list, 1);
    printList(list);

    __doubleNL();
}

void testFindFirstNode() {
    __testMessage("Find first node by value", "3 @ <address>");

        PNode list = createNode(1, createNode(2, createNode(3, createNode(4, NULL))));
    PNode found = findFirstNode(&list, 3);
    printf("%d @ %x\n", found->data, (int) found);

    __doubleNL();
}

void testDeleteNodeAfter() {
    __testMessage("Delete node after element", "1, 2, 4");

    PNode list = createNode(1, createNode(2, createNode(3, createNode(4, NULL))));
    deleteNodeAfter(&list, list->next);
    printList(list);

    __doubleNL();
}

void testDeleteNode() {
    __testMessage("Delete node", "1, 3, 4");

    PNode list = createNode(1, createNode(2, createNode(3, createNode(4, NULL))));
    deleteNode(&list, list->next);
    printList(list);

    __doubleNL();
}

void testDeleteNodeWithIndex() {
    __testMessage("Delete node by index", "1, 3, 4");

    PNode list = createNode(1, createNode(2, createNode(3, createNode(4, NULL))));
    deleteNodeWithIndex(&list, 1);
    printList(list);

    __doubleNL();
}

void testDeleteValue() {
    __testMessage("Delete nodes by value", "2, 3");

    PNode list = createNode(1, createNode(2, createNode(1, createNode(3, NULL))));
    deleteValue(&list, 1);
    printList(list);

    __doubleNL();
}

void testGetNode() {
    __testMessage("Get node", "2 @ address");

    PNode list = createNode(1, createNode(2, createNode(3, createNode(4, NULL))));
    PNode found = getNode(&list, 1);
    printf("%d @ %x\n", found->data, (int) found);

    __doubleNL();
}

void testDeleteList() {
    __testMessage("Delete whole list", "(empty list)");

    PNode list = createNode(1, createNode(2, createNode(1, createNode(3, NULL))));
    deleteList(&list);
    printList(list);

    __doubleNL();
}

void __testMessage (char *testName, char *expected) {
    printf("%s test: \n", testName);
    printf("\tExpected: %s\n", expected);
    printf("\tGot: ");
}

void __doubleNL () {
    printf("\n\n");
}

//------ functions

PNode createNode(int value, PNode next) {
    PNode n = (PNode) malloc(sizeof(TNode));
    n->data = value;
    n->next = next;
    return n;
}

void printList(PNode list) {
    if (list == NULL) {
        printf("(empty list)\n");
        return;
    }

    while(list) {
        printf("%d", list->data);
        if (list->next) printf(", ");

        list = list->next;
    }
    printf("\n");
}

void insertFront(PNode *list, int value) {
    PNode newN = createNode(value, *list);
    *list = newN;
}

void insertEnd(PNode *list, int value) {
    if (*list == NULL) {
        (*list) = createNode(value, NULL);
        return;
    }

    PNode originalStart = *list;
    while((*list)->next) {
        *list = (*list)->next;
    }

    PNode tempNext = (*list)->next;
    (*list)->next = createNode(value, tempNext);

    *list = originalStart;
}

void insertMiddle(PNode *list, int index, int value) {
    if (index < 0) {
        printf("\nCannot have index under 0\n");
        exit(1);
    }

    int loopIndex = 0;
    PNode originalStart = *list;

    while (*list) {
        if (loopIndex == index) break;
        loopIndex++;

        *list = (*list)->next;
    }

    PNode tempNext = (*list)->next;
    (*list)->next = createNode(value, tempNext);

    *list = originalStart;
}

PNode findFirstNode(PNode *list, int value) {
    PNode original = *list;

    while (*list) {
        if ((*list)->data == value) {
            PNode returnValue = *list;
            *list = original;

            return returnValue;
        }

        *list = (*list)->next;
    }

    *list = original;
    return NULL;
}

void deleteNodeAfter(PNode *list, PNode node) {
    if (node == NULL) {
        free(*list);
        return;
    }

    PNode original = *list;
    while (*list) {
        if ((*list) == node) {
            PNode newNext = (*list)->next->next;
            free((*list)->next);
            (*list)->next = newNext;

            break;
        }

        *list = (*list)->next;
    }

    *list = original;
}

void deleteNode(PNode *list, PNode node) {
    if (node == NULL) {
        free(*list);
        return;
    }

    PNode original = *list;
    while (*list) {
        if (*list == node) {
            PNode toDelete = *list;
            original = (*list)->next;
            free(toDelete);
        }

        if ((*list)->next == node) {
            PNode newNext = (*list)->next->next;
            free((*list)->next);
            (*list)->next = newNext;

            break;
        }

        *list = (*list)->next;
    }

    *list = original;
}

void deleteNodeWithIndex (PNode *list, int index) {
    deleteNode(list, getNode(list, index));
}

void deleteValue(PNode *list, int value) {
    while (findFirstNode(list, value)) {
        deleteNode(list, findFirstNode(list, value));
    }
}

PNode getNode(PNode *list, int index) {
    if (index < 0) {
        printf("\nCannot have index under 0\n");
        exit(1);
    }

    int loopIndex = 0;
    PNode originalStart = *list;

    while (*list) {
        if (loopIndex == index) break;
        loopIndex++;

        *list = (*list)->next;
    }

    PNode found = *list;
    *list = originalStart;

    return found;
}

void deleteList(PNode *list) {
    int *address = NULL;
    int size = 0;

    while (*list) {
        size++;
        address = (int *) realloc(address, sizeof (int) * size);
        address[size - 1] = (int) *list;

        *list = (*list)->next;
    }

    for (int i = 0; i < size; i++) {
        free(address + i);
    }
    free(address);
}