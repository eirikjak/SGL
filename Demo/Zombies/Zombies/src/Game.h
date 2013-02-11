#ifndef GAME_H
#define GAME_H

#include <SGL\BaseGame.h>
#include <SGL\Rendering\Screen\Screen.h>

#include <SGL/Rendering/Models/StaticModel.h>
#include <assimp\scene.h>
#include <assimp\Importer.hpp>
#include <assimp\DefaultLogger.hpp>
#include <assimp\postprocess.h>
#include <SGL/Rendering/Models/ResourceManager.h>
#include <SGL//Rendering/camera/FreeMovementCamera.h>
#include <SGL/Rendering/Voxel/Volume/OctreeVolume.h>
#include <SGL/Rendering/Models/VolumeModel.h>
#include <SGL/Rendering/Voxel/SurfaceExtractors/CubeSurfaceExtractorWithByteNormals.h>
#include <SGL/Rendering/Voxel/SurfaceExtractors/VolumeSurface.h>
#include <SGL/Rendering/Models/LineModel.h> 
#include <memory>
#include <SGL/Input/InputHandler.h>
#include <SGL/Rendering/Voxel/SurfaceExtractors/BulletSurfaceExtractor.h>
#include <SGL/Rendering/Util/FrameBuffer.h>
#include <SGL/Rendering/Models/TexturedQuad.h>
#include <SGL/Rendering/camera/Controller/UnconstrainedCameraController.h>
#include <SGL/Input/KeyMap.h>
#include <SGL\Rendering\camera\Controller\Behavior\KeyMovementBehaviour.h>
#include <SGL/Rendering/camera/Controller/Behavior/MouseFPSBehaviour.h>
#include <SGL\Rendering\Voxel\SurfaceExtractors\CubeSurfaceExtractorWithByteNormals.h>
#include <SGL\Rendering\Voxel\SurfaceExtractors\ChunkExtractor.h>

class Game: public BaseGame
{
public:
	Game(int argc, char* argv[]);
	~Game(void);


	void reshape(int width, int height);
	void update(double dt) override;
	void draw() override;
	void setup() override;

private:
	StaticModel * ballModel;
	InputHandler inputHandler;
	std::string binaryPath;
	
	Node * rootNode;

	FreeMovementCamera * cam;
	//temp
	std::shared_ptr<ResourceManager> resourceManager;
	void test();
	LineModel * crossHair;
	Pipeline * pipeline;
	Node * floorNode;

	UnconstrainedCameraController * cameraController;
	TexturedQuad * texturedQuad;

	TexturedQuad * translatedQuad;

	FrameBuffer * frameBuffer;

	Node * planetNode;
	Node * duckNode;


};
#endif