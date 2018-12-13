#include "event_handler.hpp"
#include "popup.hpp"

static void on_btn_notice_ok_clicked();
static void on_button_clicked_in_signup();
static void on_btn_song_play_clicked();
static void on_btn_login_clicked();
static void on_btn_signup_clicked();

void register_event_handler()
{
    std::cout << std::endl << " *** Event Handler Register" << std::endl;

    Gtk::Button *pButton = nullptr;

    std::cout << " > btn_notice_ok..";
    refBuilder->get_widget("btn_notice_ok", pButton);
    if (pButton)
    {
        pButton->signal_clicked().connect(sigc::ptr_fun(on_btn_notice_ok_clicked));
    }
    std::cout << " Done." << std::endl;

    std::cout << " > btn_login..";
    refBuilder->get_widget("btn_login", pButton);
    if (pButton)
    {
        pButton->signal_clicked().connect(sigc::ptr_fun(on_btn_login_clicked));
    }
    std::cout << " Done." << std::endl;

    std::cout << " > btn_signup..";
    refBuilder->get_widget("btn_signup", pButton);
    if (pButton)
    {
        pButton->signal_clicked().connect(sigc::ptr_fun(on_btn_signup_clicked));
    }
    std::cout << " Done." << std::endl;

    std::cout << " > btn_song_play..";
    refBuilder->get_widget("btn_song_play", pButton);
    if (pButton)
    {
        pButton->signal_clicked().connect(sigc::ptr_fun(on_btn_song_play_clicked));
    }
    std::cout << " Done." << std::endl;

    std::cout << " *** All Event Handler Registered." << std::endl << std::endl;
}

static void on_btn_notice_ok_clicked()
{
    //std::cout << "btn_notice_ok clicked" << std::endl;
    if (pDialog_notice)
    {
        pDialog_notice->hide(); //hide() will cause main::run() to end.
    }
}

static void on_button_clicked_in_signup()
{
    std::cout << "##################################" << std::endl;
    std::cout << "register the following information" << std::endl;
    std::cout << "new ID : " << signup_pEntry_id->get_text() << std::endl;
    std::cout << "new PW : " << signup_pEntry_pw->get_text() << std::endl;
    std::cout << "##################################" << std::endl;
    if (pSignUp)
    {
        pSignUp->hide();
    }
}

static void on_btn_song_play_clicked()
{
    for (int i = 0; i < SONGLIST_SIZE; i++)
    {
        if (pListBox_song->get_selected_row() == pListBox_song->get_row_at_index(i))
        {
            std::cout << "PLAY : " << pLabel_songlist_title[i]->get_text() << std::endl;

            std::string str = "";
            str = "PLAY : " + pLabel_songlist_title[i]->get_text();
            pLabel_notice->set_text(str);

            if (pDialog_notice == nullptr)
            {
                refBuilder->get_widget("dialog_notice", pDialog_notice);

                if (pDialog_notice)
                {
                    //Get the GtkBuilder-instantiated Button, and connect a signal handler:
                    Gtk::Button *pButton = nullptr;
                    refBuilder->get_widget("btn_notice_ok", pButton);
                    if (pButton)
                    {
                        pButton->signal_clicked().connect(sigc::ptr_fun(on_btn_notice_ok_clicked));
                    }

                    pDialog_notice->show();
                }
            }
            else
                pDialog_notice->show();
        }
    }
}

static void on_btn_login_clicked()
{
    std::cout << "===========================" << std::endl;

    std::string id = pEntry_id->get_text();
    std::string pw = pEntry_pw->get_text();

    std::cout << "ID : " << id << std::endl;
    std::cout << "PW : " << pw << std::endl;

    std::string str = "";
    str = "Welcome, " + id + "!";

    if (id != "" && pw != "")
    { /*LOGIN_SUCCESS*/
        pLabel_notice->set_text(str);
        std::cout << str << std::endl;
        pStack_main->set_visible_child("page_songlist_online");
    }
    else
    {
        //SOMETHING
        std::cout << "Wrong Account!" << std::endl;
        popup("Wrong Account!");
    }

    std::cout << "===========================" << std::endl << std::endl;
}

/*Seob's work*/
static void on_btn_signup_clicked()
{
    std::cout << "signup clicked" << std::endl;

    if (pSignUp == nullptr)
    {
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