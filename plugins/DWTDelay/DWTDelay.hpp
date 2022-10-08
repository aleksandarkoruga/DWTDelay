// PluginDWTDelay.hpp
// Aleksandar Koruga (aleksandar.koruga@gmail.com)

#pragma once

#include "SC_PlugIn.hpp"
#include <memory>
#include <vector>
#include <wavelib.h>
#define N_WL 0x200
namespace DWTDelay {

class DWTDelay : public SCUnit {
public:
    DWTDelay();

    // Destructor
     ~DWTDelay();

private:
    int m_nLevels;
    // unsigned int m_NBlocks;
    // unsigned int m_cntBlock;
    // void ProceedWavelet(const int& nSamps);
    void ProceedWavelet(const int& inPos, const int& oIdx);
    wave_object m_obj;
    wt_object m_wt;

    // Calc function
    void next(int nSamples);
    std::vector<double> m_arrWtIn = std::vector<double>(N_WL);
    std::vector<std::vector<double>> m_arrWtOut = std::vector<std::vector<double>>(2, std::vector<double>(N_WL, 0));
    // Member variables

    std::vector<double> m_buf;
    std::vector<double> m_levels;
    //std::vector<int> m_levelIdx;
    struct BufIndex {
        int wIdx;
        int outIdx;
    } m_idx;
};

} // namespace DWTDelay
