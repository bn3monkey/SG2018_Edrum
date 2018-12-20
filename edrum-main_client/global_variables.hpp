#ifndef __GLOBAL_SHAREDRUM__
#define __GLOBAL_SHAREDRUM__

#include <gtkmm.h>
#include "../edrum-resource_manager/ResourceManager.hpp"
#include "../edrum-communicator/CommunicationModule.hpp"

#define SONGLIST_SIZE 5

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
extern Gtk::Container *pFixed_play;

/**** SongList & Manager ****/
extern ResourceManager RM;
extern LocalList *pLocalList;
extern ServerList *pServerList;
extern MyList *pMyList;
extern SongList *pCurList;
extern int CurPage;

/**** Network Manager ****/
extern CommunicationModule CM;

/**** ETC ****/
extern Glib::RefPtr<Gtk::Builder> refBuilder;

#endif