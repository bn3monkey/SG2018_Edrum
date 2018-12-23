#include "event_handler.hpp"
#include "popup.hpp"

static int get_song_selected_index();
static void update_note();
static void on_btn_hit_clicked(int idx);
static void on_btn_notice_ok_clicked();
static void on_button_clicked_in_signup();
static void on_btn_song_play_clicked();
static void on_btn_login_clicked();
static void on_btn_signup_clicked();
static void on_btn_songlist_page_back_clicked();
static void on_btn_songlist_page_next_clicked();
static void on_btn_home_clicked();
static void on_btn_mypage_clicked();
static void on_btn_song_conversion_clicked();
static void on_btn_song_delete_clicked();

void register_event_handler()
{
    std::cout << std::endl << " *** Event Handler Register" << std::endl << std::endl;

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

    std::cout << " > btn_songlist_page_back..";
    refBuilder->get_widget("btn_songlist_page_back", pButton);
    if (pButton)
    {
        pButton->signal_clicked().connect(sigc::ptr_fun(on_btn_songlist_page_back_clicked));
    }
    std::cout << " Done." << std::endl;

    std::cout << " > btn_songlist_page_next..";
    refBuilder->get_widget("btn_songlist_page_next", pButton);
    if (pButton)
    {
        pButton->signal_clicked().connect(sigc::ptr_fun(on_btn_songlist_page_next_clicked));
    }
    std::cout << " Done." << std::endl;

    std::cout << " > btn_mypage..";
    refBuilder->get_widget("btn_mypage", pButton);
    if (pButton)
    {
        pButton->signal_clicked().connect(sigc::ptr_fun(on_btn_mypage_clicked));
    }
    std::cout << " Done." << std::endl;

    std::cout << " > btn_home..";
    refBuilder->get_widget("btn_home", pButton);
    if (pButton)
    {
        pButton->signal_clicked().connect(sigc::ptr_fun(on_btn_home_clicked));
    }
    std::cout << " Done." << std::endl;

    std::cout << " > btn_song_conversion..";
    refBuilder->get_widget("btn_song_conversion", pButton);
    if (pButton)
    {
        pButton->signal_clicked().connect(sigc::ptr_fun(on_btn_song_conversion_clicked));
    }
    std::cout << " Done." << std::endl;

    std::cout << " > btn_song_delete..";
    refBuilder->get_widget("btn_song_delete", pButton);
    if (pButton)
    {
        pButton->signal_clicked().connect(sigc::ptr_fun(on_btn_song_delete_clicked));
    }
    std::cout << " Done." << std::endl;



    /* Set event on play hit button - remove this block after hardware input */
    {
        std::cout << " > btn_hit..";
        pButton_hit[0]->signal_clicked().connect(sigc::bind<int>(sigc::ptr_fun(on_btn_hit_clicked), 0));
        pButton_hit[1]->signal_clicked().connect(sigc::bind<int>(sigc::ptr_fun(on_btn_hit_clicked), 1));
        pButton_hit[2]->signal_clicked().connect(sigc::bind<int>(sigc::ptr_fun(on_btn_hit_clicked), 2));
        pButton_hit[3]->signal_clicked().connect(sigc::bind<int>(sigc::ptr_fun(on_btn_hit_clicked), 3));
        std::cout << " Done." << std::endl;
    }
    /*************************************************/


    // Register custom signal - update note
    std::cout << " > timer_update_note..";
    signal_update_note().connect(sigc::ptr_fun(&update_note) );
    std::cout << " Done." << std::endl;

    std::cout << std::endl << " *** All Event Handler Registered." << std::endl << std::endl;
}

