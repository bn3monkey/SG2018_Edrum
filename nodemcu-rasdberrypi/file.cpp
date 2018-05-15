#include "file.h"
using namespace std;

#define MAX 500

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
		node1=(char**)malloc(sizeof(char*)*MAX);
		node2=(char**)malloc(sizeof(char*)*MAX);
		node1[0]=(char*) malloc(sizeof(char)*MAX*30);
		for( int i=1; i<MAX; i++){
			node1[i] = node1[ i-1 ] + 30;
		}
		node2[0]=(char*) malloc(sizeof(char)*MAX*30); 
		for( int i=1; i<MAX; i++){
			node2[i] = node2[ i-1 ] + 30;
		}

		return true;
	}

	if(strcmp(drum,"drum1")==0){
		int i;
		i = sprintf(node1[node1_cnt],"%d ",power);
		sprintf(node1[node1_cnt]+i,"%llu",msec);
		node1_cnt++;

		return true;
	}

	if(strcmp(drum,"drum2")==0){
		int i;
		i = sprintf(node2[node2_cnt],"%d ",power);
		sprintf(node2[node2_cnt]+i,"%llu",msec);
		node2_cnt++;

		return true;
	}

	if(strcmp(drum,"end")==0){
		while(fexists(fname)==true) //fname file exists
			fname[5]=fname[5]++;
		fp.open(fname);
		fp<<"2"<<"\n";
		fp<<"DRUM1 "<<node1_cnt<<"\n";
		for(int i=0;i<node1_cnt;i++){
			fp<<node1[i]<<"\n";
		}
		fp<<"DRUM2 "<<node2_cnt<<"\n";
		for(int i=0;i<node2_cnt;i++){
			fp<<node2[i]<<"\n";
		}
		free(node1[0]);
		free(node2[0]);
		free(node1);
		free(node2);

		return false;
	}
}

//file exist check
bool fexists(const char *filename){
	ifstream ifile(filename);
	return ifile;
}