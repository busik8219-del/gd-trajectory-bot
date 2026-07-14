#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(PlayLayer) {
    // Включаем поддержку update-метода (выполняется каждый кадр игры)
    void update(float dt) {
        // Сначала вызываем оригинальный метод игры, чтобы она работала физически корректно
        PlayLayer::update(dt);

        // Получаем объект игрока (нашего кубика)
        auto player = m_player1;
        
        // Если кубик мертв, уровень пройден или объект игрока не существует — ничего не делаем
        if (!player || player->m_isDead || m_hasLevelComplete) return;

        // --- ЛОГИКА "ВИДЕНИЯ" ТРАЕКТОРИИ ---
        
        // Как далеко вперед мы смотрим (в кадрах). 20 кадров — оптимально для куба.
        const int lookAheadFrames = 20; 
        
        // Создаем виртуальную копию игрока для симуляции будущего пути
        auto playerDummy = player->createDummy();
        playerDummy->startMovement(lookAheadFrames); // Просчитываем физику вперед

        bool needsJump = false;

        // Проверяем каждую точку на предсказанной траектории
        for (int i = 0; i < lookAheadFrames; ++i) {
            CCPoint futurePos = playerDummy->getPositionAtFrame(i);
            
            // "Виртуально" перемещаем копию кубика в эту точку будущего
            playerDummy->setPosition(futurePos);
            
            // Спрашиваем у игры: если копия кубика окажется там, будет ли смерть?
            if (this->playerIsInsideHazard(playerDummy)) {
                needsJump = true; // Видим шип или препятствие на пути!
                break; // Дальше можно не смотреть, нужно реагировать прямо сейчас
            }
        }

        // --- УЛУЧШЕННОЕ ДЕЙСТВИЕ ДЛЯ КУБИКА ---

        // Проверяем, касается ли куб поверхности (с учетом обычной и перевернутой гравитации)
        bool canJump = player->m_isOnGround || (player->m_isUpsideDown ? player->m_isOnSlope : player->m_isOnGround);

        if (needsJump && canJump) {
            // Имитируем нажатие кнопки прыжка (Пробел / Тап)
            this->pushButton(PlayerButton::Jump); 
            log::info("AI [Куб]: Вижу шип впереди, прыгаю!");
        } else if (!needsJump && player->m_isHolding) {
            // Если опасности больше нет, но мы "зажали" кнопку — отпускаем её, 
            // чтобы кубик не прыгал бесконечно при приземлении
            this->releaseButton(PlayerButton::Jump);
        }
    }
};