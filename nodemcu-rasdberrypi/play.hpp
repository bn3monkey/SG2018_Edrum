#include "record.h"
#include <stdio.h>

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

    //총점
    struct _score
    {
        int excellent;
        int nice;
        int good;
        int bad;
        int verybad;
        int whole_score;

        _score()
        {
            excellent = 0;
            nice = 0;
            good = 0;
            bad = 0;
            verybad = 0;
            whole_score = 0;
        }
    } score;
    

    //현재 참조하고 있는 파일에서 가져온 노트 배열. queue로서 관리한다.
    int drum_num;
    note* drum[2];
    int drum_cnt[2];
    int drum_index[2];

    //현재 참조하고 있는 파일 스트림
    FILE* fp;
    
    //노트 배열 할당 해제
    void deallocation();

    //현재 참고하고 있는 파일을 자료구조에 저장하고 
    //일부 LED 정보를 buffer에 복사한다.
    void file_initialize();
    //현재 참조하고 있는 파일의 번호를 올린다.
    void fileup();       
    //현재 참조하고 있는 파일의 번호를 내린다.
    void filedown();
    // 현재 받아온 스코어의 정보를 받는다.
    void score_in(note temp);
    // 총점을 출력한다.
    void print_endscore();

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
        int play(note* temp);

        //Serial 출력에 필요한 note를 하나 내보내고 다음 note에 대기한다.
        //note queue가 비었으면 (power : -1, msec : 0)로 세팅된 note를 리턴한다. 
        note getnote(int number);
        
};