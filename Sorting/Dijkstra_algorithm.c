#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int INF = 2147483647;

int main()
{
	int vertexes, edges, current;
	int x, y, len;
	int i, j;

	scanf ("%d", &vertexes);
	scanf ("%d", &edges);

	int** matrix   = malloc (vertexes * sizeof (int*));
	int*  distance = malloc (vertexes * sizeof (int));
	int*  deleted  = malloc (vertexes * sizeof (int));

	for (i = 0; i < vertexes; ++i)
		matrix [i] = malloc (vertexes * sizeof (int));

	for (i = 0; i < vertexes; ++i)
		distance [i] = 100500;

	for (i = 0; i < vertexes; ++i)
		deleted [i] = 0;

	for (i = 0; i < vertexes; ++i)
		for (j = 0; j < vertexes; ++j)
			matrix [i] [j] = -1;

	for (i = 0; i < edges; ++i)
	{
		scanf ("%d", &x);
		scanf ("%d", &y);
		scanf ("%d", &len);
		matrix [x] [y] = len;
		matrix [y] [x] = len;
	}
	scanf ("%d", &current);

	int flag = 0;
	int min;
	distance [current] = 0;

	while (flag != 1)
	{
		min  = INF;
		flag = 1;
		for (i = 0; i < vertexes; ++i)
		{
			if ((distance [i] < min) && (deleted [i] != 1))
			{
				min = distance [i];
				current = i;
			}
		}
		for (i = 0; i < vertexes; ++i)
		{
			if ((matrix [current] [i] >= 0) &&
				(distance [i] > distance [current] + matrix [current] [i]))
			{
				distance [i] = distance [current] + matrix [current] [i];
			}
		}
		deleted[current] ++;
		for (i = 0; i < vertexes; ++i)
			flag *= deleted [i];
	}

	for (i = 0; i < vertexes; ++i)
		printf ("%d ", distance [i]);

	return 0;
}