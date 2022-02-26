/*
    Create by IceSandwich
    https://github.com/IceSandwich/
*/

#include <iostream>
#include <gtkmm.h>

using namespace std;

Glib::IConv *iconv = nullptr;

int main() {
    /* 使用前一定要初始化，不然出一堆谁也不知道的bug */
    Glib::init();

    const char* txt = "hello\n测试中文\n😈🐕";
    const char* targetname = "中文测试.txt";





    /// 获取当前终端编码 ///
    string local_charset;
    if (!Glib::get_charset(local_charset)) {
        cout << "Info: current locale use non-urf8 charset." << endl;
        /* Glib使用的都是utf8，无需使用iconv转换什么 */
        iconv = new Glib::IConv(local_charset, "utf8");
    }
    cout << "Locale charset: " << local_charset << endl;






    /// 在非utf8编码系统下显示乱码 ///
    cout << "Text: >>>" << endl;
    cout << txt;
    cout << "<<<" << endl;





    /// 很多字符无法从utf8转到gbk ///
    // auto utf8str = Glib::locale_from_utf8(txt);
    // cout << "Utf8 to locale: >>>" << endl;
    // cout << utf8str;
    // cout << "<<<" << endl;





    /// 输出到文件 ///
    /* 同样，采用utf8了，无需转换 */
    // auto targetFilename = Glib::filename_to_utf8("中文测试.txt");
    auto targetFilename = Glib::ustring(targetname);
    /* 默认使用的就是utf8保存的，无需转为utf8再保存 */
    Glib::file_set_contents(targetFilename, txt);
    cout << "[+] Write to " << targetFilename << endl;

    auto content = Glib::file_get_contents(targetFilename);
    cout << "Read: >>>" << endl;
    cout << content;
    cout << "<<<" << endl;



    /// base64编码 ///
    auto base64_encode = Glib::Base64::encode(txt);
    cout << "Base64 encode: " << base64_encode << endl;
    cout << "Base64 decode: " << Glib::Base64::decode(base64_encode) << endl;

    return 0;
}