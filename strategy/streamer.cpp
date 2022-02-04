#include <algorithm>
#include <atomic>
#include <iostream>
#include <thread>
#include <utility>
#include <vector>
#include <tuple>

class Streamer
{
public:
    using IpAddress = std::string;
    using Port = uint16_t;
    using Vlan = uint16_t;

    struct StreamInfo
    {
        IpAddress sourceAddress_;
        IpAddress destinationAddress_;
        Port sourcePort_;
        Port destinationPort_;
        Vlan vlan_;
        bool operator==(const StreamInfo &other) const
        {
            return std::tie(sourceAddress_, destinationAddress_, sourcePort_, vlan_) == 
                   std::tie(other.sourceAddress_, other.destinationAddress_, other.sourcePort_, other.destinationPort_, other.vlan_);
        }
    };

    virtual ~Streamer() = default;
    Streamer() = default;
    Streamer(const Streamer&) = default;
    Streamer& operator=(Streamer&) = default;
    Streamer(Streamer&&) = default;
    Streamer& operator=(Streamer&&) = default;

    virtual bool addReciver(const StreamInfo& info) = 0;
    virtual bool removeReciver(const StreamInfo& info) = 0;
    virtual bool addData(const std::vector<uint8_t>& data) = 0;
    virtual bool validationData(const std::vector<uint8_t>& data) const = 0;
    virtual bool startStream() = 0;
    virtual bool stopStream() = 0;
    virtual bool streamInProgress() const = 0;
};



class StreamerImpl : public Streamer
{
public:
    StreamerImpl(std::initializer_list<StreamInfo> info) : info_(info) {
        std::cout << "C'tor: initializer_list<StreamerInfo> info\n";
    }

    StreamerImpl(const StreamInfo& info) : info_(1,info) {
        std::cout << "C'tor: const StreamInfo& info\n";
    }

    bool addReciver(const StreamInfo& info) override {
        if (findReciver(info) == std::cend(info_)) {
            info_.push_back(info);
            return true;
        }
        return false;
    }

    bool removeReciver(const StreamInfo& info) override {
        if (const auto it = findReciver(info); it != std::cend(info_)) {
            info_.erase(it);
            return true;
        }

        return false;
    }

    bool addData(const std::vector<uint8_t>& data) override {
        if (!validationData(data) || streamInProgress()) {
            return false;
        }
        data_ = data;
        return true;
    }

protected: 
    std::vector<StreamInfo>::const_iterator findReciver(const StreamInfo& info) const {
        return std::find(cbegin(info_), cend(info_), info);
    }
    std::vector<StreamInfo> info_;
    std::vector<uint8_t> data_;

};


class MpegStreamer : public StreamerImpl {
public:
    using StreamerImpl::StreamerImpl;

    bool validationData(const std::vector<uint8_t>& data) const override {
        return data.size() % 2;
    }

    bool startStream() override {
        if(streamInProgress() || data_.front() == 5) {
            return false;
        }
        
        inProgress_ = true;

        std::thread([data = std::ref(data_), inProgress = std::ref(inProgress_)](){
            for(const auto el : data.get()) {
                if(!inProgress.get()) {
                    return;
                }
                std::cout << el << ' ' << std::flush;
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
        }).detach();
        return true;
    }

    bool stopStream()  override {
        if (!streamInProgress() || data_.back() == 10) {
            return false;
        }
        inProgress_ = false;
        return true;
    }

    bool streamInProgress() const override {
        return inProgress_;
    }
private: 
    std::atomic<bool> inProgress_{false};
};

class MjpegStreamer : public StreamerImpl {
public:
    using StreamerImpl::StreamerImpl;

    bool validationData(const std::vector<uint8_t>& data) const override {
        return !(data.size() % 2);
    }

    bool startStream() override {
        if(streamInProgress() || data_.front() == 5) {
            return false;
        }
        
        inProgress_ = true;

        std::thread([data = std::ref(data_), inProgress = std::ref(inProgress_)](){
            for(const auto el : data.get()) {
                if(!inProgress.get()) {
                    return;
                }
                std::cout << el << ' ' << std::flush;
                std::this_thread::sleep_for(std::chrono::milliseconds(200));
            }
        }).detach();
        return true;
    }

    bool stopStream()  override {
        if (!streamInProgress() || data_.back() == 10) {
            return false;
        }
        inProgress_ = false;
        return true;
    }

    bool streamInProgress() const override {
        return inProgress_;
    }
private: 
    std::atomic<bool> inProgress_{false};
};


int main() {
    std::unique_ptr<Streamer> streamer = std::make_unique<MpegStreamer>(
        Streamer::StreamInfo{"192.168.0.0", "192.168.10.24", 5432, 5432, 12});
    

    std::cout << std::boolalpha << streamer->addData({1, 2, 3, 4, 5, 6, 7}) << '\n';
    std::cout << streamer->startStream() << '\n';
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << '\n' << streamer->stopStream() << '\n';

    // false 
    std::cout << std::boolalpha << streamer->addData({1, 2, 3, 4, 5, 6}) << '\n';

    // New type of Streamer
    streamer = std::make_unique<MjpegStreamer>(
        Streamer::StreamInfo{"192.168.0.0", "192.168.10.24", 5432, 5432, 12});
    
    std::cout << std::boolalpha << streamer->addData({1, 2, 3, 4, 5, 6}) << '\n';
    std::cout << streamer->startStream() << '\n';
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << '\n' << streamer->stopStream() << '\n';

    std::cout << std::boolalpha << streamer->addData({1, 2, 3, 4, 5, 6, 7}) << '\n';

}