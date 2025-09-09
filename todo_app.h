#pragma once
#include <gtkmm.h>
#include <string>

class TodoApp : public Gtk::Window {
public:
    TodoApp(void);
    ~TodoApp(void) override;
private:
    Gtk::Box vbox{Gtk::ORIENTATION_VERTICAL};
    Gtk::ScrolledWindow scrolled;
    Gtk::ListBox taskList;

    Gtk::Box hbox{Gtk::ORIENTATION_HORIZONTAL};
    Gtk::Entry entry;
    Gtk::Button btnAdd, btnSave;

    Gtk::Box hbox2{Gtk::ORIENTATION_HORIZONTAL};
    Gtk::Button btnDone, btnDelete;

    Gtk::ListBoxRow* get_selected_row(void);
    void on_add(void);
    void on_delete(void);
    void on_done(void);
    void on_save(void);
    void load_tasks(void);
    void save_tasks(void);
};