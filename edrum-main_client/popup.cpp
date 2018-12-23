#include "popup.hpp"

void popup(std::string str, bool modal)
{
    pLabel_notice->set_text(str);

    if (pDialog_notice == nullptr)
    {
        refBuilder->get_widget("dialog_notice", pDialog_notice);

        if (pDialog_notice)
        {
            if(modal)
                pDialog_notice->run();
            else
                pDialog_notice->show();
        }
        else{
            std::cerr << " *** Failed to get NOTICE DIALOG!!" << std::endl;
        }
    }
    else{
        if (modal)
            pDialog_notice->run();
        else
            pDialog_notice->show();
    }
}