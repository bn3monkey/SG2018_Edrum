//Arduino와 Rasdberry Pi간 통신시 이용할 Protocol이다.
//(드럼 종류 및 명령)  (세기)  (시간)
// 으로 Serial을 보내므로 enum을 통해 명령을 정수꼴로 정의한다.
#ifndef __SERIAL_PROTOCOL__
#define __SERIAL_PROTOCOL__

//드럼을 치는 타이밍과 LED가 켜지는 타이밍의 일치 정도에 따른 점수
#define TIME_INTERVAL 200
#define HALF_TIME_INTERVAL (TIME_INTERVAL/2)
enum score_timing
{
    passaway = -50, //-50
    excellent = 0 * TIME_INTERVAL, //-50 < x < 50
    nice = 1 * TIME_INTERVAL, // 50 < x < 150
    good = 2 * TIME_INTERVAL, // 150 < x 250
    bad = 3 * TIME_INTERVAL, // 250 < x < 350
    verybad = 4 * TIME_INTERVAL
};

//Protocol에서 drum 부분이 의미하는 것(이 명령의 종류를 통해 아두이노에서 처리)
enum serial_command
{
    cmd_idle = 0x0,
    cmd_recordstart = 0x1,
    cmd_recordend = 0x2,
    cmd_playstart = 0x3,
    cmd_playend = 0x4,
    cmd_fileup = 0x5,
    cmd_filedown = 0x6,
    cmd_downloadreq = 0x7,
    cmd_downloadres = 0x8,
    cmd_refreshreq = 0x9,
    cmd_refreshres = 0xA,

    cmd_downloadsuc = 0xB,
    cmd_downloadfail = 0xC,
    cmd_refreshsuc = 0xD,
    cmd_refreshfail = 0xE,

    cmd_scoring = 0xF,
    cmd_endscore = 0xFF,
    
    cmd_drum1 = 0x10,
    cmd_drum2 = 0x20,

    cmd_led1 = 0x100,
    cmd_led2 = 0x200,

    cmd_allocerror = 0x1000,
};

#endif
