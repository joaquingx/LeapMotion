#include "helloworld.h"
#include <iostream>


HelloWorld::HelloWorld(): m_VBox(Gtk::ORIENTATION_VERTICAL), m_button("Close"){
  set_title("Gtk::Entry");

  add(m_VBox);

  m_entry.set_max_length(50);
  m_entry.set_text("enter text....");
  m_VBox.pack_start(m_entry, Gtk::PACK_SHRINK);


  m_button.signal_clicked().connect( sigc::mem_fun(*this,&HelloWorld::on_button_clicked) );
  
  m_VBox.pack_start(m_button, Gtk::PACK_SHRINK);
  m_button.set_can_default();
  m_button.grab_default();

  show_all_children();
}

HelloWorld::~HelloWorld()
{
}



void HelloWorld::on_button_clicked()
{
  
  std::cout << "Hello World" << std::endl;
  std::string data=m_entry.get_text();
  std::cout<< data <<std::endl;


  examplewindow = new ExampleWindow(data);

  examplewindow->show();


}