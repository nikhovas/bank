#pragma once
#include "bank/interfaces/DataSource/IDataObjectMetaInfo.h"
#include "bank/DataSources//VirtualObjectMetaInfo.h"
#include <string>
#include <vector>


#define AllowCreating virtual void makeVirtual() override {}



namespace DatabaseObjects {
    using id = std::size_t;

    struct DatabaseObject {
        id object_id;
        interfaces::DataSource::IDataObjectMetaInfo* meta_info;

        virtual void makeVirtual() = 0;
    };

    struct Client: DatabaseObject {
        std::string name;
        std::string surname;
        std::string address;
        std::string passport;

        AllowCreating;
    };

    struct BankAccount: DatabaseObject {
        id client_id;
        std::time_t opened_time;
        ssize_t money;

        virtual BankAccount* lookFuture(std::time_t futureMoment, std::time_t periodInterval) = 0;
    };

    struct DebitAccount: BankAccount {
        ssize_t percentage;
        id accumulated;

        virtual BankAccount* lookFuture(std::time_t future_moment, std::time_t period_interval) override {
            DebitAccount* object = new DebitAccount();
            object->meta_info = new VirtualDataObjectMetaInfo();
            // TODO
            return object;
        }

        AllowCreating;
    };

    struct DepositAccount: BankAccount {
        ssize_t percentage;

        virtual BankAccount* lookFuture(std::time_t future_moment, std::time_t period_interval) override {
            DepositAccount* object = new DepositAccount();
            object->meta_info = new VirtualDataObjectMetaInfo();
            // TODO
            return object;
        }

        AllowCreating;
    };

    struct CreditAccount: BankAccount {
        ssize_t percentage;

        virtual BankAccount* lookFuture(std::time_t future_moment, std::time_t period_interval) override {
            CreditAccount* object = new CreditAccount();
            object->meta_info = new VirtualDataObjectMetaInfo();
            // TODO
            return object;
        }

        AllowCreating;
    };

    struct Transaction: DatabaseObject {
        std::time_t time;
        ssize_t money;

        virtual std::vector<id> getAssociatedAccounts() = 0;
    };

    struct PutTransaction: Transaction {
        id bank_account_id;

        virtual std::vector<id> getAssociatedAccounts() override {
            return {bank_account_id};
        }

        AllowCreating;
    };

    struct SendTransaction: Transaction {
        id from_bank_account_id;
        id to_bank_account_id;

        virtual std::vector<id> getAssociatedAccounts() override {
            return {from_bank_account_id, to_bank_account_id};
        }

        AllowCreating;
    };

    struct GetTransaction: Transaction {
        id bank_account_id;

        virtual std::vector<id> getAssociatedAccounts() override {
            return {bank_account_id};
        }

        AllowCreating;
    };

    struct DebitPercentsTransaction: Transaction {
        std::time_t begin_period;
        std::time_t end_period;
        id bank_account_id;

        virtual std::vector<id> getAssociatedAccounts() override {
            return {bank_account_id};
        }

        AllowCreating;
    };

    struct DepositEndTransaction: Transaction {
        id bank_account_id;

        virtual std::vector<id> getAssociatedAccounts() override {
            return {bank_account_id};
        }

        AllowCreating;
    };

    struct CreditPercentsTransaction: Transaction {
        id bank_account_id;

        virtual std::vector<id> getAssociatedAccounts() override {
            return {bank_account_id};
        }

        AllowCreating;
    };

    struct CancelTransaction: Transaction {
        id transaction_id;
        id bank_account_id;
        std::string reason;

        virtual std::vector<id> getAssociatedAccounts() override {
            return {bank_account_id};
        }

        AllowCreating;
    };
}