#include "Game.h"


Game::Game(int argc, char* argv[]):BaseGame()
{

	binaryPath = argv[0];
	int last = binaryPath.find_last_of("\\");
	binaryPath.erase(last,last + 50);

	
	init("Game",1280,720);
}



void Game::setup(){


	resourceManager = std::make_shared<ResourceManager>();
	resourceManager->setWorkingDirectory(binaryPath + "\\Assets\\");
	resourceManager->setShaderDirectory(binaryPath + "\\Assets\\Shaders\\");
	resourceManager->setModelDirectory(binaryPath + "\\Assets\\Models\\");


	rootNode = new Node();
	cam = new FreeMovementCamera(0,5.0,50.0,1280,728,glm::quat(),0.1,300);
	cam->rotateRight(6.28);

	KeyMap<KeyMovementBehaviour::Key,Direction> map ;
	map.setKey('A',KeyMovementBehaviour::Key::LEFT,Direction(-1,0.0,0.0));
	map.setKey('D',KeyMovementBehaviour::Key::RIGHT,Direction(1,0.0,0.0));
	map.setKey('W',KeyMovementBehaviour::Key::FORWARD,Direction(0.0,0.0,-1.0));
	map.setKey('S',KeyMovementBehaviour::Key::BACKWARDS,Direction(0.0,0.0,1.0));
	map.setKey('Q',KeyMovementBehaviour::Key::UP,Direction(0.0,1.0,0.0));
	map.setKey('E',KeyMovementBehaviour::Key::DOWN,Direction(0.0,-1.0,0.0));

	KeyMovementBehaviour * behaviour = new KeyMovementBehaviour(map);
	behaviour->setSpeed(20);

	MouseFPSBehaviour * mouseB= new MouseFPSBehaviour(true);
	mouseB->setSpeed(0.1,0.1);
	mouseB->setInverted(false);
	cameraController = new UnconstrainedCameraController(cam);

	cameraController->addBehaviour(behaviour);
	cameraController->addBehaviour(mouseB);


	

	const aiScene * sphereScene = resourceManager->loadModel("sphere.irr");


	PointLight * light = new PointLight();
	light->diffuse = glm::vec4(1.0,1.0,1.0,1.0);
	light->specular = glm::vec4(1.0,1.0,1.0,1.0);
	light->setRange(5000);
	light->position = glm::vec4(50.0,50.0,50,1.0);
	rootNode->addLight(light);
	pipeline = new Pipeline(10,10);



	TileAtlas * atlas = new TileAtlas("tileAtlas.png",4,1,resourceManager);
	Volume * floorVolume = new OctreeVolume(32);
	for(int x = 0;x <32 ;x++)
		for(int z = 0;z<32;z++)
			floorVolume->set(x,0,z,2);

	TileAtlas * frameBufferAtlas = new TileAtlas("tileAtlas.png",1,1,resourceManager);
	VolumeModel * floorModel = new VolumeModel(1,1,1,32,1,32,resourceManager);
	floorModel->init(atlas);
	floorModel->setSurface(0,0,0,CubeSurfaceExtractorWithByteNormals(floorVolume).extractSurface(0,0,0,32,32,32));
	floorModel->setScale(glm::vec3(100,1,100));
	floorNode = floorModel;
	rootNode->addChild(floorModel);


	Volume * volume = new OctreeVolume(32);

	for(int x = 0;x <32 ;x++){
		for(int y = 0;y<32;y++){
			for(int z = 0;z<32;z++){

				volume->set(x,y,z,2);

			}
		}
	}
	


	Texture * quadTex = new Texture(Texture::ColorFormat::FORMAT_RGB,1280,728);

	VolumeModel * model = new VolumeModel(1,1,1,32,1,32,resourceManager);
	model->init(atlas);
	model->move(glm::vec3(20,0.0,0.0));

	ChunkExtractor extractor = ChunkExtractor(&CubeSurfaceExtractorWithByteNormals(volume),32,32,32);
	model->setSurface(0,0,0,extractor.extractSurface(0,0,0));
	rootNode->addChild(model);
	pipeline = new Pipeline(10,10);




	texturedQuad = new TexturedQuad(resourceManager);
	texturedQuad->init(quadTex);
	texturedQuad->setSize(1280/4.0,728/4.0,1);
	texturedQuad->setPosition(glm::vec3(300,100,1));


	translatedQuad = new TexturedQuad(resourceManager);
	translatedQuad->init(quadTex);
	translatedQuad->setSize(1280/20.0,728/20.0,1);

	translatedQuad->setPosition(glm::vec3(100,2,50));



	this->frameBuffer= new FrameBuffer();
	this->frameBuffer->setDepthBuffer(1280,728);
	this->frameBuffer->addRenderTexture(quadTex);
	planetNode = new Node();
	duckNode = new Node();

	const aiScene * duckScene = resourceManager->loadModel("duck.dae");
	for (double i = 0.0; i< 6.28;i+=0.01){

		StaticModel * sphereModel = new StaticModel(resourceManager);
		sphereModel->initFromScene(sphereScene,sphereModel);
		sphereModel->setPosition(glm::vec3(cos(i)*100 ,5,sin(i)*100 ));
		planetNode->addChild(sphereModel);

		StaticModel * duckModel = new StaticModel(resourceManager);
		duckModel->initFromScene(duckScene,duckModel);
		duckModel->setPosition(glm::vec3(cos(i)*120 ,5,sin(i)*120 ));
		duckModel->setScale(glm::vec3(0.01,0.01,0.01));
		planetNode->addChild(duckModel);

	}
	rootNode->addChild(planetNode);
	


}

void Game::draw() {

	
	//frameBuffer->bind();


	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.4,0.4,0.4,1.0);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);

	pipeline->clear();
	pipeline->setShadowPass(false);
	pipeline->setView(cam->getViewMatrix());
	pipeline->setCameraPosition(glm::vec4(cam->getPosition(),1.0));
	pipeline->setProjection(cam->getPerspectiveProjection());
	pipeline->setViewDirection(glm::vec4(cam->getViewDirection(),1.0));


	rootNode->render(pipeline);
	/*
	glBindFramebuffer(GL_FRAMEBUFFER,0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glClearColor(0.4,0.4,0.4,1.0);
	pipeline->clear();
	pipeline->setShadowPass(false);
	pipeline->setView(cam->getViewMatrix());
	pipeline->setCameraPosition(glm::vec4(cam->getPosition(),1.0));
	pipeline->setProjection(cam->getPerspectiveProjection());
	pipeline->setViewDirection(glm::vec4(cam->getViewDirection(),1.0));
	rootNode->render(pipeline);
	translatedQuad->render(pipeline);

	glDisable(GL_DEPTH_TEST);
	pipeline->clear();
	pipeline->setProjection(glm::ortho(0.0f,(float)cam->getWidth(),0.0f,(float)cam->getHeight()));
	pipeline->setView(glm::mat4(1.0));

	//crossHair->render(pipeline);*/
	
	//texturedQuad->render(pipeline);
	swapBuffers();

}
void Game::update(double dt){

	cameraController->update(dt);

	planetNode->rotate(glm::quat(glm::vec3(0.0,1*dt,0.0)));
	duckNode->rotate(glm::quat(glm::vec3(0.0,-1*dt,0.0)));
}
void Game::reshape(int width, int height){

	if(cam)
	cam->setProjection(width,height);
}


Game::~Game(void)
{

	delete pipeline;
	delete rootNode;
}
