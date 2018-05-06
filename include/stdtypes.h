#ifndef __STDTYPES_H
#define __STDTYPES_H

/* IMPORTANT:
 * Remember that, if you want to initialize an
 * event, list, etc, in a local scope,
 * you have to declare it as 'static'
 */

#include <stdbool.h>

// List
typedef struct
{
    unsigned id;
    void* value;
} listitem;

typedef struct
{
    listitem elements[8];
    int count;       // Items in the list
    int augmentby;   // If we have to expand the array, how much would we
    bool unordered;  // If we don't mind the order, we can delete faster ( O(1) vs O(n) )

    // Don't touch th(ese|is), it's for your own safety 
    int capacity;    // The reserved space for the array
} list;

#define list_empty { .count = 0, .augmentby = 8, .unordered = false, .capacity = 8 }

extern void* list_get(list* lst, unsigned id, void* iferror);           // Gets an item by its id. In case of an error, you can choose what will notify you
extern void* list_getbyindex(list* lst, unsigned index, void* iferror); // Gets an item by its index. In case of an error, you can choose what will notify you
extern int   list_add(list* lst, void* value);                          // Adds an item at the end of the list. Returns its ID (necesary to delete it later).
extern int   list_insert(list* lst, void* value, unsigned index);       // Adds an item at a specific index of the list. Returns its ID.
extern int   list_rem(list* lst, unsigned id);                          // Removes an item with the matching ID from the list. Returns its index if found, -1 if not.
extern int   list_remat(list* lst, unsigned index);                     // Removes an item at a specific index from the list. Returns -1 if not found.

// Event

typedef struct
{
    list actions;
    int count;
} event;

#define event_empty { .count = 0, .actions = list_empty }

extern bool event_call(event ev);                       // Calls an event. Returns false if there aren't any actions in the event.
extern int  event_add(event* ev, void (*action)(void)); // Adds an action to an event. Returns its id.
extern bool event_rem(event* ev, int id);               // Removes an action from an event using its id. Returns false if the action is null.

#endif