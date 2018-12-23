#include "init.hpp"
#include "event_handler.hpp"

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

    timer_running = true;
    pThread_timer = new thread(&timer_sharedrum);
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
        pLabel_songlist_date[i]->set_text(std::string(pSD->date));
    }

    pCurList = SL;
    int mx_page = pCurList->getMaxpage();

    mx_page = mx_page < 0 ? 0 : mx_page;
    CurPage = CurPage > mx_page - 1 ? mx_page - 1 : CurPage;

    std::string str = std::to_string(CurPage + 1) + " / " + std::to_string(mx_page);
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

    // Get play hit image
    refBuilder->get_widget("img_hit0", pImage_hit[0]);
    refBuilder->get_widget("img_hit1", pImage_hit[1]);
    refBuilder->get_widget("img_hit2", pImage_hit[2]);
    refBuilder->get_widget("img_hit3", pImage_hit[3]);

    /* Get Play hit button - remove this block after hardware input */
    {
        refBuilder->get_widget("btn_hit0", pButton_hit[0]);
        refBuilder->get_widget("btn_hit1", pButton_hit[1]);
        refBuilder->get_widget("btn_hit2", pButton_hit[2]);
        refBuilder->get_widget("btn_hit3", pButton_hit[3]);
    }
    /*************************************************/

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

void timer_sharedrum(){
    std::cout << " *** Timer thread launched." << std::endl;
    uint64_t ms;

    while(1){
        ms = 
        std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()
        ).count();

        /// Critical ///
        mtx_lock_timer.lock();
        cur_time = ms;
        mtx_lock_timer.unlock();
        ////////////////

        if(!timer_running){
            break;
        }
        else{
            mtx_lock_update_note.lock();
            mtx_lock_update_note.unlock();
            m_signal_update_note.emit();
            //signal_draw();
            //update_note();
        }

        //std::this_thread::sleep_for(50ms);
        //std::this_thread::yield();
    }

    std::cout << " *** Timer thread terminating.." << std::endl;
}
