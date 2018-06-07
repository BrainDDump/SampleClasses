void swap (data_t* array, int i, int j)
{
	data_t buf = array[j];
	array[j] = array[i];
	array[i] = buf;
}

int partition (data_t* array, int first, int last)
{
	data_t main_el = array[last];

	int i = first;
	int j;

	for (j = first; j < last; j++)
	{
		if (array[j] < main_el)
		{
			swap (array, i, j);
			i++;
		}
	}
	
	swap (array, i, last);

	return i;
}

void quicksort (data_t* array, int first, int last)
{
	int mid = partition (array, first, last);

	if (first == last - 1)
		return;

	if (first < mid - 1)
		quicksort (array, first, mid - 1);

	if (mid + 1 < last)
		quicksort (array, mid + 1, last);

	return;
}
