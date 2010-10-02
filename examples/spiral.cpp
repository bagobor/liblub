#include "Application.h"

class Example : public Application {

public:
	Example(){
		width = 1920;
		height = 1200;
		programName = "Spiral";
  }

	void scene(){
		Node * plane = new Node(
				"Planet",
				{0,0,0},
				.2,
				MeshFactory::Instance().load("monkey.obj"),
				new TextureMaterial("bunny.png")
		);
		SceneGraph::Instance().addNode(plane);
		SceneGraph::Instance().addNode(new Node("Spiral",{0,0,0}, MeshFactory::Instance().spiral(),new StarMat()));
	}
};

int main(int argc, char *argv[])
{
	Example().run();

}
