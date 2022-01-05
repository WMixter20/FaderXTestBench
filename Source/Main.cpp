/*
  ==============================================================================

    This file contains the basic startup code for a JUCE application.

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FaderXTestBench.h"

//==============================================================================
class Application  : public juce::JUCEApplication
{
public:
    //==============================================================================
    Application() = default;

    const juce::String getApplicationName() override       { return "Fader X Test Bench"; }
    const juce::String getApplicationVersion() override    { return ProjectInfo::versionString; }
    //bool moreThanOneInstanceAllowed() override             { return true; }

    //==============================================================================
    void initialise (const juce::String&) override
    {
        mainWindow.reset(new MainWindow("FaderX TestBench", new FaderXTestBench, *this));
    }

    void shutdown() override
    {
        // Add your application's shutdown code here..

        mainWindow = nullptr; // (deletes our window)
    }

    //==============================================================================
    class MainWindow    : public juce::DocumentWindow
    {
    public:
        MainWindow(const juce::String& name, juce::Component* c, JUCEApplication& a)
            : DocumentWindow(name, juce::Desktop::getInstance().getDefaultLookAndFeel()
                                                               .findColour(ResizableWindow::backgroundColourId),
                             juce::DocumentWindow::allButtons),
                app(a)
        {
            setUsingNativeTitleBar(true);
            setContentOwned(c, true);

            #if JUCE_ANDROID || JUCE_IOS
            setFullScreen(true);
            #else
             setResizable(true, false);
             setResizeLimits(300, 250, 10000, 10000);
             centreWithSize(getWidth(), getHeight());
            #endif

            setVisible(true);
        }

        void closeButtonPressed() override
        {
            app.systemRequestedQuit();
        }

    private:
        JUCEApplication& app;

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };

private:
    std::unique_ptr<MainWindow> mainWindow;
};

//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (Application)
