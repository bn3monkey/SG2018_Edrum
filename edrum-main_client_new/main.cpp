#include <gtkmm.h>
#include <iostream>
#include "init.hpp"
#include "event_handler.hpp"

static Glib::RefPtr<Gtk::Application> app;

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

    init_main_client(&RM, &pLocalList, &pServerList, &pMyList);

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

    std::cout<<" Stop timer thread.."<<std::endl;
    mtx_lock_timer.lock();
    timer_running = false;
    mtx_lock_timer.unlock();

    std::cout<<" Wait for thread exit.."<<std::endl;
    if(pThread_timer->joinable()){
        pThread_timer->join();
    }

    std::cout<<" Release memory.."<<std::endl;
    if (pThread_timer)  delete pThread_timer;
    if(pMainWindow)     delete pMainWindow;
    if(pDialog_notice)  delete pDialog_notice;

    //RM.destroy();     // Segmentation fault !!
    CM.destroy();

    return 0;
}