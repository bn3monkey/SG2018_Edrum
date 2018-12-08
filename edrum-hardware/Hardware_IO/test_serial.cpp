#include <stdio.h>
#include "serial.hpp"
int main()
{
	Serial_io* io = new Serial_io();
	int flag = true;
	NoteData note;
	while(flag)
	{
		io->readSerial();
		io->setSerial(&note);
		printf("%lld %d %d\n", note.time, note.drum, note.power);
		if(note.drum == np_ok)
			flag = false;
	}
	delete io;
}
