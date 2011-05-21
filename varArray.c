int resizeVarArray(varArray *array)
{
	void *tmp = realloc(array->data,array->max * 2);
	if(!tmp)
	{
		puts("DEBUG: resizeVarArray() 1");
		return 1;
	}
	array->max *= 2;
	array->data = tmp;
	return 0;
}

int initVarArray(varArray *array,unsigned int size)
{
	void *tmp = malloc(sizeof(varArray));
	if(!tmp)
	{
		puts("DEBUG: initVarArray() 1");
		return 1;
	}
	array = tmp;
	array->max = size;
	tmp = malloc(size);
	if(!tmp)
	{
		puts("DEBUG: initVarArray() 2");
		return 1;
	}
	array->used = 0;
	array->data = tmp;
	return 0;
}
