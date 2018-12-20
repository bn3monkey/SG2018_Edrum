#include "init.hpp"
#include <stdio.h>

using namespace std;

void init_main_client(ResourceManager *pRM, LocalList **LL, ServerList **SL, MyList **ML){
    if(!CM.initialize())
    {
        std::cerr << " *** ServerConnection FAILED!!" << std::endl;
    }
    get_widget_pointer();

    if(pRM){
        if(!pRM->initialize()){
            std::cerr << " *** ResourceManager INIT FAILED!!" << std::endl;
            exit(0);
        }
        *LL = pRM->getLocallist();
        *SL = pRM->getServerlist();
        *ML = pRM->getMylist();

        update_songlist(*LL, 0);
    }
}

void update_songlist(SongList *SL, int page){
    SongData *pSD = nullptr;

    SL->updatePage(page);
    CurPage = page;

    if(SL == pLocalList){
        pLabel_songlist_type->set_text("OFFLINE");
    } else if(SL == pServerList){
        pLabel_songlist_type->set_text("ONLINE");
    } else if(SL == pMyList){
        pLabel_songlist_type->set_text("MYLIST");
    } else{
        pLabel_songlist_type->set_text("# ERROR #");
    }

    for (int i = 0; i < SONGLIST_SIZE; i++)
    {
        pSD = SL->getSong(i);

        if (pSD->name[0] == 0)
        {
            pLabel_songlist_title[i]->set_text("");
            pLabel_songlist_uploader[i]->set_text("");
            pLabel_songlist_artist[i]->set_text("");
            pLabel_songlist_date[i]->set_text("");
            continue;
        }

        pLabel_songlist_title[i]->set_text(std::string(pSD->name));
        pLabel_songlist_uploader[i]->set_text(std::string(pSD->ID));
        pLabel_songlist_artist[i]->set_text(std::string(pSD->artist));
        pLabel_songlist_date[i]->set_text("2012-12-12"/*std::string(pSD->date)*/);
    }

    pCurList = SL;

    std::string str = std::to_string(CurPage + 1) + " / " + std::to_string(pCurList->getMaxpage());
    pLabel_songlist_pagenum->set_text(str);
}

int get_widget_pointer(){
    refBuilder->get_widget("entry_pw", pEntry_pw);
    refBuilder->get_widget("entry_id", pEntry_id);
    refBuilder->get_widget("box_login", pBox_login); 
    refBuilder->get_widget("list_song", pListBox_song);
    refBuilder->get_widget("stack_main", pStack_main);
    refBuilder->get_widget("label_notice", pLabel_notice);
    refBuilder->get_widget("label_songlist_pagenum", pLabel_songlist_pagenum);
    refBuilder->get_widget("label_songlist_type", pLabel_songlist_type);
    refBuilder->get_widget("fixed_play", pFixed_play);

    char widget_name[15] = "listitem_song0";
    char label_title[27] = "label_listitem_song_title0";
    char label_uploader[] = "label_listitem_song_uploader0";
    char label_artist[] = "label_listitem_song_artist0";
    char label_date[] = "label_listitem_song_date0";

    // Initialize List widget.
    for (int i = 0; i < SONGLIST_SIZE; i++)
    {
        widget_name[strlen(widget_name) - 1] = '0' + i;
        label_title[strlen(label_title) - 1] = '0' + i;
        label_uploader[strlen(label_uploader) - 1] = '0' + i;
        label_artist[strlen(label_artist) - 1] = '0' + i;
        label_date[strlen(label_date) - 1] = '0' + i;

        try
        {
            refBuilder->get_widget(widget_name, pListItem_song[i]);
            std::cout << "Item " << i << " : " << pListItem_song[i] << std::endl;
            if(pListItem_song[i] == nullptr){
                throw "Not exist songlist item.";
            }
            refBuilder->get_widget(label_title, pLabel_songlist_title[i]);
            refBuilder->get_widget(label_uploader, pLabel_songlist_uploader[i]);
            refBuilder->get_widget(label_artist, pLabel_songlist_artist[i]);
            refBuilder->get_widget(label_date, pLabel_songlist_date[i]);
            pListBox_song->append(*pListItem_song[i]);
        }
        catch(const char *e)
        {
            std::cout << "Error : " << e << std::endl;
            return -1;
        }
    }

    // Init main page.
    pStack_main->set_visible_child("page_login");

    return 0;
}