#pragma once
#include "imgproc/FetchInterface.h"
#include <string>
#include <boost/filesystem.hpp>
#include <librealsense2/rs.hpp>

namespace surfelwarp
{
	class RealSenseFetch : public FetchInterface
	{
	public:
		using Ptr = std::shared_ptr<RealSenseFetch>;
		using path = boost::filesystem::path;

		//Just copy the string to data path
		explicit RealSenseFetch(const path& data_path);
	
		~RealSenseFetch() = default;

		//Main interface
		void FetchDepthImage(size_t frame_idx, cv::Mat& depth_img) override;
		void FetchDepthImage(size_t frame_idx, void* depth_img) override;
		void FetchRGBImage(size_t frame_idx, cv::Mat& rgb_img) override;
		void FetchRGBImage(size_t frame_idx, void* rgb_img) override;

	private:
		std::shared_ptr<rs2::pipeline> m_pipe;
		rs2::frameset m_frameset;
		cv::Mat m_prev_color;
		int m_frame_count;
	};



}