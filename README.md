# RSA_tiny
一个简单的RSA demo，利用线程池实现加解密任务提交，支持自定义密钥长度，利用gmp实现大数计算；   
RSA中采用了快速幂算法、扩展欧几里得算法；

## 环境要求
* **Linux 环境** >=Ubuntu18.04
* **Required packages for RSA_tiny:**
  * [`g++`](https://packages.debian.org/testing/g++) 
  * [`make`](https://packages.debian.org/testing/make)
  * [`cmake`](https://packages.debian.org/testing/cmake)
  * [`libgmp-dev`](https://packages.debian.org/testing/libgmp-dev)
  * [`libboost-all-dev`](https://packages.debian.org/testing/libboost-all-dev) (version >= 1.66)

  安装以上软件包, `sudo apt-get install <package-name>`.   

  ## 执行
  ```bash
  git clone https://github.com/leoZhao2/RSA_tiny.git
  cd RSA_tiny && mkdir build
  cd build && cmake ..
  make
  ```
