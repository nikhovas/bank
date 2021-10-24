#pragma once
#include "bank/DataSources/interfaces/IDataObjectMetaInfo.h"


namespace om {
    enum OperativeMemoryDatabaseStatus {
        NOT_CREATED, EXISTS, DELETED
    };


    class OperativeMemoryDataObjectMetaInfo : public IDataObjectMetaInfo {
    public:
        OperativeMemoryDatabaseStatus operative_memory_database_status;

        virtual void makeVirtual() override {}
    };
};