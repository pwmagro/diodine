/*
  ==============================================================================

    GuiData.h
    Created: 5 Sep 2022 3:56:01pm
    Author:  thesp
    Modified: pwmag, 11 Sep 2022 8:58pm

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "../../PluginProcessor.h"
#include "../CustomLooks/CustomLook.h"

namespace xynth
{
struct DefaultLookAndFeel
{
    DefaultLookAndFeel()  { juce::LookAndFeel::setDefaultLookAndFeel(lnf);    }
    ~DefaultLookAndFeel() { juce::LookAndFeel::setDefaultLookAndFeel(nullptr); }

    void updateLnf() { juce::LookAndFeel::setDefaultLookAndFeel(lnf); }

    juce::CustomLook diodide;

    // Change to desired LookAndFeel
    juce::CustomLook* lnf = &diodide;
};

struct GuiData
{
    GuiData(DiodineAudioProcessor& p, DefaultLookAndFeel& defLnf, double& s, juce::ApplicationProperties& props)
        : audioProcessor(p), scale(s), defaultLnf(defLnf), properties(props) 
    {}

    void updateLnf(int skin) 
    { 
        if (skin == diodide)
            defaultLnf.lnf = &defaultLnf.diodide;
        else
            jassertfalse; // wrong index (too many items?)

        defaultLnf.updateLnf(); 

        properties.getUserSettings()->setValue("Skin", skin);
        properties.saveIfNeeded();
    }

    DiodineAudioProcessor& audioProcessor;
    double& scale;
    DefaultLookAndFeel& defaultLnf;
    juce::ApplicationProperties& properties;

    juce::CustomLook& getLnf() { return *defaultLnf.lnf; }
    std::function<void()> showAbout;

private:
    enum skinEnum { diodide };

};
} //namespace xynth