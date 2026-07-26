#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

// 共享资源
int shared_data = 0;

// 互斥锁
pthread_mutex_t mutex;
// 条件变量
pthread_cond_t cond;

// 生产者线程
void *producer(void *arg) {
    for (int i = 0; i < 5; i++) {
        // 获取互斥锁
        pthread_mutex_lock(&mutex);
        // 更新共享资源
        shared_data++;
        printf("Producer: shared_data = %d\n", shared_data);
        // 通知消费者
        pthread_cond_signal(&cond);
        // 释放互斥锁
        pthread_mutex_unlock(&mutex);
        // 模拟一些工作
        sleep(3);
    }
    pthread_exit(NULL);
}

// 消费者线程
void *consumer(void *arg) {
    for (int i = 0; i < 5; i++) {
        // 获取互斥锁
        pthread_mutex_lock(&mutex);
        // 等待条件满足
        while (shared_data == 0) {
            pthread_cond_wait(&cond, &mutex);
        }
        // 更新共享资源
        shared_data--;
        printf("Consumer: shared_data = %d\n", shared_data);
        // 释放互斥锁
        pthread_mutex_unlock(&mutex);
        // 模拟一些工作
        sleep(1);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;

    // 初始化互斥锁
    if (pthread_mutex_init(&mutex, NULL) != 0) {
        printf("pthread_mutex_init fail");
        return 1;;
    }
    // 初始化条件变量
    if (pthread_cond_init(&cond, NULL) != 0) {
        printf("pthread_cond_init fail");
        return 1;;
    }

    // 创建生产者和消费者线程
    if (pthread_create(&producer_thread, NULL, producer, NULL) != 0) {
        printf("pthread_create fail");
        return 1;;
    }
    if (pthread_create(&consumer_thread, NULL, consumer, NULL) != 0) {
        printf("pthread_create fail");
        return 1;;
    }

    // 等待线程结束
    if (pthread_join(producer_thread, NULL) != 0) {
        printf("pthread_join fail");
        return 1;;
    }
    if (pthread_join(consumer_thread, NULL) != 0) {
        printf("pthread_join fail");
        return 1;;
    }

    // 销毁互斥锁和条件变量
    if (pthread_mutex_destroy(&mutex) != 0) {
        printf("pthread_mutex_destroy fail");
        return 1;;
    }
    if (pthread_cond_destroy(&cond) != 0) {
        printf("pthread_cond_destroy fail");
        return 1;;
    }

    return 0;
}