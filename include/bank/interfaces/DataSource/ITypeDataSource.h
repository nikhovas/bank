#pragma once


#include "bank/DataObjects.hpp"
#include "ReadOnlyTypeDataSource.h"


using DatabaseObjects::DatabaseObject;


namespace interfaces::DataSource {
    class ITypeDataSource : public ReadOnlyTypeDataSource {
    public:
        virtual DatabaseObject * getWriteObject(DatabaseObjects::id id) = 0;

        virtual DatabaseObject *newObject() = 0;

        virtual void deleteObject(DatabaseObject *object) = 0;

        virtual void save(DatabaseObject *object) = 0;

        void deleteBatch(std::vector<DatabaseObject *> batch) {
            for (DatabaseObject *obj: batch) {
                this->deleteObject(obj);
            }
        }
    };
}