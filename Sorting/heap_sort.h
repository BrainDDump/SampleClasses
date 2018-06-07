void heap_swap (data_t* array, int n, int i)
{
	data_t max = array[i - 1];
	int flag = 0;

	if (2 * i <= n)
	{
		if (array[2 * i - 1] > max)
		{
			max = array[2 * i - 1];
			flag = 1;
		}
	}
	if (2 * i + 1 <= n)
	{
		if (array[2 * i] > max)
		{
			max = array[2 * i];
			flag = 2;
		}
	}

	data_t buf;
	if (flag == 1)
	{
		buf = array[i - 1];
		array[i - 1] = max;
		array[2 * i - 1] = buf;
		heap_swap (array, n, 2 * i);
	}

	if (flag == 2)
	{
		buf = array[i - 1];
		array[i - 1] = max;
		array[2 * i] = buf;
		heap_swap (array, n, 2 * i + 1);
	}

	return;
}

void heap_build (data_t* array, int n)
{
	int i;

	for (i = n / 2; i > 0; i--)
		heap_swap (array, n, i);

	return;
}

void heap_sort (data_t* array, int n)
{
	heap_build (array, n);

	int i;
	for (i = n; i >= 2; i--)
	{
		int buf = array[0];
		array[0] = array[i - 1];
		array[i - 1] = buf;

		n--;
		heap_swap (array, n, 1);
	}

	return;
}
