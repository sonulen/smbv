#pragma once


#include <optional>
#include <variant>

#include "is_optional.h"

namespace mtl::smbv {

template <typename Derived, typename... States>
class Machine {
public:
    template <typename T>
    Machine(const T& init_state) : state_{init_state} {}

    void iterate() {
        Derived& machine = static_cast<Derived&>(*this);

        std::visit(
            [&machine](auto& state) -> void {
                const auto& event = state.iterate();

                static_assert(is_optional<decltype(event)>::value,
                              "The return iteration type must be enclosed in "
                              "an optional");

                if (event) {
                    machine.on_event(state, event.value());
                }
            },
            state_);
    }

    template <typename Event>
    auto dispatch(Event&& event) {
        Derived& machine = static_cast<Derived&>(*this);

        return std::visit(
            [&machine, &event](auto& state) -> auto {
                return machine.on_event(state, std::forward<Event>(event));
            },
            state_);
    }

protected:
    template <typename T>
    void change_state_to(T&& new_state) {
        state_ = new_state;
    }

    std::variant<States...> state_;
};

}  // namespace mtl::smbv
