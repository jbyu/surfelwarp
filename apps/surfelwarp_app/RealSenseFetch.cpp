#include <opencv2/opencv.hpp>
#include "RealSenseFetch.h"

surfelwarp::RealSenseFetch::RealSenseFetch(	const path& data_path)
{
	rs2::config config;
	config.enable_stream(RS2_STREAM_COLOR, 640, 480, RS2_FORMAT_BGR8, 30);
	config.enable_stream(RS2_STREAM_DEPTH, 640, 480, RS2_FORMAT_Z16, 30);
	// Create a shared pointer to a pipeline
	m_pipe = std::make_shared<rs2::pipeline>();
	m_pipe->start(config);
	// Initialize a shared pointer to a device with the current device on the pipeline
	//rs2::device device = m_pipe->get_active_profile().get_device();
	m_frame_count = -1;
}


void surfelwarp::RealSenseFetch::FetchDepthImage(size_t frame_idx, cv::Mat & depth_img)
{
	m_frameset = m_pipe->wait_for_frames(); // wait for next set of frames from the camera
	++m_frame_count;

	rs2::depth_frame data = m_frameset.get_depth_frame();
	depth_img =  cv::Mat(cv::Size(data.get_width(), data.get_height()), CV_8UC3, (void*)data.get_data());
}

void surfelwarp::RealSenseFetch::FetchDepthImage(size_t frame_idx, void * depth_img)
{

}

void surfelwarp::RealSenseFetch::FetchRGBImage(size_t frame_idx, cv::Mat & rgb_img)
{
	if (m_frame_count - 1 == frame_idx)
	{
		rgb_img = m_prev_color;
		return;
	}

	rs2::video_frame data = m_frameset.get_color_frame();
	rgb_img = cv::Mat(cv::Size(data.get_width(), data.get_height()), CV_16UC1, (void*)data.get_data());
	m_prev_color = rgb_img;
}

void surfelwarp::RealSenseFetch::FetchRGBImage(size_t frame_idx, void * rgb_img)
{

}
