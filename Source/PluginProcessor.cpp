/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DiodineAudioProcessor::DiodineAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ),
    treeState (*this, nullptr, "Parameters", createParameters()),
    diodine()
#endif
{

}

DiodineAudioProcessor::~DiodineAudioProcessor()
{
}

//==============================================================================
const juce::String DiodineAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DiodineAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DiodineAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DiodineAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DiodineAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DiodineAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DiodineAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DiodineAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String DiodineAudioProcessor::getProgramName (int index)
{
    return {};
}

void DiodineAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void DiodineAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Start diode sim
    diodine.init(sampleRate, samplesPerBlock);
}

void DiodineAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DiodineAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void DiodineAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    diodine.process(buffer, treeState);
}

//==============================================================================
bool DiodineAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* DiodineAudioProcessor::createEditor()
{
    return new DiodineAudioProcessorEditor(*this);
    //return new DiodineAudioProcessorEditor (*this);
}

//==============================================================================
void DiodineAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

}

void DiodineAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DiodineAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout DiodineAudioProcessor::createParameters()
{
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    params.push_back(std::make_unique<juce::AudioParameterFloat>(GAIN_ID, GAIN_NAME,  1.f,  20.f,   5.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(SAT_ID,  SAT_NAME,   0.f,   0.5f,   0.1f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(VF_ID,   VF_NAME,    0.f,   5.f,   0.2f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(VB_ID,   VB_NAME,  -20.f,   0.f, -12.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(TRR_ID,  TRR_NAME,   0.f,  20.f,   2.f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>(MIX_ID,  MIX_NAME,   0.f,   1.f,   1.f));

    params.push_back(std::make_unique<juce::AudioParameterFloat>(HUE_ID, HUE_NAME, 0.f, 360.f, 25.f));

    params.push_back(std::make_unique<juce::AudioParameterBool>(DIODE_1_ID, DIODE_1_NAME, true ));
    params.push_back(std::make_unique<juce::AudioParameterBool>(DIODE_2_ID, DIODE_2_NAME, false));

    params.push_back(std::make_unique<juce::AudioParameterBool>(DC_OFF_ID, DC_OFF_NAME, true));

    return { params.begin(), params.end() };
}