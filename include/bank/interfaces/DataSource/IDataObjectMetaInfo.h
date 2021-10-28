#pragma once


namespace interfaces::DataSource {
    class IDataObjectMetaInfo {
    public:
        virtual bool isNotExistingObject() = 0;

        virtual void makeNotExisting() = 0;
    };
}