//Arduino와 Rasdberry Pi간 통신시 이용할 Protocol이다.
//(드럼 종류 및 명령)  (세기)  (시간)
// 으로 Serial을 보내므로 enum을 통해 명령을 정수꼴로 정의한다.
#ifndef __SERIAL_PROTOCOL__
#define __SERIAL_PROTOCOL__

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

    cmd_drum1 = 0x10,
    cmd_drum2 = 0x20,

    cmd_led1 = 0x100,
    cmd_led2 = 0x200,

    cmd_allocerror = 0x1000,
};
void cmd_send(int command, int power, int chrono);
#endif
