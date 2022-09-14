/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#define APPLICATION_NAME "Diodine"
#define FILENAME_SUFFIX ".settings"
#define FOLDER_NAME "WDYM"

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DiodineAudioProcessorEditor::DiodineAudioProcessorEditor (DiodineAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), guiData(p, *defaultLnf, scale, properties), windowLayout(guiData)
{

    juce::PropertiesFile::Options fileOptions;
    fileOptions.applicationName = APPLICATION_NAME;
    fileOptions.filenameSuffix = FILENAME_SUFFIX;
    fileOptions.folderName = FOLDER_NAME;
    fileOptions.osxLibrarySubFolder = "Application Support"; // Recommended by Apple
    fileOptions.commonToAllUsers = false;
    fileOptions.ignoreCaseOfKeyNames = false;
    fileOptions.storageFormat = juce::PropertiesFile::storeAsXML;
    properties.setStorageParameters(fileOptions);

    // Set plugin window dimensions and scale
    //getConstrainer()->setFixedAspectRatio((double)WIDTH / (double)HEIGHT);
    setSize(double(WIDTH), double(HEIGHT));
    juce::Rectangle<int> defaultSize(WIDTH, HEIGHT);
    windowLayout.setBounds(defaultSize);

    setResizable(true, false);
    setResizeLimits(WIDTH, HEIGHT, WIDTH * 2, HEIGHT * 2);

    const int skin = properties.getUserSettings()->getIntValue("Skin", 0);
    guiData.updateLnf(skin);

    addAndMakeVisible(windowLayout);
}

DiodineAudioProcessorEditor::~DiodineAudioProcessorEditor()
{
}

//==============================================================================
void DiodineAudioProcessorEditor::paint (juce::Graphics& g)
{
}

void DiodineAudioProcessorEditor::resized() {
    windowLayout.setBounds(0, 0, getWidth(), getHeight());
}
