#include "UserInterface.h"

#include <string>

#include "GameSingletons.h"

UserInterface::UserInterface(Player& player) : rPlayer(player)
{
    // Initialise the SDL text
    const int success = TTF_Init();
    if(success != 0)
    {
        print("failed init")
        return;
    }
    
    CreateUI();

    pauseScreen.SetVisibility(false);
    deathScreen.SetVisibility(false);

    Button resume = Button(0,0,450,100, {99,163,92,120});
    Button restart = Button(0,0,450,100, {165,152,90,120});
    Button quit = Button(0,0,250,100, {175,130,80,120});

    resume.SetPosition(Vector2(GameWindow::GetWindowWidth() / 2 - resume.GetRect().w / 2, 340));
    restart.SetPosition(Vector2(GameWindow::GetWindowWidth() / 2 - restart.GetRect().w / 2, 500));
    quit.SetPosition(Vector2(GameWindow::GetWindowWidth() / 2 - quit.GetRect().w / 2, 680));

    buttons.push_back(resume);
    buttons.push_back(restart);
    buttons.push_back(quit);
}

void UserInterface::Update(float deltaTime)
{
    LevelTime(deltaTime);
    CheckPlayerState();
    UpdateBar();
    
    ButtonPresses();
    Respawning(deltaTime);

    
    if(rPlayer.IsPaused())
    {
        pauseScreen.SetVisibility(true);
        renderers[projBkgIndex].SetVisibility(false);
        renderers[heartBkgIndex].SetVisibility(false);
        renderers[cooldownIndex].SetVisibility(false);
        renderers[ammoIndex].SetVisibility(false);
        txtRenderers[projIndex].SetVisibility(false);

        for(auto& btn: buttons) btn.Show();

        for(int i = 0; i < 3; i++)
        {
            // Hide all the full hearts ... show the empty ones
            renderers[fullHeartIndex + i].SetVisibility(false);
            renderers[emptyHeartIndex + i].SetVisibility(false);
        }
        
        timerOn = false;
    }
    else
    {
        pauseScreen.SetVisibility(false);
        renderers[projBkgIndex].SetVisibility(true);
        renderers[cooldownIndex].SetVisibility(true);
        renderers[ammoIndex].SetVisibility(true);
        renderers[heartBkgIndex].SetVisibility(true);
        txtRenderers[projIndex].SetVisibility(true);

        for(auto& btn: buttons) btn.Hide();
        
        // Start the timer once the player starts moving or if the timer has already started and unpaused
        if(rPlayer.GetVelocity().Magnitude() > 5 ^ seconds > 0) timerOn = true;
    }
}

void UserInterface::Draw()
{
    for (auto& renderer : renderers) renderer.Draw();
    for (auto& renderer : txtRenderers) renderer.Draw();
    for(auto& button : buttons) button.Draw();
    
    pauseScreen.Draw();
    deathScreen.Draw();
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
    projBkgIndex = renderers.size() - 1;

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
    constexpr float projPadding = 30;
    const Vector2 projPos = Vector2(projBkgPos.x + projBkgSize.x/2 - projPadding, projBkgPos.y + projBkgSize.y - 30);
    TextRenderer proj = TextRenderer(font_quicksand, currentProjectile, projTxtSize, projPos);
    txtRenderers.push_back(proj);
    txtRenderers.back().SetRenderColour({120,200,200,255});
    projIndex = txtRenderers.size() - 1;
        
    
    // Background for the timer
    constexpr float timeBkgPadding = 5;
    const Vector2 timerBkgSize = Vector2(100, 50);
    const Vector2 timerBkgPos = Vector2(GameWindow::GetWindowWidth() - timerBkgSize.x - timeBkgPadding, 10);
    const ManualRenderer timeBkg = ManualRenderer(timerBkgPos, timerBkgSize);
    renderers.push_back(timeBkg);
    renderers.back().SetRenderColour(bkgColour);
    
    // The actual timer
    constexpr float timePadding = 2.5f;
    const Vector2 timerPos = Vector2(timerBkgPos.x + timePadding, timerBkgPos.y + timePadding);
    TextRenderer timer = TextRenderer(font_oxygen, time, timeSize, timerPos);
    txtRenderers.push_back(timer);
    txtRenderers.back().SetRenderColour({120,200,200,255});
    timerIndex = txtRenderers.size() - 1;
}

