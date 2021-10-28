#pragma once
#include "bank/DataObjects.hpp"


namespace interfaces::DataSource {
    class IBankAccountGetter {
    public:
        virtual std::vector<DatabaseObjects::BankAccount *> getAccountsByClientId(DatabaseObjects::id id) = 0;

        virtual std::vector<DatabaseObjects::BankAccount *> getAccountsByClient(DatabaseObjects::Client *client) {
            this->getAccountsByClientId();
        }
    }


    class ITransactionGetter {
    public:
        virtual std::vector<DatabaseObjects::Transaction *> getTransactionsByClientId(DatabaseObjects::id id) = 0;

        virtual std::vector<DatabaseObjects::Transaction *> getTransactionsByClient(DatabaseObjects::Client *client) {
            this->getTransactionsByClientId();
        }

        virtual std::vector<DatabaseObjects::Transaction *> getTransactionsByAccountId(DatabaseObjects::id id) = 0;

        virtual std::vector<DatabaseObjects::Transaction *>
        getTransactionsByAccount(DatabaseObjects::BankAccount *client) {
            this->getTransactionsByClientId();
        }
    }
}