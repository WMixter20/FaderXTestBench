#pragma once


#include <JuceHeader.h>

//==============================================================================
/*
    This component lives inside our window, and this is where you should put all
    your controls and content.
*/

class OSCSenders : public juce::Component
{
public:
    //==============================================================================
    OSCSenders()
    {
        senderLabelOne.attachToComponent(&rotaryKnobOne, false);
        addAndMakeVisible (senderLabelOne);

        rotaryKnobOne.setRange(0, 127);
        rotaryKnobOne.setSliderStyle(juce::Slider::RotaryVerticalDrag);
        rotaryKnobOne.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 25);
        addAndMakeVisible(rotaryKnobOne);

        senderLabelTwo.attachToComponent(&rotaryKnobTwo, false);
        addAndMakeVisible(senderLabelTwo);

        rotaryKnobTwo.setRange(0, 127);
        rotaryKnobTwo.setSliderStyle(juce::Slider::RotaryVerticalDrag);
        rotaryKnobTwo.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 25);
        addAndMakeVisible(rotaryKnobTwo);

        senderLabelThree.attachToComponent(&rotaryKnobThree, false);
        addAndMakeVisible(senderLabelThree);

        rotaryKnobThree.setRange(0, 127);
        rotaryKnobThree.setSliderStyle(juce::Slider::RotaryVerticalDrag);
        rotaryKnobThree.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 25);
        addAndMakeVisible(rotaryKnobThree);

        senderLabelFour.attachToComponent(&rotaryKnobFour, false);
        addAndMakeVisible(senderLabelFour);

        rotaryKnobFour.setRange(0, 127);
        rotaryKnobFour.setSliderStyle(juce::Slider::RotaryVerticalDrag);
        rotaryKnobFour.setTextBoxStyle(juce::Slider::TextBoxBelow, false, 150, 25);
        addAndMakeVisible(rotaryKnobFour);
        //==============================================================================

        rotaryKnobOne.onValueChange = [this]                                                    //OSC Message of Knob 1
            {
            if (!senderOne.send("/1/fader1", (float)rotaryKnobOne.getValue()))
                showConnectionErrorMessage("Error: could not send OSC message.");
           
            };
        if (!senderOne.connect("10.0.0.106", 9000))                                             //Target/Port of Knob 1 for TouchOSC
            showConnectionErrorMessage("Error: could n  ot connect to UDP port 9000.");

        //if (!senderOne.connect("127.0.0.1", 8000))                                             //Target/Port of Knob 1
           // showConnectionErrorMessage("Error: could n  ot connect to UDP port 9001.");
       
        //==============================================================================

        rotaryKnobTwo.onValueChange = [this]                                                   //OSC Message of Knob 2
        {
            if (!senderTwo.send("/1/fader2", (float)rotaryKnobTwo.getValue()))
                showConnectionErrorMessage("Error: could not send OSC message.");
        };

        if (!senderTwo.connect("10.0.0.106", 9000))                                             //Target/Port of Knob 2
            showConnectionErrorMessage("Error: could not connect to UDP port 9000.");

        //==============================================================================

        rotaryKnobThree.onValueChange = [this]                                                 //OSC Message of Knob 3
        {
            if (!senderThree.send("/1/fader3", (float)rotaryKnobThree.getValue()))
                showConnectionErrorMessage("Error: could not send OSC message.");
        };

        if (!senderThree.connect("10.0.0.106", 9000))                                           //Target/Port of Knob 3
            showConnectionErrorMessage("Error: could not connect to UDP port 9000.");

        //==============================================================================

        rotaryKnobFour.onValueChange = [this]                                                  //OSC Message of Knob 4
        {
            if (!senderFour.send("/1/fader4", (float)rotaryKnobFour.getValue()))
                showConnectionErrorMessage("Error: could not send OSC message.");
        };

        if (!senderFour.connect("10.0.0.106", 9000))                                            //Target/Port of Knob 4
            showConnectionErrorMessage("Error: could not connect to UDP port 9000.");


    }

    void resized() override
    {
        rotaryKnobOne.setBoundsRelative(0.00, 0.15, 0.25, 0.80);
        rotaryKnobTwo.setBoundsRelative(0.25, 0.15, 0.25, 0.80);
        rotaryKnobThree.setBoundsRelative(0.50, 0.15, 0.25, 0.80);
        rotaryKnobFour.setBoundsRelative(0.75, 0.15, 0.25, 0.80);
    }

