#include "UserInterface.h"

#include <string>

#include "GameSingletons.h"

UserInterface::UserInterface(const Player& player) : rPlayer(player)
{
    // Initialise the SDL text
    const int success = TTF_Init();
    if(success != 0)
    {
        print("failed init")
        return;
    }
    
    CreateUI();
}

void UserInterface::Update(float deltaTime)
{
    LevelTime(deltaTime);
    CheckPlayerState();
    UpdateBar();
}

void UserInterface::Draw()
{
    for (auto& renderer : renderers) renderer.Draw();
    for (auto& renderer : txtRenderers) renderer.Draw();
}

void UserInterface::CreateUI()
{
    // Background for the health.
    const Vector2 bkgPos = Vector2(10, 10);
    const Vector2 bkgSize = Vector2(250, 85);
    
    const ManualRenderer bkg = ManualRenderer(bkgPos, bkgSize);
    renderers.push_back(bkg);
    renderers.back().SetRenderColour(bkgColour);
    heartBkgIndex = renderers.size() -1;
    
    //\\//\\//\\//\\// Hearts //\\//\\//\\//\\//
    constexpr float  heartPadding = 5;
    constexpr float heartSpacing = 10;
    Vector2 heartPos = {bkgPos.x + heartPadding, bkgPos.y + heartPadding };
    for(short i = 0; i < rPlayer.GetHealth(); i++)
    {
        const ManualRenderer fullHeart = ManualRenderer("Sprites/UI/fullHeart.png", heartPos);
        renderers.push_back(fullHeart);

        // If it's the first iteration, set the index
        if(i == 0) fullHeartIndex = renderers.size() - 1;
        
        heartPos.x += fullHeart.GetDrawSize().x + heartSpacing;
    }

    heartPos = {bkgPos.x + heartPadding, bkgPos.y + heartPadding };
    for(short i = 0; i < rPlayer.GetHealth(); i++)
    {
        const ManualRenderer emptyHeart = ManualRenderer("Sprites/UI/emptyHeart.png", heartPos);
        renderers.push_back(emptyHeart);
        renderers.back().SetVisibility(false);
        
        // If it's the first iteration, set the index
        if(i == 0) emptyHeartIndex = renderers.size() - 1;
        
        heartPos.x += emptyHeart.GetDrawSize().x + heartSpacing;
    }

    // The background for the selected projectile.
    const Vector2 projBkgSize = Vector2(600, 80);
    const Vector2 projBkgPos = Vector2((GameWindow::GetWindowWidth() / 2) - projBkgSize.x / 2, 10);

    const ManualRenderer projBkg = ManualRenderer(projBkgPos, projBkgSize);
    renderers.push_back(projBkg);
    renderers.back().SetRenderColour(bkgColour);

    // The cooldown bar for the projectile
    constexpr float barPadding = 10;
    
    // Changing the size of the background also changes the size of the bar...
    maxBarWidth = projBkgSize.x - barPadding * 2;
    barWidth = maxBarWidth;
    
    const Vector2 ammoPos = Vector2(projBkgPos.x + barPadding, projBkgPos.y + barPadding);
    const Vector2 ammoSize = Vector2(barWidth, 20);
    const ManualRenderer ammoBar = ManualRenderer(ammoPos, ammoSize);
    renderers.push_back(ammoBar);

    // Setting an index so that the bar is easier to get
    ammoIndex = renderers.size() - 1;
    renderers.back().SetRenderColour(seedColour);

    
    const Vector2 cooldownPos = Vector2(projBkgPos.x + barPadding, projBkgPos.y + ammoSize.y + barPadding * 2);
    const Vector2 cooldownSize = Vector2(barWidth, 10);
    const ManualRenderer cooldownBar = ManualRenderer(cooldownPos, cooldownSize);
    renderers.push_back(cooldownBar);

    // Setting an index so that the bar is easier to get
    cooldownIndex = renderers.size() - 1;
    renderers.back().SetRenderColour({255,255,255,255});

    // The text for the projectile.

    // Background for the timer
    constexpr float timeBkgPadding = 5;
    const Vector2 timerBkgSize = Vector2(200, 50);
    const Vector2 timerBkgPos = Vector2(GameWindow::GetWindowWidth() - timerBkgSize.x - timeBkgPadding, 10);
    const ManualRenderer timeBkg = ManualRenderer(timerBkgPos, timerBkgSize);
    renderers.push_back(timeBkg);
    renderers.back().SetRenderColour(bkgColour);
    
    // The actual timer
    constexpr float timePadding = 5;
    const Vector2 timerPos = Vector2(timerBkgPos.x + timePadding, timerBkgPos.y + timePadding);
    TextRenderer timer = TextRenderer(font_oxygen, time, timeSize, timerPos);
    txtRenderers.push_back(timer);
    txtRenderers.back().SetRenderColour({120,200,200,255});
    timerIndex = txtRenderers.size() - 1;
}

