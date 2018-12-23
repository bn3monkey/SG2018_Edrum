#include "SignalQueue.hpp"
#include <stdio.h>
int main()
{
	SignalQueue q;
	FILE* fp;
	int time;
	int in[10001];
	int out[10001];
	
	fopen_s(&fp, "input.csv", "r");
	int i = 0;
	while (fscanf_s(fp, "%d, %d", &time, in + i) != -1 && i < 10000)
	{
		i++;
	}
	fclose(fp);

	SignalQueue queue;
	for (int i = 0; i < 10000; i++)
	{
		queue.push(in[i]);
		out[i] = queue.average();
	}

	fopen_s(&fp, "output.csv", "w");
	for (int i = 0; i < 10000; i++)
	{
		fprintf_s(fp, "%d, %d\n", i, out[i]);
	}
	fclose(fp);

	queue.clean();
	SignalQueue queue2;
	for (int i = 0; i < 10000; i++)
	{
		queue.push(in[i]);
		queue2.push(queue.average());
		out[i] = queue2.average();
	}

	fopen_s(&fp, "output2.csv", "w");
	for (int i = 0; i < 10000; i++)
	{
		fprintf_s(fp, "%d, %d\n", i, out[i]);
	}
	fclose(fp);
}