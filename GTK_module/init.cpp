#include "init.hpp"

int get_widget_pointer(){
    refBuilder->get_widget("entry_pw", pEntry_pw);
    refBuilder->get_widget("entry_id", pEntry_id);
    refBuilder->get_widget("box_login", pBox_login); 
    refBuilder->get_widget("list_song", pListBox_song);
    //refBuilder->get_widget("listitem_song", pListItem_song);

    char widget_name[15] = "listitem_song0";
    char label_title[27] = "label_listitem_song_title0";
    char label_uploader[] = "label_listitem_song_uploader0";
    char label_artist[] = "label_listitem_song_artist0";

    for (int i = 0; i < SONGLIST_SIZE; i++)
    {
        widget_name[strlen(widget_name) - 1] = '0' + i;
        label_title[strlen(label_title) - 1] = '0' + i;
        label_uploader[strlen(label_uploader) - 1] = '0' + i;
        label_artist[strlen(label_artist) - 1] = '0' + i;

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
            pListBox_song->append(*pListItem_song[i]);
        }
        catch(const char *e)
        {
            std::cout << "Error : " << e << std::endl;
            break;
        }
    }

    refBuilder->get_widget("notice", pLabel_notice);

    return 0;
}