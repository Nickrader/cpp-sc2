#include <vector>

#include "gtest/gtest.h"
#include "sc2api/sc2_unit.h"
#include "sc2api/sc2_unit_filters.h"

namespace {

TEST(UnitFilters, IsUnitTest) {
    sc2::Unit Type_CC;
    Type_CC.unit_type = sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER;
    sc2::IsUnit CC(sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER);
    sc2::Unit Empty;

    ASSERT_TRUE(CC(Type_CC)) << "Unit Type: " << Type_CC.unit_type;
    ASSERT_FALSE(CC(Empty)) << "Unit Type: " << Type_CC.unit_type;
}

TEST(UnitFilters, IsUnitsTest) {
    sc2::Unit Type_CC;
    Type_CC.unit_type = sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER;
    sc2::Unit Type_Marine;
    Type_Marine.unit_type = sc2::UNIT_TYPEID::TERRAN_MARINE;
    std::vector<sc2::UNIT_TYPEID> RaxUnits = {sc2::UNIT_TYPEID::TERRAN_MARINE, sc2::UNIT_TYPEID::TERRAN_MARAUDER,
                                              sc2::UNIT_TYPEID::TERRAN_GHOST};
    sc2::IsUnits Rax(RaxUnits);

    ASSERT_FALSE(Rax(Type_CC));
    ASSERT_TRUE(Rax(Type_Marine));
}

TEST(UnitFilters, IsTownHallTest) {
    sc2::Unit EmptyUnit;
    sc2::Unit MutableUnit;
    std::vector<sc2::UNIT_TYPEID> types = {sc2::UNIT_TYPEID::PROTOSS_NEXUS,
                                           sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER,
                                           sc2::UNIT_TYPEID::TERRAN_COMMANDCENTERFLYING,
                                           sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND,
                                           sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMANDFLYING,
                                           sc2::UNIT_TYPEID::TERRAN_PLANETARYFORTRESS,
                                           sc2::UNIT_TYPEID::ZERG_HATCHERY,
                                           sc2::UNIT_TYPEID::ZERG_HIVE,
                                           sc2::UNIT_TYPEID::ZERG_LAIR};

    ASSERT_FALSE(sc2::IsTownHall()(EmptyUnit));
    for (auto& type : types) {
        MutableUnit.unit_type = type;
        ASSERT_TRUE(sc2::IsTownHall()(MutableUnit));
    }
}

TEST(UnitFilters, IsMineralPatchTest) {
    sc2::Unit EmptyUnit;
    sc2::Unit MutableUnit;
    std::vector<sc2::UNIT_TYPEID> types = {sc2::UNIT_TYPEID::NEUTRAL_BATTLESTATIONMINERALFIELD750,
                                           sc2::UNIT_TYPEID::NEUTRAL_BATTLESTATIONMINERALFIELD,
                                           sc2::UNIT_TYPEID::NEUTRAL_LABMINERALFIELD750,
                                           sc2::UNIT_TYPEID::NEUTRAL_LABMINERALFIELD,
                                           sc2::UNIT_TYPEID::NEUTRAL_MINERALFIELD750,
                                           sc2::UNIT_TYPEID::NEUTRAL_MINERALFIELD,
                                           sc2::UNIT_TYPEID::NEUTRAL_PURIFIERMINERALFIELD750,
                                           sc2::UNIT_TYPEID::NEUTRAL_PURIFIERMINERALFIELD,
                                           sc2::UNIT_TYPEID::NEUTRAL_PURIFIERRICHMINERALFIELD750,
                                           sc2::UNIT_TYPEID::NEUTRAL_PURIFIERRICHMINERALFIELD,
                                           sc2::UNIT_TYPEID::NEUTRAL_RICHMINERALFIELD750,
                                           sc2::UNIT_TYPEID::NEUTRAL_RICHMINERALFIELD};

    ASSERT_FALSE(sc2::IsMineralPatch()(EmptyUnit));
    for (auto& type : types) {
        MutableUnit.unit_type = type;
        ASSERT_TRUE(sc2::IsMineralPatch()(MutableUnit));
    }
}

TEST(UnitFilters, IsVisibleMineralPatchTest) {
    sc2::Unit EmptyUnit;
    EmptyUnit.mineral_contents = 0;
    sc2::Unit MutableUnit;
    std::vector<sc2::UNIT_TYPEID> types = {sc2::UNIT_TYPEID::NEUTRAL_BATTLESTATIONMINERALFIELD750,
                                           sc2::UNIT_TYPEID::NEUTRAL_BATTLESTATIONMINERALFIELD,
                                           sc2::UNIT_TYPEID::NEUTRAL_LABMINERALFIELD750,
                                           sc2::UNIT_TYPEID::NEUTRAL_LABMINERALFIELD,
                                           sc2::UNIT_TYPEID::NEUTRAL_MINERALFIELD750,
                                           sc2::UNIT_TYPEID::NEUTRAL_MINERALFIELD,
                                           sc2::UNIT_TYPEID::NEUTRAL_PURIFIERMINERALFIELD750,
                                           sc2::UNIT_TYPEID::NEUTRAL_PURIFIERMINERALFIELD,
                                           sc2::UNIT_TYPEID::NEUTRAL_PURIFIERRICHMINERALFIELD750,
                                           sc2::UNIT_TYPEID::NEUTRAL_PURIFIERRICHMINERALFIELD,
                                           sc2::UNIT_TYPEID::NEUTRAL_RICHMINERALFIELD750,
                                           sc2::UNIT_TYPEID::NEUTRAL_RICHMINERALFIELD};

    ASSERT_FALSE(sc2::IsVisibleMineralPatch()(EmptyUnit));
    for (auto& type : types) {
        MutableUnit.unit_type = type;
        MutableUnit.mineral_contents = 42;
        ASSERT_TRUE(sc2::IsVisibleMineralPatch()(MutableUnit));
    }
}

TEST(UnitFilters, IsGeyserTest) {
    sc2::Unit EmptyUnit;
    sc2::Unit MutableUnit;
    std::vector<sc2::UNIT_TYPEID> types = {
        sc2::UNIT_TYPEID::NEUTRAL_VESPENEGEYSER,         sc2::UNIT_TYPEID::NEUTRAL_PROTOSSVESPENEGEYSER,
        sc2::UNIT_TYPEID::NEUTRAL_SPACEPLATFORMGEYSER,   sc2::UNIT_TYPEID::NEUTRAL_PURIFIERVESPENEGEYSER,
        sc2::UNIT_TYPEID::NEUTRAL_SHAKURASVESPENEGEYSER, sc2::UNIT_TYPEID::NEUTRAL_RICHVESPENEGEYSER};

    ASSERT_FALSE(sc2::IsGeyser()(EmptyUnit));
    for (auto& type : types) {
        MutableUnit.unit_type = type;
        ASSERT_TRUE(sc2::IsGeyser()(MutableUnit));
    }
}

TEST(UnitFilters, IsVisibleGeyserTest) {
    sc2::Unit EmptyUnit;
    EmptyUnit.vespene_contents = 0;
    sc2::Unit MutableUnit;
    std::vector<sc2::UNIT_TYPEID> types = {
        sc2::UNIT_TYPEID::NEUTRAL_VESPENEGEYSER,         sc2::UNIT_TYPEID::NEUTRAL_PROTOSSVESPENEGEYSER,
        sc2::UNIT_TYPEID::NEUTRAL_SPACEPLATFORMGEYSER,   sc2::UNIT_TYPEID::NEUTRAL_PURIFIERVESPENEGEYSER,
        sc2::UNIT_TYPEID::NEUTRAL_SHAKURASVESPENEGEYSER, sc2::UNIT_TYPEID::NEUTRAL_RICHVESPENEGEYSER};

    ASSERT_FALSE(sc2::IsVisibleGeyser()(EmptyUnit)) << "Vespene Contents: " << EmptyUnit.vespene_contents;
    for (auto& type : types) {
        MutableUnit.unit_type = type;
        MutableUnit.vespene_contents = 42;
        ASSERT_TRUE(sc2::IsGeyser()(MutableUnit));
    }
}

TEST(UnitFilters, IsBuildingTest) {
    sc2::Unit EmptyUnit;
    sc2::Unit MutableUnit;
    std::vector<sc2::UNIT_TYPEID> types = {
        // Terran
        sc2::UNIT_TYPEID::TERRAN_ARMORY, sc2::UNIT_TYPEID::TERRAN_BARRACKS, sc2::UNIT_TYPEID::TERRAN_BARRACKSFLYING,
        sc2::UNIT_TYPEID::TERRAN_BARRACKSREACTOR, sc2::UNIT_TYPEID::TERRAN_BARRACKSTECHLAB,
        sc2::UNIT_TYPEID::TERRAN_BUNKER, sc2::UNIT_TYPEID::TERRAN_COMMANDCENTER,
        sc2::UNIT_TYPEID::TERRAN_COMMANDCENTERFLYING, sc2::UNIT_TYPEID::TERRAN_ENGINEERINGBAY,
        sc2::UNIT_TYPEID::TERRAN_FACTORY, sc2::UNIT_TYPEID::TERRAN_FACTORYFLYING,
        sc2::UNIT_TYPEID::TERRAN_FACTORYREACTOR, sc2::UNIT_TYPEID::TERRAN_FACTORYTECHLAB,
        sc2::UNIT_TYPEID::TERRAN_FUSIONCORE, sc2::UNIT_TYPEID::TERRAN_GHOSTACADEMY,
        sc2::UNIT_TYPEID::TERRAN_MISSILETURRET, sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMAND,
        sc2::UNIT_TYPEID::TERRAN_ORBITALCOMMANDFLYING, sc2::UNIT_TYPEID::TERRAN_PLANETARYFORTRESS,
        sc2::UNIT_TYPEID::TERRAN_REFINERY, sc2::UNIT_TYPEID::TERRAN_SENSORTOWER, sc2::UNIT_TYPEID::TERRAN_STARPORT,
        sc2::UNIT_TYPEID::TERRAN_STARPORTFLYING, sc2::UNIT_TYPEID::TERRAN_STARPORTREACTOR,
        sc2::UNIT_TYPEID::TERRAN_STARPORTTECHLAB, sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOT,
        sc2::UNIT_TYPEID::TERRAN_SUPPLYDEPOTLOWERED, sc2::UNIT_TYPEID::TERRAN_REACTOR, sc2::UNIT_TYPEID::TERRAN_TECHLAB,

        // Zerg
        sc2::UNIT_TYPEID::ZERG_BANELINGNEST, sc2::UNIT_TYPEID::ZERG_CREEPTUMOR,
        sc2::UNIT_TYPEID::ZERG_CREEPTUMORBURROWED, sc2::UNIT_TYPEID::ZERG_CREEPTUMORQUEEN,
        sc2::UNIT_TYPEID::ZERG_EVOLUTIONCHAMBER, sc2::UNIT_TYPEID::ZERG_EXTRACTOR, sc2::UNIT_TYPEID::ZERG_GREATERSPIRE,
        sc2::UNIT_TYPEID::ZERG_HATCHERY, sc2::UNIT_TYPEID::ZERG_HIVE, sc2::UNIT_TYPEID::ZERG_HYDRALISKDEN,
        sc2::UNIT_TYPEID::ZERG_INFESTATIONPIT, sc2::UNIT_TYPEID::ZERG_LAIR, sc2::UNIT_TYPEID::ZERG_LURKERDENMP,
        sc2::UNIT_TYPEID::ZERG_NYDUSCANAL, sc2::UNIT_TYPEID::ZERG_NYDUSNETWORK, sc2::UNIT_TYPEID::ZERG_ROACHWARREN,
        sc2::UNIT_TYPEID::ZERG_SPAWNINGPOOL, sc2::UNIT_TYPEID::ZERG_SPINECRAWLER,
        sc2::UNIT_TYPEID::ZERG_SPINECRAWLERUPROOTED, sc2::UNIT_TYPEID::ZERG_SPIRE, sc2::UNIT_TYPEID::ZERG_SPORECRAWLER,
        sc2::UNIT_TYPEID::ZERG_SPORECRAWLERUPROOTED, sc2::UNIT_TYPEID::ZERG_ULTRALISKCAVERN,

        // Protoss
        sc2::UNIT_TYPEID::PROTOSS_ASSIMILATOR, sc2::UNIT_TYPEID::PROTOSS_CYBERNETICSCORE,
        sc2::UNIT_TYPEID::PROTOSS_DARKSHRINE, sc2::UNIT_TYPEID::PROTOSS_FLEETBEACON, sc2::UNIT_TYPEID::PROTOSS_FORGE,
        sc2::UNIT_TYPEID::PROTOSS_GATEWAY, sc2::UNIT_TYPEID::PROTOSS_NEXUS, sc2::UNIT_TYPEID::PROTOSS_PHOTONCANNON,
        sc2::UNIT_TYPEID::PROTOSS_PYLON, sc2::UNIT_TYPEID::PROTOSS_PYLONOVERCHARGED,
        sc2::UNIT_TYPEID::PROTOSS_ROBOTICSBAY, sc2::UNIT_TYPEID::PROTOSS_ROBOTICSFACILITY,
        sc2::UNIT_TYPEID::PROTOSS_STARGATE, sc2::UNIT_TYPEID::PROTOSS_TEMPLARARCHIVE,
        sc2::UNIT_TYPEID::PROTOSS_TWILIGHTCOUNCIL, sc2::UNIT_TYPEID::PROTOSS_WARPGATE,
        sc2::UNIT_TYPEID::PROTOSS_SHIELDBATTERY};

    ASSERT_FALSE(sc2::IsBuilding()(EmptyUnit));
    for (auto& type : types) {
        MutableUnit.unit_type = type;
        ASSERT_TRUE(sc2::IsBuilding()(MutableUnit));
    }
}

TEST(UnitFilters, IsWorkerTest) {
    sc2::Unit EmptyUnit;
    sc2::Unit MutableUnit;
    std::vector<sc2::UNIT_TYPEID> types = {sc2::UNIT_TYPEID::TERRAN_SCV, sc2::UNIT_TYPEID::ZERG_DRONE,
                                           sc2::UNIT_TYPEID::PROTOSS_PROBE};

    ASSERT_FALSE(sc2::IsWorker()(EmptyUnit));
    for (auto& type : types) {
        MutableUnit.unit_type = type;
        ASSERT_TRUE(sc2::IsWorker()(MutableUnit));
    }
}

TEST(UnitFilters, IsVisibleTest) {
    sc2::Unit EmptyUnit;
    sc2::Unit MutableUnit;
    MutableUnit.display_type = sc2::Unit::DisplayType::Visible;

    ASSERT_FALSE(sc2::IsVisible()(EmptyUnit));
    ASSERT_TRUE(sc2::IsVisible()(MutableUnit));
    for (int i = 2; i <= 4; ++i) {  // check: Snapshot, Hidden, Placeholder
        MutableUnit.display_type = static_cast<sc2::Unit::DisplayType>(i);
        ASSERT_FALSE(sc2::IsVisible()(MutableUnit));
    }
}

TEST(UnitFilters, IsCarryingMineralsTest) {
    sc2::Unit EmptyUnit;
    sc2::Unit MutableUnit;
    std::vector<sc2::BUFF_ID> types = {sc2::BUFF_ID::CARRYMINERALFIELDMINERALS,
                                       sc2::BUFF_ID::CARRYHIGHYIELDMINERALFIELDMINERALS};

    ASSERT_FALSE(sc2::IsCarryingMinerals(EmptyUnit));
    for (auto& type : types) {
        MutableUnit.buffs.emplace_back(type);
        ASSERT_TRUE(sc2::IsCarryingMinerals(MutableUnit));
        MutableUnit.buffs.pop_back();
        ASSERT_FALSE(sc2::IsCarryingMinerals(MutableUnit));
    };
}

TEST(UnitFilters, IsCarryingVespene) {
    sc2::Unit EmptyUnit;
    sc2::Unit MutableUnit;
    std::vector<sc2::BUFF_ID> types = {sc2::BUFF_ID::CARRYHARVESTABLEVESPENEGEYSERGAS,
                                       sc2::BUFF_ID::CARRYHARVESTABLEVESPENEGEYSERGASPROTOSS,
                                       sc2::BUFF_ID::CARRYHARVESTABLEVESPENEGEYSERGASZERG};

    ASSERT_FALSE(sc2::IsCarryingVespene(EmptyUnit));
    for (auto& type : types) {
        MutableUnit.buffs.emplace_back(type);
        ASSERT_TRUE(sc2::IsCarryingVespene(MutableUnit));
        MutableUnit.buffs.pop_back();
        ASSERT_FALSE(sc2::IsCarryingVespene(MutableUnit));
    };
}

}  // namespace

//--------------------------------------------------
// Maybe should initialize sc2::Unit with default values in API
// Can cause test to fail unless expliciltly set to 0
// visible minerals/vespense based on mineral contents > 0
