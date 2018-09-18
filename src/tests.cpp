#include "gtest/gtest.h"
#include "CAvaraApp.h"
#include "CBSPPart.h"
#include "CPlayerManager.h"
#include "CNetManager.h"
#include "CAvaraGame.h"
#include "CWalkerActor.h"
#include "CBSPWorld.h"
#include <nanogui/nanogui.h>
#include "FastMat.h"
#include "Parser.h"
#include "CSoundHub.h"

#include <iostream>
using namespace std;

class TestSoundHub : public CSoundHubImpl {
public:
    virtual Fixed* EarLocation() { return ear; }
    /*
    virtual Fixed DistanceToLevelOne() { return 0; }
    virtual void MuteFlag(Boolean) {}
    virtual void AttachMixer(CSoundMixer *aMixer) {}
    //virtual void CreateSound(short kind) {}

    virtual SampleHeaderHandle LoadSample(short resId) { return 0; }
    virtual SampleHeaderHandle PreLoadSample(short resId) { return 0; }
    virtual SampleHeaderHandle RequestSample(short resId) { return 0; }
    virtual void FreeUnusedSamples() {}

    virtual void FreeOldSamples() {}
    virtual void FlagOldSamples() {}

    virtual void Restock(CBasicSound *aSound) {}
    //virtual CBasicSound *Aquire(short kind) {}
    virtual CBasicSound *GetSoundSampler(short kind, short resId) { return 0; }

    //virtual void CreateSoundLinks(short n) {}
    //virtual void DisposeSoundLinks() {}
    virtual SoundLink *GetSoundLink() { return 0; }
    virtual void ReleaseLink(SoundLink *linkPtr) {}
    virtual void ReleaseLinkAndKillSounds(SoundLink *linkPtr) {}

    virtual void SetMixerLink(SoundLink *newLink) {}
    virtual SoundLink *UpdateRightVector(Fixed *right) { return 0; }
    virtual int ReadTime() { return 0; }
    virtual void HouseKeep() {}

    virtual void Dispose() {}
    virtual void MixerDispose() {}
    virtual void HushFlag(bool) {}
    virtual bool Stereo() { return true; }
    */
private:
    Fixed ear[3];

};
class TestPlayerManager : public CPlayerManager {
public:
    TestPlayerManager(CAvaraGame* game) {
        itsGame = game;
        playa = 0;
    }
    virtual CAbstractPlayer* GetPlayer() { return playa; }
    virtual void SetPlayer(CAbstractPlayer* p) { playa = p; }
    virtual short Slot() { return 0; }
    virtual void AbortRequest() {}
    virtual Boolean IsLocalPlayer() { return true; }
    virtual void GameKeyPress(char c) {}
    virtual FunctionTable *GetFunctions() { return new FunctionTable(); }
    virtual void DeadOrDone() {}
    virtual short Position() { return 0; }
    virtual Str255& PlayerName() { return str; }
    virtual std::deque<char>& LineBuffer() { return lineBuffer; }
    virtual void Dispose() {}
    virtual void NetDisconnect() {}
    virtual short IsRegistered() { return 0; }
    virtual void IsRegistered(short) {}
    virtual Str255& PlayerRegName() { return str; }
    virtual short LoadingStatus() { return 0; }
    virtual void SetPlayerStatus(short newStatus, long theWin) {}
    virtual void ChangeNameAndLocation(StringPtr theName, Point location) {}
    virtual void SetPosition(short pos) {}
    virtual void RosterKeyPress(unsigned char c) {}
    virtual void RosterMessageText(short len, char *c) {}
    virtual short LevelCRC() { return 0; }
    virtual OSErr LevelErr() { return noErr; }
    virtual OSType LevelTag() { return 0; }
    virtual void LevelCRC(short) {}
    virtual void LevelErr(OSErr) {}
    virtual void LevelTag(OSType) {}
    virtual void LoadStatusChange(short serverCRC, OSErr serverErr, OSType serverTag) {}
    virtual void ResumeGame() {}
    virtual uint32_t DoMouseControl(Point *deltaMouse, Boolean doCenter) { return 0; }
    virtual void HandleEvent(SDL_Event &event) {}
    virtual void SendFrame() { itsGame->topSentFrame++; }
    virtual void ViewControl() {}
    virtual Fixed RandomKey() { return 0;}
    virtual void RandomKey(Fixed) {}
    virtual CAbstractPlayer *ChooseActor(CAbstractPlayer *actorList, short myTeamColor) { return 0; }
    virtual short GetStatusChar() { return 0; }
    virtual short GetMessageIndicator() { return 0; }
    virtual std::string GetChatString(int maxChars) { return ""; }
    virtual void StoreMugShot(Handle mugHandle) {}
    virtual Handle GetMugShot() { return 0; }

