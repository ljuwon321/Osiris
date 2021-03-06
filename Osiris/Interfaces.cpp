#include <stdexcept>
#include <Windows.h>

#include "Interfaces.h"

Interfaces::Interfaces() noexcept
{
    try {
        engine = find<Engine>("engine", "VEngineClient014");
        engineTrace = find<EngineTrace>("engine", "EngineTraceClient004");
        entityList = find<EntityList>("client_panorama", "VClientEntityList003");
        client = find<Client>("client_panorama", "VClient018");
        cvar = find<Cvar>("vstdlib", "VEngineCvar007");
        modelInfo = find<ModelInfo>("engine", "VModelInfoClient004");
        modelRender = find<ModelRender>("engine", "VEngineModel016");
        materialSystem = find<MaterialSystem>("materialsystem", "VMaterialSystem080");
        renderView = find<RenderView>("engine", "VEngineRenderView014");
        inputSystem = find<InputSystem>("inputsystem", "InputSystemVersion001");
    }
    catch (const std::runtime_error& e) {
        MessageBox(NULL, e.what(), "Error", MB_OK | MB_ICONERROR);
        exit(EXIT_FAILURE);
    }
}
