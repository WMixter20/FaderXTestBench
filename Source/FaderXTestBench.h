#pragma once


//#include <JuceHeader.h>
int senderPortNum = 9000; //9000 for Touch OSC
int recevierPortNum = 8000; //8000 For Touch OSC 
                            //8000 works with touch bridge  (make sure local host is sleceted)  

juce::String senderPortIP = "192.168.86.48"; // Target local IP 

int currentPortNumber = -1;

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
        if (!senderOne.connect(senderPortIP, senderPortNum))                                             //Target/Port of Knob 1
            showConnectionErrorMessage("Error: could n  ot connect to UDP port 9000.");

        //==============================================================================

        rotaryKnobTwo.onValueChange = [this]                                                   //OSC Message of Knob 2
        {
            if (!senderTwo.send("/1/fader2", (float)rotaryKnobTwo.getValue()))
                showConnectionErrorMessage("Error: could not send OSC message.");
        };

        if (!senderTwo.connect(senderPortIP, senderPortNum))                                             //Target/Port of Knob 2
            showConnectionErrorMessage("Error: could not connect to UDP port 9000.");

        //==============================================================================

        rotaryKnobThree.onValueChange = [this]                                                 //OSC Message of Knob 3
        {
            if (!senderThree.send("/1/fader3", (float)rotaryKnobThree.getValue()))
                showConnectionErrorMessage("Error: could not send OSC message.");
        };

        if (!senderThree.connect(senderPortIP, senderPortNum))                                           //Target/Port of Knob 3
            showConnectionErrorMessage("Error: could not connect to UDP port 9000.");

        //==============================================================================

        rotaryKnobFour.onValueChange = [this]                                                  //OSC Message of Knob 4
        {
            if (!senderFour.send("/1/fader4", (float)rotaryKnobFour.getValue()))
                showConnectionErrorMessage("Error: could not send OSC message.");
        };

        if (!senderFour.connect(senderPortIP, senderPortNum))                                            //Target/Port of Knob 4
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
        if (!connect(recevierPortNum))                                                               //Port for Receivers
            showConnectionErrorMessage("Error: could not connect to UDP port " + recevierPortNum);


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
//==============================================================================
class OSCSenderPortControl : public juce::Component,
                       private juce::OSCReceiver::Listener<juce::OSCReceiver::MessageLoopCallback>
{
public:
    //==============================================================================
    OSCSenderPortControl()
    {

        addAndMakeVisible(portNumberLabel);
        portNumberField.setEditable(true, true, true);                               //THIS LABEL I want to use to change senderPortNum Not WORKING
        addAndMakeVisible(portNumberField);


        addAndMakeVisible(connectButton);
        connectButton.onClick = [this] { connectButtonClicked(); };




        updateConnectionStatusLabel();
        addAndMakeVisible(connectionStatusLabel);

        portNumberField.onTextChange = [this]
        {
            senderPortNum = portNumberField.getText().getIntValue();
        };
        

        oscReceiver.addListener(this);

    }
    void resized()
    {
        portNumberLabel.setBounds(10, 18, 130, 25);
        portNumberField.setBounds(140, 18, 50, 25);
        connectButton.setBounds(210, 18, 100, 25);

        connectionStatusLabel.setBounds(450, 18, 240, 25);
        //oscLogListBox.setBounds(0, 60, 700, 340);


    }

private:
    //==============================================================================
    juce::Label portNumberLabel{ {}, "Sender Port Number: " };
    juce::Label portNumberField{ {}, "9002" };
    juce::TextButton connectButton{ "Connect" };
    juce::Label connectionStatusLabel;

    
    juce::OSCReceiver oscReceiver;
    OSCSenders senders;

    //int currentPortNumber = -1;

    //==============================================================================
    void connectButtonClicked()
    {

        if (!isConnected())
            connect();
        else
            disconnect();

        updateConnectionStatusLabel();
    }

    //==============================================================================
    void clearButtonClicked()
    {
        //oscLogListBox.clear();
    }

    //==============================================================================
    void oscMessageReceived(const juce::OSCMessage& message) override
    {
        //oscLogListBox.addOSCMessage(message);
    }

    void oscBundleReceived(const juce::OSCBundle& bundle) override
    {
        //oscLogListBox.addOSCBundle(bundle);
    }

    //==============================================================================
    void connect()
    {
        auto portToConnect = portNumberField.getText().getIntValue();

        if (!isValidOscPort(portToConnect))
        {
            handleInvalidPortNumberEntered();
            return;
        }

        if (isValidOscPort(portToConnect))
        {
            currentPortNumber = portToConnect;
            senderPortNum = currentPortNumber;
            connectButton.setButtonText("Disconnect");
        }
        else
        {
            handleConnectError(portToConnect);
        }
    }

    //==============================================================================
    void disconnect()
    {
        if (oscReceiver.disconnect())
        {
            currentPortNumber = -1;
            senderPortNum = currentPortNumber;
            connectButton.setButtonText("Connect");
        }
        else
        {
            handleDisconnectError();
        }
    }

    //==============================================================================
    void handleConnectError(int failedPort)
    {
        juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::WarningIcon,
            "OSC Connection error",
            "Error: could not connect to port " + juce::String(failedPort),
            "OK");
    }

    //==============================================================================
    void handleDisconnectError()
    {
        juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::WarningIcon,
            "Unknown error",
            "An unknown error occurred while trying to disconnect from UDP port.",
            "OK");
    }

    //==============================================================================
    void handleInvalidPortNumberEntered()
    {
        juce::AlertWindow::showMessageBoxAsync(juce::MessageBoxIconType::WarningIcon,
            "Invalid port number",
            "Error: you have entered an invalid UDP port number.",
            "OK");
    }

    //==============================================================================
    bool isConnected() const
    {
        return currentPortNumber != -1;
    }

    //==============================================================================
    bool isValidOscPort(int port) const
    {
        return port > 0 && port < 65536;
    }

    //==============================================================================
    void updateConnectionStatusLabel()
    {
        juce::String text = "Status: ";

        if (isConnected())
            text += "Connected to UDP port " + juce::String(currentPortNumber);
        else
            text += "Disconnected";

        auto textColour = isConnected() ? juce::Colours::green : juce::Colours::red;

        connectionStatusLabel.setText(text, juce::dontSendNotification);
        connectionStatusLabel.setFont(juce::Font(15.00f, juce::Font::bold));
        connectionStatusLabel.setColour(juce::Label::textColourId, textColour);
        connectionStatusLabel.setJustificationType(juce::Justification::centredRight);
    }

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(OSCSenderPortControl)
};
/*
class SerialDATA : public juce::Component
                        
{
public:
    //==============================================================================
    SerialDATA()
    {
        //get a list of serial ports installed on the system, as a StringPairArray containing a friendly name and the port path
        juce::StringPairArray portlist = SerialPort::getSerialPortPaths();
        if (portlist.size())
        {
            //open the first port on the system
            SerialPort* pSP = new SerialPort(portlist.getAllValues()[0], SerialPortConfig(9600, 8, SerialPortConfig::SERIALPORT_PARITY_NONE, SerialPortConfig::STOPBITS_1, SerialPortConfig::FLOWCONTROL_NONE));
            if (pSP->exists())
            {
                //create streams for reading/writing
                SerialPortOutputStream* pOutputStream = new SerialPortOutputStream(pSP);
                SerialPortInputStream* pInputStream = new SerialPortInputStream(pSP);

                pOutputStream->write("hello world via serial", 22); //write some bytes

                //read chars one at a time:
                char c;
                while (!pInputStream->isExhausted())
                    pInputStream->read(&c, 1);

                //or, read line by line:
                juce::String s;
                while (pInputStream->canReadLine())
                    s = pInputStream->readNextLine();

                //or ask to be notified when a new line is available:
                pInputStreams->addChangeListener(this); //we must be a ChangeListener to receive notifications
                pInputStream->setNotify(SerialPortInputStream::NOTIFY_ON_CHAR, '\n');

                //or ask to be notified whenever any character is received
                //NOTE - use with care at high baud rates!!!!
                pInputStream->setNotify(SerialPortInputStream::NOTIFY_ALWAYS);

                //please see class definitions for other features/functions etc		
            }
        }
    }
    //==============================================================================
private:
    // Your private member variables go here...
    juce::TextButton sendButton;
    juce::TextButton getButton;
    juce::TextButton loadButton;
    juce::TextButton saveButton;
    juce::Rectangle<int> buttonsArea;
    juce::Label textLabel{ {}, "Serial Ports" };
    juce::Font textFont{ 16.0f };
    juce::ComboBox serialPortMenu;
    juce::StringPairArray portlist;
    //SerialPort* pSP;
    SerialPortOutputStream* pOutputStream;
    SerialPortInputStream* pInputStream;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(SerialDATA)
};
*/
//==============================================================================
class FaderXTestBench : public juce::Component                                                  //Complies Code into GUI
{
public:
    FaderXTestBench()
    {
        //addAndMakeVisible(monitor);
        addAndMakeVisible(receivers);
        addAndMakeVisible(senders);
        addAndMakeVisible(senderPortControl);
        //addAndMakeVisible(SerialDATA);

        TopTabs.setTitle("Test1");
        BottomTabs.setTitle("Test2");


        const auto tabColour1 = getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId).darker(0.1f);

        TopTabs.addTab("Senders", tabColour1, &senders, false);
        TopTabs.addTab("OSC Ports", tabColour1, &senderPortControl, false);
        addAndMakeVisible(TopTabs);

        const auto tabColour2 = getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId).darker(0.1f);

        BottomTabs.addTab("Recievers", tabColour2, &receivers, false);
       // BottomTabs.addTab("Serial Ports", tabColour2, &SerialDATA, false);
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

        //oscMonitor.setBounds(lowerBounds.removeFromTop(getHeight() / 2));
    }

private:
  
    juce::TabbedComponent TopTabs{ juce::TabbedButtonBar::Orientation::TabsAtTop};
    juce::TabbedComponent BottomTabs{ juce::TabbedButtonBar::Orientation::TabsAtTop};


    OSCSenders  senders;
    OSCReceivers receivers;
    OSCSenderPortControl senderPortControl;
    //OSCMonitorDemo2 SerialDATA;
   

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FaderXTestBench)
};
