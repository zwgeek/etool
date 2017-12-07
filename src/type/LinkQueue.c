#include "LinkQueue.h"


etool_linkQueue* etool_linkQueue_create(const unsigned int typeSize)
{
	etool_linkQueue *queue = malloc(sizeof(etool_linkQueue));
	if (queue == 0) { return 0; }
	struct _etool_linkNode *node = malloc(sizeof(struct _etool_linkNode));
	if (node == 0) { free(queue); return 0; }
	node->next = 0;
	queue->typeSize = typeSize;
	queue->length = 0;
	queue->front = node;
	queue->rear = node;
	return queue;
}

void etool_linkQueue_destroy(etool_linkQueue *queue)
{
	struct _etool_linkNode *node;
	while (queue->front->next != 0) {
		node = queue->front->next;
		queue->front->next = node->next;
		free(node);
	}
	free(queue->front);
	free(queue);
}

void etool_linkQueue_clear(etool_linkQueue *queue)
{
	struct _etool_linkNode *node;
	while (queue->front->next != 0) {
		node = queue->front->next;
		queue->front->next = node->next;
		free(node);
	}
	queue->length = 0;
	queue->rear = queue->front;	
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
	if (queue->length == 0) { return -1; }
	if (value != 0) {
		int n;
		for (n = 0; n < queue->typeSize; n++) {
			((unsigned char*)value)[n] = queue->front->next->data[n];
		}
	}
	return 0;
}

int etool_linkQueue_peer_get(etool_linkQueue *queue, void *value)
{
	if (queue->length == 0) { return -1; }
	if (value != 0) {
		int n;
		for (n = 0; n < queue->typeSize; n++) {
			((unsigned char*)value)[n] = queue->rear->data[n];
		}
	}
	return 0;
}

int etool_linkQueue_enter(etool_linkQueue *queue, void *value)
{
	struct _etool_linkNode *node = malloc(sizeof(struct _etool_linkNode));
	if (node == 0) { return -1; }
	int n;
	for (n = 0; n < queue->typeSize; n++) {
		node->data[n] = ((unsigned char*)value)[n];
	}
	node->next = 0;
	queue->rear->next = node;
	queue->rear = node;
	queue->length++;
	return 0;
}

int etool_linkQueue_peer_enter(etool_linkQueue *queue, void *value)
{
	struct _etool_linkNode *node = malloc(sizeof(struct _etool_linkNode));
	if (node == 0) { return -1; }
	int n;
	for (n = 0; n < queue->typeSize; n++) {
		node->data[n] = ((unsigned char*)value)[n];
	}
	node->next = queue->front->next;
	queue->front->next = node;
	queue->length++;
	return 0;
}

int etool_linkQueue_exit(etool_linkQueue *queue, void *value)
{
	if (queue->length == 0) { return -1; }
	struct _etool_linkNode *node = queue->front->next;	
	if (value != 0) {
		int n;
		for (n = 0; n < queue->typeSize; n++) {
			((unsigned char*)value)[n] = node->data[n];
		}
	}
	queue->front->next = node->next;
	queue->length--;
	free(node);
	return 0;
}

int etool_linkQueue_peer_exit(etool_linkQueue *queue, void *value)
{
	if (queue->length == 0) { return -1; }
	int n;
	struct _etool_linkNode *node = queue->front->next;
	for (n = 2; n < queue->length; n++) {
		node = node->next;
	}
	if (value != 0) {
		for (n = 0; n < queue->typeSize; n++) {
			((unsigned char*)value)[n] = queue->rear->data[n];
		}
	}
	free(queue->rear);
	queue->rear = node;
	queue->length--;
	return 0;
}

etool_linkQueueIterator* etool_linkQueueIterator_init(etool_linkQueue *queue)
{
	if (queue->length == 0) { return 0; }
	etool_linkQueueIterator *iterator = malloc(sizeof(etool_linkQueueIterator));
	if (iterator == 0) { return 0; }
	iterator->data = queue->front->next->data;
	iterator->next = queue->front->next->next;
	return iterator;
}

int etool_linkQueueIterator_next(etool_linkQueueIterator *iterator)
{
	if (iterator->next == 0) {
		free(iterator);
		return 0;
	}
	iterator->data = iterator->next->data;
	iterator->next = iterator->next->next;
	return 1;
}