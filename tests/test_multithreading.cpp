//
//  test_multithreading.cpp
//  blocking_queue
//
//  Created by Dmitrii Torkhov <dmitriitorkhov@gmail.com> on 29.08.2021.
//  Copyright © 2021 Dmitrii Torkhov. All rights reserved.
//

#include <chrono>
#include <numeric>
#include <random>
#include <thread>

#include <blocking_queue/blocking_queue.h>

namespace {

    const auto c_data_len = 1000;
    const auto c_producers_count = 100;

}

int main() {
    std::vector<int> data(c_data_len);

    std::random_device rd;
    std::default_random_engine engine(rd());
    std::generate(data.begin(), data.end(), std::ref(engine));

    //

    oo::blocking_queue<int> queue;

    //

    const auto producer_fn = [&]() {
        for (size_t i = 0; i < c_data_len; ++i) {
            const auto value = data[i];
            queue.push(value);

            if (i % 10 == 0) {
                using namespace std::chrono_literals;
                std::this_thread::sleep_for(5ms);
            }
        }
    };

    std::vector<std::shared_ptr<std::thread>> producers;
    for (size_t i = 0; i < c_producers_count; ++i) {
        producers.push_back(std::make_shared<std::thread>(producer_fn));
    }

    //

    std::vector<int> result;

    const auto consumer_fn = [&]() {
        while (!queue.is_done()) {
            const auto i = queue.pop();
            result.push_back(i);
        }
    };

    std::thread consumer{consumer_fn};

    //

    for (const auto &producer: producers) {
        producer->join();
    }

    queue.set_done();

    //

    consumer.join();

    //

    const auto data_sum = std::accumulate(data.begin(), data.end(), 0LL);
    const auto result_sum = std::accumulate(result.begin(), result.end(), 0LL);

    //

    return result_sum == data_sum * c_producers_count ? 0 : 1;
}