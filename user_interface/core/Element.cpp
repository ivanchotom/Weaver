#include "core/Element.h"
#include "database/Database.h"
#include <algorithm>
#include <stdexcept>

namespace UI
{

    Element::Element(std::shared_ptr<Element> parent, const std::string &name)
        : name(name), parent(parent)
    {
        if (parent)
        {
            parent->addChild(shared_from_this());
        }
    }

    Database *Element::getDatabase() const
    {
        return database;
    }

    void Element::addChild(std::shared_ptr<Element> child)
    {
        if (!child)
            return;

        if (!hasChild(child))
        {
            children.push_back(child);
            child->setParent(shared_from_this());
        }
    }

    void Element::removeChild(std::shared_ptr<Element> child)
    {
        if (!child)
            return;

        auto it = std::find(children.begin(), children.end(), child);
        if (it != children.end())
        {
            (*it)->setParent(nullptr);
            children.erase(it);
        }
    }

    bool Element::hasChild(std::shared_ptr<Element> child) const
    {
        return std::find(children.begin(), children.end(), child) != children.end();
    }

    void Element::clearChildren()
    {
        for (auto &child : children)
        {
            child->setParent(nullptr);
        }
        children.clear();
    }

    void Element::registerWithDatabase(Database *db)
    {
        if (!db)
            throw std::invalid_argument("Database cannot be null");

        if (database != db)
        {
            if (database)
                unregisterFromDatabase();

            database = db;
            database->registerElement(shared_from_this());
        }
    }

    void Element::unregisterFromDatabase()
    {
        if (database)
        {
            database->unregisterElement(getId());
            database = nullptr;
        }
    }

    void Element::setActive(bool active)
    {
        isActive = active;
    }

    bool Element::getActive() const
    {
        return isActive;
    }

    void Element::updatePath()
    {
        // Implementation for path updating if needed
    }

    void Element::setId(int newId)
    {
        id = newId;
    }

    void Element::setParent(std::shared_ptr<Element> newParent)
    {
        parent = newParent;
    }

    void Element::removeExpiredChildren()
    {
        auto newEnd = std::remove_if(children.begin(), children.end(),
                                     [](const std::shared_ptr<Element> &child)
                                     { return !child; });
        children.erase(newEnd, children.end());
    }

} // namespace UI