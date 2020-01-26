#pragma once

#include "CWindow.h"

class CNetworkWindow : public CWindow {
public:
    CNetworkWindow(CApplication *app);

    virtual ~CNetworkWindow();

    virtual bool DoCommand(int theCommand) override;

    virtual void PrefChanged(std::string name) override;

protected:
	nanogui::TextBox *addressBox;
    nanogui::TextBox *latencyBox;
    nanogui::TextBox *trackerBox;
    nanogui::Button *connectBtn;
    nanogui::Button *startBtn;
};
