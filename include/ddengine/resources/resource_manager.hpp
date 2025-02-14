#pragma once

#include <ddenginepch.hpp>

#include <ddengine/resources/shader.hpp>
#include <ddengine/resources/texture.hpp>
#include <ddengine/resources/font.hpp>

class IResourceStorage
{
  public:
  virtual ~IResourceStorage() = default;
  virtual void erase(const std::string &handle) = 0;
};

template<typename T>
class ResourceStorage : public IResourceStorage
{
  public:
  std::unordered_map<std::string, T> resources;

  void erase(const std::string &handle) override
  {
    resources.erase(handle);
  }
};

class ResourceManager
{
  public:
  ResourceManager(){};

  template<typename T>
  ResourceStorage<T>& getStorage()
  {
    std::type_index typeId = std::type_index(typeid(T));

    // Component storage doesnt exist
    if(storages.find(typeId) == storages.end())
    {
      storages[typeId] = std::make_shared<ResourceStorage<T>>();
    }

    return *static_cast<ResourceStorage<T>*>(storages[typeId].get());
  }

  template<typename T, typename... Args>
  T* addResource(const std::string &name, Args&&... args)
  {
    auto &storage = getStorage<T>();
    auto [it, inserted] = storage.resources.emplace(name, T(std::forward<Args>(args)...));
    return &it->second;
  }

  template<typename T>
  T* getResource(const std::string &name)
  {
    auto &storage = getStorage<T>();
    auto it = storage.resources.find(name);

    return (it != storage.resources.end()) ? &it->second : nullptr;
  }

  template<typename T>
  bool hasResource(const std::string &name)
  {
    auto &storage = getStorage<T>();
    return storage.resources.find(name) != storage.resources.end();
  }

  protected:
  std::unordered_map<std::type_index, std::shared_ptr<IResourceStorage>> storages;
};