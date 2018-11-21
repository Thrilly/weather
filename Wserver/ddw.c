#include "global.h"

DepDataWeather	*add_ddw(DepDataWeather *list, char* dep, char* dep_name, char* weather, int temp)
{
	DepDataWeather *node = malloc(sizeof(struct s_data_weather));
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

DepDataWeather	*insert_ddw(DepDataWeather *list, char* lineCsv)
{
	printf("%s\n", lineCsv);
	const char virg[2] = ",";

	int i = 0;
	char* dep;
	char* dep_name;
	char* weather;
	char *val;
	int temp;

	val = strtok(lineCsv, virg);
	while( val != NULL ) {
		if (i == 0) {
			dep = val;
		} else if(i == 1){
			dep_name = val;
		} else if(i == 2){
			weather = val;
		} else if(i == 3){
			temp = atoi(val);
		}
		val = strtok(NULL, virg);
		i++;
	}

	DepDataWeather *current = search_ddw(list, dep);
	if (current != NULL) {
		return edit_ddw(list, dep, weather, temp);
	} else {
		return add_ddw(list, dep, dep_name, weather, temp);
	}
	return (NULL);
}

DepDataWeather	*edit_ddw(DepDataWeather *list, char* dep, char* weather, int temp)
{
	DepDataWeather *current = search_ddw(list, dep);
	if (current == NULL) {
		return NULL;
	}
	current->weather       = weather;
	current->temp   		= temp;
	return (list);
}


DepDataWeather *search_ddw(DepDataWeather *list, char* dep)
{
    if (list == NULL) {
		return NULL;
	}

	while (list != NULL) {
		if (strcmp(dep,list->dep) == 0) {
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

DepDataWeather *delete_ddw(DepDataWeather *list, char* dep)
{
    if (list == NULL) {
		return NULL;
	}

    if (strcmp(dep,list->dep) == 0) {
        DepDataWeather* tmp = list->next;
        free(list);
        tmp = delete_ddw(tmp, dep);
        return tmp;
    } else {
        list->next = delete_ddw(list->next, list->next->dep);
        return list;
    }
}