static void update_note(){
    int dest_x = 0, dest_y = 0;
    int src_x = 0, src_y = 0;
    static uint64_t now_time = 0;
    static uint64_t pre_time = 0;
    static unsigned int delta_time = 0;
    unsigned int delta_y = 0;

    //mtx_lock_update_note.lock();

    pre_time = now_time;
    /// Critical ///
    mtx_lock_timer.lock();
    now_time = cur_time;
    mtx_lock_timer.unlock();
    ////////////////
    if(pre_time == 0)
        pre_time = now_time;
    
    // Get DELTA_TIME
    delta_time += now_time - pre_time;

    //mtx_lock_fixed_play.lock();
    src_x = ((Gtk::Widget *)pFixed_play)->get_allocation().get_x();
    //src_y = ((Gtk::Widget *)pFixed_play)->get_allocation().get_y();
    src_y = ((Gtk::Widget *)pImage_hit[0])->get_allocation().get_y();
    //mtx_lock_fixed_play.unlock();

    if(delta_time > 15){
        delta_y = delta_time;
        delta_time = 0;
        //mtx_lock_image_notes.lock();
        for (unsigned int i = 0; i < Image_notes.size(); i++)
        {
            //dest_x = ((Gtk::Widget *)(Image_notes[i]->pImg))->get_allocation().get_x() - src_x;
            dest_x = Image_notes[i]->note_idx * NOTE_IMG_SIZE;
            //dest_y = ((Gtk::Widget *)(Image_notes[i]->pImg))->get_allocation().get_y() - src_y;
            //dest_y -= delta_y;
            dest_y = src_y - (int)(now_time - Image_notes[i]->gen_time);

            if (dest_y < -NOTE_IMG_SIZE)
            {
                std::cout << "delete note_" << i << std::endl;
                Image_notes[i]->pImg->hide();
                delete Image_notes[i]->pImg;
                delete Image_notes[i];
                Image_notes.erase(Image_notes.begin() + i);
                i--;
                continue;
            }

            //mtx_lock_fixed_play.lock();
            ((Gtk::Fixed *)pFixed_play)->move(*(Gtk::Widget *)(Image_notes[i]->pImg), dest_x, dest_y);
            //mtx_lock_fixed_play.unlock();
        }
        //mtx_lock_image_notes.unlock();
    }
    //mtx_lock_update_note.unlock();
}

static void on_btn_hit_clicked(int idx){
    int dest_x = 0, dest_y = 0;
    int src_x = 0, src_y = 0;

    std::cout << "btn_hit" << idx << " clicked." << std::endl;

    //mtx_lock_fixed_play.lock();
    src_x = ((Gtk::Widget *)pFixed_play)->get_allocation().get_x();
    src_y = ((Gtk::Widget *)pFixed_play)->get_allocation().get_y();
    //mtx_lock_fixed_play.unlock();

    Gtk::Image *pImg = nullptr;
    switch (idx)
    {
    case 0:
        pImg = new Gtk::Image("resources/circle_resized/circle_green.png");
        break;
    case 1:
        pImg = new Gtk::Image("resources/circle_resized/circle_orange.png");
        break;
    case 2:
        pImg = new Gtk::Image("resources/circle_resized/circle_red.png");
        break;
    case 3:
        pImg = new Gtk::Image("resources/circle_resized/circle_blue.png");
        break;
    default:
        return;
        break;
    }

    if (!pImg)
    {
        std::cerr << " *** Failed to generate new note!" << std::endl;
        return;
    }

    dest_x = ((Gtk::Widget *)pImage_hit[idx])->get_allocation().get_x() - src_x;
    dest_y = ((Gtk::Widget *)pImage_hit[idx])->get_allocation().get_y() - src_y;
    std::cout << " # NEW Widget : " << dest_x << ", " << dest_y << std::endl;

    //mtx_lock_fixed_play.lock();
    ((Gtk::Fixed*)pFixed_play)->put(*(Gtk::Widget*)pImg, dest_x, dest_y);
    ((Gtk::Fixed*)pFixed_play)->move(*(Gtk::Widget*)pImg, dest_x, dest_y);
    //mtx_lock_fixed_play.unlock();
    pImg->show();
    
    GAMENOTE *pGN = new GAMENOTE;
    pGN->pImg = pImg;
    mtx_lock_timer.lock();
    pGN->gen_time = cur_time;
    mtx_lock_timer.unlock();
    pGN->note_idx = idx;
    
    //mtx_lock_image_notes.lock();
    Image_notes.push_back(pGN);
    //mtx_lock_image_notes.unlock();

    while(Gtk::Main::events_pending()) Gtk::Main::iteration();
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
    std::string id = signup_pEntry_id->get_text();
    std::string pw = signup_pEntry_pw->get_text();

    std::cout << "##################################" << std::endl;
    std::cout << "register the following information" << std::endl;
    std::cout << "new ID : " << id << std::endl;
    std::cout << "new PW : " << pw << std::endl;
    std::cout << "##################################" << std::endl;


    std::string str = "";

    if(!CM.isinitialized()){
        for(int i=0; i<5; i++){
            if(CM.initialize())
            {
                std::cout << " > Server connected." << std::endl;
                break;
            }
            else{
                std::cerr << " > Failed to connect server. Retrying..." << i + 1 << std::endl;
            }
        }
        if(!CM.isinitialized()){
            popup("Failed to connect server.");
            //return;
        }
    }
    if (CM.signup(id, pw))
    //if(id != "" && pw != "")
    { /*LOGIN_SUCCESS*/

        str = "Welcome!\nYour ID : ["+ id+"]\nYour PW : [" + pw + "]" ;
        pLabel_notice->set_text(str);
        std::cout << str << std::endl;
        popup(str);
    }
    else
    {
        std::cout << "Not valid ID/PW!" << std::endl;
        popup("Not valid ID/PW!");
    }

    if (pSignUp)
    {
        pSignUp->hide();
    }
}

