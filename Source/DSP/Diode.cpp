/*
  ==============================================================================

    Diode.cpp
    Created: 10 Sep 2022 5:27:07pm
    Author:  pwmag

  ==============================================================================
*/

#include "Diode.h"

namespace WDYM {
    Diode::Diode()
    {
        diodeProperties = {};
        samplesPerMs = 0;
        lastSample = 0;
    }

    Diode::~Diode() {

    }

    void Diode::init(double sampleRate, int samplesPerBlock) {
        samplesPerMs = sampleRate / 1000.f;
    }

    void Diode::process(juce::AudioBuffer<float>& buffer, juce::AudioProcessorValueTreeState& apvts) {
        auto ch = buffer.getNumChannels();
        auto sm = buffer.getNumSamples();

        diodeProperties.diode1 = apvts.getRawParameterValue(DIODE_1_ID)->load();
        diodeProperties.diode2 = apvts.getRawParameterValue(DIODE_2_ID)->load();
        diodeProperties.vf = apvts.getRawParameterValue(VF_ID)->load();
        diodeProperties.vb = apvts.getRawParameterValue(VB_ID)->load();
        diodeProperties.trr = apvts.getRawParameterValue(TRR_ID)->load();
        diodeProperties.gain = apvts.getRawParameterValue(GAIN_ID)->load();
        diodeProperties.sat = apvts.getRawParameterValue(SAT_ID)->load() * 10;
        diodeProperties.mix = apvts.getRawParameterValue(MIX_ID)->load();

        if (diodeProperties.diode1 && diodeProperties.diode2) {
            for (int c = 0; c < ch; c++) {
                auto channelWr = buffer.getWritePointer(c);
                auto channelRd = buffer.getReadPointer(c);

                for (int s = 0; s < sm; s++) {
                    channelWr[s] = ((1 - diodeProperties.mix) * channelRd[s]) + (diodeProperties.mix * wsSym(channelRd[s]));
                }
            }
        }
        else if (diodeProperties.diode1) {
            for (int c = 0; c < ch; c++) {
                auto channelWr = buffer.getWritePointer(c);
                auto channelRd = buffer.getReadPointer(c);

                for (int s = 0; s < sm; s++) {
                    channelWr[s] = ((1 - diodeProperties.mix) * channelRd[s]) + (diodeProperties.mix * wsAsym(channelRd[s]));
                }
            }
        }
        else if (diodeProperties.diode2) {
            for (int c = 0; c < ch; c++) {
                auto channelWr = buffer.getWritePointer(c);
                auto channelRd = buffer.getReadPointer(c);

                for (int s = 0; s < sm; s++) {
                    channelWr[s] = -(((1 - diodeProperties.mix) * channelRd[s]) + (diodeProperties.mix * wsAsym(channelRd[s])));
                }
            }
        }
        else {
            for (int c = 0; c < ch; c++) {
                auto channelWr = buffer.getWritePointer(c);
                auto channelRd = buffer.getReadPointer(c);

                for (int s = 0; s < sm; s++) {
                    channelWr[s] = -(((1 - diodeProperties.mix) * channelRd[s]));
                }
            }
        }
    }

    float Diode::wsAsym(float x) {
        // Saturate
        x = std::tanh((diodeProperties.sat + 0.1) * x) / (std::tanh(diodeProperties.sat + 0.1) * (diodeProperties.sat / 10.f + 1));

        // Gain
        float s = x * (1 + diodeProperties.gain);

        // Rectify
        float o1 = 0;
        if (s > diodeProperties.vf)
            o1 = s - diodeProperties.vf;
        float o2;
        if (s > diodeProperties.vb)
            o2 = o1;
        else
            o2 = s - diodeProperties.vb * 0.9;

        // Normalize
        float o3 = o2 / (diodeProperties.gain + 1);

        // Clip
        x = std::max(o3, -1.f);
        x = std::min(x, 1.f);


        return x;

    }

    float Diode::wsSym(float x) {
        // Saturate
        x = std::tanh((diodeProperties.sat + 0.1) * x) / (std::tanh(diodeProperties.sat + 0.1) * (diodeProperties.sat / 10.f + 1));

        // Gain
        float s = x * (1 + diodeProperties.gain);

        // Rectify
        s = abs(s);
        float o1 = 0;
        if (s > diodeProperties.vf)
            o1 = s - diodeProperties.vf;
        else
            s = 0;

        // Normalize
        float o2 = o1 / (diodeProperties.gain + 1);

        // Clip
        x = std::min(o2, 1.f);


        return x;
    }

    void Diode::recover(juce::AudioBuffer<float>& buffer) {

    }
}