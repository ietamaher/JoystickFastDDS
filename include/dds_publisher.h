#ifndef DDS_PUBLISHER_H
#define DDS_PUBLISHER_H

#include <chrono>
#include <thread>

#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
//#include "JoystickData.h"  // Include the generated header
 #include "JoystickDataPubSubTypes.h"


class DDSPublisher {
public:
    DDSPublisher();
    ~DDSPublisher();

    void publishJoystickData(const std::vector<int>& buttons, const std::vector<float>& axes);
    void publish(JoystickData& data);

    // Additional methods for DDS initialization and cleanup

private:
    eprosima::fastdds::dds::DomainParticipant* participant_;
    eprosima::fastdds::dds::Publisher* publisher_;
    eprosima::fastdds::dds::Topic* topic_;
    eprosima::fastdds::dds::DataWriter* writer_;
};

#endif // DDS_PUBLISHER_H
