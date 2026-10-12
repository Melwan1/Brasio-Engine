#pragma once

#include <sstream>

#include <core/manager.hh>
#include <io/logging/logger.hh>

namespace brasio::core
{
    template <typename IdType, typename ObjectType>
    void Manager<IdType, ObjectType>::loadFile(const fs::path &yamlFile)
    {
        const YAML::Node &node = YAML::LoadFile(yamlFile.string());
        for (const YAML::Node &objectNode : node)
        {
            const IdType &id = objectNode["id"].as<IdType>();
            if (_objectIdMap.contains(id))
            {
                std::ostringstream oss;
                oss << id;
                BRASIO_LOG_ERROR("Manager already contains id " + oss.str() + " for YAML file "
                                     + yamlFile.string(),
                                 { "MANAGER" });
                continue;
            }
            registerObject(id, createObject(objectNode));
        }
    }

    template <typename IdType, typename ObjectType>
    void Manager<IdType, ObjectType>::registerObject(const IdType &id,
                                                     std::unique_ptr<ObjectType> object)
    {
        _objects.emplace_back(std::move(object));
        _objectIdMap.insert({ id, _objects.back().get() });
    }

    template <typename IdType, typename ObjectType>
    ObjectType *Manager<IdType, ObjectType>::get(const IdType &id) const
    {
        const auto iterator = _objectIdMap.find(id);
        if (iterator == _objectIdMap.end())
        {
            std::ostringstream oss;
            oss << id;
            BRASIO_LOG_CRITICAL("Manager does not contain id " + oss.str(), { "MANAGER" });
            return nullptr;
        }
        return iterator->second;
    }
} // namespace brasio::core
