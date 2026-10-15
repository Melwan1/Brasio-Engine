#pragma once

#include <filesystem>
#include <map>
#include <memory>
#include <vector>

#include <yaml-cpp/yaml.h>

namespace fs = std::filesystem;

namespace brasio::core
{
    template <typename IdType, typename ObjectType>
    class Manager
    {
    public:
        void loadFile(const fs::path &yamlFile);
        virtual std::unique_ptr<ObjectType> createObject(const YAML::Node &config) = 0;
        void registerObject(const IdType &id, std::unique_ptr<ObjectType> object);
        ObjectType *get(const IdType &id) const;

    protected:
        std::vector<std::unique_ptr<ObjectType>> _objects;
        std::map<IdType, ObjectType *> _objectIdMap;
    };

} // namespace brasio::core

#include <core/manager.hxx>
