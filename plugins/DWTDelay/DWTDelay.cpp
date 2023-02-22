// PluginDWTDelay.cpp
// Aleksandar Koruga (aleksandar.koruga@gmail.com)

#include "SC_PlugIn.hpp"
#include "DWTDelay.hpp"

static InterfaceTable* ft;

namespace DWTDelay {


    DWTDelay::DWTDelay() : m_idx({ 0,0 }), m_buf(NEXTPOWEROFTWO(static_cast<int>(sampleRate())), 0), m_levels(0, 0), m_nLevels(sc_min(numInputs() - 1, 32)) /*m_levelIdx(m_nLevels,0)*/, m_obj(wave_init("db4")), m_wt(wt_init(m_obj, "dwt", N_WL, sc_min(numInputs() - 1, 32))) {


        setDWTExtension(m_wt, "sym");// Options are "per" and "sym". Symmetric is the default option
        setWTConv(m_wt, "direct");


        mCalcFunc = make_calc_function<DWTDelay, &DWTDelay::next>();
        next(1);
    }


    DWTDelay::~DWTDelay()
    {
        wave_free(m_obj);
        wt_free(m_wt);
    };

    void DWTDelay::ProceedWavelet(const int& inPos, const int& oIdx)
    {

        //for each level compute a wavelet then unite different levels from different wavelets into one

        auto levelIdx = 0;
        for (auto nW = 0; nW < m_wt->lenlength - 1; ++nW)
        {
            auto rdIdx = (static_cast<int>(m_idx.wIdx + m_buf.size() * 2 - static_cast<int>(sc_wrap(in(1 + (nW % m_nLevels))[inPos], 0.0f, 1.0f) * static_cast<float>(m_buf.size())))) & (m_buf.size() - 1);

            if (rdIdx + N_WL > m_buf.size())
            {
                //split memcpy in 2
                auto amtR = (rdIdx + N_WL) & (m_buf.size() - 1);
                auto amtL = N_WL - amtR;

                memcpy(&m_arrWtIn[0], &m_buf[rdIdx], amtL * sizeof(double));
                if (amtR > 0)
                    memcpy(&m_arrWtIn[amtL], &m_buf[0], amtR * sizeof(double));


            }
            else
            {
                //copy directly
                memcpy(&m_arrWtIn[0], &m_buf[rdIdx], N_WL * sizeof(double));
            }
            dwt(m_wt, &(m_arrWtIn[0]));

            if (m_levels.size() != m_wt->outlength) {
                m_levels.resize(m_wt->outlength);
            }

            memcpy(&m_levels[levelIdx], &m_wt->output[levelIdx], m_wt->length[nW] * sizeof(double));

            levelIdx += m_wt->length[nW];
        }
        memcpy(&m_levels[0], &m_wt->output[0], m_levels.size() * sizeof(double));
        idwt(m_wt, &(m_arrWtOut[oIdx][0]));
        for (auto i = 0; i < N_WL; ++i)
        {
            m_arrWtOut[oIdx][i] *= sc_hanwindow(static_cast<float>(i) / static_cast<float>(N_WL));
        }





        /*
        auto offset = 0;
        for (auto level = 0; level < m_nLevels; ++level)
        {

            auto delta = static_cast<double>(N_WL) / static_cast<double>(m_wt->length[level]);

            for (auto j = 0; j < m_wt->length[level]; ++j)
            {
                m_wt->output[offset+j] ;
            }

            offset += m_wt->length[level];
        }
        */

    }

    /*void DWTDelay::ProceedWavelet()
    {


            dwt(m_wt, &(m_arrWtIn[0]) );


            auto offset = 0;
            for (auto level = 0; level < m_j; ++level)
            {

                auto delta = static_cast<double>(N_WL) / static_cast<double>(m_wt->length[level]);

                for (auto j = 0; j < m_wt->length[level]; ++j)
                {
                    double cIn = delta * j;
                    double  iIn = 0;
                    double fracIn = std::modf(cIn, &iIn);

                    auto interp = 1.0 - fracIn;

                    auto rescaled = static_cast<double>((in(level+1))[((int)iIn) & (nSamps - 1)]) * interp +
                        fracIn * static_cast<double>((in(level+1))[(N_WL * i + (int)iIn + 1) & (nSamps - 1)]);
                    m_wt->output[offset+j] *= rescaled;

                }

                offset += m_wt->length[level];
            }
            idwt(m_wt, &(m_arrWtOut[0]));


    }
    */
    void DWTDelay::next(int nSamples) {

        for (auto i = 0; i < nSamples; ++i)
        {
            m_buf[m_idx.wIdx] = static_cast<double>(in(0)[i]);
            ++m_idx.wIdx;
            m_idx.wIdx &= (m_buf.size() - 1);

            auto ovIdx = (m_idx.outIdx + (N_WL / 2)) & (N_WL - 1);
            (out(0))[i] = 0.5f * static_cast<float>(m_arrWtOut[0][m_idx.outIdx] + m_arrWtOut[1][ovIdx]);
            ++m_idx.outIdx;
            m_idx.outIdx &= (N_WL - 1);
            if (m_idx.outIdx == 0)
            {
                ProceedWavelet(i, 0);
            }
            if (m_idx.outIdx == N_WL / 2)
            {
                ProceedWavelet(i, 1);
            }
        }


        /*m_NBlocks = N_WL / nSamples;

        const float* input = in(0);
        const float* gain = in(1);
        float* outbuf = out(0);
        if((nSamples&0x3F)==0x0)
        {
            if (nSamples >= N_WL)
            {
                ProceedWavelet(nSamples);
            }
            else
            {
                for (auto i = 0; i < nSamples; ++i)
                {
                    m_arrWtIn[i+m_cntBlock*nSamples] = in(0)[i];
                    out(0)[i] = m_arrWtOut[i + m_cntBlock * nSamples];
                }
                ++m_cntBlock;
                m_cntBlock &= (m_NBlocks-1);
                if (m_cntBlock == 0)
                {
                    ProceedWavelet();
                }


            }
            // simple gain function
            //for (int i = 0; i < nSamples; ++i) {
             //   outbuf[i] = input[i] ;
            //}

        }
        else
        {
            for (int i = 0; i < nSamples; ++i) {
                outbuf[i] = input[i] * gain[i];
            }

        }*/
    }

} // namespace DWTDelay

PluginLoad(DWTDelayUGens) {
    // Plugin magic
    ft = inTable;
    registerUnit<DWTDelay::DWTDelay>(ft, "DWTDelay", false);
}
