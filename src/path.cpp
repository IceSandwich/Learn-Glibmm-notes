/*
    Create by IceSandwich
    https://github.com/IceSandwich/
*/

#include <iostream>
#include <vector>
#include <gtkmm.h>

using namespace std;

typedef string (*KVMapFunc)(const string&);

inline void printKV(string key, string value, string prefix = "") {
    cout << prefix << key << ": " << value << endl;
}

inline void printSeperator() {
    cout << endl;
}

void printList(string title, vector<string> list, KVMapFunc mapping = nullptr) {
    cout << title << ": " << endl;
    if (mapping) {
        for (auto elem : list) {
            printKV(elem, mapping(elem), "\t");
        }
    } else {
        for (auto elem : list) {
            cout << "\t" << elem << endl;
        }
    }
}

int main(int argc, char** argv) {
    /* 使用前一定要初始化，不然出一堆谁也不知道的bug */
    gtk_init(&argc, &argv);
    // Glib::init();
    // Gio::init();


    vector<string> demoFilenamePartList = {
        "E:\\",
        "example",
        "a.txt"
    };
    Glib::ustring demoUri = "https://www.baidu.com/index.php?a=1&username=您好";


    printKV("Application name", Glib::get_application_name());
    printKV("Program name", Glib::get_prgname());
    printList("Env", Glib::listenv(), Glib::getenv);
    printKV("User name", Glib::get_user_name());
    printKV("Real name", Glib::get_real_name());
    printKV("Host name", Glib::get_host_name());
    printKV("Home dir", Glib::get_home_dir());
    printKV("Tmp dir", Glib::get_tmp_dir());
    printKV("Current dir", Glib::get_current_dir());
    printKV("Desktop", Glib::get_user_special_dir(Glib::USER_DIRECTORY_DESKTOP));
    printKV("User data dir", Glib::get_user_data_dir());
    printKV("User config dir", Glib::get_user_config_dir());
    printKV("User cache dir", Glib::get_user_cache_dir());
    printKV("User runtime dir", Glib::get_user_runtime_dir());
    printList("Sys data dir", Glib::get_system_data_dirs());
    printList("Sys config dir", Glib::get_system_config_dirs());
    printSeperator();






    auto demoFilename = Glib::build_filename(demoFilenamePartList);
    cout << "Input path: " << demoFilename << endl;

    if (Glib::path_is_absolute(demoFilename)) {
        cout << " - It's a absolute file path." << endl;
    } else {
        cout << " - It's a relative file path." << endl;
    }

    string prefix = " - ";
    printKV("Path skip root", Glib::path_skip_root(demoFilename), prefix);
    printKV("Basename", Glib::path_get_basename(demoFilename), prefix);
    printKV("Dirname", Glib::path_get_dirname(demoFilename), prefix);
    printKV("Canonicalize Filename", Glib::canonicalize_filename(demoFilename), prefix);
    printSeperator();

    printKV("G++ program", Glib::find_program_in_path("g++"));
    printKV("Format size", Glib::format_size(3292528, Glib::FORMAT_SIZE_DEFAULT));
    printSeperator();

    printList("Command line", Glib::shell_parse_argv("--save \"a.jpg\" -I/usr/include -j 8"));
    printSeperator();

    auto escapeUri = Glib::uri_escape_string(demoUri);
    printKV("Url", demoUri);
    printKV("Escape", escapeUri);
    printKV("Scheme", Glib::uri_parse_scheme(demoUri));
    printKV("Unescape", Glib::uri_unescape_string(escapeUri));

    return 0;
}