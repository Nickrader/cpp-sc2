#include <sc2api/sc2_api.h>
#include <sc2api/sc2_unit_filters.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "../src/sc2api/sc2_game_settings.cc"

using namespace sc2;
// What other maps have mineral paths??? Goldenwall, ...

//const char* map = kMapGoldenWall;
const char* map = kMapSentinel;


class Bot : public Agent {
 public:
  bool mined_removable_once = false;

  virtual void OnGameStart() final {
    Actions()->SendActions(); // putting in here to attempt repro, 10 runs debug no crash.  Issue #37
    std::stringstream strs;
    std::string outfile = "../data/neutral_units.txt";
    std::ofstream ofs(outfile, std::ios_base::app);

    Units aa = Observation()->GetUnits(Unit::Alliance::Neutral);
    std::sort(aa.begin(), aa.end());
    std::vector<std::string> bb;
    for (auto elem : aa) {
      bb.push_back(UnitTypeToName(elem->unit_type));
    }
    std::vector<std::string> ss;
    std::sort(bb.begin(), bb.end());
    std::unique_copy(bb.begin(), bb.end(), std::back_inserter(ss));
    for (auto& elem : ss) {
      std::cout << elem << '\n';
      strs << elem << '\n';
    }

    ofs << strs.rdbuf();
    ofs.close();
  }

  virtual void OnStep() final {
    // std::cout << Observation()->GetGameLoop() << std::endl;
    if (!mined_removable_once) {
      MineRemovable();
    }
  }

  void MineRemovable() {
    const Unit* blocking_mineral = nullptr;
    Units minerals = Observation()->GetUnits(Unit::Alliance::Neutral,
                                             IsBlockingMineralPatch());
    blocking_mineral = minerals.begin().operator*();
    Units workers = Observation()->GetUnits(sc2::IsWorker());
    auto it = workers.begin();
    auto cheeky_scv = *it;
    Actions()->UnitCommand(cheeky_scv, sc2::ABILITY_ID::SMART,
                           blocking_mineral);
    std::cout << blocking_mineral->mineral_contents;
    mined_removable_once = true;
  }
};

int main(int argc, char* argv[]) {
  Coordinator coordinator;
  coordinator.LoadSettings(argc, argv);

  Bot bot;
  coordinator.SetParticipants(
      {CreateParticipant(Race::Terran, &bot), CreateComputer(Race::Zerg)});

  coordinator.LaunchStarcraft();
  coordinator.StartGame(map);

  while (coordinator.Update()) {
  }

  return 0;
}
