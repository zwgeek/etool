#include "SeqStack.h"


etool_seqStack* etool_seqStack_create(const unsigned int typeSize, const unsigned int size)
{
	etool_seqStack *stack = malloc(sizeof(etool_seqStack));
	if (stack == 0) { return 0; }
	stack->data = malloc(typeSize * size);
	if (stack->data == 0) { return 0; }
	stack->typeSize = typeSize;
	stack->size = size;
	stack->top = 0;
	stack->mode = ETOOL_MODE_CREATE;
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
	stack->mode = ETOOL_MODE_INIT;
	return stack;
}

void etool_seqStack_clear(etool_seqStack *stack)
{
	stack->top = 0;
}

int etool_seqStack_length(etool_seqStack *stack)
{
	return stack->top;
}

int etool_seqStack_empty(etool_seqStack *stack)
{
	//1为真, 0为假
	return (stack->top == 0) ? 1 : 0;
}

int etool_seqStack_full(etool_seqStack *stack)
{
	//1为真, 0为假
	return (stack->top == stack->size) ? 1 : 0;
}

int etool_seqStack_push(etool_seqStack *stack, void *value)
{
	if (stack->top == stack->size) {
		switch (stack->mode) {
		case ETOOL_MODE_CREATE :
			{ ETOOL_SEQSTACK_EXTEND(stack); }\
		case ETOOL_MODE_INIT :
			return -1;
		default :
			return -1;
		}
	}
	int offset = stack->top * stack->typeSize;
	for (int n = 0; n < stack->typeSize; n++) {
		stack->data[offset + n] = ((unsigned char*)value)[n];
	}
	stack->top++;
	return 0;
}

int etool_seqStack_pop(etool_seqStack *stack, void *value)
{
	if (stack->top == 0) {
		return -1;
	}
	int offset = (stack->top - 1) * stack->typeSize;
	if (value != 0) {
		for (int n = 0; n < stack->typeSize; n++) {
			((unsigned char*)value)[n] = stack->data[offset + n];
		}
	}
	stack->top--;
	return 0;
}