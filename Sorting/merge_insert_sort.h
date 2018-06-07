void merge_insert_sort (data_t* array, int first, int last)
{
	if (last - first <= 25)
	{
		insert_sort (&array[first], last - first + 1);
		return;
	}

	int middle = (first + last) / 2;
	int len_1 = middle - first + 1;
	int len_2 = last - middle;

	merge_insert_sort (array, first, middle);
	merge_insert_sort (array, middle + 1, last);

	data_t* buf_1 = (data_t*)malloc ((len_1 + 1) * sizeof (data_t));
	data_t* buf_2 = (data_t*)malloc ((len_2 + 1) * sizeof (data_t));

	int i, j, k;
	int flag = 0;

	for (i = 0; i < len_1; i++)
		buf_1[i] = array[first + i];
	for (j = 0; j < len_2; j++)
		buf_2[j] = array[middle + 1 + j];

	buf_1[len_1] = MAX_DATA_VAL;
	buf_2[len_2] = MAX_DATA_VAL;

	i = 0;
	j = 0;

	for (k = first; k <= last; k++)
	{
		if (buf_1[i] < buf_2[j])
		{
			array[k] = buf_1[i];
			i++;
		}
		else
		{
			array[k] = buf_2[j];
			j++;
		}
	}

	free (buf_1);
	free (buf_2);

	return;
}
