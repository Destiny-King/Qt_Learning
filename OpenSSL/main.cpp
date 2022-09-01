#include <iostream>
#include <openssl/rand.h>
#include <thread>
#include <time.h>

using namespace std;

int main() {
  for (;;) {
    //用时间做随机数种子
    time_t t = time(0);
    RAND_seed(&t, sizeof(t));

    //生成随机数
    unsigned char buf[10] = {0};
    int len = sizeof(buf);
    int re = RAND_bytes(buf, len);
    for (int i = 0; i < len; ++i) {
      cout << "[" << (int)buf[i] << "]";
    }
    cout << endl;
    this_thread::sleep_for(1000ms);
  }

  return 0;
}