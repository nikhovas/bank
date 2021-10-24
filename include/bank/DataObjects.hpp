#pragma once
#include "bank/DataSources/interfaces/IDataObjectMetaInfo.h"


namespace DatabaseObjects {
    using id = std::size_t;

    struct DatabaseObject {
        id object_id;
        IDataObjectMetaInfo* meta_info;
    };

    struct Client: DatabaseObject {
        std::string name;
        std::string surname;
        std::string address;
        std::string passport;
    };

    struct BankAccount: DatabaseObject {
        id client_id;
        std::time_t opened_time;
        ssize_t money;
    };

    struct DebitAccount: BankAccount {
        ssize_t percentage;
        id accumulated;
    };

    struct DepositAccount: BankAccount {
        ssize_t percentage;
    };

    struct CreditAccount: BankAccount {
        ssize_t percentage;
    };

    struct Transaction: DatabaseObject {
        std::time_t time;
        ssize_t money;
    };

    struct PutTransaction: Transaction {
        id bank_account_id;
    };

    struct SendTransaction: Transaction {
        id from_bank_account_id;
        id to_bank_account_id;
    };

    struct GetTransaction: Transaction {
        id bank_account_id;
    };

    struct DebitPercentsTransaction: Transaction {
        std::time_t begin_period;
        std::time_t end_period;
    };

    struct DepositEndTransaction: Transaction {
    };

    struct CreditPercentsTransaction: Transaction {
    };

    struct CancelTransaction: Transaction {
        id transaction_id;
        std::string reason;
    };
}