// PluginDWTDelay.cpp
// Aleksandar Koruga (aleksandar.koruga@gmail.com)

#include "SC_PlugIn.hpp"
#include "DWTDelay.hpp"

static InterfaceTable* ft;

namespace DWTDelay {

DWTDelay::DWTDelay() {
    mCalcFunc = make_calc_function<DWTDelay, &DWTDelay::next>();
    next(1);
}

void DWTDelay::next(int nSamples) {
    const float* input = in(0);
    const float* gain = in(1);
    float* outbuf = out(0);

    // simple gain function
    for (int i = 0; i < nSamples; ++i) {
        outbuf[i] = input[i] * gain[i];
    }
}

} // namespace DWTDelay

PluginLoad(DWTDelayUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<DWTDelay::DWTDelay>(ft, "DWTDelay", false);
}
