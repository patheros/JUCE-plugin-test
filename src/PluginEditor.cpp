/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginEditor.h"

#include "PluginProcessor.h"

//==============================================================================
TestpluginAudioProcessorEditor::TestpluginAudioProcessorEditor(TestpluginAudioProcessor &p) :
  AudioProcessorEditor(&p),
  audioProcessor(p)
  {
  // Make sure that before the constructor has finished, you've set the
  // editor's size to whatever you need it to be.
  setSize(400, 300);

  // load Image from BinaryData
  svgimg = juce::Drawable::createFromImageData(BinaryData::jucelogo_svg, BinaryData::jucelogo_svgSize);

  // these define the parameters of our slider object
  midiVolume.setSliderStyle (juce::Slider::LinearBarVertical);
  midiVolume.setRange (0.0, 127.0, 1.0);
  midiVolume.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
  midiVolume.setPopupDisplayEnabled (true, false, this);
  midiVolume.setTextValueSuffix (" Volume");
  midiVolume.setValue(1.0);
  midiVolume.addListener (this); // add the listener to the slider

  // this function adds the slider to the editor
  addAndMakeVisible (&midiVolume);

  
}

TestpluginAudioProcessorEditor::~TestpluginAudioProcessorEditor() {}

//==============================================================================

void TestpluginAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    audioProcessor.noteOnVel = midiVolume.getValue();
}

//==============================================================================
void TestpluginAudioProcessorEditor::paint(juce::Graphics &g) {
  // (Our component is opaque, so we must completely fill the background with a
  // solid colour)
  g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
  svgimg->drawWithin(g, getLocalBounds().toFloat(), juce::Justification::centred, 1);

  g.setColour(juce::Colours::black);
  g.setFont(30.0f);
  g.drawFittedText("I made this!", getLocalBounds(), juce::Justification::centred, 1);

  // set the current drawing colour to black
  g.setColour (juce::Colours::black);
 
  // set the font size and draw text to the screen
  g.setFont (15.0f);
 
  g.drawFittedText ("Midi Volume", 0, 0, 100, 30, juce::Justification::centred, 1);
}

void TestpluginAudioProcessorEditor::resized() {
  // This is generally where you'll want to lay out the positions of any
  // subcomponents in your editor..

  // sets the position and size of the slider with arguments (x, y, width, height)
  midiVolume.setBounds (20, 30, 20, getHeight() - 60);
}