private:
    //==============================================================================
    void showConnectionErrorMessage(const juce::String& messageText)
    {
        juce::AlertWindow::showMessageBoxAsync(juce::AlertWindow::WarningIcon,
            "Connection error",
            messageText,
            "OK");
    }
    //==============================================================================
    juce::Slider rotaryKnobOne, 
                 rotaryKnobTwo, 
                 rotaryKnobThree, 
                 rotaryKnobFour;

   juce::Label senderLabelOne { {}, "Sender 1" },
               senderLabelTwo{ {}, "Sender 2" },
               senderLabelThree{ {}, "Sender 2" },
               senderLabelFour{ {}, "Sender 2" };

    juce::OSCSender senderOne,
                    senderTwo, 
                    senderThree, 
                    senderFour;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OSCSenders)
};
//==============================================================================
class OSCReceivers : public juce::Component,
                     private juce::OSCReceiver,
                     private juce::OSCReceiver::ListenerWithOSCAddress<juce::OSCReceiver::MessageLoopCallback>
{
public:
    //==============================================================================
    OSCReceivers()
    {
        receiverLabel1.attachToComponent(&rotaryKnobOne, false);                            //Drawing Knob 1 and Label
        addAndMakeVisible(receiverLabel1);

        rotaryKnobOne.setRange(0, 127);
        rotaryKnobOne.setSliderStyle(juce::Slider::RotaryVerticalDrag);
        rotaryKnobOne.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 150, 25);
        addAndMakeVisible(rotaryKnobOne);

        receiverLabel2.attachToComponent(&rotaryKnobTwo, false);                            //Drawing Knob 2 and Label
        addAndMakeVisible(receiverLabel2);

        rotaryKnobTwo.setRange(0, 127);
        rotaryKnobTwo.setSliderStyle(juce::Slider::RotaryVerticalDrag);
        rotaryKnobTwo.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 150, 25);
        addAndMakeVisible(rotaryKnobTwo);

        receiverLabel3.attachToComponent(&rotaryKnobThree, false);                            //Drawing Knob 3 and Label
        addAndMakeVisible(receiverLabel3);

        rotaryKnobThree.setRange(0, 127);
        rotaryKnobThree.setSliderStyle(juce::Slider::RotaryVerticalDrag);
        rotaryKnobThree.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 150, 25);
        addAndMakeVisible(rotaryKnobThree);

        receiverLabel4.attachToComponent(&rotaryKnobFour, false);                            //Drawing Knob 4 and Label
        addAndMakeVisible(receiverLabel4);

        rotaryKnobFour.setRange(0, 127);
        rotaryKnobFour.setSliderStyle(juce::Slider::RotaryVerticalDrag);
        rotaryKnobFour.setTextBoxStyle(juce::Slider::TextBoxBelow, true, 150, 25);
        addAndMakeVisible(rotaryKnobFour);

        //==============================================================================
        if (!connect(8000))                                                                     //Port for Receivers
            showConnectionErrorMessage("Error: could not connect to UDP port 8000.");


        addListener(this, "/1/fader1");                                                         //Message/Adress for Knob 1
        addListener(this, "/1/fader2");
        addListener(this, "/1/fader3");
        addListener(this, "/1/fader4");

    }

    void resized() override
    {
        rotaryKnobOne.setBoundsRelative(0.00, 0.15, 0.25, 0.80);
        rotaryKnobTwo.setBoundsRelative(0.25, 0.15, 0.25, 0.80);
        rotaryKnobThree.setBoundsRelative(0.50, 0.15, 0.25, 0.80);
        rotaryKnobFour.setBoundsRelative(0.75, 0.15, 0.25, 0.80);

    }

    //==============================================================================

private:

    //==============================================================================
    
    void oscMessageReceived(const juce::OSCMessage& message) override
    {
        
        if (message.getAddressPattern() == "/1/fader1" && message.size() == 1 && message[0].isFloat32())
        {
            rotaryKnobOne.setValue(juce::jlimit(0.0f, 127.0f, message[0].getFloat32()));
        };

        if (message.getAddressPattern() == "/1/fader2" && message.size() == 1 && message[0].isFloat32())
        {
            rotaryKnobTwo.setValue(juce::jlimit(0.0f, 127.0f, message[0].getFloat32()));
        };

        if (message.getAddressPattern() == "/1/fader3" && message.size() == 1 && message[0].isFloat32())
        {
            rotaryKnobThree.setValue(juce::jlimit(0.0f, 127.0f, message[0].getFloat32()));
        };

        if (message.getAddressPattern() == "/1/fader4" && message.size() == 1 && message[0].isFloat32())
        {
            rotaryKnobFour.setValue(juce::jlimit(0.0f, 127.0f, message[0].getFloat32()));
        };


        //if (message.size() == 1 && message[0].isFloat32())
            //rotaryKnobOne.setValue(juce::jlimit(0.0f, 127.0f, message[0].getFloat32()));
            //rotaryKnobTwo.setValue(juce::jlimit(0.0f, 127.0f, message[0].getFloat32()));
    }
    


    void showConnectionErrorMessage(const juce::String& messageText)
    {
        juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::WarningIcon,
            "Connection error",
            messageText,
            "OK");
    }



    //==============================================================================
    juce::Slider rotaryKnobOne, 
                 rotaryKnobTwo,  
                 rotaryKnobThree, 
                 rotaryKnobFour;

    juce::Label receiverLabel1 { {}, "Receiver 1" },
                receiverLabel2{ {}, "Receiver 2" },
                receiverLabel3{ {}, "Receiver 3" },
                receiverLabel4{ {}, "Receiver 4" };


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OSCReceivers)
};

