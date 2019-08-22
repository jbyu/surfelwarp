//
// Created by wei on 5/22/18.
//

#include <boost/filesystem.hpp>
#include "common/common_utils.h"
#include "common/ConfigParser.h"
#include "core/SurfelWarpSerial.h"
#include "RealSenseFetch.h"

int main(int argc, char** argv) {
	using namespace surfelwarp;
	
	//Get the config path
	std::string config_path;
	if (argc <= 1) {
#if defined(WIN32)
		config_path = "C:/Users/wei/Documents/Visual Studio 2015/Projects/surfelwarp/test_data/boxing_config.json";
#else
		config_path = "/home/wei/Documents/programs/surfelwarp/test_data/boxing_config.json";
#endif
	} else {
		config_path = std::string(argv[1]);
	}

	//Parse it
	auto& config = ConfigParser::Instance();
	config.ParseConfig(config_path);

	//The context
	//auto context = initCudaContext();

	//Save offline
	bool offline_rendering = true;

	//Construct the fetch processor
	//FileFetch::Ptr fetcher = std::make_shared<FileFetch>(ConfigParser::Instance().data_path());
	RealSenseFetch::Ptr fetcher = std::make_shared<RealSenseFetch>(ConfigParser::Instance().data_path());

	//The processing loop
	SurfelWarpSerial::Ptr fusion = std::make_shared<SurfelWarpSerial>(fetcher);
	fusion->ProcessFirstFrame();

#if 0
	for(auto i = 0; i < config.num_frames(); i++){
		LOG(INFO) << "The " << i << "th Frame";
		fusion->ProcessNextFrameWithReinit(offline_rendering);
	}
#else
	GLFWwindow* window = fusion->GetWindow();
	int frame = 0;
	/* Loop until the user closes the window */
	while (! glfwWindowShouldClose(window))
	{
		//if (frame < config.num_frames())
		{
			/* Render here */
			glClear(GL_COLOR_BUFFER_BIT);
			fusion->ProcessNextFrameWithReinit(false);
			/* Swap front and back buffers */
			glfwSwapBuffers(window);
			++frame;
		}
		/* Poll for and process events */
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
#endif
	
	//destroyCudaContext(context);
}