void UserInterface::CheckPlayerState()
{
    if(rPlayer.IsPaused()) return;;
    
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
            txtRenderers[projIndex].SetRenderColour(seedColour);
            renderers[projBkgIndex].SetRenderColour(seedBkgColour);
            currentProjectile = "SEED";
            break;
            
        case Projectile::EWeaponTypes::Petal:
            renderers[ammoIndex].SetRenderColour(petalColour);
            txtRenderers[projIndex].SetRenderColour(petalColour);
            renderers[projBkgIndex].SetRenderColour(petalBkgColour);
            currentProjectile = "PETAL";
            break;
        
        case Projectile::EWeaponTypes::Sun:
            renderers[ammoIndex].SetRenderColour(sunColour);
            txtRenderers[projIndex].SetRenderColour(sunColour);
            renderers[projBkgIndex].SetRenderColour(sunBkgColour);
            currentProjectile = "SUN";
            break;
    }
    txtRenderers[projIndex].SetText(currentProjectile);
}

void UserInterface::Respawning(float deltaTime)
{
    if(rPlayer.IsDead())
    {
        deathDelayTimer += deltaTime;
        if(deathDelayTimer > .35f) deathScreen.SetVisibility(true);
    }

    if(!deathScreen.IsVisible()) return;

    if(rPlayer.Respawn())
    {
        deathScreen.SetVisibility(false);
        seconds = 0;
        minutes = 0;
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
    if(!timerOn) return;
    
    seconds = seconds + deltaTime;

    if(seconds > 60)
    {
        minutes++;
        seconds = 0;
    }

    time = (minutes < 10? "0" + std::to_string(minutes) : std::to_string((minutes))) + ":" + (seconds < 10? "0" + std::to_string(static_cast<int>(seconds)) : std::to_string((static_cast<int>(seconds))));
    txtRenderers[timerIndex].SetText(time);
}

void UserInterface::ButtonPresses()
{
    if(!pauseScreen.IsVisible()) return;

    const SDL_Point mousePos = { static_cast<int>(rPlayer.GetMousePos().x), static_cast<int>(rPlayer.GetMousePos().y)};
    if(!rPlayer.LMB()) return;
    
    for(int i = 0; i < 3; i++)
    {
        switch (i)
        {
            // Resume
            case 0:
                if(SDL_PointInRect(&mousePos, &buttons[i].GetRect())) PressResume();
                break;

            // Restart
            case 1:
                if(SDL_PointInRect(&mousePos, &buttons[i].GetRect())) PressRestart();
                break;

            // Quit
            case 2:
                if(SDL_PointInRect(&mousePos, &buttons[i].GetRect())) PressQuit();
                break;
        }
    }
}

void UserInterface::PressResume()
{
    pauseScreen.SetVisibility(false);
    rPlayer.Unpause();
}

void UserInterface::PressRestart()
{
    rPlayer.Respawn(true);
    PressResume();
}

void UserInterface::PressQuit()
{
    GameWindow::CloseGame();
}


//\\//\\//\\//\\////\\//\\//\\//\\// Buttons //\\//\\//\\//\\////\\//\\//\\//\\//


UserInterface::Button::Button(int x, int y, int w, int h, SDL_Color colour)
{
    renderer.SetPosition(x, y);
    renderer.SetDrawSize(w, h);

    renderer.SetRenderColour(colour);
}

UserInterface::Button::Button(SDL_Rect rect, SDL_Color colour)
{
    renderer.SetPosition(rect.x, rect.y);
    renderer.SetDrawSize(rect.w, rect.h);

    renderer.SetRenderColour(colour);
}