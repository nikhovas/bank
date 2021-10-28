#pragma once
#include <unordered_map>
#include <bank/DataObjects.hpp>
#include "bank/interfaces/DataSource/ITypeDataSource.h"
#include "DataObjectMetaInfo.h"
#include "bank/exceptions.h"
#include "UniqueIdGetter.h"


namespace OperativeMemory {
    using DatabaseObjects::id;
    namespace dsi = interfaces::DataSource;


    class TypeDataSource : public dsi::ITypeDataSource {
    public:
        TypeDataSource() {}

        DatabaseObject* getObject(DatabaseObjects::id id) override {
            DatabaseObjects::DatabaseObject* object = this->return_pos(id)->second;
            DataObjectMetaInfo *meta_info = new DataObjectMetaInfo();
            object->meta_info = meta_info;
            return this->return_pos(id)->second;
        }

        DatabaseObject* getWriteObject(DatabaseObjects::id id) override {
            // REWRITE
            DatabaseObjects::DatabaseObject* object = this->return_pos(id)->second;
            DataObjectMetaInfo *meta_info = new DataObjectMetaInfo();
            object->meta_info = meta_info;
            return this->return_pos(id)->second;
        }

        void deleteObject(DatabaseObject* object) override {
            auto pos = this->return_pos(object->object_id);
            this->data_storage_.erase(pos);
            DataObjectMetaInfo *meta_info = this->getObjectMetaInfo(object);
            meta_info->operative_memory_database_status = DatabaseStatus::DELETED;
        }

        void save(DatabaseObject* object) override {
            DataObjectMetaInfo *meta_info = this->getObjectMetaInfo(object);
            meta_info->operative_memory_database_status = DatabaseStatus::EXISTS;
            this->data_storage_[object->object_id] = object;
        }

    protected:
        typename std::unordered_map<id, DatabaseObject*>::iterator return_pos(DatabaseObjects::id id) {
            auto pos = this->data_storage_.find(id);
            if (pos != this->data_storage_.end()) {
                return pos;
            } else {
                throw ObjectDoesNotExists{};
            }
        }

        DataObjectMetaInfo *getObjectMetaInfo(DatabaseObject* object) {
            DataObjectMetaInfo *meta_info = dynamic_cast<DataObjectMetaInfo *>(object->meta_info);
            if (meta_info == nullptr) {
                throw BadDataSourceForObject();
            }
            return meta_info;
        }

        std::unordered_map<id, DatabaseObject*> data_storage_;
    };

    template<typename T>
    class DefaultOperativeMemoryTypeDataSource : public TypeDataSource {
    public:
        DatabaseObject* newObject() override {
            id new_object_id = this->unique_id_getter->getNew();
            T* object = new T();
            object->object_id = new_object_id;
            DataObjectMetaInfo *meta_info = new DataObjectMetaInfo();
            object->meta_info = meta_info;
            meta_info->operative_memory_database_status = DatabaseStatus::NOT_CREATED;
            return object;
        }

        DefaultOperativeMemoryTypeDataSource(UniqueIdGetter* unique_id_getter) : unique_id_getter(unique_id_getter) {}
    protected:
        UniqueIdGetter* unique_id_getter;
    };
};