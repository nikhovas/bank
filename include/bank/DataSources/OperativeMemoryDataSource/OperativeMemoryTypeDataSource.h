#pragma once
#include <unordered_map>
#include <bank/DataObjects.hpp>
#include "bank/DataSources/interfaces/ITypeDataSource.h"
#include "OperativeMemoryDataObjectMetaInfo.h"
#include "bank/exceptions.h"


namespace om {
    using DatabaseObjects::id;


    template<typename T>
    class OperativeMemoryTypeDataSource : public ITypeDataSource<T> {
    public:
        OperativeMemoryTypeDataSource() {}

        T getObject(DatabaseObjects::id id, GetObjectOptions option = GetObjectOptions::READ_ONLY) override {
            T object = this->return_pos(id)->second;
            OperativeMemoryDataObjectMetaInfo *meta_info = new OperativeMemoryDataObjectMetaInfo();
            object.meta_info = meta_info;
            return this->return_pos(id)->second;
        }

        T newObject() override {
            id new_object_id = this->new_unique_id_++;
            T object{0};
            object.object_id = new_object_id;
            OperativeMemoryDataObjectMetaInfo *meta_info = new OperativeMemoryDataObjectMetaInfo();
            object.meta_info = meta_info;
            meta_info->operative_memory_database_status = OperativeMemoryDatabaseStatus::NOT_CREATED;
            return object;
        }

        void deleteObject(T &object) override {
            auto pos = this->return_pos(object.object_id);
            this->data_storage_.erase(pos);
            OperativeMemoryDataObjectMetaInfo *meta_info = this->getObjectMetaInfo(object);
            meta_info->operative_memory_database_status = OperativeMemoryDatabaseStatus::DELETED;
        }

        void save(T &object) override {
            OperativeMemoryDataObjectMetaInfo *meta_info = this->getObjectMetaInfo(object);
            meta_info->operative_memory_database_status = OperativeMemoryDatabaseStatus::EXISTS;
            this->data_storage_[object.object_id] = object;
        }

    private:
        typename std::unordered_map<id, T>::iterator return_pos(DatabaseObjects::id id) {
            auto pos = this->data_storage_.find(id);
            if (pos != this->data_storage_.end()) {
                return pos;
            } else {
                throw ObjectDoesNotExists{};
            }
        }

        OperativeMemoryDataObjectMetaInfo *getObjectMetaInfo(T &object) {
            OperativeMemoryDataObjectMetaInfo *meta_info = dynamic_cast<OperativeMemoryDataObjectMetaInfo *>(object.meta_info);
            if (meta_info == nullptr) {
                throw BadDataSourceForObject();
            }
            return meta_info;
        }

        std::unordered_map<id, T> data_storage_;
        id new_unique_id_{0};
    };
};