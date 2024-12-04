#include<memory>
#include"rclcpp.hpp"
#include<rclcpp/node.hpp>
#include"rclcpp/subscription.hpp"
#include"rclcpp/subscription_base.hpp"
#include"sensor_msgs/msg/joy.hpp"

class JoyPublisher : public rclcpp::Node
{
    public:
    JoyPublisher():rclcpp::Node("joy_publisher")
    {
    const rclcpp::QoS qos = rclcpp::QoS(10).best_effort();
    sub1 = this-> create_subscription<sensor_msgs::msg::Joy>
                ("/joy",qos,
                std::bind(&JoyPublisher::subscription_callback, this, std::placeholders::_1));
    }
    private:
    void subscription_callback(const sensor_msgs::msg::Joy::UniquePtr msg){
        RCLCPP_INFO(this -> get_logger(), " %.6f \n",msg.axes[1]);
    }
    rclcpp::Subscription<sensor_msgs::msg::Joy>::SharedPtr sub1;
};

int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);
  rclcpp::spin(std::make_shared<JoyPublisher>());
  rclcpp::shutdown();
  return 0;
}
