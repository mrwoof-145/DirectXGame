#include <Engine/Explorer/Explorer.h>
using namespace Engine::Explorer;

Explorer::Explorer() = default;

Explorer::~Explorer() {
    for (auto* instance : m_Instances) {
        delete instance;   // free memory for each Instance
    }
    m_Instances.clear();  // vector itself is destroyed here
}

const std::vector<Instance*>& Explorer::GetAllInstances() const {
    return m_Instances;
}

void Explorer::New(Instance* inst) {
    m_Instances.push_back(inst);
}
