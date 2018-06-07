void insert_sort (data_t* array, int n)
{
	int i, j;
	data_t buf;

	for (i = 1; i < n; i ++)
	{
		buf = array[i];
		j = i - 1;

		while ((array[j] > buf) && (j >= 0))
		{
			array[j + 1] = array[j];
			j--;
		}

		array[j + 1] = buf;
	}

	return;
}
