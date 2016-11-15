
#include <unistd.h>
#include <pthread.h>	// pthread_create
#include <iostream>
#include <string.h>	// strerror
using namespace std;

void* run(void*);	// 线程函数
void* thread1_run(void* arg);
void* thread2_run(void* arg);
void printids(char const* s);

// 互斥变量
pthread_mutex_t mqlock = PTHREAD_MUTEX_INITIALIZER;
// 条件变量
pthread_cond_t mqlock_ready = PTHREAD_COND_INITIALIZER;
// 共享资源
int g_share_res = 0;
bool g_stop = false;

int main(){
	
	pthread_t ntid1, ntid2;	// 线程标识
	int err = pthread_create(&ntid1, nullptr, thread1_run, nullptr);	// 创建线程
	if (err)
	{
		cerr << "Can't create thread thread1_run:" << strerror(err) << "!" << endl;
		return 1;
	}
	err = pthread_create(&ntid2, nullptr, thread2_run, nullptr);	// 创建线程
	if (err)
	{
		cerr << "Can't create thread thread2_run:" << strerror(err) << "!" << endl;
		return 1;
	}
	printids("main thread: ");
//	err = pthread_cancel(ntid);
	void* exit_code = nullptr;
	err = pthread_join(ntid1, &exit_code);
	err = pthread_join(ntid2, &exit_code);
	return 0;
}

void* run(void*)
{
	printids("new thread: ");
	cout << "线程退出" << endl;
	return (void*)8;
}

void printids(char const* s)
{
	pid_t pid = getpid();
	pthread_t tid = pthread_self();
	cout << s << " pid " << pid << " tid " << tid<< endl;
}

void* thread1_run(void* arg)
{
	int i = 0;
	while (i < 100)
	{
		pthread_mutex_lock(&mqlock);
//		list_add_tail(pkt, &pkt_queue);
		g_share_res = ++i;
		pthread_mutex_unlock(&mqlock);
		// 通知线程2条件发生变化
		pthread_cond_signal(&mqlock_ready);
		sleep(5);
	}
	g_stop = true;
	return nullptr;
}

void* thread2_run(void* arg)
{
	while (!g_stop)
	{
		pthread_mutex_lock(&mqlock);
//		while (list_empty(&pkt_queue))
		{
			// 若队列为空，则休眠等待条件改变
			pthread_cond_wait(&mqlock_ready, &mqlock);	// 休眠等待线程1来唤醒
			// 此处函数返回，会自动加锁mqlock
		}
//		pkt = getnextpkt(&pkt_queue);
		pthread_mutex_unlock(&mqlock);
//		handle_packet(pkt);	// 处理此分组
		cout << "g_share_res=" << g_share_res << endl;
	}
	return nullptr;
}
