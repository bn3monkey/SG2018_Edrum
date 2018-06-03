#include "record.h"
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

    public:
        Serial_play()
        {
            current_filenum = 0;
            playable = makefilename(current_filenum, current_filename);
            playing = false;
        }

        //Serial에서 들어온 문자열 명령에 따라서 필요한 함수들을 수행한다.
        void play(note* temp, char* buf);

        //현재 참조하고 있는 파일의 번호를 올린다.
        void fileup(char* buf);       
        //현재 참조하고 있는 파일의 번호를 내린다.
        void filedown(char* buf);
};