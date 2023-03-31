
#ifndef BOARD_H
#define BOARD_H
#include <map>
#include <functional>
#include <utility>

namespace time_line {
enum class Action {
    CHANGED_SCALE, BOOKMARK_CREATED, BUTTON_CLICKED,GROUP_CREATED
};

class Board
{
private:
    Board();
    using signalFun = std::function<void>;
    //std::map<Action,signalFun> all_signals;
// map of each signal to slot
//each component registers slot
public:
    static Board& instance()
    {
        static Board INSTANCE;
        return INSTANCE;
    }

    void add_signals(const std::vector<std::pair<Action, signalFun>> &){};

};
}

#endif // BOARD_H