void UserInterface::CheckPlayerState()
{
    switch (rPlayer.GetHealth())
    {
        case 0:
            for(int i = 0; i < 3; i++)
            {
                // Hide all the full hearts ... show the empty ones
                renderers[fullHeartIndex + i].SetVisibility(false);
                renderers[emptyHeartIndex + i].SetVisibility(true);
            }

            renderers[heartBkgIndex].SetRenderColour(dangerColour);
            break;

        case 1:
            // 1st Heart
            renderers[fullHeartIndex].SetVisibility(true);
            renderers[emptyHeartIndex].SetVisibility(false);

            // 2nd Heart
            renderers[fullHeartIndex + 1].SetVisibility(false);
            renderers[emptyHeartIndex + 1].SetVisibility(true);

            // 3rd Heart
            renderers[fullHeartIndex + 2].SetVisibility(false);
            renderers[emptyHeartIndex + 2].SetVisibility(true);
        
            renderers[heartBkgIndex].SetRenderColour(dangerColour);
            break;

        case 2:
            // 1st Heart
            renderers[fullHeartIndex].SetVisibility(true);
            renderers[emptyHeartIndex].SetVisibility(false);

            // 2nd Heart
            renderers[fullHeartIndex + 1].SetVisibility(true);
            renderers[emptyHeartIndex + 1].SetVisibility(false);

            // 3rd Heart
            renderers[fullHeartIndex + 2].SetVisibility(false);
            renderers[emptyHeartIndex + 2].SetVisibility(true);

            renderers[heartBkgIndex].SetRenderColour(bkgColour);
            break;

        case 3:
            for(int i = 0; i < 3; i++)
            {
                // Show all the full hearts ... hide the empty ones
                renderers[fullHeartIndex + i].SetVisibility(true);
                renderers[emptyHeartIndex + i].SetVisibility(false);
            }
            renderers[heartBkgIndex].SetRenderColour(bkgColour);
            break;
    }
    
    switch (rPlayer.GetType())
    {
        case Projectile::EWeaponTypes::Seed:
            renderers[ammoIndex].SetRenderColour(seedColour);
            break;
            
        case Projectile::EWeaponTypes::Petal:
            renderers[ammoIndex].SetRenderColour(petalColour);
            break;
        
        case Projectile::EWeaponTypes::Sun:
            renderers[ammoIndex].SetRenderColour(sunColour);
            break;
    }
}

void UserInterface::UpdateBar()
{
    const float ammoPercent = rPlayer.GetAmmo() / rPlayer.GetMaxAmmo();
    renderers[ammoIndex].SetDrawSize({ammoPercent * maxBarWidth, renderers[ammoIndex].GetDrawSize().y});

    const float cooldownPercent = rPlayer.GetShootTimer() / rPlayer.GetWeaponCooldown();
    renderers[cooldownIndex].SetDrawSize({cooldownPercent * maxBarWidth, renderers[cooldownIndex].GetDrawSize().y});
}

void UserInterface::LevelTime(float deltaTime)
{
    seconds = seconds + deltaTime;

    if(seconds > 60)
    {
        minutes++;
        seconds = 0;
    }

    time = (minutes < 10? "0" + std::to_string(minutes) : std::to_string((minutes))) + ":" + (seconds < 10? "0" + std::to_string(static_cast<int>(seconds)) : std::to_string((static_cast<int>(seconds))));
    txtRenderers[timerIndex].SetText(time);
}
