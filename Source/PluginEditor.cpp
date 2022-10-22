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

    // Load global plugin scale
    auto* propertiesFile = properties.getUserSettings();
    if (propertiesFile) {
        localWidth = propertiesFile->getDoubleValue(LOCAL_WIDTH_ID, localWidth);
        localHeight = propertiesFile->getDoubleValue(LOCAL_HEIGHT_ID, localHeight);
    }

    // Set plugin window dimensions and scale
    setSize(double(localWidth), double(localHeight));
    juce::Rectangle<float> defaultSize(localWidth, localHeight);
    windowLayout.setBounds(defaultSize.toNearestInt());

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
    g.reduceClipRegion(getLocalBounds());
}

void DiodineAudioProcessorEditor::resized() {
    localWidth = getWidth();
    localHeight = getHeight();

    properties.getUserSettings()->setValue(LOCAL_WIDTH_ID, localWidth);
    properties.getUserSettings()->setValue(LOCAL_HEIGHT_ID, localHeight);

    properties.saveIfNeeded();

    windowLayout.setBounds(0, 0, localWidth, localHeight);
    
}
