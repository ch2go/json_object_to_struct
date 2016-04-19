
#include <stdio.h>

#include "stdint.h "

#include "json_object.h"

#include "struct_parser.h"
#include <memory.h> 

struct child_t{
	char *name;
	int age;
};

#define OFFSET_CHILD(x) offsetof(struct child_t, x)



const attr_defs_t child_attr_def[] = {
	{ "name", OFFSET_CHILD(name), NULL, 0 },
	{ "age", OFFSET_CHILD(age), NULL, 0 },
	{ NULL, }

};

struct  person_test{
	char * name;
	int age;
	struct array_list *child_array_list;


};

#define OFFSET(x) offsetof(struct person_test, x)

const attr_defs_t person_attr_def[] = {
	{ "name", OFFSET(name), NULL, 0 },
	{ "age", OFFSET(age), NULL, 0 },
	{ "child", OFFSET(child_array_list), child_attr_def, sizeof(struct child_t) },
	{ NULL, }
};

int main()
{
	char ch;
	char **name = NULL;
	//struct json_object *p_json_obj = json_tokener_parse("{\"name\" : \"juner\",\"age\" : 18, }");
	struct json_object *p_json_obj = json_object_from_file("json.txt");

	struct person_test *p_person = (struct person_test *) malloc(sizeof(struct person_test));

	struct child_t *p_child = NULL;


	memset(p_person, 0, sizeof(struct person_test));

	printf("=====>%s\n", json_object_get_string(p_json_obj));



	json_to_struct(p_person, p_json_obj, person_attr_def);

	//printf("Person attr show [name]: %s  [age]:%d\n", p_person->child->name, p_person->child->age);


	p_child = (struct child_t *)array_list_get_idx(p_person->child_array_list, 1);


	printf("PRESS ANY KEY TO EXIT!");

	ch = getchar();

	return 1;

}




