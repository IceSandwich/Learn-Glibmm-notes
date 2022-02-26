/*
    Create by IceSandwich
    https://github.com/IceSandwich/
*/

#include <iostream>
#include <gtkmm.h>

using namespace std;

Glib::RefPtr<Glib::MainLoop> loop;

unsigned long long Fibonacci(int n) {
    if (n < 3) return 1;
    return Fibonacci(n - 1) + Fibonacci(n - 2);
}

bool timeoutCallback() {
    static int counter = 1;
    cout << "Timeout hit: " << counter << endl;
    if (counter == 3) {
        cout << "Reach end. Quit timeout." << endl;
        loop->quit();
        return false;
    }
    ++counter;
    return true;
}

int main() {

    /// 计时器 ///
    Glib::Timer timer;
    unsigned long long res = 1;
    cout << "Running..." << endl;
    timer.start();
    res = Fibonacci(44);
    timer.stop();
    /* 使用 timer.reset(); 对计时器重置 */
    cout << "Time used: " << timer.elapsed() << "s" << endl;
    cout << "Result: " << res << endl;





    /// 定时器 ///
    /* 新建MainLoop，可以是GtkMainLoop */
    loop = Glib::MainLoop::create();
    /* 参数单位为毫秒 */
    auto timeout = Glib::TimeoutSource::create(2000);
    timeout->connect(sigc::ptr_fun(timeoutCallback));
    /* 附加到主线程 */
    timeout->attach(loop->get_context());

    cout << "Timeout id: " << timeout->get_id() << endl;
    /* 数字越小，优先级越高 */
    cout << "Timeout priority: " << timeout->get_priority() << endl;

    /* 启动主线程，由timeoutCallback调用quit即可退出 */
    loop->run();
    



    
    cout << "Program exit normally." << endl;
    return 0;
}