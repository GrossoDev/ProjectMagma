#include <string.h>   // memcpy
#include <stdtypes.h>

//
// Event
//

bool event_call(event ev)
{
    int i;
    for (i = 0; i < ev.count; i++)
    {
        void* getted = list_getbyindex(&ev.actions, i, NULL);
        
        if (getted != NULL)
        {
            void (*func)(void) = getted; // Cast back to function pointer
            func();
        }
    }

    return (ev.count != 0);
}
int event_add(event* ev, void (*action)(void))
{
    ev->actions.unordered = true; // Events don't care about order

    list_add(&ev->actions, action);

    return ev->count++;
}
bool event_rem(event* ev, int id)
{
    ev->actions.unordered = true; // Events don't care about order

    int index = list_rem(&ev->actions, id);

    return (index == -1);
}

//
// List
//

unsigned nextID = 0; // Store here the next ID

void expandlist(list* lst)
{
    lst->augmentby = lst->augmentby == 0 ? 8 : lst->augmentby; // 8 is default
    
    lst->capacity += lst->augmentby;
    listitem newlist[lst->capacity]; // create a new, expanded array

    memcpy(newlist, lst->elements, lst->count); // put the elements back to where they where.
}

void* list_get(list* lst, unsigned id, void* iferror)
{
    int i;
    for(i = 0; i < lst->count; i++) // Iterate every item...
        if (lst->elements[i].id == id) break; // until we found it.
    if (i >= lst->count) return (void*)iferror; // If we ran out of items, there's no item with that ID

    return lst->elements[i].value;
}
void* list_getbyindex(list* lst, unsigned index, void* iferror)
{
    if (index >= lst->count) return (void*)iferror;

    return lst->elements[index].value;
}
int list_add(list* lst, void* value)
{
    if (lst->capacity <= lst->count) // If array is not large enough, expand it
        expandlist(lst);

    lst->elements[lst->count].id = nextID;
    lst->elements[lst->count].value = value;

    lst->count += 1;

    return nextID++;
}
int list_insert(list* lst, void* item, unsigned index)
{

}
int list_rem(list* lst, unsigned id)
{
    int i;
    for(i = 0; i < lst->count; i++) // Iterate every item...
        if (lst->elements[i].id == id) break; // until we found it.
    if (i == lst->count) return -1; // If we ran out of items, there's no item with that ID

    if (!lst->unordered)
        memcpy(&lst->elements[i], &lst->elements[i+1], lst->count-i+1); // shift all items one place back
    else
        lst->elements[i] = lst->elements[lst->count-1]; // just replace it with the last item (faster)

    --lst->count; // Here we decrement the counter

    return i;
}
int list_remat(list* lst, unsigned index)
{
    if (index >= lst->count) return -1; // It goes off the array, don't proceed

    if (!lst->unordered)
        memcpy(&lst->elements[index], &lst->elements[index+1], lst->count-index+1); // shift all items one place back
    else
        lst->elements[index] = lst->elements[lst->count-1]; // just replace it with the last item (faster)

    --lst->count; // Here we decrement the counter

    return 0;
}