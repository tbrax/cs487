// Simple Game
// Trace Braxling
// Based on example by Dr. Jonathan Metzgar et al
// UAF CS Game Design and Architecture Course
#include <gamelib.hpp>
#include <gamelib_action.hpp>

#pragma comment(lib, "gamelib.lib")

class PlaySoundCommand : public GameLib::InputCommand {
public:
    PlaySoundCommand(int audioClipId, bool stopPrevious)
        : musicClipId_{ audioClipId }
        , stopPrevious_{ stopPrevious } {}

    const char* type() const override { return "PlaySoundCommand"; }

    bool execute(float amount) override {
        GameLib::Locator::getAudio()->playAudio(musicClipId_, stopPrevious_);
        return true;
    }

private:
    int musicClipId_{ 0 };
    bool stopPrevious_{ false };
};

class PlayMusicCommand : public GameLib::InputCommand {
public:
    PlayMusicCommand(int musicClipId)
        : musicClipId_{ musicClipId } {}

    const char* type() const override { return "PlayMusicCommand"; }

    bool execute(float amount) override {
        GameLib::Locator::getAudio()->playMusic(musicClipId_, -1, 0);
        return true;
    }

private:
    int musicClipId_{ 0 };
    bool stopPrevious_{ false };
};

class QuitCommand : public GameLib::InputCommand {
public:
    const char* type() const override { return "QuitCommand"; }
    bool execute(float amount) override {
        GameLib::Locator::getContext()->quitRequested = true;
        return true;
    }
};

class MovementCommand : public GameLib::InputCommand {
public:
    const char* type() const override { return "MovementCommand"; }
    bool execute(float amount) override {
        // apply slight curve
        if (amount < 0.1f && amount > -0.1f)
            amount = 0.0f;
        else if (amount > 0.5f)
            amount = 1.0f;
        else if (amount < -0.5f)
            amount = -1.0f;
        else if (amount > 0.0f)
            amount = 0.5f;
        else
            amount = -0.5f;
        return InputCommand::execute(amount);
    }
};

void testSprites(GameLib::Context& context, int spriteCount, int& spritesDrawn, SDL_Texture* testPNG, SDL_Texture* testJPG);

