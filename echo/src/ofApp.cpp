//
// Copyright (c) 2014 Christopher Baker <https://christopherbaker.net>
//
// SPDX-License-Identifier:    MIT
//


#include "ofApp.h"

string num;
void ofApp::setup()
{
    // 1. Upload the `Echo.ino` sketch (in this example's `Arduino/` folder) to
    // an Arduino-compatible board.
    //
    // 2. Check the "listDevices" call in the `ofApp::setup()` function to make
    // sure the correct serial device is connected.
    //
    // 3. Run this app.

    std::vector<ofx::IO::SerialDeviceInfo> devicesInfo = ofx::IO::SerialDeviceUtils::listDevices();

    ofLogNotice("ofApp::setup") << "Connected Devices: ";

    for (std::size_t i = 0; i < devicesInfo.size(); ++i)
    {
        ofLogNotice("ofApp::setup") << "\t" << devicesInfo[i];
    }

    if (!devicesInfo.empty())
    {
        // Connect to the first matching device.
        bool success = device.setup(devicesInfo[0], 115200);

        if (success)
        {
            ofLogNotice("ofApp::setup") << "Successfully setup " << devicesInfo[0];
        }
        else
        {
            ofLogNotice("ofApp::setup") << "Unable to setup " << devicesInfo[0];
        }
    }
    else
    {
        ofLogNotice("ofApp::setup") << "No devices connected.";
    }
}


void ofApp::update()
{
    // The serial device can throw exeptions.
    try
    {
        // Read all bytes from the device;
        uint8_t buffer[1024];

        while (device.available() > 0)
        {
            std::size_t sz = device.readBytes(buffer, 1024);

            std::cout << buffer[0];
            num = buffer[0];
//            for (std::size_t i = 0; i < sz; ++i)
//            {
//                std::cout << buffer[0];
//            }
        }


    }
    catch (const std::exception& exc)
    {
        ofLogError("ofApp::update") << exc.what();
    }
}


void ofApp::draw()
{
    ofBackgroundGradient(ofColor::white, ofColor::black);
    ofDrawBitmapStringHighlight("Connected to " + device.port(), 20, 20);
    ofDrawBitmapStringHighlight(num, 20, 45);
    if(ofToInt(num) == 1){
        ofLogNotice("One");
    } else if(ofToInt(num) == 2){
        ofLogNotice("Two");
    }
}

