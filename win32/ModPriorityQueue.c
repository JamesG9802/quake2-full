#include <stdlib.h>

#include "ModList.h"
#include "ModPriorityQueue.h"


ModList* ModPriorityQueue_Create()
{
	return ModList_Create();
}
void ModPriorityQueue_Destroy(ModList* list)
{
	for (int i = 0; i < list->length; i++)
	{
		free(list->elements[i]);
	}
	ModList_Destroy(list);
}
void ModPriorityQueue_Insert(ModList* list, void* element, float priority)
{
	int insertIndex = 0;
	for (int i = 0; i < list->length; i++)
	{
		if (((ModElement*)(list->elements[i]))->priority < priority)
		{
			break;
		}
	}
	ModElement* modElement = malloc(sizeof(ModElement));
	modElement->element = element;
	modElement->priority = priority;
	ModList_Insert(list, modElement, insertIndex);
}
void* ModPriorityQueue_Remove(ModList* list, void* element)
{
	for (int i = 0; i < list->length; i++)
	{
		if (((ModElement*)(list->elements[i]))->element == element)
		{
			return ModList_Remove(list, i);
		}
	}
	return NULL;
}
void* ModPriorityQueue_Pop(ModList* list)
{
	return ModList_Pop(list);
}
void* ModPriorityQueue_At(ModList* list, int index)
{
	return ((ModElement*)(list->elements[index]))->element;
}