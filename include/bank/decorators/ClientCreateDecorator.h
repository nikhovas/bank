#pragma once


#include "bank/interfaces/decorators/ITypeDataSourceDecorator.h"
#include "bank/DataObjects.hpp"
#include "bank/interfaces/DataSource/helpers/IGetClientsByTransactionsHelper.h"


namespace decorators {
    namespace deci = interfaces::decorators;
    namespace dsi = interfaces::DataSource;

    class ClientCreateDecorator : public deci::ITypeDataSourceDecorator {
    public:
        ClientCreateDecorator(ITypeDataSource *i_type_data_source) :
        ITypeDataSourceDecorator(i_type_data_source) {}

        virtual void save(DatabaseObject *object) override {
            DatabaseObjects::Client* client = dynamic_cast<DatabaseObjects::Client*>(object);
            if (client->surname == "" || client->name == "") {
                throw BadNameOrSurnameForClient();
            }

            return this->i_type_data_source->save(object);
        }
    };
};