class AnnouncementsComponent : public juce::Component
{
public:
    AnnouncementsComponent()
    {
        addAndMakeVisible(descriptionLabel);

        textEntryBox.setMultiLine(true);
        textEntryBox.setReturnKeyStartsNewLine(true);
        textEntryBox.setText("Announcement text.");
        addAndMakeVisible(textEntryBox);

        priorityComboBox.addItemList({ "Priority - Low", "Priority - Medium", "Priority - High" }, 1);
        priorityComboBox.setSelectedId(2);
        addAndMakeVisible(priorityComboBox);

        announceButton.onClick = [this]
        {
            auto priority = [this]
            {
                switch (priorityComboBox.getSelectedId())
                {
                case 1:   return juce::AccessibilityHandler::AnnouncementPriority::low;
                case 2:   return juce::AccessibilityHandler::AnnouncementPriority::medium;
                case 3:   return juce::AccessibilityHandler::AnnouncementPriority::high;
                }

                jassertfalse;
                return juce::AccessibilityHandler::AnnouncementPriority::medium;
            }();

            juce::AccessibilityHandler::postAnnouncement(textEntryBox.getText(), priority);
        };

        addAndMakeVisible(announceButton);

        setTitle("Announcements");
        setHelpText("Type some text into the box and click the announce button to have it read out.");
        setFocusContainerType(FocusContainerType::focusContainer);
    }

    void resized() override
    {
        juce::Grid grid;

        grid.templateRows = { juce::Grid::TrackInfo(juce::Grid::Fr(3)),
                              juce::Grid::TrackInfo(juce::Grid::Fr(1)),
                              juce::Grid::TrackInfo(juce::Grid::Fr(1)),
                              juce::Grid::TrackInfo(juce::Grid::Fr(1)),
                              juce::Grid::TrackInfo(juce::Grid::Fr(1)),
                              juce::Grid::TrackInfo(juce::Grid::Fr(1)) };

        grid.templateColumns = { juce::Grid::TrackInfo(juce::Grid::Fr(3)),
                                 juce::Grid::TrackInfo(juce::Grid::Fr(2)) };

        grid.items = { juce::GridItem(descriptionLabel).withMargin(2).withColumn({ juce::GridItem::Span(2), {} }),
                       juce::GridItem(textEntryBox).withMargin(2).withArea({ 2 }, { 1 }, { 5 }, { 2 }),
                       juce::GridItem(priorityComboBox).withMargin(2).withArea({ 5 }, { 1 }, { 6 }, { 2 }),
                       juce::GridItem(announceButton).withMargin(2).withArea({ 4 }, { 2 }, { 5 }, { 3 }) };

        grid.performLayout(getLocalBounds());
    }

private:
    juce::Label descriptionLabel{ {}, "This is a demo of posting system announcements that will be read out by an accessibility client.\n\n"
                                 "You can enter some text to be read out in the text box below, set a priority for the message and then "
                                 "post it using the \"Announce\" button." };

    juce::TextEditor textEntryBox;
    juce::ComboBox priorityComboBox;
    juce::TextButton announceButton{ "Announce" };

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(AnnouncementsComponent)
};

//==============================================================================
class FaderXTestBench : public juce::Component
{
public:
    FaderXTestBench()
    {
        //addAndMakeVisible(monitor);
        addAndMakeVisible(receivers);
        addAndMakeVisible(senders);

        TopTabs.setTitle("Test1");
        BottomTabs.setTitle("Test2");


        const auto tabColour1 = getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId).darker(0.1f);

        TopTabs.addTab("Senders", tabColour1, &senders, false);
        TopTabs.addTab("OSC Port Num", tabColour1, &announcementsComponent, false);
        addAndMakeVisible(TopTabs);

        const auto tabColour2 = getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId).darker(0.1f);

        BottomTabs.addTab("Senders", tabColour2, &receivers, false);
        //BottomTabs.addTab("OSC Port Num", tabColour, &announcementsComponent, false);
        addAndMakeVisible(BottomTabs);

        setSize(800, 400);
    } 

    void resized() override
    {
        auto bounds = getLocalBounds();

        auto lowerBounds = bounds.removeFromBottom(getHeight() / 2);
        //auto halfBounds = bounds.removeFromRight(getWidth() / 2);

        TopTabs.setBounds(bounds);
        BottomTabs.setBounds(lowerBounds);

       // senders.setBounds(bounds);
       // receivers.setBounds(lowerBounds);

        //monitor.setBounds(lowerBounds.removeFromTop(getHeight() / 2));
    }

private:
  
    juce::TabbedComponent TopTabs{ juce::TabbedButtonBar::Orientation::TabsAtTop};
    juce::TabbedComponent BottomTabs{ juce::TabbedButtonBar::Orientation::TabsAtTop};


    AnnouncementsComponent announcementsComponent;

    OSCSenders  senders;
    OSCReceivers receivers;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FaderXTestBench)
};
