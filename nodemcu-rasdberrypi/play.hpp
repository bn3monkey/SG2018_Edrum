#include "record.h"
#include <fstream>

class Serial_play
{
    //현재 참조하고 있는 파일의 번호.
    int current_filenum;
    //현재 참조하고 있는 파일의 이름
    char current_filename[50];
    //파일의 수행가능 여부
    bool playable;

    //현재 채점 중인지 여부
    bool playing;

    //현재 참조하고 있는 파일에서 가져온 노트 배열.
    note* drum1;
    int drum1_cnt;
    note* drum2;
    int drum2_cnt;

    //현재 참조하고 있는 파일 스트림
    ifstream fp;
    
    //노트 배열 할당 해제
    void deallocation();

    //현재 참고하고 있는 파일을 자료구조에 저장하고 
    //일부 LED 정보를 buffer에 복사한다.
    void file_initialize(char* buf);
    //현재 참조하고 있는 파일의 번호를 올린다.
    void fileup(char* buf);       
    //현재 참조하고 있는 파일의 번호를 내린다.
    void filedown(char* buf);

    public:
        Serial_play()
        {
            current_filenum = 0;
            playable = makefilename(current_filenum, current_filename);
            playing = false;

            if(playable)
            {
                printf("File can be opend : %s\n", current_filename);
            }
            else
            {
                printf("File cannot be opend : %s\n", current_filename);
            }
        }

        //Serial에서 들어온 문자열 명령에 따라서 필요한 함수들을 수행한다.
        void play(note* temp, char* buf);

        
};