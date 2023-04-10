# laser_noise_remove
remove robot surrounding laser noise. woring good so far 
#
Include the necessary ROS header files and the sensor_msgs/LaserScan message header file.

Define a LaserScanFilter class with class member variables including:

- ros::NodeHandle nh_: ROS node handle, used for node parameter reading and topic subscription/publishing operations.
- ros::Subscriber scan_sub_: subscriber of the laser data, subscribing to the "/scan" topic.
- ros::Publisher scan_pub_: publisher of the filtered laser data, publishing to the "scan_filtered" topic.
- int filter_size_: filter window size, read from the ROS parameter server, with a default value of 5.
#
#
Define the constructor of the LaserScanFilter class LaserScanFilter(), where:
the filter window size filter_size_ is read from the ROS parameter server through the ROS node handle nh_.
the laser data subscriber scan_sub_ is initialized, subscribing to the "/scan" topic, with a queue length of 10 and a callback function of LaserScanFilter::scanCallback().
the filtered laser data publisher scan_pub_ is initialized, publishing to the "scan_filtered" topic, with a queue length of 10.
Define the callback function of the LaserScanFilter class scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan), where:
the original laser data is copied, a new variable of type sensor_msgs::LaserScan called scan_filtered is created to store the filtered laser data.
the laser data is filtered, iterating through each point of the laser data and skipping invalid values and the first and last points.
for valid points, a certain number of points (determined by the filter window size filter_size_) around the point are selected, invalid values are removed, the median is calculated, and the median is used as the laser value of the point.
the filtered laser data scan_filtered is published to the "scan_filtered" topic.
In the main function, the ROS node is initialized, a LaserScanFilter class object filter is created, and then the ROS main loop is entered to wait for the callback functions of the subscriber and publisher to execute.
The overall process is: subscribe to laser data -> filter processing -> publish filtered laser data.