    virtual CAbstractPlayer *TakeAnyActor(CAbstractPlayer *actorList) { return 0; }
    virtual short PlayerColor() { return 0; }
    virtual Boolean IncarnateInAnyColor() { return false; }
    virtual void ResendFrame(long theFrame, short requesterId, short commandCode) {}
    virtual void SpecialColorControl() {}
    virtual PlayerConfigRecord& TheConfiguration() { return pcr; }
    virtual Handle MugPict() { return 0; }
    virtual void MugPict(Handle) {}
    virtual long MugSize() { return 0; }
    virtual long MugState() { return 0; }
    virtual void MugSize(long) {}
    virtual void MugState(long) {}
    virtual long WinFrame() { return 0; }
    virtual void ProtocolHandler(struct PacketInfo *thePacket) {}
    virtual void IncrementAskAgainTime(int) {}
private:
    CAvaraGame *itsGame;
    CAbstractPlayer *playa;
    std::deque<char> lineBuffer;
    Str255 str;
    PlayerConfigRecord pcr;
};

class TestNetManager : public CNetManager {
public:
    CPlayerManager* CreatePlayerManager(short id) {
        return new TestPlayerManager(itsGame);
    }
};

class TestApp : public CAvaraApp {
public:
    virtual bool DoCommand(int theCommand) {return false;}
    virtual void MessageLine(short index, short align) {}
    virtual void DrawUserInfoPart(short i, short partList) {}
    virtual void ParamLine(short index, short align, StringPtr param1, StringPtr param2) {}
    virtual void StartFrame(long frameNum) {}
    virtual void BrightBox(long frameNum, short position) {}
    virtual void LevelReset() {}
    virtual long Number(const std::string name) { return 0; }
    virtual OSErr LoadLevel(std::string set, OSType theLevel) { return noErr; }
    virtual void ComposeParamLine(StringPtr destStr, short index, StringPtr param1, StringPtr param2) {}
    virtual void NotifyUser() {}
    virtual json Get(const std::string name) {}
    virtual void Set(const std::string name, const std::string value) {}
    virtual void Set(const std::string name, long value) {}
    virtual void Set(const std::string name, json value) {}
    virtual CNetManager* GetNet() { return itsNet; }
    virtual void SetNet(CNetManager* net) { itsNet = net; }
    virtual SDL_Window* sdlWindow() { return 0; }
    virtual void StringLine(StringPtr theString, short align) {}
    virtual CAvaraGame* GetGame() { return 0; }
    virtual void Done() {}
    virtual void BroadcastCommand(int) {}
private:
    CNetManager *itsNet;
};

class TestGame : public CAvaraGame {
public:
    TestGame(int frameTime) : CAvaraGame(frameTime) {}
    virtual CNetManager* CreateNetManager() { return new TestNetManager(); }
    virtual CSoundHub* CreateSoundHub() { TestSoundHub *t = new TestSoundHub(); t->ISoundHub(64,64); return t;}
};

vector<Fixed> DropHector(int steps, int ticksPerStep, Fixed fromHeight, int frameTime) {
    TestApp app;
    TestGame game(frameTime);
    gCurrentGame = &game;
    InitParser();
    game.IAvaraGame(&app);
    game.EndScript();
    app.GetNet()->ChangeNet(kNullNet, "");
    CWalkerActor *hector = new CWalkerActor();
    hector->IAbstractActor();
    hector->BeginScript();
    hector->EndScript();
    game.itsNet->playerTable[0]->SetPlayer(hector);
    hector->itsManager = game.itsNet->playerTable[0];
    hector->location[0] = hector->location[2] = 0;
    hector->location[1] = fromHeight;
    hector->location[3] = FIX1;
    game.AddActor(hector);
    game.GameStart();
    vector<Fixed> altitudes;
    for (int i = 0; i < steps; i++) {
        game.nextScheduledFrame = 0;
        game.itsNet->activePlayersDistribution = 1;
        altitudes.push_back(hector->location[1]);
        for (int k = 0; k < ticksPerStep; k++) {
            game.GameTick();
        }
    }
    altitudes.push_back(hector->location[1]);
    return altitudes;
}

TEST(GRAVITY, HectorFalling) {
    vector<Fixed> at64ms = DropHector(50, 1, FIX(200), 64);
    vector<Fixed> at32ms = DropHector(50, 2, FIX(200), 32);
    vector<Fixed> at16ms = DropHector(50, 4, FIX(200), 16);
    ASSERT_EQ(at64ms.back(), 6126784) << "64ms simulation fell wrong amount";
    ASSERT_EQ(at64ms.size(), at32ms.size()) << "DropHector didn't do ticks right";
    for (int i = 0; i < at64ms.size(); i++) {
        double f64 = ToFloat(at64ms[i]);
        double f32 = ToFloat(at32ms[i]);
        double f16 = ToFloat(at32ms[i]);
        ASSERT_LT(abs(f64-f32)/f64, 0.01) << "not close enough after " << i << " ticks.";
        ASSERT_LT(abs(f64-f16)/f64, 0.01) << "not close enough after " << i << " ticks.";
    }
}

int main(int argc, char **argv) {
    CBSPPart::actuallyRender = false;
    nanogui::init();
    InitMatrix();
    ::testing::InitGoogleTest(&argc, argv);
    int r = RUN_ALL_TESTS();
    nanogui::shutdown();
    return r;
}