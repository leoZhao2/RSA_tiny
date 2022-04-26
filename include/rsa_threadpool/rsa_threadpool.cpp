#include"rsa_threadpool.h"

// std::random_device rd;
// std::mt19937 mt(rd());
// std::uniform_int_distribution<int>dist(-1000, 1000);
// auto rnd = std::bind(dist, mt);

int rsa_threadpool(int plain_data){
    //create threadpool
    ThreadPool pool(3);
    //init
    pool.init();
    int key_len = 16;
    mpz_t e,n,d;
    mpz_init(e);
    mpz_init(n);
    mpz_init(d);

    mpz_t msg_plain,msg_encrypt;
    mpz_t msg_decrypt;
    mpz_init_set_ui(msg_plain,plain_data);
    mpz_init(msg_encrypt);
    mpz_init(msg_decrypt);


    auto future = pool.submit(rsa_create,std::ref(e),std::ref(n),std::ref(d),key_len);
    future.get();
    gmp_printf("e: %Zd\n",e);
    gmp_printf("n: %Zd\n",n);
    gmp_printf("d: %Zd\n",d);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    auto future1 = pool.submit(encrypt,std::ref(msg_encrypt),std::ref(msg_plain),std::ref(e),std::ref(n));
    future1.get();
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    auto future2 = pool.submit(decrypt,std::ref(msg_decrypt),std::ref(msg_encrypt),std::ref(d),std::ref(n));
    future2.get();
    gmp_printf("decrypt: %Zd\n",msg_decrypt);

    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    pool.shutdown();

    int result = 0;
    mpz_export(&result, 0, -1, sizeof result, 0, 0, msg_decrypt);
    return result;
}

