#include "todo_app.h"

#include <fstream>
#include <iostream>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/sha.h>
#include <vector>

static const std::string STORAGE_FILE = "todo.txt";

// Key and IV for AES-256-CBC (for demo, use a secure key/iv management in production)
const std::string AES_KEY = "0123456789abcdef0123456789abcdef"; // 32 bytes
const std::string AES_IV  = "abcdef9876543210";                 // 16 bytes

std::vector<unsigned char> 
aes_encrypt(
    const std::string& plaintext, 
    const std::string& key) 
{
    std::vector<unsigned char> ciphertext(plaintext.size() + EVP_MAX_BLOCK_LENGTH);
    int outlen1 = 0, outlen2 = 0;

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr,
                       reinterpret_cast<const unsigned char*>(key.data()),
                       reinterpret_cast<const unsigned char*>(AES_IV.data()));

    EVP_EncryptUpdate(ctx, ciphertext.data(), &outlen1,
                      reinterpret_cast<const unsigned char*>(plaintext.data()), plaintext.size());
    EVP_EncryptFinal_ex(ctx, ciphertext.data() + outlen1, &outlen2);

    EVP_CIPHER_CTX_free(ctx);
    ciphertext.resize(outlen1 + outlen2);
    return ciphertext;
}

std::string 
aes_decrypt(
    const std::vector<unsigned char>& ciphertext, 
    const std::string& key) 
{
    std::vector<unsigned char> plaintext(ciphertext.size());
    int outlen1 = 0, outlen2 = 0;

    EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
    EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), nullptr,
                       reinterpret_cast<const unsigned char*>(key.data()),
                       reinterpret_cast<const unsigned char*>(AES_IV.data()));

    EVP_DecryptUpdate(ctx, plaintext.data(), &outlen1, ciphertext.data(), ciphertext.size());
    EVP_DecryptFinal_ex(ctx, plaintext.data() + outlen1, &outlen2);

    EVP_CIPHER_CTX_free(ctx);
    plaintext.resize(outlen1 + outlen2);
    return std::string(plaintext.begin(), plaintext.end());
}

std::string 
password_to_aes_key(const std::string& password) 
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char*>(password.data()), password.size(), hash);
    return std::string(reinterpret_cast<char*>(hash), SHA256_DIGEST_LENGTH);
}

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

    Gtk::Dialog keyDialog("Enter Password", *this);
    keyDialog.set_default_size(400, 100);
    Gtk::Box* content = keyDialog.get_content_area();
    Gtk::Entry keyInput;
    keyInput.set_placeholder_text("Enter password");
    keyInput.set_visibility(false); // Hide password input
    content->pack_start(keyInput, Gtk::PACK_EXPAND_WIDGET, 10);
    keyInput.show();
    keyDialog.add_button("OK", Gtk::RESPONSE_OK);

    int result = keyDialog.run();

    if (result == Gtk::RESPONSE_OK) {
        std::string password = keyInput.get_text();
        aes_key = password_to_aes_key(password);
    } else {
        std::string password = "defaultpassword";
        aes_key = password_to_aes_key(password);
    }

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
    std::ifstream f(STORAGE_FILE, std::ios::binary);
    if (!f) {
        std::cout << "Not found " << STORAGE_FILE << std::endl;
        return;
    }
    while (f) {
        uint32_t len = 0;
        f.read(reinterpret_cast<char*>(&len), sizeof(len));
        if (!f || len == 0) break;
        std::vector<unsigned char> encrypted(len);
        f.read(reinterpret_cast<char*>(encrypted.data()), len);
        if (!f) break;
        std::string decrypted = aes_decrypt(encrypted, aes_key);

        auto label = Gtk::make_managed<Gtk::Label>(decrypted);
        label->set_xalign(0);

        if (decrypted.rfind("[x]", 0) == 0) {
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
    std::ofstream f(STORAGE_FILE, std::ios::binary | std::ios::trunc);
    for (auto row : taskList.get_children()) {
        if (auto r = dynamic_cast<Gtk::ListBoxRow*>(row)) {
            if (auto child = dynamic_cast<Gtk::Label*>(r->get_child())) {
                std::string line = child->get_text();
                auto encrypted = aes_encrypt(line, aes_key);
                // Write length and data for each line
                uint32_t len = encrypted.size();
                f.write(reinterpret_cast<const char*>(&len), sizeof(len));
                f.write(reinterpret_cast<const char*>(encrypted.data()), len);
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

