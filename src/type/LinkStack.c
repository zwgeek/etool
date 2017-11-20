#include "LinkStack.h"


etool_linkStack* etool_linkStack_create(const unsigned int typeSize)
{
	etool_linkStack *stack = malloc(sizeof(etool_linkStack));
	if (stack == 0) { return 0; }
	stack->typeSize = typeSize;
	stack->length = 0;
	stack->top = 0;
	return stack;
}

void etool_linkStack_destroy(etool_linkStack *stack)
{
	struct _etool_linkNode *node;
	while (stack->top != 0) {
		node = stack->top;
		stack->top = node->next;
		free(node);
	}
	free(stack);
}

void etool_linkStack_clear(etool_linkStack *stack)
{
	struct _etool_linkNode *node;
	while (stack->top != 0) {
		node = stack->top;
		stack->top = node->next;
		free(node);
	}
	stack->length = 0;
}

int etool_linkStack_length(etool_linkStack *stack)
{
	return stack->length;
}

int etool_linkStack_empty(etool_linkStack *stack)
{
	//1为真, 0为假
	return (stack->length == 0) ? 1 : 0;
}

int etool_linkStack_get(etool_linkStack *stack, void *value)
{
	if (stack->top == 0) { return -1; }
	struct _etool_linkNode *node = stack->top;
	if (value != 0) {
		for (int n = 0; n < stack->typeSize; n++) {
			((unsigned char*)value)[n] = node->data[n];
		}
	}
	return 0;
}

int etool_linkStack_push(etool_linkStack *stack, void *value)
{
	struct _etool_linkNode *node = malloc(sizeof(struct _etool_linkNode));
	if (node == 0) { return -1; }
	for (int n = 0; n < stack->typeSize; n++) {
		node->data[n] = ((unsigned char*)value)[n];
	}
	node->next = stack->top;
	stack->top = node;
	stack->length++;
	return 0;
}

int etool_linkStack_pop(etool_linkStack *stack, void *value)
{
	if (stack->top == 0) { return -1; }
	struct _etool_linkNode *node = stack->top;
	stack->top = node->next;
	stack->length--;
	if (value != 0) {
		for (int n = 0; n < stack->typeSize; n++) {
			((unsigned char*)value)[n] = node->data[n];
		}
	}
	free(node);
	return 0;
}