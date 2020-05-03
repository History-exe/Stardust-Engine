#include <Platform/Platform.h>
#include <Graphics/2D/TilemapAnim.h>
#include <Graphics/2D/CharacterSprite.h>
#include <Utilities/Input.h>
#include <Graphics/2D/TopDownController.h>
#include <Graphics/2D/SideScrollerController.h>
#include <Utilities/Logger.h>
#include <Graphics/UI/UIText.h>
PSP_MODULE_INFO("Stardust", 0, 1, 0);
PSP_MAIN_THREAD_ATTR(THREAD_ATTR_VFPU | THREAD_ATTR_USER);
PSP_HEAP_SIZE_KB(-1024);

using namespace Stardust;

int main() {
	Platform::initPlatform();

	Graphics::Texture* charTex = Graphics::TextureUtil::LoadPng("./link.png");
	Graphics::TextureAtlas* charAtlas = new Graphics::TextureAtlas({13.0f, 13.0f});
	Graphics::Render2D::CharacterSprite* charSprite = new Graphics::Render2D::CharacterSprite({ 32, 32 }, charAtlas, charTex);

	Graphics::Render2D::CharacterDirectionalAnimInfo* info = new Graphics::Render2D::CharacterDirectionalAnimInfo();
	info->top = { 26, 1 };
	info->down = { 0, 3 };
	info->left = { 13, 3 };
	info->right = { 39, 3 };

	charSprite->addAnimEvent("default", info);

	Graphics::Render2D::CharacterDirectionalAnimInfo* info2 = new Graphics::Render2D::CharacterDirectionalAnimInfo();
	info2->top = { 78, 4 };
	info2->down = { 52, 4 };
	info2->left = { 65, 4 };
	info2->right = { 91, 4 };

	charSprite->addAnimEvent("walk", info2);
	charSprite->setDefaultAnimEvent("default");
	charSprite->position(240, 136);
	charSprite->setLayer(10);

	Graphics::Render2D::TopDownController controller = Graphics::Render2D::TopDownController(charSprite, 128.0f);
	Utilities::addActionKeyPair("walkLeft", PSP_CTRL_LEFT);
	Utilities::addActionKeyPair("walkUp", PSP_CTRL_UP);
	Utilities::addActionKeyPair("walkDown", PSP_CTRL_DOWN);
	Utilities::addActionKeyPair("walkRight", PSP_CTRL_RIGHT); 
	controller.registerHandlers();
	controller.setPosition({ 240, 136 });
	controller.getAnimController()->setCharacterTickRateRelative(12);
	controller.getAnimController()->setTickRate(8);

	Graphics::Render2D::Tilemap* tmap = new Graphics::Render2D::Tilemap(new Graphics::TextureAtlas(32), Graphics::TextureUtil::LoadPng("./terrain_atlas.png"));

	for (int i = 0; i < 480 / 16; i++) {
		Graphics::Render2D::Tile* tile = new Graphics::Render2D::Tile();

		tile->offset = { i * 16, 200 };
		tile->extent = { 16, 16 };
		tile->rgba = 0xFFFFFFFF;
		tile->layer = 0;
		tile->rotation = 0;
		tile->texIndex = 0;
		tile->physics = true;

		tmap->addTile(tile);
	}

	Graphics::UI::UIText* txt = new Graphics::UI::UIText({ 100, 100 }, "Hello World!");
	txt->setOptions({ 0.5f, 0xFFFF00FF, INTRAFONT_ALIGN_LEFT });

	tmap->loadTileFromJSON("./example.json");

	tmap->buildMap();
	
	controller.addPhysicsTileMap(tmap);
	 

	Graphics::g_RenderCore.Set2DMode();

	while (!Utilities::KeyPressed(PSP_CTRL_START)) {
		Graphics::g_RenderCore.BeginCommands();
		Graphics::g_RenderCore.Clear();
		
		controller.update(0.016f);
		controller.draw();


		tmap->drawMap();

		txt->draw();
		Graphics::g_RenderCore.EndCommands();
		Platform::platformUpdate();
	}

	Platform::exitPlatform();
	return 0;
}