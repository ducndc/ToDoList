#include "todo_app.h"

class MainApp : public Gtk::Application {
protected:
    MainApp() : Gtk::Application("org.example.todo") {}

    void on_activate() override 
    {
        auto win = new TodoApp();
        add_window(*win);
        win->show();
    }

public:
    static Glib::RefPtr<MainApp> create() 
    {
        return Glib::RefPtr<MainApp>(new MainApp());
    }
};

int main(int argc, char* argv[]) 
{
    auto app = MainApp::create();
    return app->run(argc, argv);
}