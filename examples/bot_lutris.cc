#include <s2clientprotocol/raw.pb.h>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "sc2api/sc2_api.h"
#include "sc2api/sc2_common.h"
#include "sc2api/sc2_interfaces.h"
#include "sc2api/sc2_micro.h"
#include "sc2api/sc2_unit.h"
#include "sc2api/sc2_unit_filters.h"
#include "sc2api/typeids/sc2_5.0.12_typeenums.h"
#include "sc2lib/sc2_lib.h"
#include "sc2utils/sc2_manage_process.h"

class FooBot : public sc2::Agent {
public:
    uint32_t restarts_ = 0;
    uint32_t min = 22 * 10;
    bool trigger = false;
    sc2::Boxing box_one;

    FooBot() = default;

    void OnGameStart() final {
        std::cout << "Starting a new game (" << restarts_ << " restarts)" << std::endl;
        const sc2::ObservationInterface* observation = Observation();
        sc2::Units InitialCC =
            observation->GetUnits(sc2::Unit::Alliance::Self, sc2::IsUnit(sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER));
        float offset = 50;
        box_one = sc2::Boxing(InitialCC[0], offset);
    };

    void OnStep() final {
        uint32_t game_loop = Observation()->GetGameLoop();
        sc2::Point2D target = Observation()->GetGameInfo().enemy_start_locations[0];

        if (game_loop > min && !trigger) {
            sc2::Units units = Observation()->GetUnits(sc2::Unit::Alliance::Self);
            for (auto& it_unit : units) {
                sc2::Point2D point = it_unit->pos;
                if (sc2::Boxing::IsInBox(box_one, point)) {
                    Actions()->UnitCommand(it_unit, sc2::ABILITY_ID::SMART, target);
                }
            }
            trigger = true;
        }
    };

    void OnGameEnd() final {
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

    // Define exports
    // to get the <Identifier> numeral
    // lutris -l | grep "StarCraft II"

    // to get bash script
    // lutris -b game.sh <Identifier>
    // i.e.  lutris -b sc2_bash.sh 2

    // export WINEPREFIX="/home/ransak/Games/battlenet"
    // export WINE="/home/ransak/.local/share/lutris/runners/wine/wine-ge-8-26-x86_64/bin/wine"
    coordinator.SetLutris();
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
