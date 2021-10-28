#pragma once


using DatabaseObjects::DatabaseObject;


namespace interfaces::DataSource {
    class ReadOnlyTypeDataSource {
    public:
        virtual DatabaseObject * getObject(DatabaseObjects::id id) = 0;

        std::vector<DatabaseObject *> getBatch(std::vector<DatabaseObjects::id> ids) {
            std::vector<DatabaseObject *> result;
            result.reserve(ids.size());
            for (auto id: ids) {
                result.push_back(std::move(this->getObject(id)));
            }

            return result;
        }
    };
}