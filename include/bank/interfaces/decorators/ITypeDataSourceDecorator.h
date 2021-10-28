#pragma once
#include "bank/interfaces/DataSource/ITypeDataSource.h"


namespace interfaces::decorators {
    namespace dsi = interfaces::DataSource;
    using DatabaseObjects::id;


    class ITypeDataSourceDecorator : public dsi::ITypeDataSource {
    public:
        ITypeDataSourceDecorator(ITypeDataSource *i_type_data_source) : i_type_data_source(i_type_data_source) {}

        virtual DatabaseObject * getObject(DatabaseObjects::id id) override {
            return this->i_type_data_source->getObject(id);
        }

        virtual DatabaseObject *
        getWriteObject(DatabaseObjects::id id) override {
            return this->i_type_data_source->getWriteObject(id);
        }

        virtual DatabaseObject *newObject() override {
            return this->i_type_data_source->newObject();
        }

        virtual void deleteObject(DatabaseObject *object) override {
            return this->i_type_data_source->deleteObject(object);
        }

        virtual void save(DatabaseObject *object) override {
            return this->i_type_data_source->save(object);
        }
    protected:
        ITypeDataSource *i_type_data_source;
    };
}