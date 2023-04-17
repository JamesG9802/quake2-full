#include <stdlib.h>

#include "ModList.h"

/*	Helper Methods	*/
void ModList_Resize(ModList* list, unsigned long newLength)
{
	void** newBlock = malloc(sizeof(void*) * newLength);
	for (int i = 0; i < list->length; i++)
		newBlock[i] = list->elements[i];
	list->elements = newBlock;
	list->capacity = newLength;
}

ModList* ModList_Create()
{
	ModList* modlist = malloc(sizeof(ModList));
	if (!modlist) return NULL;
	modlist->elements = malloc(sizeof(void*) * 1);
	modlist->length = 0;
	modlist->capacity = 1;
	return modlist;
}

void ModList_Append(ModList* list, void* item)
{
	//	If the list is at full capacity, double the size of the list
	if (list->length >= list->capacity)
		ModList_Resize(list, list->capacity * 2);
	list->elements[list->length] = item;
	list->length++;
}
void ModList_Insert(ModList* list, void* item, int index)
{
	int i;
	//	If the list is at full capacity, double the size of the list
	if (list->length >= list->capacity)
		ModList_Resize(list, list->capacity * 2);

	if (index < 0 || index > list->length)
		return;
	for (i = list->length; i > index; i--)
		list->elements[i] = list->elements[i - 1];
	list->elements[index] = item;
	list->length++;
}
void* ModList_Remove(ModList* list, int index)
{
	int i;
	void* item = NULL;
	if (index < 0 || index >= list->length)
		return item;
	item = list->elements[index];
	for (i = index; i < list->length - 1; i++)
		list->elements[i] = list->elements[i + 1];
	list->length--;
	return item;
}
void* ModList_Pop(ModList* list)
{
	return ModList_Remove(list, list->length - 1);
}
void ModList_Destroy(ModList* list)
{
	free(list->elements);
	free(list);
}
unsigned long ModList_Length(ModList* list)
{
	return list->length;
}