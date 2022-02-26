/*
    Create by IceSandwich
    https://github.com/IceSandwich/
*/

#include <iostream>
#include <gtkmm.h>

using namespace std;

int main() {
    Glib::init();

    const Glib::ustring moduleName = "xxx.dll";

    // FIXME: complete this file
    cout << "[WARNING] This program doesn't complete." << endl;
    cout << "[WARNING] This program will not work properly." << endl;
    cout << endl;

    auto moduleFilename = Glib::Module::build_path("", moduleName);

    auto module = Glib::Module(moduleFilename);
    if (!module) {
        cout << "[-] Can't load module " << moduleFilename << endl;
        cout << "[-] Error: " << module.get_last_error() << endl;
        exit(-1);
    }
    cout << "[+] Loaded module " << moduleFilename << " Module name: " << module.get_name() << endl;

    void *symbolFunc = nullptr;

    if (!module.get_symbol("function_name", symbolFunc)) {
        cout << "Can't load symbol." << endl;
        cout << module.get_last_error() << endl;
        exit(-1);
    }
    cout << "[+] Loaded symbol." << endl;

    return 0;
}