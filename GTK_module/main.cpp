#include <gtkmm.h>
#include <iostream>

#define SONGLIST_SIZE 5

Gtk::Dialog *pDialog = nullptr;
Gtk::Box *pBox_login = nullptr;
Gtk::Window *pMainWindow = nullptr;
Gtk::Entry *pEntry_id = nullptr;
Gtk::Entry *pEntry_pw = nullptr;
Gtk::Label *pLabel_notice = nullptr;
Gtk::ListBox *pListBox_song = nullptr;
Gtk::Widget *pListItem_song[SONGLIST_SIZE] = {nullptr};
Gtk::Label *pLabel_songlist_title[SONGLIST_SIZE] = {nullptr};
Gtk::Label *pLabel_songlist_uploader[SONGLIST_SIZE] = {nullptr};
Gtk::Label *pLabel_songlist_artist[SONGLIST_SIZE] = {nullptr};

static Glib::RefPtr<Gtk::Application> app;
Glib::RefPtr<Gtk::Builder> refBuilder;

static void on_button_clicked()
{
    std::cout << "btn_dialog clicked" << std::endl;
    if (pDialog)
    {
        pDialog->hide(); //hide() will cause main::run() to end.
    }
}

static void on_btn_song_play_clicked(){
    for (int i = 0; i < SONGLIST_SIZE; i++){
        if(pListBox_song->get_selected_row() == pListBox_song->get_row_at_index(i))
        {
            std::cout << "PLAY : " << pLabel_songlist_title[i]->get_text() << std::endl;

            std::string str = "";
            str = "PLAY : " + pLabel_songlist_title[i]->get_text();
            pLabel_notice->set_text(str);

            if (pDialog == nullptr)
            {
                refBuilder->get_widget("DialogBasic", pDialog);

                if (pDialog)
                {
                    //Get the GtkBuilder-instantiated Button, and connect a signal handler:
                    Gtk::Button *pButton = nullptr;
                    refBuilder->get_widget("quit_button", pButton);
                    if (pButton)
                    {
                        pButton->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
                    }

                    pDialog->show();
                }
            }
            else
                pDialog->show();
        }
    }

}

static void on_btn_login_clicked()
{
    std::cout << "btn_login clicked" << std::endl;

    std::cout << "ID : " << pEntry_id->get_text() << std::endl;
    std::cout << "PW : " << pEntry_pw->get_text() << std::endl;

    std::string str = "";
    str = "Welcome, " + pEntry_id->get_text() + "!";
    pLabel_notice->set_text(str);

    if(pDialog == nullptr){
        refBuilder->get_widget("DialogBasic", pDialog);

        if (pDialog)
        {
            //Get the GtkBuilder-instantiated Button, and connect a signal handler:
            Gtk::Button *pButton = nullptr;
            refBuilder->get_widget("quit_button", pButton);
            if (pButton)
            {
                pButton->signal_clicked().connect(sigc::ptr_fun(on_button_clicked));
            }

            pDialog->show();
        }
    }
    else
        pDialog->show();

    pBox_login->hide();

    std::cout << "dialog created" << std::endl;
}

static void on_window_main_destroyed()
{
    std::cout << "destroy!" << std::endl;
}

int main(int argc, char *argv[])
{
    app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");

    //Load the GtkBuilder file and instantiate its widgets:
    // NO_EXCEPTION > Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("window_main.glade");
    refBuilder = Gtk::Builder::create();
    try
    {
        refBuilder->add_from_file("window_main.glade");
    }
    catch (const Glib::FileError &ex)
    {
        std::cerr << "FileError: " << ex.what() << std::endl;
        return 1;
    }
    catch (const Glib::MarkupError &ex)
    {
        std::cerr << "MarkupError: " << ex.what() << std::endl;
        return 1;
    }
    catch (const Gtk::BuilderError &ex)
    {
        std::cerr << "BuilderError: " << ex.what() << std::endl;
        return 1;
    }

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

    //Get the GtkBuilder-instantiated Dialog:
    refBuilder->get_widget("window_main", pMainWindow);
    if (pMainWindow)
    {
        Gtk::Button *pButton = nullptr;
        refBuilder->get_widget("btn_login", pButton);
        if (pButton)
        {
            pButton->signal_clicked().connect(sigc::ptr_fun(on_btn_login_clicked));
        }
        refBuilder->get_widget("btn_song_play", pButton);
        if (pButton)
        {
            pButton->signal_clicked().connect(sigc::ptr_fun(on_btn_song_play_clicked));
        }

        //gtk_widget_set_size_request(GTK_WIDGET(pMainWindow), 1920, 1080);
        //gtk_window_fullscreen((GtkWindow*)pMainWindow);
        
        pMainWindow->fullscreen();
        pMainWindow->grab_focus();
        app->run(*pMainWindow);
    }

    if(pMainWindow) delete pMainWindow;
    if(pDialog)     delete pDialog;

    return 0;
}