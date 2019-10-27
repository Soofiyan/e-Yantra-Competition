/*
*
* Function Name: dijsktra1
* Input: int source,int targets
* Output: int *
* Logic: Takes the source from where bot has to start and destination to be reached and find shortest path using dijkstra algorithm.
		Returns the starting pointer of path.
* Example Call: p = dijsktra1(4,5); //Gets bot off node and Turns left until black line is encountered
*
*/
int* dijsktra1(int source,int target)
{
	int dist[41], prev[41], selected[41],dij_path[41];
	int dij_len;
	int i = 0;
	for (i = 0; i <= 41; i++)
	dist[i] = selected[i] = prev[i] = 0;
	int m, min, start, d, j, temp;
	for (i = 1; i <= nodes; i++)
	{
		dist[i] = 99;
		prev[i] = -1;
	}
	start = source;
	selected[start] = 1;

	dist[start] = 0;
	while (selected[target] == 0)
	{
		min = 99;
		m = 0;
		for (i = 1; i <= nodes; i++)
		{
			d = dist[start] + graph[start][i];
			if (d < dist[i] && selected[i] == 0)
			{
				dist[i] = d;
				prev[i] = start;
			}
			if (min > dist[i] && selected[i] == 0)
			{
				min = dist[i];
				m = i;
			}
		}
		start = m;
		selected[start] = 1;
	}
	start = target;
	i = 0;
	while (start != -1)
	{
		dij_path[++i] = start;
		start = prev[start];
	}
	j = i;
	dij_len = i;
	i = 1;
	while (i < j) {
		temp = dij_path[i];
		dij_path[i] = dij_path[j];
		dij_path[j] = temp;
		i++;
		j--;
	}
	/*for(int i=1;i<=dij_len;i++){
		lcd_print(1,1,dij_path[i],2);
		_delay_ms(1000);
	}*/
	_delay_ms(100);
	return dij_path;
}