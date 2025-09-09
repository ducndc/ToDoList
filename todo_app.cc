#include "todo_app.h"
#include <fstream>

static const std::string STORAGE_FILE = "todo.txt";

TodoApp::TodoApp(void) 
{
    set_title("TODO APP");
    set_default_size(600, 900);

    vbox.set_orientation(Gtk::ORIENTATION_VERTICAL);
    add(vbox);

    scrolled.add(taskList);
    scrolled.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    vbox.pack_start(scrolled, Gtk::PACK_EXPAND_WIDGET, 5);

    hbox.pack_start(entry, Gtk::PACK_EXPAND_WIDGET, 5);
    btnAdd.set_label("Add");
    hbox.pack_start(btnAdd, Gtk::PACK_SHRINK, 5);
    vbox.pack_start(hbox, Gtk::PACK_SHRINK, 5);

    btnDone.set_label("Mark Done");
    btnDelete.set_label("Delete");
    btnSave.set_label("Save");
    hbox2.pack_start(btnDone, Gtk::PACK_EXPAND_WIDGET, 5);
    hbox2.pack_start(btnDelete, Gtk::PACK_EXPAND_WIDGET, 5);
    hbox2.pack_start(btnSave, Gtk::PACK_EXPAND_WIDGET, 5);
    vbox.pack_start(hbox2, Gtk::PACK_SHRINK, 5);

    btnAdd.signal_clicked().connect(sigc::mem_fun(*this, &TodoApp::on_add));
    btnDelete.signal_clicked().connect(sigc::mem_fun(*this, &TodoApp::on_delete));
    btnDone.signal_clicked().connect(sigc::mem_fun(*this, &TodoApp::on_done));
    btnSave.signal_clicked().connect(sigc::mem_fun(*this, &TodoApp::on_save));

    load_tasks();
    show_all_children();
}

TodoApp::~TodoApp(void) 
{
    save_tasks();
}

Gtk::ListBoxRow* 
TodoApp::get_selected_row(void) 
{
    return taskList.get_selected_row();
}

void 
TodoApp::on_add(void) 
{
    auto text = entry.get_text();

    if (!text.empty()) {
        auto label = Gtk::make_managed<Gtk::Label>(text);
        label->set_xalign(0);
        auto row = Gtk::make_managed<Gtk::ListBoxRow>();
        row->add(*label);
        taskList.append(*row);
        row->show_all();
        entry.set_text("");
    }
}

void 
TodoApp::on_delete(void) 
{
    auto row = get_selected_row();

    if (row) {
        taskList.remove(*row);
    }
}

void 
TodoApp::on_done(void) 
{
    auto row = get_selected_row();

    if (row) {
        if (auto child = dynamic_cast<Gtk::Label*>(row->get_child())) {
            auto text = child->get_text();

            if (text.substr(0, 4) != "[x] ") {
                child->set_text("[x] " + text);
            }
        }
    }
}

void 
TodoApp::load_tasks(void) 
{
    std::ifstream f(STORAGE_FILE);

    if (!f) return;

    std::string line;

    while (std::getline(f, line)) {
        auto label = Gtk::make_managed<Gtk::Label>(line);
        label->set_xalign(0);
        auto row = Gtk::make_managed<Gtk::ListBoxRow>();
        row->add(*label);
        taskList.append(*row);
    }

    show_all_children();
}

void 
TodoApp::save_tasks(void) 
{
    std::ofstream f(STORAGE_FILE, std::ios::trunc);
    
    for (auto row : taskList.get_children()) {
        if (auto r = dynamic_cast<Gtk::ListBoxRow*>(row)) {
            if (auto child = dynamic_cast<Gtk::Label*>(r->get_child())) {
                f << child->get_text() << "\n";
            }
        }
    }
}

void TodoApp::on_save(void)
{
    save_tasks();
}