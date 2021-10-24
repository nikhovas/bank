#pragma once


#include "bank/DataObjects.hpp"


enum GetObjectOptions {
    READ_ONLY, READ_WRITE
};


template<typename T>
class ITypeDataSource {
public:
    virtual T getObject(DatabaseObjects::id id, GetObjectOptions option = GetObjectOptions::READ_ONLY) = 0;
    virtual T newObject() = 0;
    virtual void deleteObject(T& object) = 0;
    virtual void save(T& object) = 0;

    void deleteBatch(std::vector<T> batch) {
        for (T& obj : batch) {
            this->deleteObject(obj);
        }
    }

    std::vector<T> getBatch(std::vector<DatabaseObjects::id> ids) {
        std::vector<T> result;
        result.reserve(ids.size());
        for (auto id : ids) {
            result.push_back(std::move(this->getObject(id)));
        }

        return result;
    }
};