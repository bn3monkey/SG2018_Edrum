#include "popup.hpp"

void popup(std::string str)
{
    pLabel_notice->set_text(str);

    if (pDialog_notice == nullptr)
    {
        refBuilder->get_widget("dialog_notice", pDialog_notice);

        if (pDialog_notice)
        {
            pDialog_notice->show();
        }
        else{
            std::cerr << " *** Failed to get NOTICE DIALOG!!" << std::endl;
        }
    }
    else
        pDialog_notice->show();
}