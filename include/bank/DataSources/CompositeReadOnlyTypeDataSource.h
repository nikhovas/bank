#pragma once
#include <bank/interfaces/DataSource/ReadOnlyTypeDataSource.h>
#include <vector>


namespace dsi = interfaces::DataSource;


class CompositeReadOnlyTypeDataSource : public dsi::ReadOnlyTypeDataSource {
public:
    CompositeReadOnlyTypeDataSource(const std::vector<dsi::ITypeDataSource*>& elements) : elements(elements) {}

    DatabaseObject* getObject(DatabaseObjects::id id) override {
        for (dsi::ITypeDataSource* data_source : this->elements) {
            try {
                return data_source->getObject(id);
            } catch (ObjectDoesNotExists& exc) {}
        }

        throw ObjectDoesNotExists();
    }

protected:
    std::vector<dsi::ITypeDataSource*> elements;
};