// upload. 20181223

static void on_btn_song_upload_clicked()
{
	int idx = get_song_selected_index();

	if(idx == -1) return;

	std::string str = "", title = "";
	title = pLabel_song_title[idx]->get_text();
	str = "UPLOAD : " + title;

	if(title != ""){
		if(pCurList == pMyList){
			popup("Uploading data - [" + title + "]");
			((MyList*)pCurList)->upload(idx);
			popup("Upload Complete! - [" + title + "]",true);
		}
		popup(str,true);
	}
	else{
		popup("Invalid song to upload.");
	}
}

static void on_btn_song_play_clicked()
{
    int idx = get_song_selected_index();

    if(idx == -1)
        return;

    std::string str = "", title = "";
    title = pLabel_songlist_title[idx]->get_text();
    str = "PLAY : " + title;

    //playable song!
    if(title != ""){
        std::cout << str << std::endl;

        if(pCurList == pServerList){
            popup("Downloading data - [" + title + "]");
            ((ServerList*)pCurList)->download(idx);
            popup("Download complete! - [" + title + "]", true);
        }

        popup(str, true);

        pStack_main->set_visible_child("page_play");
    }
    //non-playable!
    else{
        popup("Not valid song!");
    }
}

static void on_btn_login_clicked()
{
    std::cout << "===========================" << std::endl;

    std::string id = pEntry_id->get_text();
    std::string pw = pEntry_pw->get_text();

    std::cout << "ID : " << id << std::endl;
    std::cout << "PW : " << pw << std::endl;
    std::cout << "===========================" << std::endl << std::endl;

    std::string str = "";
    str = "Welcome, " + id + "!";

    if(!CM.isinitialized()){
        for(int i=0; i<5; i++){
            if(CM.initialize())
            {
                std::cout << " > Server connected." << std::endl;
                break;
            }
            else{
                std::cerr << " > Failed to connect server. Retrying..." << i + 1 << std::endl;
            }
        }
        if(!CM.isinitialized()){
            popup("Failed to connect server.");
            //return;
        }
    }
    if (CM.login(id, pw))
    //if(id != "" && pw != "")
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
}

static void on_btn_songlist_page_back_clicked(){
    CurPage = (CurPage - 1) < 0 ? 0 : (CurPage - 1);

    std::string str = std::to_string(CurPage + 1) + " / " + std::to_string(pCurList->getMaxpage());
    pLabel_songlist_pagenum->set_text(str);

    update_songlist(pCurList, CurPage);
}

static void on_btn_songlist_page_next_clicked(){
    if (++CurPage >= pCurList->getMaxpage())
        CurPage--;

    std::string str = std::to_string(CurPage + 1) + " / " + std::to_string(pCurList->getMaxpage());
    pLabel_songlist_pagenum->set_text(str);

    update_songlist(pCurList, CurPage);
}

static void on_btn_home_clicked(){
    if(pCurList == pServerList || pCurList == pLocalList)
        return;
    else
        update_songlist(pServerList, 0);
}

static void on_btn_mypage_clicked(){
    if(pCurList != pMyList)
        update_songlist(pMyList, 0);
}

static void on_btn_song_conversion_clicked(){
    if(pCurList == pMyList)
        return;
    
    if(pCurList == pServerList)
        update_songlist(pLocalList, 0);
    else if(pCurList == pLocalList)
        update_songlist(pServerList, 0);
    else
        return;
}

static void on_btn_song_delete_clicked(){
    if(pCurList == pServerList)
        return;
    
    int idx = get_song_selected_index();

    if(idx < 0 || idx >= SONGLIST_SIZE)
        return;

    if(pCurList == pLocalList)
        ((LocalList*)pCurList)->remove(idx);
    else if(pCurList == pMyList)
        ((MyList*)pCurList)->remove(idx);
    else{
        std::cerr<<" *** Wrong list type!"<<std::endl;
        exit(0);
    }

    update_songlist(pCurList, CurPage);
}

static int get_song_selected_index(){
    for (int i = 0; i < SONGLIST_SIZE; i++)
    {
        if (pListBox_song->get_selected_row() == pListBox_song->get_row_at_index(i))
        {
            return i;
        }
    }
    return -1;
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
