
#ifndef __STRUCT_PARSER_H__
#define __STRUCT_PARSER_H__

#include <stddef.h>
#include "stdint.h "
#include "json_object.h"
typedef int BOOL;



typedef struct attr_defs  {
	char * name;
	size_t off;
	struct attr_defs *attr_def_ext;
	int size_ext;
} attr_defs_t;


int json_to_struct(void * struct_obj, json_object *json_object, attr_defs_t* attrs);


#endif







