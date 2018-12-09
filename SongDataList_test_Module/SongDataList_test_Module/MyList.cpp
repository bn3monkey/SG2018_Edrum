#include "MyList.hpp"

// 현재 Page에 해당하는 SongData를 추가한다.
bool MyList::insert(int local_id, std::string name, std::string artist, std::string ID , int drum_amount, const std::vector<NoteData> notelist)
{
	//1. 현재 SongData에 해당하는 곡 데이터 파일이 이미 디렉토리 상에 존재하면, 추가하지 않는다.
	SongData song;
	if (song.exist(path, name, artist, ID))
	{
		std::cerr << "ERROR : there is already file which has same name." << std::endl;
		return false;
	}
	//2. 현재 SongData에 해당하는 곡 데이터 파일을 생성한다.
	if (!song.pre_write(this->path, local_id, name, artist, ID, drum_amount, (int)notelist.size()))
	{
		std::cerr << "ERROR : mylist insert" << std::endl;
		return false;
	}
	if (!song.write(notelist) )
	{
		std::cerr << "ERROR : mylist insert" << std::endl;
		return false;
	}
	//3. 총 곡 리스트에 현재 곡을 추가한다.
	all_songs.push_back(song);

	//4. 보여주는 곡 리스트를 업데이트한다.
	if (!updatePage(current_page))
	{
		std::cerr << "ERROR : mylist insert" << std::endl;
		return false;
	}
	return true;
}
// 현재 Page에 해당하는 SongData를 업로드한다.
bool MyList::upload(int song_num)
{
	return true;
}
// 현재 Page에 해당하는 SongData를 삭제한다.
bool MyList::upload_cancel(int song_num)
{
	return true;
}