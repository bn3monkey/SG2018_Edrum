#include "file.h"
using namespace std;

char fname[] = "drum_0.txt";
ofstream fp;


//test code
/*
void main(){
	note a,b;
	bool c;
	a.drum=0;
	b.drum=2;
	b.msec=1231;
	b.power=443;
	c=makefile(a);
	c=makefile(b);
	return;
}*/

//make file
bool makefile(note note){
	if(note.drum==0){ //start
		while(fexists(fname)==true) //fname file exists
			fname[5]=fname[5]++;
		fp.open(fname);
		return true;
	}
	
	if(note.drum==1||note.drum==2){ //drum
		fp<<note.drum; //drum종류 타격시간 타격세기 순으로 입력
		fp<<" ";
		fp<<note.msec;
		fp<<" ";
		fp<<note.power;
		fp<<"\n";
		return true;
	}
	
	if(note.drum==3){ //end
		fp.close();
		return false;
	}
}

//file exist check
bool fexists(const char *filename){
	ifstream ifile(filename);
	return ifile;
}