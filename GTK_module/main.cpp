#include <gtkmm.h>
#include <iostream>
#include "init.hpp"

#define SONGLIST_SIZE 5

Gtk::Dialog *pDialog = nullptr;
Gtk::Dialog *pSignUp = nullptr;
Gtk::Box *pBox_login = nullptr;
Gtk::Window *pMainWindow = nullptr;
Gtk::Entry *pEntry_id = nullptr;
Gtk::Entry *signup_pEntry_id = nullptr;
Gtk::Entry *pEntry_pw = nullptr;
Gtk::Entry *signup_pEntry_pw = nullptr;
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

static void on_button_clicked_in_signup()
{
    std::cout << "##################################" << std::endl;
    std::cout << "register the following information" << std::endl;
    std::cout << "new ID : " << signup_pEntry_id->get_text() << std::endl;
    std::cout << "new PW : " << signup_pEntry_pw->get_text() << std::endl;
    std::cout << "##################################" << std::endl;
    if(pSignUp)
    {
        pSignUp->hide();
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

/*Seob's work*/
static void on_btn_signup_clicked(){

    std::cout << "signup clicked" << std::endl;

    if(pSignUp == nullptr){
        refBuilder->get_widget("SignUp", pSignUp);
        
        if (pSignUp)
        {
            //Get the GtkBuilder-instantiated Button, and connect a signal handler:
            Gtk::Button *pButton = nullptr;
            refBuilder->get_widget("signup_entry_pw", signup_pEntry_pw);
            refBuilder->get_widget("signup_entry_id", signup_pEntry_id);
            refBuilder->get_widget("btn_signup_in_register", pButton);
            //refBuilder->get_widget("quit_button", pButton);
            if (pSignUp)
            {
                pButton->signal_clicked().connect(sigc::ptr_fun(on_button_clicked_in_signup));
            }
            
            pSignUp->show();
        }
    }
    else
        pSignUp->show();

    //pBox_login->hide();

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

    get_widget_pointer();

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
        
        refBuilder->get_widget("btn_signup", pButton);
        if(pButton)
        {
            pButton->signal_clicked().connect(sigc::ptr_fun(on_btn_signup_clicked));
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