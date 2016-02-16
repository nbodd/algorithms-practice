//
//  concurrency_consumer_producer.cpp
//  algorithms
//
//  Created by Nick on 2/16/16.
//  Copyright © 2016 Nick. All rights reserved.
//

#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>
#include <condition_variable>
#include <memory>

using namespace std;

class ThreadSafeBuffer {
private:
    static const int MAX_SIZE = 15;
    
    char buffer[MAX_SIZE];
    int capacity;
    int count;
    int front;
    int rear;
    
    mutex bufferMutex;
    condition_variable not_full;
    condition_variable not_empty;
    
public:
    
    ThreadSafeBuffer()
        : capacity(MAX_SIZE)
        , count(0)
        , front(0)
        , rear(0)
    { }
    
    void produce(char byte) {
        unique_lock<mutex> lock(bufferMutex);
        
        not_full.wait(lock, [this](){ return (count != capacity); });
        
        buffer[rear] = byte;
        count++;
        
        
        cout << "Inserting " << byte << " at " << rear << endl;
        rear = (rear + 1) % capacity;
        
        not_empty.notify_one();
    }
    
    char consume() {
        unique_lock<mutex> lock(bufferMutex);
        
        not_empty.wait(lock, [this](){ return (count != 0); });
        
        char ch = buffer[front];
        count--;
        
        cout << "Returning " << ch << " from " << front << endl;
        front = (front + 1) % capacity;
        
        not_full.notify_one();
        return ch;
        
    }
};

static recursive_mutex printMutex;

void consumer(int id, ThreadSafeBuffer& buffer){
    for(int i = 0; i < 50; ++i){
        int value = buffer.consume();
        unique_lock<recursive_mutex> l(printMutex);
        //std::cout << "Consumer " << id << " fetched " << value << std::endl;
        l.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
}

void producer(int id, ThreadSafeBuffer& buffer){
    for(int i = 0; i < 75; ++i){
        buffer.produce((char) i);
        unique_lock<recursive_mutex> l(printMutex);
        //std::cout << "Produced " << id << " produced " << i << std::endl;
        l.unlock();
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int consumer_producer_main(){
    ThreadSafeBuffer buffer;
    
    std::thread c1(consumer, 0, std::ref(buffer));
    std::thread c2(consumer, 1, std::ref(buffer));
    std::thread c3(consumer, 2, std::ref(buffer));
    std::thread p1(producer, 3, std::ref(buffer));
    std::thread p2(producer, 4, std::ref(buffer));
    
    c1.join();
    c2.join();
    c3.join();
    p1.join();
    p2.join();
    
    return 0;
}

class Philosopher {
private:
    shared_ptr<mutex> left;
    shared_ptr<mutex> right;
    int id;
    
    static mutex printMutex;
    
public:
    
    Philosopher(shared_ptr<mutex> & _left, shared_ptr<mutex> & _right, int _id)
    : left(_left)
    , right(_right)
    , id(_id)
    { }
    
    void dine() {
        chrono::milliseconds timeout(120);
        
        //start dining
        for (int i=0; i<25; ++i) {
            {
                lock_guard<mutex> l(*left);
                lock_guard<mutex> r(*right);
                lock_guard<mutex> p(printMutex);
                cout << "Philosopher " << id << " eating now.. " << i+1 << " time " << endl;
            }
            this_thread::sleep_for(timeout);
        }
    }
};

mutex Philosopher::printMutex;

int philosopher_main() {
    shared_ptr<mutex> forks[] = {   make_shared<mutex>(),
                                    make_shared<mutex>(),
                                    make_shared<mutex>(),
                                    make_shared<mutex>(),
                                    make_shared<mutex>()
                                };

    shared_ptr<Philosopher> philosophers[5];
    for (int i=0; i<5; ++i) {
        if (i % 2 == 0) {
            philosophers[i] = make_shared<Philosopher>(forks[i], forks[(i+1) % 5], i+1);
        } else {
            philosophers[i] = make_shared<Philosopher>(forks[(i+1) % 5], forks[i], i+1);
        }
    }
    
    shared_ptr<thread> th[5];
    for (int i=0; i<5; ++i) {
        th[i] = make_shared<thread>(bind(&Philosopher::dine, philosophers[i]));
    }
    
    for (int i=0; i<5; ++i) {
        th[i]->join();
    }
    
    return 0;
    
}