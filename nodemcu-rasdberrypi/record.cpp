#include "record.h"
#include "serial_protocol.h"

using namespace std;

#define NOTE_MAX 10000

note* drum1;
note* drum2;
int drum1_cnt = 0;
int drum2_cnt = 0;
ofstream fp;
bool recording = false;

static void deallocation()
{
	if(drum1 != NULL)
		delete drum1;
	if(drum2 != NULL)
		delete drum2;
}

bool makefile(note* temp, char* filename)
{
	int fileindex = 0;
	
	if(!recording && temp->drum == cmd_recordstart){
		drum1_cnt = 0;
		drum2_cnt = 0;
		drum1 = new note[NOTE_MAX];
		if(drum1 == NULL)
		{
			fprintf(stderr, "DRUM1 NODE ALLOCATION ERROR!\n");
		}
		drum2 = new note[NOTE_MAX];
		if(drum2 == NULL)
		{
			fprintf(stderr, "DRUM2 NODE ALLOCATION ERROR!\n");
			deallocation();
		}

		recording = true;

		return true;
	}

	if(recording && temp->drum == cmd_drum1){
		drum1[drum1_cnt++] = *temp;
		return true;
	}

	if(recording && temp->drum == cmd_drum2){
		drum2[drum2_cnt++] = *temp;
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
		fp<<"DRUM1 "<<drum1_cnt<<"\n";
		for(int i=0;i<drum1_cnt;i++){
			fp<<drum1[i].power<<" "<<drum1[i].msec<<endl;
		}
		fp<<"DRUM2 "<<drum2_cnt<<"\n";
		for(int i=0;i<drum2_cnt;i++){
			fp<<drum2[i].power<<" "<<drum2[i].msec<<endl;
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