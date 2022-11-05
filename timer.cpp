#include "Poco/Timer.h"
#include "Poco/Thread.h"
#include "Poco/Stopwatch.h"

#include <boost/regex.hpp>
#include <string>
#include <iostream>

using Poco::Timer;
using Poco::TimerCallback;
using Poco::Thread;
using Poco::Stopwatch;

class TimerExample{
public:
    TimerExample(){ _sw.start();}
    void onTimer(Timer& timer){
        std::cout << "Callback called after " << _sw.elapsed()/1000 << " milliseconds." << std::endl;
    }
private:
    Stopwatch _sw;
};

int main(int argc, char** argv){
    TimerExample example;
    Timer timer(250, 500);
    timer.start(TimerCallback<TimerExample>(example, &TimerExample::onTimer));

    Thread::sleep(3000);
    timer.stop();

    std::string s = "correct@email.com", s2="bademail";
    boost::regex expr{"\\b[a-zA-Z0-9._%-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,4}\\b"};
    std::cout << std::boolalpha << boost::regex_match(s, expr) << '\n';
    std::cout << std::boolalpha << boost::regex_match(s2, expr) << '\n';

    return 0;
}
