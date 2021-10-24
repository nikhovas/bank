#pragma once
#include "bank/DataObjects.hpp"
#include "OperativeMemoryTypeDataSource.h"
#include "bank/DataSources/interfaces/IDataSource.h"


namespace om {
    struct OperativeMemoryDataSource : public IDataSource {
    public:
        ITypeDataSource<DatabaseObjects::Client>* getClientStorage() override {
            return &this->client_storage;
        }

    private:
        OperativeMemoryTypeDataSource<DatabaseObjects::Client> client_storage;
    };
};