int main(int argc, char** argv) {
    GameLib::Context context(1280, 720, GameLib::WindowDefault);
    GameLib::Audio audio;
    GameLib::InputHandler input;
    GameLib::Graphics graphics{ &context };

    GameLib::Locator::provide(&context);
    if (context.audioInitialized())
        GameLib::Locator::provide(&audio);
    GameLib::Locator::provide(&input);
    GameLib::Locator::provide(&graphics);

    PlaySoundCommand play0(0, false);
    PlaySoundCommand play1(1, false);
    PlaySoundCommand play2(2, false);
    PlaySoundCommand play3(3, false);
    PlayMusicCommand playMusic1(0);
    PlayMusicCommand playMusic2(1);
    PlayMusicCommand playMusic3(2);
    QuitCommand quitCommand;
    MovementCommand xaxisCommand;
    MovementCommand yaxisCommand;

    input.back = &quitCommand;
    input.key1 = &play0;
    input.key2 = &play1;
    input.key3 = &play2;
    input.key4 = &play3;
    input.key5 = &playMusic1;
    input.key6 = &playMusic2;
    input.key7 = &playMusic3;
    input.axis1X = &xaxisCommand;
    input.axis1Y = &yaxisCommand;

    context.addSearchPath("./assets");
    context.addSearchPath("../assets");
    SDL_Texture* testPNG = context.loadImage("godzilla.png");
    SDL_Texture* testJPG = context.loadImage("parrot.jpg");
    graphics.setTileSize(32, 32);
    int spriteCount = context.loadTileset(0, 32, 32, "Tiles32x32.png");
    if (!spriteCount) {
        HFLOGWARN("Tileset not found");
    }

    context.loadAudioClip(0, "starbattle-bad.wav");
    context.loadAudioClip(1, "starbattle-dead.wav");
    context.loadAudioClip(2, "starbattle-endo.wav");
    context.loadAudioClip(3, "starbattle-exo.wav");
    context.loadAudioClip(4, "starbattle-ok.wav");
    context.loadAudioClip(5, "starbattle-pdead.wav");
    context.loadMusicClip(0, "starbattlemusic1.mp3");
    context.loadMusicClip(1, "starbattlemusic2.mp3");
    context.loadMusicClip(2, "distoro2.mid");

    GameLib::World world;
    GameLib::Locator::provide(&world);
    std::string worldPath = context.findSearchPath("world.txt");
    if (!world.load(worldPath)) {
        HFLOGWARN("world.txt not found");
    }

    Hf::StopWatch stopwatch;
    double spritesDrawn = 0;
    double frames = 0;
    GameLib::Actor player(new GameLib::SimpleInputComponent(), new GameLib::BoxPhysicsComponent(), new GameLib::SimpleGraphicsComponent());
    player.speed = (float)graphics.getTileSizeX() * 0.5;
    player.position.x = graphics.getCenterX() / (float)graphics.getTileSizeX();
    player.position.y = graphics.getCenterY() / (float)graphics.getTileSizeY();
    player.spriteId = 2;

    // GameLib::MoveAction moveAction;
    // moveAction.setActor(&player);

    world.actors.push_back(&player);

    GameLib::Actor randomPlayer(new GameLib::LinearInputComponent(),
								new GameLib::SimplePhysicsComponent(), 
								new GameLib::SimpleGraphicsComponent());

    world.actors.push_back(&randomPlayer);
    randomPlayer.position.x = graphics.getCenterX() / (float)graphics.getTileSizeX();
    randomPlayer.position.y = graphics.getCenterY() / (float)graphics.getTileSizeY();
    randomPlayer.spriteId = 256;
    randomPlayer.speed = (float)graphics.getTileSizeX();

 //   for (int i = 0; i < 1; i++) {
 //       GameLib::Actor randomPlayer(new GameLib::LinearInputComponent(), new GameLib::SimplePhysicsComponent(), new GameLib::SimpleGraphicsComponent());

 //       world.actors.push_back(&randomPlayer);
 //       randomPlayer.position.x = graphics.getCenterX() / (float)graphics.getTileSizeX();
 //       randomPlayer.position.y = graphics.getCenterY() / (float)graphics.getTileSizeY();
 //       randomPlayer.spriteId = 256;
 //       randomPlayer.speed = (float)graphics.getTileSizeX();
	//}

    float t0 = stopwatch.Stop_sf();

    while (!context.quitRequested) {
        float t1 = stopwatch.Stop_sf();
        float dt = t1 - t0;
        t0 = t1;
        GameLib::Context::deltaTime = dt;
        GameLib::Context::currentTime_s = t1;
        GameLib::Context::currentTime_ms = t1 * 1000;

        context.getEvents();
        input.handle();

        context.clearScreen({ 255, 0, 255, 255 });

        for (unsigned x = 0; x < world.worldSizeX; x++) {
            for (unsigned y = 0; y < world.worldSizeY; y++) {
                GameLib::SPRITEINFO s;
                s.position = { x * 32, y * 32 };
                auto t = world.getTile(x, y);
                context.drawTexture(s.position, 0, t.charDesc);
            }
        }

        world.update(dt, graphics);

        context.swapBuffers();
        frames++;
        std::this_thread::yield();
    }
    double totalTime = stopwatch.Stop_s();
    HFLOGDEBUG("Sprites/sec = %5.1f", spritesDrawn / totalTime);
    HFLOGDEBUG("Frames/sec = %5.1f", frames / totalTime);

    return 0;
}

void testSprites(GameLib::Context& context, int spriteCount, int& spritesDrawn, SDL_Texture* testPNG, SDL_Texture* testJPG) {
    // if (context.keyboard.scancodes[SDL_SCANCODE_ESCAPE]) {
    //    context.quitRequested = true;
    //}

    // An arbitrary number roughly representing 4k at 8 layers, 32x32 sprites
    // constexpr int SpritesToDraw = 128 * 72 * 8;
    // An arbitrary number roughly representing HD at 4 layers, 32x32 sprites
    constexpr int SpritesToDraw = 5;
    // 60 * 34 * 4;
    for (int i = 0; i < SpritesToDraw; i++) {
        GameLib::SPRITEINFO s;
        s.position = { rand() % 1280, rand() % 720 };
        s.center = { 0.0f, 0.0f };
        s.flipFlags = 0;
        s.angle = (float)(rand() % 360);
        // context.drawTexture(0, rand() % spriteCount, s);
        s.position = { rand() % 1280, rand() % 720 };
        context.drawTexture(s.position, 0, rand() % spriteCount);
    }
    spritesDrawn += SpritesToDraw;

    context.drawTexture({ 50, 0 }, { 100, 100 }, testPNG);
    context.drawTexture({ 250, 250 }, { 100, 100 }, testJPG);
}
