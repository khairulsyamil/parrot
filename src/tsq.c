/* tsq.c
 *  Copyright: 2001-2003 The Perl Foundation.  All Rights Reserved.
 *  CVS Info
 *     $Id$
 *  Overview:
 *     Thread-safe queues
 *  Data Structure and Algorithms:
 *  History:
 *  Notes:
 *  References:
 */

#include "parrot/parrot.h"
static QUEUE_ENTRY * nosync_pop_entry(QUEUE *queue);

/* A synchronized entry popper */
QUEUE_ENTRY *
pop_entry(QUEUE *queue) {
    QUEUE_ENTRY *returnval;
    queue_lock(queue);
    returnval = nosync_pop_entry(queue);
    queue_unlock(queue);
    return returnval;
}

/* Grab an entry off the queue with no synchronization. Internal only,
   because it's darned evil and shouldn't be used outside the
   module. It's in here so we don't have to duplicate pop code */
static
QUEUE_ENTRY *
nosync_pop_entry(QUEUE *queue) {
    QUEUE_ENTRY *returnval;
    if (!queue->head) {
        return NULL;
    }
    returnval = queue->head;
    if (queue->head == queue->tail) {
        queue->head = NULL;
        queue->tail = NULL;
    } else {
        queue->head = queue->head->next;
    }
    returnval->next = NULL;
    return returnval;
}

QUEUE_ENTRY *
wait_for_entry(QUEUE *queue) {
    QUEUE_ENTRY *returnval;
    queue_lock(queue);
    while (queue->head == NULL) {
        queue_wait(queue);
    }
    returnval = nosync_pop_entry(queue);
    queue_unlock(queue);
    return returnval;

}

void
push_entry(QUEUE *queue, QUEUE_ENTRY *entry) {
    queue_lock(queue);
    /* Is there something in the queue? */
    if (queue->tail) {
        queue->tail->next = entry;
        queue->tail = entry;
    } else {
        queue->head = entry;
        queue->tail = entry;
    }
    queue_signal(queue);
    queue_unlock(queue);
}

void
queue_lock(QUEUE *queue) {
    LOCK(queue->queue_mutex);
}

void
queue_unlock(QUEUE *queue) {
    UNLOCK(queue->queue_mutex);
}

/* This function wakes up *every* thread waiting on the queue */
void
queue_signal(QUEUE *queue) {
    COND_BROADCAST(queue->queue_condition);
}

void
queue_wait(QUEUE *queue) {
    COND_WAIT(queue->queue_condition, queue->queue_mutex);
}

/*
 * Local variables:
 * c-indentation-style: bsd
 * c-basic-offset: 4
 * indent-tabs-mode: nil
 * End:
 *
 * vim: expandtab shiftwidth=4:
*/
