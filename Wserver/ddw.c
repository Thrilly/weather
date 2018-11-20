#include "global.h"

DepDataWeather	*add_ddw(DepDataWeather *list, int dep, char* dep_name, char* weather, int temp)
{
	DepDataWeather * node = NULL;
	node = malloc(sizeof(node));
	if (node == NULL) {
	    return NULL;
	}

	node->next     		= list;
	node->dep     		= dep;
	node->dep_name     	= dep_name;
	node->weather       = weather;
	node->temp   		= temp;
	return (node);
}

// DepDataWeather	*edit_ddw(DepDataWeather *list, int dep, char* dep_name, char* weather, int temp)
// {
// 	// if (list == NULL) {
// 	// 	return NULL;
// 	// }
// 	//
// 	// node->next     		= list;
// 	// node->dep     		= dep;
// 	// node->dep_name     	= dep_name;
// 	// node->weather       = weather;
// 	// node->temp   		= temp;
// 	return (list);
// }


DepDataWeather *search_ddw(DepDataWeather *list, int dep)
{
    if (list == NULL) {
		return NULL;
	}

	while (list != NULL) {
		if (dep == list->dep) {
			return list;
		}
		list = list->next;
	}

	return NULL;
}

int count_ddw(DepDataWeather *list)
{
    if (list == NULL) {
		return 0;
	}

	int count = 0;

	while (list != NULL) {
		count++;
		list = list->next;
	}

	return count;
}

DepDataWeather *delete_ddw(DepDataWeather *list, int dep)
{
    if (list == NULL) {
		return NULL;
	}

    if (dep == list->dep) {
        DepDataWeather* tmp = list->next;
        free(list);
        tmp = delete_ddw(tmp, dep);
        return tmp;
    } else {
        list->next = delete_ddw(list->next, list->next->dep);
        return list;
    }
}
