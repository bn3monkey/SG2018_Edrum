# ShareDrum - Capstone2 Project  

# 목차  
1. [Dependency](#1-dependency)
2. [Installation](#2-installation)  
3. [Naming Rule](#3-naming-rule)
4. [Progress](#4-progress)  
4.1. [Done](#41-done)  
4.2. [TODO](#42-todo)  

# 1. Dependency  
* Language : `CPP`  
* Library : `gtkmm-3.0`  
 
# 2. Installation  
Open terminal and type following command :  
```
 ~$ sudo apt-get install libgtkmm-3.0-dev 
```

# 3. Naming Rule
* Widget ID
> `widget-type`\_`group`\_`descript`(can skip group)  
> Example : `box_songlist_online`, `btn_login`  

* Widget Pointer
> p`Widget-type`\_`group`\_`descript`(can skip group)  
> Example : `pLabel_songlist_title`, `pBox_login`  

* Event Handler Function Name
> on_`Widget-ID`_`event`  
> Example : ```void on_btn_login_clicked();```  

# 4. Progress

# 4.1. Done
* GTK Window Creation
* Read UI from `*.glade`  
* Register event handler in `*.cpp` & `*.glade` (need interlock of both file)
* Create **_Fullscreen_** GTK Widget/Window

# 4.2. TODO
* Flip next page(After login)
