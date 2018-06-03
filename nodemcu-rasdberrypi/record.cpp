#include "record.h"
#include "serial_protocol.h"

using namespace std;

#define LINE_MAX 16
#define NOTE_MAX 10000

char** node1;
char** node2;
int node1_cnt = 0;
int node2_cnt = 0;
ofstream fp;
bool recording = false;

static void deallocation()
{
	for(int i=0;i<NOTE_MAX;i++)
	{
		if(node1[i] != NULL)
			free(node1[i]);
	}
	for(int i=0;i<NOTE_MAX;i++)
	{
		if(node2[i] != NULL)
			free(node2[i]);
	}
	if(node1 != NULL)
		free(node1);
	if(node2 != NULL)
		free(node2);
}

bool makefile(note* temp, char* filename)
{
	int fileindex = 0;
	
	if(!recording && temp->drum == cmd_recordstart){
		node1_cnt = 0;
		node2_cnt = 0;
		node1=(char**)malloc(sizeof(char*)*NOTE_MAX);
		if(node1 == NULL)
		{
			fprintf(stderr, "node1 allocation ERROR!\n");
			deallocation();
		}
		node2=(char**)malloc(sizeof(char*)*NOTE_MAX);
		if(node2 == NULL)
		{
			fprintf(stderr, "node2 allocation ERROR!\n");
			deallocation();
		}
		for( int i=0; i<NOTE_MAX; i++){
			node1[i] = (char *)malloc(sizeof(char)*LINE_MAX);
			if(node1[i])
			{
				fprintf(stderr, "node1[%d] allocation ERROR!\n", i);
				deallocation();
			}
		}
		for( int i=0; i<NOTE_MAX; i++){
			node2[i] =  (char *)malloc(sizeof(char)*LINE_MAX);
			if(node2[i])
			{
				fprintf(stderr, "node2[%d] allocation ERROR!\n", i);
				deallocation();
			}
		}
		recording = true;

		return true;
	}

	if(recording && temp->drum == cmd_drum1){
		sprintf(node1[node1_cnt],"%d %llu",temp->power,temp->msec);
		node1_cnt++;

		return true;
	}

	if(recording && temp->drum == cmd_drum2){
		sprintf(node2[node2_cnt],"%d %llu",temp->power,temp->msec);
		node2_cnt++;

		return true;
	}

	if(recording && temp->drum == cmd_recordend){
		int trial = 10000;
		while(trial--)
		{
			if(makefilename(fileindex, filename)) //fname file exists
				fileindex +=1;
			else
				break;
		}
		fp.open(filename);
		fp<<"2"<<"\n";
		fp<<"DRUM1 "<<node1_cnt<<"\n";
		for(int i=0;i<node1_cnt;i++){
			fp<<node1[i]<<"\n";
		}
		fp<<"DRUM2 "<<node2_cnt<<"\n";
		for(int i=0;i<node2_cnt;i++){
			fp<<node2[i]<<"\n";
		}
		deallocation();
		fp.close();
		recording = true;
		return false;
	}

	return true;

}

//file exist check
bool fexists(const char *filename){
	ifstream ifile(filename);
	return (bool)(ifile);
}
//make filename
bool makefilename(int num, char* filename)
{
	sprintf(filename, "drum_%d.txt", num);
	return fexists(filename);
}