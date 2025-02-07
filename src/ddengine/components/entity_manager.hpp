#pragma once

#include <ddenginepch.hpp>

#include <ddengine/components/transform.hpp>
#include <ddengine/components/text.hpp>
#include <ddengine/components/sprite.hpp>

class IComponentStorage
{
  public:
  virtual ~IComponentStorage() = default;
  virtual void erase(unsigned int handle) = 0;
};

template<typename T>
class ComponentStorage : public IComponentStorage
{
  public:
  std::unordered_map<unsigned int, T> components;

  void erase(unsigned int handle) override
  {
    components.erase(handle);
  }
};


class EntityManager
{
  public:
  std::vector<unsigned int> entities;

  EntityManager(){};

  unsigned int create()
  {
    // Reuse destroyed entities
    if(!this->unusedEntities.empty())
    {
      auto unusedHandle = this->unusedEntities[0];
      this->unusedEntities.erase(this->unusedEntities.begin());

      return unusedHandle;
    }

    // Create a new entity
    unsigned int handle = this->entities.size();
    this->entities.push_back(handle);

    return handle;
  }

  void destroy(unsigned int handle)
  {
    if(!exists(handle))
    {
      return;
    }

    this->removeComponents(handle);
    this->unusedEntities.push_back(handle);
  }

  template<typename T>
  ComponentStorage<T>& getStorage()
  {
    std::type_index typeId = std::type_index(typeid(T));

    // Component storage doesnt exist
    if(storages.find(typeId) == storages.end())
    {
      storages[typeId] = std::make_shared<ComponentStorage<T>>();
    }

    return *static_cast<ComponentStorage<T>*>(storages[typeId].get());
  }

  template<typename T>
  T* getComponent(unsigned int handle)
  {
    auto &storage = getStorage<T>();
    auto it = storage.components.find(handle);

    return (it != storage.components.end()) ? &it->second : nullptr;
  }

  template<typename T, typename... Args>
  T* addComponent(unsigned int handle, Args&&... args)
  {
    auto &storage = getStorage<T>();
    auto [it, inserted] = storage.components.emplace(handle, T(std::forward<Args>(args)...));

    return &it->second;
  }

  template<typename T>
  bool hasComponent(unsigned int handle)
  {
    auto &storage = getStorage<T>();
    return storage.find(handle) != storage.end();
  }

  void removeComponents(unsigned int handle)
  {
    for(auto &[type, storage] : storages)
    {
      storage->erase(handle);
    }
  }

  bool exists(unsigned int handle)
  {
    return handle <= this->entities.size() -1;
  }
  
  private:
  std::vector<unsigned int> unusedEntities;
  std::unordered_map<std::type_index, std::shared_ptr<IComponentStorage>> storages;
};