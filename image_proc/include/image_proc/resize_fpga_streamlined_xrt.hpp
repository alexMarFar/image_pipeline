/*
      ____  ____
     /   /\/   /
    /___/  \  /   Copyright (c) 2021, Xilinx®.
    \   \   \/    Author: Víctor Mayoral Vilches <victorma@xilinx.com>
     \   \
     /   /        Licensed under the Apache License, Version 2.0 (the "License");
    /___/   /\    you may not use this file except in compliance with the License.
    \   \  /  \   You may obtain a copy of the License at
     \___\/\___\            http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

    Inspired by past work from Willow Garage, Inc., Andreas Klintberg,
      Joshua Whitley
*/

#ifndef IMAGE_PROC_RESIZE_FPGA_STREAMLINED_XRT_HPP_
#define IMAGE_PROC_RESIZE_FPGA_STREAMLINED_XRT_HPP_

#include <rclcpp/rclcpp.hpp>
#include <image_transport/image_transport.hpp>
#include <ament_index_cpp/get_resource.hpp>

#include <cstring>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <thread>

#include "experimental/xrt_bo.h"
#include "experimental/xrt_device.h"
#include "experimental/xrt_kernel.h"

#include <vitis_common/common/ros_opencl_120.hpp>

namespace image_proc
{

class ResizeNodeFPGAStreamlinedXRT
  : public rclcpp::Node
{
public:
  explicit ResizeNodeFPGAStreamlinedXRT(const rclcpp::NodeOptions &);

protected:
  image_transport::CameraPublisher pub_image_;
  image_transport::CameraSubscriber sub_image_;

  rclcpp::TimerBase::SharedPtr timer_;

  int interpolation_;
  bool use_scale_;
  bool profile_;
  double scale_height_;
  double scale_width_;
  int height_;
  int width_;

  xrt::device device;
  xrt::uuid uuid;
  xrt::kernel krnl_resize;

  std::mutex connect_mutex_;

  void connectCb();

  void imageCb(
    sensor_msgs::msg::Image::ConstSharedPtr image_msg,
    sensor_msgs::msg::CameraInfo::ConstSharedPtr info_msg);
};

}  // namespace image_proc

#endif  // IMAGE_PROC_RESIZE_FPGA_STREAMLINED_XRT_HPP_
