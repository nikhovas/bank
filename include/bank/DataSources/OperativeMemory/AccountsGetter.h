#pragma once


namespace OperativeMemory {
    namespace dsi = interfaces::DataSource;


    class AccountsGetter : public dsi::ITypeDataSource {
    public:
        std::vector<DatabaseObject *> getAccountsById(std::vector<DatabaseObjects::id> ids) {
            std::vector<DatabaseObject *> result;
            result.reserve(ids.size());
            for (auto id: ids) {
                result.push_back(std::move(this->getObject(id)));
            }

            return result;
        }
    };
}