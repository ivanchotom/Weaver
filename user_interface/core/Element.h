#pragma once

#include <string>
#include <vector>
#include <memory>

namespace UI
{

    class Database;

    class Element : public std::enable_shared_from_this<Element>
    {
    private:
        int id;
        std::string name;
        std::weak_ptr<Element> parent;
        std::vector<std::shared_ptr<Element>> children;
        Database *database;

    public:
        Element(std::shared_ptr<Element> parent, const std::string &name);
        virtual ~Element() = default;

        // Getters
        virtual std::shared_ptr<Element> getElement() { return shared_from_this(); }
        virtual int getId() const { return id; }
        virtual bool isVisible() const { return visible; }
        virtual void setVisible(bool visible) { this->visible = visible; }
        virtual bool isEnabled() const { return enabled; }
        virtual void setEnabled(bool enabled) { this->enabled = enabled; }
        virtual const std::string &getName() const { return name; }
        virtual std::shared_ptr<Element> getParent() const { return parent.lock(); }
        virtual const std::vector<std::shared_ptr<Element>> &getChildren() const { return children; }
        Database *getDatabase() const;

        // Element hierarchy
        void addChild(std::shared_ptr<Element> child);
        void removeChild(std::shared_ptr<Element> child);
        bool hasChild(std::shared_ptr<Element> child) const;
        void clearChildren();

        // Database registration
        void registerWithDatabase(Database *db);
        void unregisterFromDatabase();

        // Virtual interface
        virtual void render() = 0;

        virtual void setActive(bool active);
        virtual bool getActive() const;

        void updatePath();

    protected:
        bool isActive = true;
        bool visible = true;
        bool enabled = true;

        void setId(int newId);
        void setParent(std::shared_ptr<Element> newParent);

    private:
        void removeExpiredChildren();
    };

}