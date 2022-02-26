/*
    Create by IceSandwich
    https://github.com/IceSandwich/
*/

#include <iostream>
#include <gtkmm.h>

using namespace std;

void printCase(string title, string pattern, string content, Glib::RegexCompileFlags compileFlags = (Glib::RegexCompileFlags)0, Glib::RegexMatchFlags matchFlags = (Glib::RegexMatchFlags)0, int entryIdx = -1) {
    cout << "[+] Running case: " << title << endl;
    cout << "[+] Case pattern: " << pattern << endl;

    auto regex = Glib::Regex::create(pattern, compileFlags);
    Glib::MatchInfo matchinfo;
    if (!regex->match(content, matchinfo, matchFlags)) {
        cout << "[-] No matches!" << endl << endl;
        return;
    }
    cout << "[+] Found matched!" << endl;

    for (; matchinfo.matches(); matchinfo.next()) {
        if (entryIdx == -1) {
            for (auto subgroup : matchinfo.fetch_all()) {
                cout << " - Item: " << subgroup << endl;
            }
        } else {
            cout << " - Item(" << entryIdx << "): " << matchinfo.fetch(entryIdx) << endl;
        }
        cout << "[+] Next match..." << endl;
    }
    cout << endl;
}

int main() {
    /* 使用前一定要初始化，不然出一堆谁也不知道的bug */
    Glib::init();

    Glib::ustring html = 
    "<!DOCTYPE html>\n"
    "<html lang=\"en\">\n"
    "<head>\n"
    "    <title>Document</title>\n"
    "</head>\n"
    "<body>\n"
    "    <p><img src=\"/example.jpg\">Example img</p>\n"
    "    <h2><img alt=\"Help\" src=\"root/a.webp\">Example img2</h2>\n"
    "    <!-- var jsObj =    {\n"
    "        username: \"John\",\n"
    "        password:  123456,\n"
    "        info: {\n"
    "           id: \"Acdef123\"\n"
    "        }\n"
    "    }; -->\n"
    "</body>\n"
    "</html>\n";

    cout << "Html file: >>> " << endl;
    cout << html;
    cout << "<<<" << endl << endl;
    




    /// 获取页面标题 ///
    printCase("FetchTitle", "<title>(.*?)</title>", html, Glib::REGEX_OPTIMIZE, (Glib::RegexMatchFlags)0, 1);





    /// 获取注释里的js对象 ///
    /* Glib::REGEX_DOTALL 让点支持换行符（默认是不匹配换行符的） */
    printCase("FetchJsObject", "jsObj\\s*?=\\s*?({.*?});", html, Glib::REGEX_DOTALL | Glib::REGEX_OPTIMIZE, (Glib::RegexMatchFlags)0, 1);




    /// 获取所有图像地址 ///
    /* Glib::REGEX_EXTENDED 支持 (?=xxx) 这种语法 */
    printCase("FetchImgSrc", "(?=<img).*?src=\"(.*?)\"", html, Glib::REGEX_EXTENDED | Glib::REGEX_OPTIMIZE, (Glib::RegexMatchFlags)0, 1);


    /// 有用的链接 ///
    // https://www.lzone.de/examples/Glib%20GRegex
    return 0;
}