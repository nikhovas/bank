#pragma once
#include <bank/DataObjects.hpp>


namespace OperativeMemory {
    using DatabaseObjects::id;
    class UniqueIdGetter {
    public:
        id getNew() {
            return this->new_id++;
        }
    private:
        id new_id{0};
    };
};