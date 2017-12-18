#include "CircQueue.h"


etool_circQueue* etool_circQueue_create(const unsigned int typeSize, const unsigned int size)
{
	etool_circQueue *queue = malloc(sizeof(etool_circQueue));
	if (queue == 0) { return 0; }
	queue->data = malloc(typeSize * size);
	if (queue->data == 0) { free(queue); return 0; }
	queue->typeSize = typeSize;
	queue->size = size;
	queue->front = 0;
	queue->rear = 0;
	queue->mode = ETOOL_CIRCQUEUE_MODE_CREATE;
	return queue;
}

void etool_circQueue_destroy(etool_circQueue *queue)
{
	free(queue->data);
	free(queue);
}

int etool_circQueue_size(const unsigned int typeSize, const unsigned int size)
{
	return sizeof(etool_circQueue) + typeSize * size;
}

etool_circQueue* etool_circQueue_init(void *block, const unsigned int typeSize, const unsigned int size)
{
	if (block == 0) { return 0; }
	etool_circQueue *queue = block;
	queue->data = block + sizeof(etool_circQueue);
	queue->typeSize = typeSize;
	queue->size = size;
	queue->front = 0;
	queue->rear = 0;
	queue->mode = ETOOL_CIRCQUEUE_MODE_INIT;
	return queue;
}

void etool_circQueue_clear(etool_circQueue *queue)
{
	queue->front = 0;
	queue->rear = 0;
}

int etool_circQueue_length(etool_circQueue *queue)
{
	return (queue->rear - queue->front + queue->size) % queue->size;
}

int etool_circQueue_empty(etool_circQueue *queue)
{
	return queue->rear == queue->front;
}

int etool_circQueue_full(etool_circQueue *queue)
{
	return (queue->rear + 1) % queue->size == queue->front;
}

int etool_circQueue_get(etool_circQueue *queue, void *value)
{
	if (queue->rear == queue->front) {
		return -1;
	}
	if (value != 0) {
		int n, offset = (queue->front + 1) % queue->size * queue->typeSize;
		for (n = 0; n < queue->typeSize; n++) {
			((unsigned char*)value)[n] = queue->data[offset + n];
		}
	}
	return 0;
}

int etool_circQueue_peer_get(etool_circQueue *queue, void *value)
{
	if (queue->rear == queue->front) {
		return -1;
	}
	if (value != 0) {
		int n, offset = queue->rear * queue->typeSize;
		for (n = 0; n < queue->typeSize; n++) {
			((unsigned char*)value)[n] = queue->data[offset + n];
		}
	}
	return 0;	
}

int etool_circQueue_enter(etool_circQueue *queue, const void *value)
{
	if ((queue->rear + 1) % queue->size == queue->front) {
		switch (queue->mode) {
		case ETOOL_CIRCQUEUE_MODE_CREATE :
			{ ETOOL_CIRCQUEUE_EXTEND(queue); }
		case ETOOL_CIRCQUEUE_MODE_INIT :
			return -1;
		default :
			return -1;
		}
	}
	queue->rear = (queue->rear + 1) % queue->size;
	int n, offset = queue->rear * queue->typeSize;
	for (n = 0; n < queue->typeSize; n++) {
		queue->data[offset + n] = ((unsigned char*)value)[n];
	}
	return 0;
}

int etool_circQueue_peer_enter(etool_circQueue *queue, const void *value)
{
	if ((queue->rear + 1) % queue->size == queue->front) {
		switch (queue->mode) {
		case ETOOL_CIRCQUEUE_MODE_CREATE :
			{ ETOOL_CIRCQUEUE_EXTEND(queue); }
		case ETOOL_CIRCQUEUE_MODE_INIT :
			return -1;
		default :
			return -1;
		}
	}
	int n, offset = queue->front * queue->typeSize;
	for (n = 0; n < queue->typeSize; n++) {
		queue->data[offset + n] = ((unsigned char*)value)[n];
	}
	queue->front = (queue->front - 1 + queue->size) % queue->size;
	return 0;
}

int etool_circQueue_exit(etool_circQueue *queue, void *value)
{
	if (queue->rear == queue->front) {
		return -1;
	}
	queue->front = (queue->front + 1) % queue->size;
	if (value != 0) {
		int n, offset = queue->front * queue->typeSize;
		for (n = 0; n < queue->typeSize; n++) {
			((unsigned char*)value)[n] = queue->data[offset + n];
		}
	}
	return 0;
}

int etool_circQueue_peer_exit(etool_circQueue *queue, void *value)
{
	if (queue->rear == queue->front) {
		return -1;
	}
	if (value != 0) {
		int n, offset = queue->rear * queue->typeSize;
		for (n = 0; n < queue->typeSize; n++) {
			((unsigned char*)value)[n] = queue->data[offset + n];
		}
	}
	queue->rear = (queue->rear - 1 + queue->size) % queue->size;
	return 0;	
}

etool_circQueueIterator* etool_circQueueIterator_init(etool_circQueue *queue)
{
	if (queue->rear == queue->front) { return 0; }
	etool_circQueueIterator *iterator = malloc(sizeof(etool_circQueueIterator));
	if (iterator == 0) { return 0; }
	iterator->data = queue->data + ((queue->front + 1)  % queue->size) * queue->typeSize;
	iterator->queue = queue;
	iterator->num = (queue->front + 2)  % queue->size;
	return iterator;
}

int etool_circQueueIterator_next(etool_circQueueIterator *iterator)
{
	etool_circQueue *queue = iterator->queue;
	if (queue->rear == iterator->num) {
		free(iterator);
		return 0;
	}
	iterator->data = queue->data + iterator->num * queue->typeSize;
	iterator->num = (iterator->num + 1)  % queue->size;
	return 1;
}