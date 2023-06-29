#include <iostream>
#include <vector>

#include "sc2api/sc2_api.h"
#include "sc2lib/sc2_lib.h"
#include "sc2utils/sc2_manage_process.h"

class FooBot : public sc2::Agent {
public:
    uint32_t restarts_;

    FooBot() : restarts_(0) {
    }

    virtual void OnGameStart() final {
        std::cout << "Starting a new game (" << restarts_ << " restarts)" << std::endl;
    };

    virtual void OnStep() final {
        uint32_t game_loop = Observation()->GetGameLoop();

        if (game_loop % 100 == 0) {
            sc2::Units units = Observation()->GetUnits(sc2::Unit::Alliance::Self);
            for (auto& it_unit : units) {
                sc2::Point2D target = sc2::FindRandomLocation(Observation()->GetGameInfo());
                Actions()->UnitCommand(it_unit, sc2::ABILITY_ID::SMART, target);
            }
        }
    };

    virtual void OnGameEnd() final {
        ++restarts_;
        std::cout << "Game ended after: " << Observation()->GetGameLoop() << " loops " << std::endl;
    };

private:
};

//*************************************************************************************************
int main(int argc, char* argv[]) {
    sc2::Coordinator coordinator;
    if (!coordinator.LoadSettings(argc, argv)) {
        return 1;
    }

    // Add the custom bot, it will control the players.
    FooBot bot;

    // Define
    const std::string wine = "/home/leon/.local/share/lutris/runners/wine/wine-ge-8-26-x86_64/bin/wine64";
    //    const std::string wine = "/usr/bin/wine"; // 

    // {"start","/d","/path/to/Support64/","/unix","/path/to/SC2Switcher"}
    const std::vector<std::string> runner = {
        "start", "/d", "/home/leon/Games/battlenet/drive_c/Program Files (x86)/StarCraft II/Support64/", "/unix",
        "/home/leon/Games/battlenet/drive_c/Program Files (x86)/StarCraft II/Support64/SC2Switcher_x64.exe"};
    coordinator.SetLutris(wine, runner);

    coordinator.SetParticipants({CreateParticipant(sc2::Race::Terran, &bot), CreateComputer(sc2::Race::Terran)});

    // Start the game.
    coordinator.LaunchStarcraft();

    // Step forward the game simulation.
    bool do_break = false;
    while (!do_break) {
        coordinator.StartGame("Ladder2017Season1/AbyssalReefLE.SC2Map");
        while (coordinator.Update() && !do_break) {
            if (sc2::PollKeyPress()) {
                do_break = true;
            }
        }
    }

    return 0;
}
