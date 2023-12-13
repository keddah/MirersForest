#include "UserInterface.h"

#include "GameSingletons.h"

UserInterface::UserInterface(const Player& player) : rPlayer(player)
{
    txtRenderers.push_back(timeTxt);

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
    
    Vector2 ammoPos = Vector2(projBkgPos.x + barPadding, projBkgPos.y + barPadding);
    Vector2 ammoSize = Vector2(barWidth, 20);
    const ManualRenderer ammoBar = ManualRenderer(ammoPos, ammoSize);
    renderers.push_back(ammoBar);

    // Setting an index so that the bar is easier to get
    ammoIndex = renderers.size() - 1;
    renderers.back().SetRenderColour(seedColour);

    
    Vector2 cooldownPos = Vector2(projBkgPos.x + barPadding, projBkgPos.y + ammoSize.y + barPadding * 2);
    Vector2 cooldownSize = Vector2(barWidth, 10);
    const ManualRenderer cooldownBar = ManualRenderer(cooldownPos, cooldownSize);
    renderers.push_back(cooldownBar);

    // Setting an index so that the bar is easier to get
    cooldownIndex = renderers.size() - 1;
    renderers.back().SetRenderColour({255,255,255,255});

    // The text for the projectile.
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
    timeTxt.SetText("builders");

    const float ammoPercent = rPlayer.GetAmmo() / rPlayer.GetMaxAmmo();
    renderers[ammoIndex].SetDrawSize({ammoPercent * maxBarWidth, renderers[ammoIndex].GetDrawSize().y});

    const float cooldownPercent = rPlayer.GetShootTimer() / rPlayer.GetWeaponCooldown();
    renderers[cooldownIndex].SetDrawSize({cooldownPercent * maxBarWidth, renderers[cooldownIndex].GetDrawSize().y});
}

void UserInterface::LevelTime(float deltaTime)
{
    seconds = floor(seconds + deltaTime);

    if(static_cast<int>(seconds) % 60 == 0)
    {
        minutes++;
        seconds = 0;
    }

    
}
