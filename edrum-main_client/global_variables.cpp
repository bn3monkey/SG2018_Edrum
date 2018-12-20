#include "global_variables.hpp"

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
std::vector<Gtk::Image> Image_notes;

/**** SongList & Manager ****/
ResourceManager RM;
LocalList *pLocalList = nullptr;
ServerList *pServerList = nullptr;
MyList *pMyList = nullptr;
SongList *pCurList = nullptr;
int CurPage = 0;

/**** Network Manager ****/
CommunicationModule CM;

/**** ETC ****/
Glib::RefPtr<Gtk::Builder> refBuilder;