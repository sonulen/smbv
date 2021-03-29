#include <array>
#include <iostream>
#include <smbv_machine.hpp>

using mtl::smbv::Machine;

class Before {
public:
    enum class MY_CUSTOM_EVENT {
        HIT,
        ROAD,
        JACK,
        DONT,
        YOU,
        COME,
        BACK,
        NO_MORE
    };

    Before() {
        std::cout << "Before state!" << std::endl;
    }

    std::optional<MY_CUSTOM_EVENT> iterate() {
        if (true) {
            return MY_CUSTOM_EVENT::HIT;
        }

        // Keep calm, do nothing
        return {};
    }
};

class After {
public:
    enum class YA_CUSTOM_EVENT { NOW, WHEN, I, WAS, A, LITTLE, BOY };

    After() {
        std::cout << "After state!" << std::endl;
    }

    std::optional<YA_CUSTOM_EVENT> iterate() {
        if (false) {
            return YA_CUSTOM_EVENT::NOW;
        }
        return {};
    }
};

/// State Machine
class TimeMachine : public Machine<TimeMachine, Before, After> {
public:
    TimeMachine() : Machine<TimeMachine, Before, After>(Before{}) {}

    template <typename State, typename Event>
    bool on_event(State&, const Event&) {
        std::cout << "I have no idea!" << std::endl;
        return false;
    }

    bool on_event(Before&, const Before::MY_CUSTOM_EVENT& event) {
        if (event == Before::MY_CUSTOM_EVENT::HIT) {
            state_.emplace<After>();
            return true;
        }
        return false;
    }

    template <typename T>
    bool is_state() {
        return std::visit(
            [](auto& state) -> bool {
                return std::is_same_v<decltype(state), T&>;
            },
            state_);
    }
};


int main() {
    TimeMachine machine;

    std::cout << std::boolalpha
              << "State == Before = " << machine.is_state<Before>()
              << std::endl;

    machine.iterate();

    std::cout << std::boolalpha
              << "State == After = " << machine.is_state<After>() << std::endl;


    return 0;
}