#include "global_variables.hpp"

/**** Mutex ****/
std::mutex mtx_lock_timer;
std::mutex mtx_lock_fixed_play;
std::mutex mtx_lock_image_notes;
std::mutex mtx_lock_update_note;

/**** Timer Thread ****/
std::thread *pThread_timer = nullptr;
uint64_t cur_time = 0;
bool timer_running = false;

/**** Custum Signal - Timer ****/
type_signal_update_note m_signal_update_note;
//type_signal_update_note signal_update_note(){ return m_signal_update_note; }

/**** Widget Pointer ****/
Gtk::Dialog *pDialog_notice = nullptr;
Gtk::Label *pLabel_notice = nullptr;
Gtk::Dialog *pSignUp = nullptr;
Gtk::Box *pBox_login = nullptr;
Gtk::Window *pMainWindow = nullptr;
Gtk::Entry *pEntry_id = nullptr;
Gtk::Entry *signup_pEntry_id = nullptr;
Gtk::Entry *pEntry_pw = nullptr;
Gtk::Entry *signup_pEntry_pw = nullptr;
Gtk::ListBox *pListBox_song = nullptr;
Gtk::Widget *pListItem_song[SONGLIST_SIZE] = {nullptr};
Gtk::Label *pLabel_songlist_title[SONGLIST_SIZE] = {nullptr};
Gtk::Label *pLabel_songlist_uploader[SONGLIST_SIZE] = {nullptr};
Gtk::Label *pLabel_songlist_artist[SONGLIST_SIZE] = {nullptr};
Gtk::Label *pLabel_songlist_date[SONGLIST_SIZE] = {nullptr};
Gtk::Label *pLabel_songlist_pagenum = nullptr;
Gtk::Label *pLabel_songlist_type = nullptr;
Gtk::Stack *pStack_main = nullptr;

/**** Play UI ****/
Gtk::Container *pFixed_play = nullptr;
std::vector<GAMENOTE*> Notes_meta;//Image_notes;
std::vector<Gtk::Image*> Notes_img;//Image_notes;
std::vector<int> Notes_visible;
Gtk::Image *pImage_hit[4] = {nullptr};
Gtk::Button *pButton_hit[4] = {nullptr};
int NOTE_GAP = 0;
int NOTE_CNT = 0;

/**** SongList & Manager ****/
ResourceManager RM;
LocalList *pLocalList = nullptr;
ServerList *pServerList = nullptr;
MyList *pMyList = nullptr;
SongList *pCurList = nullptr;
int CurPage = 0;

/**** Network Manager ****/
CommunicationModule *CM;

/**** Hardware IO ****/
HardWare_IO HI;

/**** ETC ****/
Glib::RefPtr<Gtk::Builder> refBuilder;