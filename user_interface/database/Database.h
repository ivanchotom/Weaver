#pragma once

#include "core/Element.h"
#include <memory>
#include <unordered_map>
#include <string>
#include <vector>
#include <functional>

namespace UI
{
    class Database
    {
    public:
        Database() = default;
        ~Database() = default;

        // Element registration
        void registerElement(std::shared_ptr<Element> element);
        void unregisterElement(int id);

        // Element retrieval
        std::shared_ptr<Element> getElementById(int id) const;
        std::shared_ptr<Element> getElementByName(const std::string &name) const;
        std::vector<std::shared_ptr<Element>> findElements(std::function<bool(const Element &)> predicate) const;

        // Database queries
        size_t getElementCount() const { return elementsById.size(); }
        bool hasElement(int id) const;
        bool hasElement(const std::string &name) const;

        // Database management
        void clear();
        std::vector<std::shared_ptr<Element>> getAllElements() const;
        void removeOrphanedElements();

    private:
        // Primary storage - by ID
        std::unordered_map<int, std::shared_ptr<Element>> elementsById;

        // Secondary index - by name
        std::unordered_map<std::string, std::shared_ptr<Element>> elementsByName;

        // Helper methods
        void validateElement(const std::shared_ptr<Element> &element) const;
        void removeElementFromIndices(const std::shared_ptr<Element> &element);
    };
} // namespace UI