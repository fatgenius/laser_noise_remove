/**************************************************************

Author: dubutian
Email: dbtlive@gmail.com
Date: 2023/03/13
Description: This C++ file is used to remove the noise from radar data.
Note: (Other additional information, if any)
**************************************************************/

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

class LaserScanFilter
{
public:
    LaserScanFilter();

private:
    void scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan);

    ros::NodeHandle nh_;
    ros::Subscriber scan_sub_;
    ros::Publisher scan_pub_;
    int filter_size_;
};

LaserScanFilter::LaserScanFilter()
{
    nh_ = ros::NodeHandle("~");
    nh_.param("filter_size", filter_size_, 5);
    scan_sub_ = nh_.subscribe<sensor_msgs::LaserScan>("/scan", 10, &LaserScanFilter::scanCallback, this);
    scan_pub_ = nh_.advertise<sensor_msgs::LaserScan>("scan_filtered", 10);
}

void LaserScanFilter::scanCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
    // 复制原始激光数据
    sensor_msgs::LaserScan scan_filtered = *scan;

    // 对激光数据进行滤波处理
    for (int i = 0; i < scan->ranges.size(); ++i) {
        // 跳过无效值和第一个和最后一个点
        if (std::isnan(scan->ranges[i]) || i == 0 || i == scan->ranges.size() - 1) {
            continue;
        }

        // 计算中值
        std::vector<float> range_data;
        for (int j = i - filter_size_/2; j <= i + filter_size_/2; ++j) {
            if (!std::isnan(scan->ranges[j])) {
                range_data.push_back(scan->ranges[j]);
            }
        }
        if (range_data.size() > 0) {
            std::sort(range_data.begin(), range_data.end());
            scan_filtered.ranges[i] = range_data[range_data.size() / 2];
        }
    }

    // 发布滤波后的激光数据
    scan_pub_.publish(scan_filtered);
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "laser_scan_filter");
    LaserScanFilter filter;
    ros::spin();
    return 0;
}
