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
        static float waveshape(float x, juce::AudioProcessorValueTreeState& apvts);

    private:
        typedef struct {
            bool diode1 = true;
            bool diode2 = false;
            float vf = 0;
            float vb = 0;
            float trr = 0;
            float gain = 0;
            float sat = 0;
            float mix = 1;
        } DiodeProperties_t;

        static float wsAsym(float x, DiodeProperties_t& diodeProperties);
        static float wsSym(float x, DiodeProperties_t& diodeProperties);
        void recover(juce::AudioBuffer<float>& buffer);


        DiodeProperties_t diodeProperties;
        
        float samplesPerMs;

        float lastSample;
    };
}