/*
    Copyright ©1994-1996, Juri Munkki
    All rights reserved.

    File: CAvaraApp.h
    Created: Wednesday, November 16, 1994, 01:25
    Modified: Monday, September 2, 1996, 10:23
*/

#pragma once

#include "CApplication.h"
//#include "PolyColor.h"
#include "CLevelWindow.h"
#include "CNetworkWindow.h"
#include "CPlayerWindow.h"
#include "CRosterWindow.h"
#include "CTrackerWindow.h"

#include <SDL2/SDL.h>
#include <string>
#include <deque>

class CAvaraGame;
class CNetManager;

class CAvaraApp {
public:

    virtual void MessageLine(short index, short align) = 0;
    virtual std::deque<std::string> GetMessageLines() = 0;
    virtual void DrawUserInfoPart(short i, short partList) = 0;
    virtual void ParamLine(short index, short align, StringPtr param1, StringPtr param2) = 0;
    virtual void StartFrame(long frameNum) = 0;
    virtual void BrightBox(long frameNum, short position) = 0;
    virtual void LevelReset() = 0;
    virtual long Number(const std::string name) = 0;
    virtual OSErr LoadLevel(std::string set, OSType theLevel) = 0;
    virtual void ComposeParamLine(StringPtr destStr, short index, StringPtr param1, StringPtr param2) = 0;
    virtual void NotifyUser() = 0;
    virtual json Get(const std::string name) = 0;
    virtual void Set(const std::string name, const std::string value) = 0;
    virtual void Set(const std::string name, long value) = 0;
    virtual void Set(const std::string name, json value) = 0;
    virtual CNetManager* GetNet() = 0;
    virtual void SetNet(CNetManager*) = 0;
    virtual SDL_Window* sdlWindow() = 0;
    virtual void StringLine(StringPtr theString, short align) = 0;
    virtual CAvaraGame* GetGame() = 0;
    virtual void Done() = 0;
};
class CCAvaraApp : public CApplication, public CAvaraApp {
public:
    CAvaraGame *itsGame;
    CNetManager *gameNet;

    CPlayerWindow *playerWindow;
    CLevelWindow *levelWindow;
    CNetworkWindow *networkWindow;
    CRosterWindow *rosterWindow;
    CTrackerWindow *trackerWindow;

    std::deque<std::string> messageLines;

    CCAvaraApp();
    ~CCAvaraApp();

    virtual void idle() override;
    virtual void drawContents() override;

    virtual bool DoCommand(int theCommand) override;
    virtual void WindowResized(int width, int height) override;

    virtual void Done() override;

    virtual bool handleSDLEvent(SDL_Event &event) override;
    virtual void drawAll() override;

    OSErr LoadLevel(std::string set, OSType theLevel);
    void NotifyUser();

    virtual void AddMessageLine(std::string line);
    virtual std::deque<std::string> GetMessageLines();
    // From CInfoPanel
    virtual void SetIndicatorDisplay(short i, short v);
    virtual void NumberLine(long theNum, short align);
    virtual void DrawUserInfoPart(short i, short partList);
    virtual void BrightBox(long frameNum, short position);
    virtual void MessageLine(short index, short align);
    virtual void LevelReset();
    virtual void ParamLine(short index, short align, StringPtr param1, StringPtr param2);
    virtual void StartFrame(long frameNum);
    virtual void StringLine(StringPtr theString, short align);
    virtual void ComposeParamLine(StringPtr destStr, short index, StringPtr param1, StringPtr param2);
    virtual void SetNet(CNetManager*);
    virtual CNetManager* GetNet();
    virtual CAvaraGame* GetGame();
    virtual json Get(const std::string name) { return CApplication::Get(name); }
    virtual void Set(const std::string name, const std::string value) { CApplication::Set(name, value); }
    virtual void Set(const std::string name, long value) { CApplication::Set(name, value); }
    virtual void Set(const std::string name, json value) { CApplication::Set(name, value); }
    virtual SDL_Window* sdlWindow() { return CApplication::sdlWindow(); }
    virtual long Number(const std::string name) { return CApplication::Number(name); }
};
