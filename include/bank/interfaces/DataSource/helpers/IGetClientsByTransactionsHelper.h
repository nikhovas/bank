#pragma once


#include "bank/DataObjects.hpp"


namespace interfaces::DataSource {
    class IGetClientsByTransactionsHelper {
    public:
        std::vector<DatabaseObjects::Client *> getObjects(const std::vector<DatabaseObjects::Transaction *> &transactions) {
            std::vector<DatabaseObjects::Client *> result;

            for (DatabaseObjects::Transaction *obj: transactions) {
                std::vector<DatabaseObjects::Client *> obj_res = this->getObjects(obj);
                result.insert(result.end(), obj_res.begin(), obj_res.end());
            }

            return result;
        }

        virtual std::vector<DatabaseObjects::Client *> getObjects(DatabaseObjects::Transaction *transaction) = 0;

        std::vector<DatabaseObjects::id> getIds(const std::vector<DatabaseObjects::Transaction *> &transactions) {
            std::vector<DatabaseObjects::id> result;

            for (DatabaseObjects::Transaction *obj: transactions) {
                std::vector<DatabaseObjects::id> obj_res = this->getIds(obj);
                result.insert(result.end(), obj_res.begin(), obj_res.end());
            }

            return result;
        }

        virtual std::vector<DatabaseObjects::id> getIds(DatabaseObjects::Transaction *transaction) = 0;
    };
}