#ifndef __POPUP_SHAREDRUM__
#define __POPUP_SHAREDRUM__

#include <gtkmm.h>
#include <iostream>

extern Gtk::Dialog *pDialog_notice;
extern Gtk::Label *pLabel_notice;

extern Glib::RefPtr<Gtk::Builder> refBuilder;

void popup(std::string str, bool modal);

#endif