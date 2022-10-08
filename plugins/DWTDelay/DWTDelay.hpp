// PluginDWTDelay.hpp
// Aleksandar Koruga (aleksandar.koruga@gmail.com)

#pragma once

#include "SC_PlugIn.hpp"

namespace DWTDelay {

class DWTDelay : public SCUnit {
public:
    DWTDelay();

    // Destructor
    // ~DWTDelay();

private:
    // Calc function
    void next(int nSamples);

    // Member variables
};

} // namespace DWTDelay
