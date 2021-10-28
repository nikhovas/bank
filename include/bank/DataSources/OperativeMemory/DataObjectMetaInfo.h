#pragma once
#include "bank/interfaces/DataSource/IDataObjectMetaInfo.h"


namespace OperativeMemory {
    namespace dsi = interfaces::DataSource;


    enum DatabaseStatus {
        NOT_CREATED, EXISTS, DELETED, NOT_EXISTING_OBJECT
    };


    class DataObjectMetaInfo : public dsi::IDataObjectMetaInfo {
    public:
        DatabaseStatus operative_memory_database_status;

        virtual bool isNotExistingObject() override {
            return this->operative_memory_database_status == DatabaseStatus::NOT_EXISTING_OBJECT;
        }

        virtual void makeNotExisting() override {
            this->operative_memory_database_status = DatabaseStatus::NOT_EXISTING_OBJECT;
        }
    };
};