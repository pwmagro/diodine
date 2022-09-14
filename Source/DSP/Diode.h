/*
  ==============================================================================

    Diode.h
    Created: 10 Sep 2022 5:27:07pm
    Author:  pwmag

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../Common/Constants.h"

namespace WDYM {
    class Diode {
    public:
        Diode();
        ~Diode();
        void init(double sampleRate, int samplesPerBlock);
        void process(juce::AudioBuffer<float>& buffer, juce::AudioProcessorValueTreeState &apvts);

    private:
        float wsAsym(float x);
        float wsSym(float x);
        void recover(juce::AudioBuffer<float>& buffer);

        struct {
            bool diode1 = true;
            bool diode2 = false;
            float vf = 0;
            float vb = 0;
            float trr = 0;
            float gain = 0;
            float sat = 0;
            float mix = 1;
        } diodeProperties;
        
        float samplesPerMs;

        float lastSample;
    };
}