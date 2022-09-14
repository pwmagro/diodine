/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "GUI/WindowLayout.h"
#include "GUI/Utils/GuiData.h"

//==============================================================================
/**
*/
class DiodineAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    DiodineAudioProcessorEditor (DiodineAudioProcessor&);
    ~DiodineAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

    juce::SharedResourcePointer<xynth::DefaultLookAndFeel> defaultLnf;

private:
    juce::ApplicationProperties properties;
    double scale = 1.f;
    xynth::GuiData guiData;
    WindowLayout windowLayout;

    DiodineAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DiodineAudioProcessorEditor)
};
