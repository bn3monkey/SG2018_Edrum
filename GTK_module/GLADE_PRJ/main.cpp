#include <gtkmm.h>
#include <iostream>

Gtk::Dialog *pDialog = nullptr;
Gtk::Window *pMainWindow = nullptr;

static Glib::RefPtr<Gtk::Application> app;
Glib::RefPtr<Gtk::Builder> refBuilder;

static void on_button_clicked()
{
    std::cout << "btn_dialog clicked" << std::endl;
    if (pDialog){
        pDialog->hide(); //hide() will cause main::run() to end.
    }
}

static void on_btn_main_clicked()
{
    std::cout << "btn_main clicked" << std::endl;

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

    //Get the GtkBuilder-instantiated Dialog:
    refBuilder->get_widget("window_main", pMainWindow);
    if (pMainWindow)
    {
        Gtk::Button *pButton = nullptr;
        refBuilder->get_widget("btn_main", pButton);
        if (pButton)
        {
            pButton->signal_clicked().connect(sigc::ptr_fun(on_btn_main_clicked));
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