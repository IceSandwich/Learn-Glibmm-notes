/*
    Create by IceSandwich
    https://github.com/IceSandwich/
*/

#include <iostream>
#include <map>
#include <gtkmm.h>

using namespace std;

map<string, Glib::Checksum::ChecksumType> mapping = {
    {"MD5", Glib::Checksum::CHECKSUM_MD5},
    {"SHA1", Glib::Checksum::CHECKSUM_SHA1},
    {"SHA256", Glib::Checksum::CHECKSUM_SHA256},
    {"SHA384", Glib::Checksum::CHECKSUM_SHA384},
    {"SHA512", Glib::Checksum::CHECKSUM_SHA512},
};

int main() {
    Glib::init();

    string inputdata = "data check\n中文测试\n🐕";

    cout << "Input: >>>" << endl;
    cout << inputdata;
    cout << "<<<" << endl << endl;

    for (auto kv : mapping) {
        cout << kv.first << ": " << Glib::Checksum::compute_checksum(kv.second, inputdata) << endl;
    }

    return 0;
}