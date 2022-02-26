/*
    Create by IceSandwich
    https://github.com/IceSandwich/
*/

#include <iostream>
#include <fcntl.h>
#include <gtkmm.h>

using namespace std;

int main() {
    /* 使用前一定要初始化，不然出一堆谁也不知道的bug */
    Glib::init();
    Gio::init();



    const char* directory = "output";
    const char* filename = "demo.txt";
    const char* filetarget = "target.txt";
    const char* tmpfileprefix = "learnglibmm_filesystem-";

    const char* appenddata = "append data?\n";
    Glib::ustring filedata = "Hello world\nCould u see me?\n中文测试\n";





    /// 创建文件夹，确保不存在再创建，不然出错 ///

    /* 注意 Gio::File 并不代表文件，尽管它的名称是 文件 的意思。*/
    /* 可以理解为python中的路径 Path 类，描述的是一个文件/文件夹的路径 */
    auto folder = Gio::File::create_for_path(directory);
    if (folder->query_exists()) {
        cout << "[+] Folder " << folder->get_path() << " already exists." << endl;
    } else {
        if (folder->make_directory()) {
            cout << "[+] Create directory: " << folder->get_path() << endl;
        } else {
            cout << "[-] Unhandled error when creating folder" << folder->get_path() << ". Program exits.\n" << endl;
            exit(-1);
        }
    }





    /// 创建并写入文件夹下的文件，同样要求不存在才创建，不然出错 ///
    auto file = folder->get_child(filename);
    /* Glibmm 方法： Glib::file_test(filename, Glib::FILE_TEST_EXISTS); */
    if (file->query_exists()) {
        cout << "[+] File: " << file->get_path() << " already exists." << endl;
    } else {
        /* 创建文件，传入 CreateFlags::PRIVATE 使得文件只读 */
        auto stream = file->create_file();
        cout << "[+] Create file: " << file->get_path() << endl;

        auto inputlength = filedata.bytes();
        cout << "[+] Write bytes: " << inputlength << endl;
        stream->write_all(filedata, inputlength);
        if (stream->close()) {
            cout << "[+] Write to file: " << filedata << endl;
        } else {
            cout << "[-] Close file " << file->get_path() << " failed." << endl;
        }
    }






    /// 复制文件，目标文件无需调用create_file()，目标文件不需要保证存在，但源文件要保证存在 ///
    auto file2 = folder->get_child(filetarget);
    /* 复制文件，传入 CopyFlags::OVERWRITE 使得覆盖目标文件*/
    if (file->copy(file2)) {
        cout << "[+] Copy from " << filename << " to " << filetarget << endl;
    } else {
        cout << "[-] Copy from " << filename << " to " << filetarget << " failed." << endl;
    }






    /// 获得文件所在文件夹(文件的父级) 或者 获取文件夹所在的文件夹(文件夹的父级) ///
    auto parent = file2->get_parent();
    auto basename = file2->get_basename();
    cout << "[+] File " << basename << " parent: " << parent->get_path() << endl;
    cout << "[+] Parent basename: " << parent->get_basename() << endl;










    /// 获取文件的 追加 流，同样不必保证文件存在，同样传入 CreateFlags::PRIVATE 使得文件只读 ///
    auto appendHandler = file2->append_to();
    appendHandler->write(appenddata); /* write 和 write_all 都可以，后者可指定部分写入 */
    if (appendHandler->close()) {
        cout << "[+] Append to file: " << appenddata << endl;
    } else {
        cout << "[-] Close file " << file2->get_path() << " failed." << endl;
    }





    /// 从Uri获取文件描述 ///
    auto file2_uri = file2->get_uri();
    cout << "[+] Uri for file " << file2->get_path() << endl;
    auto file2_FromUri = Gio::File::create_for_uri(file2_uri);





    /// 读取文件 ///
    /* 使用 load_partial_contents 分部分读取大文件 */
    char* content = new char[100];
    gsize length = sizeof(char) * 100;
    if (!file2_FromUri->load_contents(content, length)) {
        cout << "[-] Can't load content from " << file2_FromUri->get_path() << endl;
    } else {
        cout << "[+] Load content from " << file2_FromUri->get_path() << " >>>" << endl;
        cout << content << endl;
        cout << "<<<" << endl;
    }





    /// Glib 方法 读取文件 ///
    cout << "[+] Glib get: >>> " << endl;
    cout << Glib::file_get_contents(file2->get_path());
    cout << "<<<" << endl;





    /// UTF-8 路径 ///
    cout << "[+] Parse name: " << file2_FromUri->get_parse_name() << endl;




    /// 这里可以获取程序的工作目录 ///
    auto relativeRoot = Gio::File::create_for_commandline_arg("");
    cout << "[+] Working directory: " << relativeRoot->get_path() << endl;




    /// 得到相对地址，并从相对地址转到绝对地址 ///
    /* 注意顺序，由根目录调用get_relative_path(descendant)得到descendant相对于根目录的相对路径 */
    auto relativePath = relativeRoot->get_relative_path(file);
    cout << "[+] File " << file->get_basename() << " relative path: " << relativePath << endl;
    auto resolveFile = relativeRoot->resolve_relative_path(relativePath);
    cout << "[+] Resolve from relative path: " << resolveFile->get_path() << endl;




    /// 创建链接，Windows无法工作？ ///
    #if defined(UNIX) || defined(LINUX)
    if (file2->make_symbolic_link(symbolname)) {
        cout << "[+] Create symbolic " << symbolname << endl;
    } else {
        cout << "[-] Can't create symbolic " << symbolname << endl;
    }
    #endif




    /// 读取文件夹下所有文件，设置 attributes 可过滤需要的文件名，要确保是目录且目录存在  ///
    cout << "[+] Enumerate children in " << relativeRoot->get_path() << " :" << endl;
    auto filelist_enumerator = relativeRoot->enumerate_children();
    Glib::RefPtr<Gio::FileInfo> fileinfo; /* Gio::File::query_info() 可得到 Gio::FileInfo */
    while (fileinfo = filelist_enumerator->next_file()) {
        if (fileinfo->get_file_type() == (Gio::FileType)G_FILE_TYPE_DIRECTORY) {
            cout << " - Folder: " << fileinfo->get_name() << endl;
        } else {
            cout << " - File: " << fileinfo->get_name() << " Size: " << fileinfo->get_size() << endl;
        }
    }
    filelist_enumerator->close();





    /// Glibmm方法 读取文件夹下所有文件 ///
    cout << "[+] Glib get:" << endl;
    auto dir = Glib::Dir(relativeRoot->get_path());
    for (auto dirfile : dir) {
        if (Glib::file_test(dirfile, Glib::FILE_TEST_IS_DIR)) {
            cout << " - Folder: " << dirfile << endl;
        } else {
            if (Glib::str_has_suffix(dirfile, ".ini")) {
                cout << " - Ini File: " << dirfile << endl;
            } else if (Glib::str_has_suffix(dirfile, ".txt")) {
                cout << " - Txt File: " << dirfile << endl;
            } else {
                cout << " - File: " << dirfile << endl;
            }
        }
    }
    dir.close();





    /// 删除文件 ///
    if (file2->remove()) {
        cout << "[+] Remove " << file2->get_path() << endl;
    } else {
        cout << "[-] Can't remove " << file2->get_path() << endl;
    }






    /// 移入垃圾桶 ///
    if (file->trash()) {
        cout << "[+] Move " << file->get_path() << " to trashcan" << endl;
    } else {
        cout << "[+] Can't move " << file->get_path() << " to trashcan" << endl;
    }






    /// 删除目录，需要保证目录为空 ///
    if (folder->remove()) {
        cout << "[+] Remove " << folder->get_path() << endl;
    } else {
        cout << "[-] Can't remove " << folder->get_path() << endl;
    }






    /// 创建临时文件 ///
    /* 使用 open 函数创建的文件，该函数会修改 tmpfilename 变量为创建的文件的路径 */
    /* 注意Glib是以二进制形式打开的文件 */
    string tmpfilename;
    auto tmpFile = Glib::file_open_tmp(tmpfilename, tmpfileprefix);
    write(tmpFile, filedata.c_str(), filedata.size());
    close(tmpFile);
    cout << "Create temp: " << tmpfilename << endl;
    /* 删除该临时文件，注释掉可看到输出的文件 */
    // unlink(tmpfilename.c_str());






    /// 其他有用的函数 ///
    /* Gio::File::set_display_name 重命名文件/文件夹 */
    /* Gio::File::move 移动文件/文件夹，传入 CopyFlags::OVERWRITE 以覆盖 */
    /* Gio::File::monitor/monitor_file/monitor_directory 监视文件/文件夹 */

    return 0;
}