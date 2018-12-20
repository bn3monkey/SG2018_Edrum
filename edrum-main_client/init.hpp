#ifndef __INIT_SHAREDRUM__
#define __INIT_SHAREDRUM__

#include <gtkmm.h>
#include <iostream>
#include "global_variables.hpp"

void init_main_client(ResourceManager *pRM, LocalList **LL, ServerList **SL, MyList **ML);
void update_songlist(SongList *SL, int page);
int get_widget_pointer();


#endif