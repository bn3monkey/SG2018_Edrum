#ifndef __GLOBAL_SHAREDRUM__
#define __GLOBAL_SHAREDRUM__

#include <gtkmm.h>
#include <thread>
#include <mutex>
#include "../edrum-resource_manager/ResourceManager.hpp"
#include "../edrum-communicator/CommunicationModule.hpp"
#include "../edrum-hardware/Hardware_IO/Hardware_IO.hpp"

#define SONGLIST_SIZE 5
#define NOTE_IMG_SIZE 172
#define NOTE_MAX_CNT 100

/**** Mutex ****/
extern std::mutex mtx_lock_timer;
extern std::mutex mtx_lock_fixed_play;
extern std::mutex mtx_lock_image_notes;
extern std::mutex mtx_lock_update_note;

/**** Timer Thread ****/
extern std::thread *pThread_timer;
extern uint64_t cur_time;
extern bool timer_running;

/**** Custum Signal - Timer ****/
typedef sigc::signal<void> type_signal_update_note;
//typedef Glib::Dispatcher type_signal_update_note;
extern type_signal_update_note m_signal_update_note;
//type_signal_update_note signal_update_note();

/**** Widget Pointer ****/
extern Gtk::Dialog *pDialog_notice;
extern Gtk::Label *pLabel_notice;
extern Gtk::Dialog *pSignUp;
extern Gtk::Box *pBox_login;
extern Gtk::Window *pMainWindow;
extern Gtk::Entry *pEntry_id;
extern Gtk::Entry *signup_pEntry_id;
extern Gtk::Entry *pEntry_pw;
extern Gtk::Entry *signup_pEntry_pw;
extern Gtk::Label *pLabel_notice;
extern Gtk::ListBox *pListBox_song;
extern Gtk::Widget *pListItem_song[SONGLIST_SIZE];
extern Gtk::Label *pLabel_songlist_title[SONGLIST_SIZE];
extern Gtk::Label *pLabel_songlist_uploader[SONGLIST_SIZE];
extern Gtk::Label *pLabel_songlist_artist[SONGLIST_SIZE];
extern Gtk::Label *pLabel_songlist_date[SONGLIST_SIZE];
extern Gtk::Label *pLabel_songlist_pagenum;
extern Gtk::Label *pLabel_songlist_type;
extern Gtk::Stack *pStack_main;

/**** Play UI ****/
struct GAMENOTE{
    bool active;
    uint64_t gen_time;
    int note_idx;
};
extern Gtk::Container *pFixed_play;
extern std::vector<GAMENOTE*> Notes_meta;//Image_notes;
extern std::vector<Gtk::Image*> Notes_img;//Image_notes;
extern std::vector<int> Notes_visible;
extern Gtk::Image *pImage_hit[4];
extern Gtk::Button *pButton_hit[4];
extern int NOTE_GAP;
extern int NOTE_CNT;

/**** SongList & Manager ****/
extern ResourceManager RM;
extern LocalList *pLocalList;
extern ServerList *pServerList;
extern MyList *pMyList;
extern SongList *pCurList;
extern int CurPage;

/**** Network Manager ****/
extern CommunicationModule *CM;

/**** Hardware IO ****/
extern Hardware_IO HI;

/**** ETC ****/
extern Glib::RefPtr<Gtk::Builder> refBuilder;

#endif
