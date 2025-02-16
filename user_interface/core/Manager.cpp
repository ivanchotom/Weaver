#include "core/Manager.h"
#include "internal/imGui/window/ImGuiWindow.h"

namespace UI
{
    Manager::Manager()
        : database(std::make_unique<Database>()),
          factory(std::make_unique<ImGuiFactory>())
    {
    }

    Manager::~Manager()
    {
        // Cleanup is handled automatically by unique_ptr
    }

    void Manager::initialize()
    {
        // Create the root window
        rootWindow = factory->createWindow(database.get(), nullptr, "Root Window");
    }
}
