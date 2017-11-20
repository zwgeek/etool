#include "LinkQueue.h"


etool_linkQueue* etool_linkQueue_create(const unsigned int typeSize)
{
	etool_linkQueue *queue = malloc(sizeof(etool_linkQueue));
	if (queue == 0) { return 0; }
	queue->typeSize = typeSize;
	queue->length = 0;
	queue->front = 0;
	queue->rear = 0;
	return queue;
}

void etool_linkQueue_destroy(etool_linkQueue *queue)
{
	struct _etool_linkNode *node;
	while (queue->front != 0) {
		node = queue->front;
		queue->front = node->next;
		free(node);
	}
	free(queue);
}

void etool_linkQueue_clear(etool_linkQueue *queue)
{
	struct _etool_linkNode *node;
	while (queue->front != 0) {
		node = queue->front;
		queue->front = node->next;
		free(node);
	}
	queue->length = 0;
	queue->rear = 0;	
}

int etool_linkQueue_length(etool_linkQueue *queue)
{
	return queue->length;
}

int etool_linkQueue_empty(etool_linkQueue *queue)
{
	//1为真, 0为假
	return (queue->length == 0) ? 1 : 0;
}

int etool_linkQueue_get(etool_linkQueue *queue, void *value)
{
	if (queue->front == 0) { return -1; }
	struct _etool_linkNode *node = queue->front;
	if (value != 0) {
		for (int n = 0; n < queue->typeSize; n++) {
			((unsigned char*)value)[n] = node->data[n];
		}
	}
	return 0;
}

int etool_linkQueue_enter(etool_linkQueue *queue, void *value)
{
	struct _etool_linkNode *node = malloc(sizeof(struct _etool_linkNode));
	if (node == 0) { return -1; }
	for (int n = 0; n < queue->typeSize; n++) {
		node->data[n] = ((unsigned char*)value)[n];
	}
	queue->rear->next = node;
	queue->rear = node;
	node->next = 0;
	queue->length++;
	return 0;
}

int etool_linkQueue_exit(etool_linkQueue *queue, void *value)
{
	if (queue->front == 0) { return -1; }
	struct _etool_linkNode *node = queue->front;
	queue->front = node->next;
	queue->length--;
	if (value != 0) {
		for (int n = 0; n < queue->typeSize; n++) {
			((unsigned char*)value)[n] = node->data[n];
		}
	}
	free(node);
	return 0;
}