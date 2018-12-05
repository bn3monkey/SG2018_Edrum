#include <gtkmm.h>
#include <iostream>

Gtk::Dialog *pDialog = nullptr;

static void on_button_clicked()
{
    std::cout << "btn_clicked!" << std::endl;
    if (pDialog)
        pDialog->hide(); //hide() will cause main::run() to end.
}

static void on_window_main_destroyed()
{
    std::cout << "destroy!" << std::endl;
}

int main(int argc, char *argv[])
{
    auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");

    //Load the GtkBuilder file and instantiate its widgets:
    // NO_EXCEPTION > Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file("window_main.glade");
    Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
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

        app->run(*pDialog);
    }

    delete pDialog;
}