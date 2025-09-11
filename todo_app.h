#pragma once
#include <gtkmm.h>
#include <string>
#include <iomanip>
#include <sstream>

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
    Gtk::Button btnAdd, btnSave, btnEdit;

    Gtk::Box hbox2{Gtk::ORIENTATION_HORIZONTAL};
    Gtk::Button btnDone, btnDelete;

    Gtk::Entry keyEntry;
    std::string aes_key;

    Gtk::ListBoxRow* GetSelectedRow(void);
    std::string CurrentDate(void);
    void AddTask(void);
    void DeleteTask(void);
    void EditTask(void);
    void SetTaskDone(void);
    void LoadTasks(void);
    void SaveTasks(void);
};
