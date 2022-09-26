#include <sc2api/sc2_api.h>

#include <iostream>

using namespace sc2;

const char* map_path = kMapBelShirVestigeLE;

class Bot : public Agent {
  void OnGameStart() final {
    std::cout << "Game Started: \n";
    std::cout << "Map: " << map_path << '\n';
    const ObservationInterface* observation = Observation();
    std::initializer_list<Filter> filters{
        IsGeyser(), IsWorker(), IsVisibleMineralPatch()};

    Units bravo_team = observation->GetUnitsAllOf(filters);
    std::cout << "Result AllOf: \n";
    for (auto a : bravo_team) {
        std::cout << UnitTypeToName(a->unit_type) << '\n';
    }

    std::cout << "\n\n";

    Units charlie_team = observation->GetUnitsNoneOf(filters);
    std::cout << "Result NoneOf: \n";
    for (auto a : charlie_team) {
        std::cout << UnitTypeToName(a->unit_type) << '\n';
    }
  }
};

int main(int argc, char* argv[]) {
  Coordinator coordinator;
  coordinator.LoadSettings(argc, argv);

  Bot bot;
  coordinator.SetParticipants(
      {CreateParticipant(Race::Terran, &bot), CreateComputer(Race::Protoss)});

  coordinator.LaunchStarcraft();
  coordinator.StartGame(map_path);

  while (coordinator.Update()) {
  };
  return 0;
}
