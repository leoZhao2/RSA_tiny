#pragma once
#include <gmp.h>
#include <ctime>


void getEulerValue(mpz_t &p, mpz_t &q, mpz_t &euler);

void createPrimePQ(mpz_t &rand_p, mpz_t &rand_q, const int MAX_BITS);

void createPrimeE(mpz_t &e, mpz_t euler);

void encrypt(mpz_t &ciphertext, mpz_t &plaintext, mpz_t &e, mpz_t &n);

void decrypt(mpz_t &plaintext, mpz_t &ciphertext, mpz_t &d, mpz_t &n);

void get_d(mpz_t &e, mpz_t &euler, mpz_t &tmp, mpz_t &a, mpz_t &b);

void rsa_test(int KEY_LEN);

void rsa_create(mpz_t &r_e,mpz_t &r_n,mpz_t &r_d,int KEY_LEN);