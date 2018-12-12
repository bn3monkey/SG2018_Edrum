#include <gtkmm.h>
#include <iostream>
#include "init.hpp"
#include "event_handler.hpp"
#include "../edrum-resource_manager/ResourceManager.hpp"

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

int main(int argc, char *argv[])
{
    ResourceManager RM;

    RM.initialize();


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
        register_event_handler();
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