#include "svo_factory.hpp"

namespace svo_ros2
{

namespace factory
{
    CameraBundle::Ptr loadCameraFromYaml(const rclcpp::Node::SharedPtr node)
    {
    std::string calib_file = node->get_parameter
    vk::param<std::string>(pnh, "calib_file", "~/cam.yaml");
    CameraBundle::Ptr ncam = CameraBundle::loadFromYaml(calib_file);
    std::cout << "loaded " << ncam->numCameras() << " cameras";
    for(const auto& cam : ncam->getCameraVector())
        cam->printParameters(std::cout, "");
    return ncam;
    }

    FrameHandlerMono::Ptr makeMono(const rclcpp::Node::SharedPtr node, const CameraBundlePtr & cam = nullptr)
    {
        // create camera
        CameraBundle::Ptr ncam = (cam) ? cam : 

    }
}


}   //  namespace svo_ros2