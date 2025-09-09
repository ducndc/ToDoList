#include <gtkmm.h>
#include <fstream>
#include <string>

static const std::string STORAGE_FILE = "todo.txt";

class TodoApp : public Gtk::Window {
public:
    TodoApp() {
        set_title("TODO App (GTKmm)");
        set_default_size(600, 900);

        // Layout
        vbox.set_orientation(Gtk::ORIENTATION_VERTICAL);
        add(vbox);

        // List of tasks
        scrolled.add(taskList);
        scrolled.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
        vbox.pack_start(scrolled, Gtk::PACK_EXPAND_WIDGET, 5);

        // Entry + Add button
        hbox.pack_start(entry, Gtk::PACK_EXPAND_WIDGET, 5);
        btnAdd.set_label("Add");
        hbox.pack_start(btnAdd, Gtk::PACK_SHRINK, 5);
        vbox.pack_start(hbox, Gtk::PACK_SHRINK, 5);

        // Action buttons
        btnDone.set_label("Mark Done");
        btnDelete.set_label("Delete");
        hbox2.pack_start(btnDone, Gtk::PACK_EXPAND_WIDGET, 5);
        hbox2.pack_start(btnDelete, Gtk::PACK_EXPAND_WIDGET, 5);
        vbox.pack_start(hbox2, Gtk::PACK_SHRINK, 5);

        // Signals
        btnAdd.signal_clicked().connect(sigc::mem_fun(*this, &TodoApp::on_add));
        btnDelete.signal_clicked().connect(sigc::mem_fun(*this, &TodoApp::on_delete));
        btnDone.signal_clicked().connect(sigc::mem_fun(*this, &TodoApp::on_done));

        load_tasks();
        show_all_children();
    }

    ~TodoApp() override {
        save_tasks();
    }

private:
    Gtk::Box vbox{Gtk::ORIENTATION_VERTICAL};
    Gtk::ScrolledWindow scrolled;
    Gtk::ListBox taskList;

    Gtk::Box hbox{Gtk::ORIENTATION_HORIZONTAL};
    Gtk::Entry entry;
    Gtk::Button btnAdd;

    Gtk::Box hbox2{Gtk::ORIENTATION_HORIZONTAL};
    Gtk::Button btnDone, btnDelete;

    Gtk::ListBoxRow* get_selected_row() {
        return taskList.get_selected_row();
    }

    void on_add() {
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

    void on_delete() {
        auto row = get_selected_row();
        if (row) {
            taskList.remove(*row);
        }
    }

    void on_done() {
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

    void load_tasks() {
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

    void save_tasks() {
        std::ofstream f(STORAGE_FILE, std::ios::trunc);
        for (auto row : taskList.get_children()) {
            if (auto r = dynamic_cast<Gtk::ListBoxRow*>(row)) {
                if (auto child = dynamic_cast<Gtk::Label*>(r->get_child())) {
                    f << child->get_text() << "\n";
                }
            }
        }
    }
};

class MainApp : public Gtk::Application {
protected:
    MainApp() : Gtk::Application("org.example.todo") {}
    void on_activate() override {
        auto win = new TodoApp();
        add_window(*win);
        win->show();
    }
public:
    static Glib::RefPtr<MainApp> create() {
        return Glib::RefPtr<MainApp>(new MainApp());
    }
};

int main(int argc, char* argv[]) {
    auto app = MainApp::create();
    return app->run(argc, argv);
}

