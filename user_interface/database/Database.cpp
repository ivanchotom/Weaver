#include "database/Database.h"
#include <stdexcept>
#include <algorithm>

namespace UI
{
    void Database::registerElement(std::shared_ptr<Element> element)
    {
        if (!element)
        {
            throw std::invalid_argument("Cannot register null element");
        }

        validateElement(element);

        // Check for duplicate ID
        if (hasElement(element->getId()))
        {
            throw std::runtime_error("Element with ID " + std::to_string(element->getId()) + " already exists");
        }

        // Check for duplicate name
        if (hasElement(element->getName()))
        {
            throw std::runtime_error("Element with name '" + element->getName() + "' already exists");
        }

        // Add to both indices
        elementsById[element->getId()] = element;
        elementsByName[element->getName()] = element;
    }

    void Database::unregisterElement(int id)
    {
        auto it = elementsById.find(id);
        if (it != elementsById.end())
        {
            removeElementFromIndices(it->second);
        }
    }

    std::shared_ptr<Element> Database::getElementById(int id) const
    {
        auto it = elementsById.find(id);
        return (it != elementsById.end()) ? it->second : nullptr;
    }

    std::shared_ptr<Element> Database::getElementByName(const std::string &name) const
    {
        auto it = elementsByName.find(name);
        return (it != elementsByName.end()) ? it->second : nullptr;
    }

    std::vector<std::shared_ptr<Element>> Database::findElements(std::function<bool(const Element &)> predicate) const
    {
        std::vector<std::shared_ptr<Element>> results;
        for (const auto &pair : elementsById)
        {
            if (predicate(*pair.second))
            {
                results.push_back(pair.second);
            }
        }
        return results;
    }

    bool Database::hasElement(int id) const
    {
        return elementsById.find(id) != elementsById.end();
    }

    bool Database::hasElement(const std::string &name) const
    {
        return elementsByName.find(name) != elementsByName.end();
    }

    void Database::clear()
    {
        elementsById.clear();
        elementsByName.clear();
    }

    std::vector<std::shared_ptr<Element>> Database::getAllElements() const
    {
        std::vector<std::shared_ptr<Element>> elements;
        elements.reserve(elementsById.size());
        for (const auto &pair : elementsById)
        {
            elements.push_back(pair.second);
        }
        return elements;
    }

    void Database::removeOrphanedElements()
    {
        std::vector<int> toRemove;
        for (const auto &pair : elementsById)
        {
            if (pair.second.use_count() == 1) // Only referenced by the database
            {
                toRemove.push_back(pair.first);
            }
        }

        for (int id : toRemove)
        {
            unregisterElement(id);
        }
    }

    void Database::validateElement(const std::shared_ptr<Element> &element) const
    {
        if (element->getId() < 0)
        {
            throw std::invalid_argument("Element ID must be non-negative");
        }

        if (element->getName().empty())
        {
            throw std::invalid_argument("Element name cannot be empty");
        }
    }

    void Database::removeElementFromIndices(const std::shared_ptr<Element> &element)
    {
        elementsById.erase(element->getId());
        elementsByName.erase(element->getName());
    }
} // namespace UI