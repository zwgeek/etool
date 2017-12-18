#include "SeqStack.h"


etool_seqStack* etool_seqStack_create(const unsigned int typeSize, const unsigned int size)
{
	etool_seqStack *stack = malloc(sizeof(etool_seqStack));
	if (stack == 0) { return 0; }
	stack->data = malloc(typeSize * size);
	if (stack->data == 0) { free(stack); return 0; }
	stack->typeSize = typeSize;
	stack->size = size;
	stack->top = 0;
	stack->bottom = size;
	stack->mode = ETOOL_SEQSTACK_MODE_CREATE;
	return stack;
}

void etool_seqStack_destroy(etool_seqStack *stack)
{
	free(stack->data);
	free(stack);
}

int etool_seqStack_size(const unsigned int typeSize, const unsigned int size)
{
	return sizeof(etool_seqStack) + typeSize * size;
}

etool_seqStack* etool_seqStack_init(void *block, const unsigned int typeSize, const unsigned int size)
{
	if (block == 0) { return 0; }
	etool_seqStack *stack = block;
	stack->data = block + sizeof(etool_seqStack);
	stack->typeSize = typeSize;
	stack->size = size;
	stack->top = 0;
	stack->bottom = size;
	stack->mode = ETOOL_SEQSTACK_MODE_INIT;
	return stack;
}

void etool_seqStack_clear(etool_seqStack *stack)
{
	stack->top = 0;
	stack->bottom = stack->size;
}

int etool_seqStack_length(etool_seqStack *stack)
{
	return stack->top;
}

int etool_seqStack_other_length(etool_seqStack *stack)
{
	return stack->size - stack->bottom;
}

int etool_seqStack_empty(etool_seqStack *stack)
{
	return stack->top == 0 && stack->bottom == stack->size;
}

int etool_seqStack_full(etool_seqStack *stack)
{
	return stack->top == stack->bottom;
}

int etool_seqStack_get(etool_seqStack *stack, void *value)
{
	if (stack->top == 0) {
		return -1;
	}
	if (value != 0) {
		int n, offset = (stack->top - 1) * stack->typeSize;
		for (n = 0; n < stack->typeSize; n++) {
			((unsigned char*)value)[n] = stack->data[offset + n];
		}
	}
	return 0;
}

int etool_seqStack_other_get(etool_seqStack *stack, void *value)
{
	if (stack->bottom == stack->size) {
		return -1;
	}
	if (value != 0) {
		int n, offset = stack->bottom * stack->typeSize;
		for (n = 0; n < stack->typeSize; n++) {
			((unsigned char*)value)[n] = stack->data[offset + n];
		}
	}
	return 0;
}

int etool_seqStack_push(etool_seqStack *stack, const void *value)
{
	if (stack->top == stack->bottom) {
		switch (stack->mode) {
		case ETOOL_SEQSTACK_MODE_CREATE :
			{ ETOOL_SEQSTACK_EXTEND(stack); }
		case ETOOL_SEQSTACK_MODE_INIT :
			return -1;
		default :
			return -1;
		}
	}
	int n, offset = stack->top * stack->typeSize;
	for (n = 0; n < stack->typeSize; n++) {
		stack->data[offset + n] = ((unsigned char*)value)[n];
	}
	stack->top++;
	return 0;
}

int etool_seqStack_other_push(etool_seqStack *stack, const void *value)
{
	if (--stack->bottom < stack->top) {
		switch (stack->mode) {
		case ETOOL_SEQSTACK_MODE_CREATE :
			{ ETOOL_SEQSTACK_EXTEND(stack); }
		case ETOOL_SEQSTACK_MODE_INIT :
			return -1;
		default :
			return -1;
		}
	}
	int n, offset = stack->bottom * stack->typeSize;
	for (n = 0; n < stack->typeSize; n++) {
		stack->data[offset + n] = ((unsigned char*)value)[n];
	}
	return 0;
}

int etool_seqStack_pop(etool_seqStack *stack, void *value)
{
	if (stack->top == 0) {
		return -1;
	}
	stack->top--;
	if (value != 0) {
		int n, offset = stack->top * stack->typeSize;
		for (n = 0; n < stack->typeSize; n++) {
			((unsigned char*)value)[n] = stack->data[offset + n];
		}
	}
	return 0;
}

int etool_seqStack_other_pop(etool_seqStack *stack, void *value)
{
	if (stack->bottom == stack->size) {
		return -1;
	}
	if (value != 0) {
		int n, offset = stack->bottom * stack->typeSize;
		for (n = 0; n < stack->typeSize; n++) {
			((unsigned char*)value)[n] = stack->data[offset + n];
		}
	}
	stack->bottom++;
	return 0;
}

etool_seqStackIterator* etool_seqStackIterator_init(etool_seqStack *stack)
{
	if (stack->top == 0) { return 0; }
	etool_seqStackIterator *iterator = malloc(sizeof(etool_seqStackIterator));
	if (iterator == 0) { return 0; }
	iterator->data = stack->data + (stack->top - 1) * stack->typeSize;
	iterator->stack = stack;
	iterator->num = stack->top - 2;
	return iterator;
}

int etool_seqStackIterator_next(etool_seqStackIterator *iterator)
{
	etool_seqStack *stack = iterator->stack;
	if (iterator->num == -1) {
		free(iterator);
		return 0;
	}
	iterator->data = stack->data + iterator->num * stack->typeSize;
	iterator->num--;
	return 1;
}

etool_seqStackIterator* etool_seqStackIterator_other_init(etool_seqStack *stack)
{
	if (stack->bottom == stack->size) { return 0; }
	etool_seqStackIterator *iterator = malloc(sizeof(etool_seqStackIterator));
	if (iterator == 0) { return 0; }
	iterator->data = stack->data + stack->bottom * stack->typeSize;
	iterator->stack = stack;
	iterator->num = stack->bottom + 1;
	return iterator;
}

int etool_seqStackIterator_other_next(etool_seqStackIterator *iterator)
{
	etool_seqStack *stack = iterator->stack;
	if (iterator->num == stack->size) {
		free(iterator);
		return 0;
	}
	iterator->data = stack->data + iterator->num * stack->typeSize;
	iterator->num++;
	return 1;
}