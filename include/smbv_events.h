#pragma once

namespace mtl::smbv {

namespace bidirectional {

enum class ACTION { FALLTHROUGH, KEEP_ON };

struct Event {
    ACTION action;
};

}  // namespace bidirectional

namespace multidirectional {

template <typename T>
struct Event {
    T action;
};

}  // namespace multidirectional

}  // namespace mtl::smbv