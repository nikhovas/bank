#pragma once
#include "bank/interfaces/DataSource/IDataObjectMetaInfo.h"
#include "bank/DataSources//VirtualObjectMetaInfo.h"
#include "constants.h"
#include <boost/date_time/gregorian/gregorian.hpp>
#include <string>
#include <vector>
#include <ctime>


#define AllowCreating virtual void makeVirtual() override {}



namespace DatabaseObjects {
    using namespace boost::gregorian;
    using namespace constants;
    
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
        date opened_date;
        double money;

        virtual BankAccount* lookFuture(date futureMoment, date_duration periodInterval) = 0;

//    private:
        struct PaymentsResult {
            date closest_payment;
            date latest_payment;
            size_t num_payments;
        };

        PaymentsResult getPaymentsBound(date today, date future_moment, date_duration period_interval) {
            size_t num_payments = 0;

            auto it = day_iterator(opened_date, period_interval.days());
            while (today > *it) {
                ++it;
            }
            date closest_payment = *it;
            while (future_moment >= *it) {
                ++it;
                num_payments += 1;
            }
            date last_payment = *(--it);
            return {closest_payment, last_payment, num_payments};

        }
    };

    struct DebitAccount: BankAccount {
        double interest_rate;
        double accumulated;

        virtual BankAccount* lookFuture(date future_moment, date_duration period_interval) override {
            DebitAccount* object = new DebitAccount();
            object->meta_info = new VirtualDataObjectMetaInfo();
            object->opened_date = opened_date;
            object->client_id = client_id;
            object->interest_rate = interest_rate;

            date today = day_clock::local_day();
            auto res = getPaymentsBound(today, future_moment, period_interval);

            double future_money = accumulated + money * (1 + interest_rate / daysPerYear * (res.closest_payment - today).days());
            future_money *= pow(1 + interest_rate / daysPerYear * period_interval.days(), res.num_payments - 1);
            object->money = future_money;

            return object;
        }

        AllowCreating;
    };

    struct DepositAccount: BankAccount {
        double interest_rate;
        double accumulated;
        date end_date;

        virtual BankAccount* lookFuture(date future_moment, date_duration period_interval) override {
            DepositAccount* object = new DepositAccount();
            object->meta_info = new VirtualDataObjectMetaInfo();
            object->opened_date = opened_date;
            object->client_id = client_id;
            object->interest_rate = interest_rate;

            date today = day_clock::local_day();
            future_moment = std::min(future_moment, end_date);
            auto res = getPaymentsBound(today, future_moment, period_interval);

            double future_money = accumulated + money * (1 + interest_rate / daysPerYear * (res.closest_payment - today).days());
            future_money *= pow(1 + interest_rate / daysPerYear * period_interval.days(), res.num_payments - 1);
            object->money = future_money;

            return object;
        }

        AllowCreating;
    };

    struct CreditAccount: BankAccount {
        double credit_limit;
        double commission;

        virtual BankAccount* lookFuture(date future_moment, date_duration period_interval) override {
            CreditAccount* object = new CreditAccount();
            object->meta_info = new VirtualDataObjectMetaInfo();
            object->opened_date = opened_date;
            object->client_id = client_id;
            object->commission = commission;
            object->credit_limit = credit_limit;
            object->money = money;
            return object;
        }

        AllowCreating;
    };

    struct Transaction: DatabaseObject {
        time_t time;
        double money;

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
        date begin_period;
        date end_period;
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