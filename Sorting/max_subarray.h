struct Subarray
{
	int    first;
	int    last;
	data_t summ;
};

struct Subarray max_subarray (data_t* array, int first, int last)
{
	struct Subarray buf_0;

	if (first == last)
	{
		buf_0.first = first;
		buf_0.last = last;
		buf_0.summ = array[first];

		return (buf_0);
	}

	struct Subarray buf_1, buf_2;

	int mid = (first + last) / 2;

	buf_1 = max_subarray (array, first, mid);
	buf_2 = max_subarray (array, mid + 1, last);

	int i = 1;
	data_t summ = array[mid];

	while (array[mid - i] > 0)
	{
		summ += array[mid - i];
		i++;
	}

	buf_0.first = mid - i + 1;

	i = 1;
	while (array[mid + i] > 0)
	{
		summ += array[mid + i];
		i++;
	}

	buf_0.last = mid + i - 1;
	buf_0.summ = summ;

	int flag = 0;
	if (buf_0.summ > buf_1.summ)
	{
		if (buf_0.summ > buf_2.summ)
			flag = 0;
		else
			flag = 2;
	}
	else
	{
		if (buf_1.summ > buf_2.summ)
			flag = 1;
		else
			flag = 2;
	}

	if (flag == 0)
		return buf_0;
	if (flag == 1)
		return buf_1;

	return buf_2;
}
