#include "file.h"
using namespace std;

#define LINE_MAX 16
#define NOTE_MAX 10000

char fname[] = "drum_0.txt";
char** node1;
char** node2;
int node1_cnt = 0;
int node2_cnt = 0;
ofstream fp;

bool makefile(char* temp){
	char drum[10];
	int power;
	unsigned long long int msec;
	sscanf(temp,"%s %d %llu",drum,&power,&msec);

	if(strcmp(drum,"start")==0){
		node1_cnt = 0;
		node2_cnt = 0;
		node1=(char**)malloc(sizeof(char*)*NOTE_MAX);
		node2=(char**)malloc(sizeof(char*)*NOTE_MAX);
		for( int i=0; i<NOTE_MAX; i++){
			node1[i] = (char *)malloc(sizeof(char)*LINE_MAX);
		}
		for( int i=0; i<NOTE_MAX; i++){
			node2[i] =  (char *)malloc(sizeof(char)*LINE_MAX);
		}

		return true;
	}

	if(strcmp(drum,"DRUM1")==0){
		sprintf(node1[node1_cnt],"%d %llu",power,msec);
		node1_cnt++;

		return true;
	}

	if(strcmp(drum,"DRUM2")==0){
		sprintf(node2[node2_cnt],"%d %llu",power,msec);
		node2_cnt++;

		return true;
	}

	if(strcmp(drum,"end")==0){
		while(fexists(fname)==true) //fname file exists
			fname[5]=fname[5]+1;
		fp.open(fname);
		fp<<"2"<<"\n";
		fp<<"DRUM1 "<<node1_cnt<<"\n";
		for(int i=0;i<node1_cnt;i++){
			fp<<node1[i]<<"\n";
			free(node1[i]);
		}
		fp<<"DRUM2 "<<node2_cnt<<"\n";
		for(int i=0;i<node2_cnt;i++){
			fp<<node2[i]<<"\n";
			free(node2[i]);
		}
		free(node1);
		free(node2);
		fp.close();

		return false;
	}
	return true;
}

//file exist check
bool fexists(const char *filename){
	ifstream ifile(filename);
	return (bool)(ifile);
}
