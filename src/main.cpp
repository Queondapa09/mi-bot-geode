#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <algorithm>
#include <map>
#include <string>

using namespace geode::prelude;

class $modify(BotPlayLayer, PlayLayer) {
    void setupHasCompleted() {
        PlayLayer::setupHasCompleted();
        this->scanLevel();
    }

    void scanLevel() {
        std::map<int, int> counts;
        float maxX = 0.f;
        int total = 0;

        for (auto obj : CCArrayExt<GameObject*>(m_objects)) {
            counts[static_cast<int>(obj->m_objectType)]++;
            maxX = std::max(maxX, obj->getPositionX());
            total++;
        }

        int hazards = counts[static_cast<int>(GameObjectType::Hazard)];
        int solids = counts[static_cast<int>(GameObjectType::Solid)];

        std::string name = m_level->m_levelName;
        log::info("Nivel: {}", name);
        log::info("Objetos: {} | Hazards: {} | Bloques: {} | Largo (x): {}",
                  total, hazards, solids, maxX);

        Notification::create(
            fmt::format("{}: {} objetos, {} hazards", name, total, hazards),
            NotificationIcon::Success
        )->show();
    }
};
