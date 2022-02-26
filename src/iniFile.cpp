/*
    Create by IceSandwich
    https://github.com/IceSandwich/
*/

#include <iostream>
#include <vector>
#include <gtkmm.h>

using namespace std;

int main() {
    Glib::init();

    const char* keyFilename = "key.ini";

    /// 写入 kv文件/ini文件 ///
    auto keyfile = Glib::KeyFile();

    string groupName1 = "First Group";
    keyfile.set_integer(groupName1, "AttrInt", 1024);
    keyfile.set_string(groupName1, "Name", "Key File Example\tthis value shows\nescaping");
    keyfile.set_string(groupName1, "Welcome", "Hello");
    keyfile.set_locale_string(groupName1, "Welcome", "zh", "您好");
    keyfile.set_locale_string(groupName1, "Welcome", "fr", "Bonjour");
    keyfile.set_locale_string(groupName1, "Welcome", "em", "🐕");

    string groupName2 = "Another Group";
    auto numbersList = vector<int>({2, 20, -200, 0});
    keyfile.set_integer_list(groupName2, "Numbers", numbersList);
    auto booleansList = vector<bool>({true, false, true, true});
    keyfile.set_boolean_list(groupName2, "Booleans", booleansList);

    /* 删除键，使用 remove_group 删除组 */
    keyfile.remove_key(groupName1, "AttrInt");

    /* 保存文件 */
    if (!keyfile.save_to_file(keyFilename)) {
        cout << "[-] Can't save to " << keyFilename << endl;
        exit(-1);
    }
    cout << "[+] Save to " << keyFilename << endl;





    /// 读取 kv文件/ini文件 ///
    auto keyfile2 = Glib::KeyFile();
    if (!keyfile2.load_from_file(keyFilename)) {
        cout << "[-] Can't load from " << keyFilename << endl;
        exit(-1);
    }
    cout << "[+] Load kv file from " << keyFilename << endl;

    cout << "Numbers:" << endl;
    for (auto num : keyfile2.get_integer_list(groupName2, "Numbers")) {
        cout << "\t" << num << endl;
    }
    cout << "Booleans:" << endl;
    for (auto num : keyfile2.get_boolean_list(groupName2, "Booleans")) {
        cout << "\t" << num << endl;
    }
    cout << "Name: " << keyfile2.get_string(groupName1, "Name") << endl;

    cout << "Welcome: " << keyfile2.get_string(groupName1, "Welcome") << endl;

    // FIXME: Test fail.  
    //      Expect: Welcome[fr]: Bonjour
    //         Got: Welcome[fr]: Hello
    cout << "Welcome[fr]: " << keyfile2.get_locale_string(groupName1, "Welcome", "fr") << endl;

    cout << "Welcome[zh]: " << keyfile2.get_locale_string(groupName1, "Welcome", "zh") << endl;

    // FIXME: Test fail.  
    //      Expect: Welcome[em]: 🐕
    //         Got: Welcome[em]: Hello
    cout << "Welcome[em]: " << keyfile2.get_locale_string(groupName1, "Welcome", "em") << endl;

    return 0;
}