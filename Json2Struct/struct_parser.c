

#include "struct_parser.h"
#include "stdint.h "
#include "json_object.h"



int json_to_struct(void * struct_obj, json_object *json_object, attr_defs_t* attrs)
{
	int attr_index = 0;
	char * name;

	if (struct_obj == NULL || json_object == NULL || attrs == NULL)
	{
		return -1;
	}

	while ((name = attrs[attr_index].name) != NULL)
	{
		size_t offset = attrs[attr_index].off;

		struct json_object *p_json_obj = json_object_object_get(json_object, name);


		if (p_json_obj != NULL)
		{
			json_type type = json_object_get_type(p_json_obj);


			switch (type)
			{
			case json_type_boolean:
			{
									  BOOL *p_bool = (BOOL *)((int)struct_obj + attrs[attr_index].off);
									  *p_bool = json_object_get_boolean(p_json_obj);

			}

				break;

			case json_type_double:
			{
									 double *p_double = (double *)((int)struct_obj + attrs[attr_index].off);
									 *p_double = json_object_get_double(p_json_obj);
			}
				break;

			case json_type_int:
			{
								  int *p_int = (int *)((int)struct_obj + attrs[attr_index].off);
								  *p_int = json_object_get_int(p_json_obj);
			}

				break;

			case json_type_string:
			{
									 char** p_string = (char**)((int)struct_obj + attrs[attr_index].off);
									 char *str = json_object_get_string(p_json_obj);
									 if (str != NULL && strlen(str) > 0)
										 *p_string = strdup(str);

			}
				break;

			case json_type_object:
			{
									 void **p_struct_obj = (int *)((int)struct_obj + attrs[attr_index].off);
									// struct json_object *sub_json_obj = json_object_get_object(p_json_obj);
									 *p_struct_obj = malloc(attrs[attr_index].size_ext);

									 memset(*p_struct_obj, 0, attrs[attr_index].size_ext);

									 if (p_struct_obj != NULL && attrs[attr_index].attr_def_ext != NULL && p_json_obj)
										 json_to_struct(*p_struct_obj, p_json_obj, attrs[attr_index].attr_def_ext);

			}
				break;

			case json_type_array:
			{
									struct array_list **p_array = (int *)((int)struct_obj + attrs[attr_index].off);
									struct array_list *p_json_arr = json_object_get_array(p_json_obj);

									if (p_json_arr)
									{
										int arr_len = array_list_length(p_json_arr);

										if (arr_len > 0) 
										{
											*p_array = (struct array_list *)array_list_new(NULL);

											if (p_array){

												int i = 0;
												for (; i < arr_len; i++)
												{
													void * p_strcut_obj_ext = (void*)malloc(attrs[attr_index].size_ext);
													memset(p_strcut_obj_ext, 0, attrs[attr_index].size_ext);
													json_to_struct(p_strcut_obj_ext, (struct json_object *)array_list_get_idx(p_json_arr, i), attrs[attr_index].attr_def_ext);
													array_list_add(*p_array, p_strcut_obj_ext);
												}

											}

										}



									}

			}

				break;



			default:
				break;
			}


		}

		attr_index++;
	}

	if (attr_index <= 1)
	{
		return -1;
	}

	return 0;

}









