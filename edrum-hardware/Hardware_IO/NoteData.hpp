#ifndef __NOTE__
#define __NOTE__

enum NoteProtocol
{
	np_none = 0x00,
	//drum 0x10 ~ 0x30
	np_drum1 = 0x01,
	np_drum2 = 0x02,

	//switch 0x40 ~ 0x60
	np_up = 0x03,
	np_down = 0x04,
	np_right = 0x05,
	np_left = 0x06,
	np_ok = 0x07,
	np_idle = 0x08,
	np_num,

};

class NoteData
{
public:
	unsigned long long time;
	int drum;
	int power;

	NoteData(unsigned long _time = 0, int _drum = 0, int _power = 0) : time(_time), drum(_drum), power(_power)
	{}
	NoteData(const NoteData& e)
	{
		this->time = e.time;
		this->drum = e.drum;
		this->power = e.power;
	}
	
};

#endif
