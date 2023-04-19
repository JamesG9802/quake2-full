#pragma once

/// <summary>
/// Represents an item with its priority.
/// </summary>
typedef struct ModElement {
	void* element;
	float priority;
} ModElement;

/// <summary>
/// Internally is just a ModList.
/// </summary>
/// <returns></returns>
ModList* ModPriorityQueue_Create();
/// <summary>
/// YOU ARE RESPONSIBLE FOR FREEING ANY ALLOCATED ELEMENTS.
/// </summary>
/// <param name="list"></param>
void ModPriorityQueue_Destroy(ModList* list);
void ModPriorityQueue_Insert(ModList* list, void* element, float priority);
void* ModPriorityQueue_Remove(ModList* list, void* element);
void* ModPriorityQueue_Pop(ModList* list);
void* ModPriorityQueue_At(ModList* list, int index);
