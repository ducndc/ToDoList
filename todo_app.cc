#include "todo_app.h"
#include <fstream>

static const std::string STORAGE_FILE = "todo.txt";

TodoApp::TodoApp(void) 
{
    set_title("TODO APP");
    set_default_size(600, 900);
    maximize();

    Pango::FontDescription font;
    font.set_family("Sans");
    font.set_size(14 * Pango::SCALE);
    taskList.override_font(font);
    entry.override_font(font);
    btnAdd.override_font(font);
    btnDone.override_font(font);
    btnDelete.override_font(font);
    btnSave.override_font(font);
    btnEdit.override_font(font);

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
    btnEdit.set_label("Edit");

    hbox2.pack_start(btnDone, Gtk::PACK_EXPAND_WIDGET, 5);
    hbox2.pack_start(btnEdit, Gtk::PACK_EXPAND_WIDGET, 5);
    hbox2.pack_start(btnDelete, Gtk::PACK_EXPAND_WIDGET, 5);
    hbox2.pack_start(btnSave, Gtk::PACK_EXPAND_WIDGET, 5);
    vbox.pack_start(hbox2, Gtk::PACK_SHRINK, 5);

    btnAdd.signal_clicked().connect(sigc::mem_fun(*this, &TodoApp::AddTask));
    btnEdit.signal_clicked().connect(sigc::mem_fun(*this, &TodoApp::EditTask));
    btnDelete.signal_clicked().connect(sigc::mem_fun(*this, &TodoApp::DeleteTask));
    btnDone.signal_clicked().connect(sigc::mem_fun(*this, &TodoApp::SetTaskDone));
    btnSave.signal_clicked().connect(sigc::mem_fun(*this, &TodoApp::SaveTasks));

    LoadTasks();
    show_all_children();
}

TodoApp::~TodoApp(void) 
{
    SaveTasks();
}

std::string 
TodoApp::CurrentDate(void)
{
    auto t = std::time(nullptr);
    std::tm tm{};
    localtime_r(&t, &tm);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M");
    return oss.str();
}

Gtk::ListBoxRow* 
TodoApp::GetSelectedRow(void) 
{
    return taskList.get_selected_row();
}

void 
TodoApp::AddTask(void) 
{
    auto text = entry.get_text();

    if (!text.empty()) {
        std::string datedTask = "[" + CurrentDate() + "] " + text;

        auto label = Gtk::make_managed<Gtk::Label>(datedTask);
        label->set_xalign(0);
        
        auto row = Gtk::make_managed<Gtk::ListBoxRow>();
        row->add(*label);
        taskList.append(*row);
        row->show_all();

        entry.set_text("");
    }
}

void 
TodoApp::DeleteTask(void) 
{
    auto row = GetSelectedRow();

    if (row) {
        taskList.remove(*row);
    }
}

void 
TodoApp::SetTaskDone(void) 
{
    auto row = GetSelectedRow();

    if (row) {
        if (auto child = dynamic_cast<Gtk::Label*>(row->get_child())) {
            auto text = child->get_text();

            if (text.substr(0, 4) != "[x] ") {
                child->set_text("[x] " + text);
                Pango::AttrList attrs;
                auto attr = Pango::Attribute::create_attr_strikethrough(true);
                attrs.insert(attr);
                child->set_attributes(attrs);

                child->override_color(Gdk::RGBA("green"));    
            }
        }
    }
}

void 
TodoApp::LoadTasks(void) 
{
    std::ifstream f(STORAGE_FILE);

    if (!f) return;

    std::string line;

    while (std::getline(f, line)) {
        auto label = Gtk::make_managed<Gtk::Label>(line);
        label->set_xalign(0);

        if (line.rfind("[x]", 0) == 0) {
            Pango::AttrList attrs;
            auto attr = Pango::Attribute::create_attr_strikethrough(true);
            attrs.insert(attr);
            label->set_attributes(attrs);
            label->override_color(Gdk::RGBA("green"));
        }

        auto row = Gtk::make_managed<Gtk::ListBoxRow>();
        row->add(*label);
        taskList.append(*row);
    }

    show_all_children();
}

void 
TodoApp::SaveTasks(void) 
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

void 
TodoApp::EditTask(void) 
{
    auto row = taskList.get_selected_row();
    
    if (row) {
        if (auto child = dynamic_cast<Gtk::Label*>(row->get_child())) {
            Gtk::Dialog dialog("Edit Task", *this);
            dialog.set_default_size(800, 120);

            Gtk::Box* content = dialog.get_content_area();

            Gtk::Entry entry;
            entry.set_text(child->get_text());

            Pango::FontDescription font;
            font.set_family("Sans");     
            font.set_size(14 * Pango::SCALE);
            entry.override_font(font);

            entry.set_activates_default(true);
            content->pack_start(entry, Gtk::PACK_EXPAND_WIDGET, 10);
            entry.show();

            dialog.add_button("Cancel", Gtk::RESPONSE_CANCEL);
            dialog.add_button("Save", Gtk::RESPONSE_OK);

            int result = dialog.run();
            if (result == Gtk::RESPONSE_OK) {
                child->set_text(entry.get_text());
            }
        }
    }
}

