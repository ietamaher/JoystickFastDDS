#include "dds_publisher.h"

using namespace eprosima::fastdds::dds;

DDSPublisher::DDSPublisher() {
    // Create DomainParticipant
    DomainParticipantQos participant_qos;
    participant_ = DomainParticipantFactory::get_instance()->create_participant(0, participant_qos);
    if (participant_ == nullptr) {
        throw std::runtime_error("Failed to create DomainParticipant!");
    }

    // Register the Type
    TypeSupport type(new JoystickDataPubSubType());
    type.register_type(participant_);

    // Create Topic
    topic_ = participant_->create_topic("JoystickTopic", "JoystickData", TOPIC_QOS_DEFAULT);
    if (topic_ == nullptr) {
        throw std::runtime_error("Failed to create Topic!");
    }

    // Create Publisher
    PublisherQos publisher_qos;
    publisher_ = participant_->create_publisher(publisher_qos, nullptr);
    if (publisher_ == nullptr) {
        throw std::runtime_error("Failed to create Publisher!");
    }

    // Create DataWriter
    DataWriterQos writer_qos;
    writer_ = publisher_->create_datawriter(topic_, writer_qos, nullptr);
    if (writer_ == nullptr) {
        throw std::runtime_error("Failed to create DataWriter!");
    }
}

DDSPublisher::~DDSPublisher() {
    if (writer_ != nullptr) {
        publisher_->delete_datawriter(writer_);
    }
    if (publisher_ != nullptr) {
        participant_->delete_publisher(publisher_);
    }
    if (topic_ != nullptr) {
        participant_->delete_topic(topic_);
    }
    if (participant_ != nullptr) {
        DomainParticipantFactory::get_instance()->delete_participant(participant_);
    }
}

void DDSPublisher::publish(JoystickData& data) {
    writer_->write(&data);
}
